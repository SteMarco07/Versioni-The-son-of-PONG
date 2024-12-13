from pyray import *
from Funzioni_Varie import scrivi_messaggio
import cv2 as cv
import mediapipe.python.solutions.hands as mp_hands


class Gioco:
    def __init__(self, g1, g2, pallina):
        self.__fatto_una_volta = None
        self.__musiche = None
        self.__giocatori = [g1, g2]
        self.__pallina = pallina
        self.__stato = 0
        # 0) inizio partita
        # 1) nel corso dell partita
        # 2) pausa come interruzione del giocatore
        # 3) pausa dovuta a un giocatore che segna un punto
        # 4) vittoria
        # 5) menu vari che aggiungeremo [prima o poi]
        self.__cam = self.carica_camera()
        self.__hands = mp_hands.Hands(
            static_image_mode=False,
            max_num_hands=2,
            min_detection_confidence=0.6
        )
        self.__frame = None
        self.__frame_count = 0

    def carica_camera(self, n_cam=0):
        cam = cv.VideoCapture(n_cam)
        width, height = 1280, 720
        cam.set(cv.CAP_PROP_FRAME_WIDTH, width)
        cam.set(cv.CAP_PROP_FRAME_HEIGHT, height)
        return cam

    def aggiorna_frame(self):
        success, frame = self.__cam.read()
        self.__frame = cv.flip(frame, 1)

        if not success:
            print("Frame della videocamera non disponibile")
            return

        self.__frame = cv.cvtColor(frame, cv.COLOR_BGR2RGB)

    def aggiorna_giocatori(self):

        self.aggiorna_frame()

        hands_detected = self.__hands.process(self.__frame)

        if hands_detected.multi_hand_landmarks:

            altezza1 = self.__giocatori[0].get_barretta().get_h()
            altezza2 = self.__giocatori[1].get_barretta().get_h()

            indici = []

            for hand_landmarks in hands_detected.multi_hand_landmarks:
                fingertip = hand_landmarks.landmark[8]
                # h, w, _ = self.__frame.shape
                # cx, cy = int(fingertip.x * w), int(fingertip.y * h)
                # cv.circle(self.__frame, (cx, cy), 10, (0, 255, 0), -1)
                indici.append((fingertip.x, fingertip.y))

            indici.sort(key=lambda pos: pos[0], reverse=True)

            if len(indici) > 0 and 0 < indici[0][1] * get_screen_height() - altezza1 / 2 and indici[0][
                1] * get_screen_height() + altezza1 / 2 < get_screen_height():
                self.__giocatori[0].get_barretta().set_y(int(indici[0][1] * get_screen_height() - altezza1 / 2))

            if len(indici) > 1 and 0 < indici[1][1] * get_screen_height() - altezza2 / 2 and indici[1][
                1] * get_screen_height() + altezza2 / 2 < get_screen_height():
                self.__giocatori[1].get_barretta().set_y(int(indici[1][1] * get_screen_height() - altezza2 / 2))

    def aggiungi_punto(self, indice):
        self.__giocatori[indice].aggiungi_punto()

    def aggiorna(self):
        if self.__frame_count == 3:
            self.aggiorna_giocatori()
            self.__frame_count = 0

        barretta1 = self.__giocatori[0].get_barretta()
        barretta2 = self.__giocatori[1].get_barretta()

        self.__pallina.aggiorna_y(get_screen_height())
        self.__pallina.aggiorna_x(barretta1, barretta2)

        self.__frame_count += 1

    def reset_pallina(self):
        self.__pallina.reset()

    def controlla_pallina(self):
        return self.__pallina.assegna_punto()

    def pallina_off_screen(self):
        self.__pallina.set_x(-1000)
        self.__pallina.set_y(-1000)

    def get_stato(self):
        return self.__stato

    def reset(self):
        self.__pallina.reset()
        self.__giocatori[0].reset()
        self.__giocatori[1].reset()
        self.__stato = 0

    def set_stato(self, stato):
        self.__stato = stato
        if stato == 1:
            self.riprendi("partita")
        elif stato == 2 or stato == 3:
            self.metti_in_pausa("partita")

    def disegna_fine_partita(self, punteggio_fine_partita):
        if self.__giocatori[0].get_punteggio() == punteggio_fine_partita:
            scrivi_messaggio("IL GIOCATORE 1 HA VINTO", 40)

        elif self.__giocatori[1].get_punteggio() == punteggio_fine_partita:
            scrivi_messaggio("IL GIOCATORE 2 HA VINTO", 40)

    def disegna(self):
        for i in range(0, get_screen_height(), 80):
            l = 6
            draw_rectangle(int((get_screen_width() - l) / 2), i, l, 40, WHITE)

        self.__pallina.disegna()
        self.__giocatori[0].disegna(get_screen_width() * 0.25, 50)
        self.__giocatori[1].disegna(get_screen_width() * 0.75, 50)

    def carica_musica(self):
        self.__musiche = {
            "chill": load_sound('assets/chill.mp3'),
            "partita": load_sound('assets/partita.mp3'),
            "vittoria": load_sound('assets/vittoria.mp3'),
            "punto": load_sound('assets/punto.mp3')

        }

    def __gestisci_musiche(self, target):
        for key, OST in self.__musiche.items():
            if is_sound_playing(OST) and key != target:
                stop_sound(OST)
        if not is_sound_playing(self.__musiche[target]):
            play_sound(self.__musiche[target])

    def qualcuno_sta_per_vincere(self, chi, PUNTI_FINALI):
        if self.__giocatori[chi].sta_per_vincere(PUNTI_FINALI):
            return chi
        else:
            return -1

    def riproduci_musica(self):
        if self.__stato != 2 and self.__stato != 3:
            if self.__stato == 0:
                target = "chill"
            elif self.__stato == 1:
                target = "partita"
                self.__fatto_una_volta = False
            else:
                target = "vittoria"
            self.__gestisci_musiche(target)

    def metti_in_pausa(self, key):
        pause_sound(self.__musiche[key])

    def riprendi(self, key):
        resume_sound(self.__musiche[key])
