from pyray import *
from Funzioni_Varie import scrivi_messaggio
import cv2 as cv
import mediapipe.python.solutions.hands as mp_hands
from Mano import *
from Colore import Colore

N_MIN_FRAME_CONSECUTIVI = 12

class Gioco:
    def __init__(self, g1, g2, pallina, colore, modello):
        self.__indici = []
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
        self.__hands = mp_hands.Hands(
            static_image_mode=False,
            max_num_hands=2,
            min_detection_confidence=0.6
        )
        self.__frame = None
        self.__frame_count = 0
        self.__v_barretta_1 = 0
        self.__v_barretta_2 = 0
        self.__salta_frame = 3
        self.__cam_h = 720
        self.__cam_w = 1280
        self.__cam = self.carica_camera()
        self.aggiorna_frame()
        self.__mano = Mano(modello)
        self.__conta_frame_consecutivi = 0
        self.__colore = colore

    def carica_camera(self, n_cam=0):
        cam = cv.VideoCapture(n_cam)
        cam.set(cv.CAP_PROP_FRAME_WIDTH, self.__cam_w)
        cam.set(cv.CAP_PROP_FRAME_HEIGHT, self.__cam_h)
        return cam

    def aggiorna_frame(self):
        success, frame = self.__cam.read()
        self.__frame = cv.flip(frame, 1)

        if not success:
            print("Frame della videocamera non disponibile")
            return

        self.__frame = cv.cvtColor(frame, cv.COLOR_BGR2RGB)

    def aggiorna_giocatori(self):
        self.__indici = []
        self.aggiorna_frame()

        hands_detected = self.__hands.process(self.__frame)

        if hands_detected.multi_hand_landmarks:

            altezza1 = self.__giocatori[0].get_barretta().get_h()
            altezza2 = self.__giocatori[1].get_barretta().get_h()

            for hand_landmarks in hands_detected.multi_hand_landmarks:
                fingertip = hand_landmarks.landmark[8]
                self.__indici.append((fingertip.x + 2 * (0.5 - fingertip.x), fingertip.y))

            self.__indici.sort()

            if (len(self.__indici) > 0 and 0 < self.__indici[0][1] * get_screen_height() - altezza1 / 2 and
                    self.__indici[0][1] * get_screen_height() + altezza1 / 2 < get_screen_height()):
                self.__v_barretta_1 = int((self.__indici[0][1] * get_screen_height() - altezza1 / 2 - self.__giocatori[
                    0].get_barretta().get_y()) / self.__salta_frame)

            if (len(self.__indici) > 1 and 0 < self.__indici[1][1] * get_screen_height() - altezza2 / 2 and
                    self.__indici[1][1] * get_screen_height() + altezza2 / 2 < get_screen_height()):
                self.__v_barretta_2 = int((self.__indici[1][1] * get_screen_height() - altezza1 / 2 - self.__giocatori[
                    1].get_barretta().get_y()) / self.__salta_frame)

    def aggiungi_punto(self, indice):
        self.__giocatori[indice].aggiungi_punto()

    def aggiorna(self):
        if self.__frame_count == self.__salta_frame:
            self.__v_barretta_1 = self.__v_barretta_2 = 0
            self.aggiorna_giocatori()
            self.__frame_count = 0

        self.__giocatori[0].aggiorna_barretta(self.__v_barretta_1)
        self.__giocatori[1].aggiorna_barretta(self.__v_barretta_2)

        barretta1 = self.__giocatori[0].get_barretta()
        barretta2 = self.__giocatori[1].get_barretta()

        self.__pallina.aggiorna_y(get_screen_height())
        self.__pallina.aggiorna_x(barretta1, barretta2)

        self.__frame_count += 1

    def attiva_rgb(self):
        if self.__frame_count > self.__salta_frame:
            if self.__mano.get_gesto(self.__frame) == "Victory":
                self.__conta_frame_consecutivi += 1
                if self.__conta_frame_consecutivi == N_MIN_FRAME_CONSECUTIVI:
                    self.__conta_frame_consecutivi = 0
                    self.__colore.cambia_stato_rgb()
                self.__conta_frame_consecutivi = 0

    def cambia_valore_pausa(self):
        if self.__stato == 1:
            self.__stato = 2
            return
        if self.__stato == 2:
            self.__stato = 1
            return

    def get_gesto(self):
        self.aggiorna_frame()
        ritorno = self.__mano.get_gesto(self.__frame)
        if ritorno == "Victory":
            self.attiva_rgb()
        else :
            return ritorno

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
            scrivi_messaggio("IL GIOCATORE 1 HA VINTO", self.__colore)

        elif self.__giocatori[1].get_punteggio() == punteggio_fine_partita:
            scrivi_messaggio("IL GIOCATORE 2 HA VINTO", self.__colore)

    def disegna(self):
        self.__colore.aggiorna_rgb()
        n_x, n_y = (get_screen_width() - self.__cam_w) // 2, (get_screen_height() - self.__cam_h) // 2
        # Disegna il contorno del frame
        draw_rectangle_lines(n_x, n_y, int(self.__cam_w), int(self.__cam_h), self.__colore.get_colore())
        # Disegna i punti delle dita
        if len(self.__indici) > 0:
            draw_circle(int(self.__indici[0][0] * self.__cam_w + n_x), int(self.__indici[0][1] * self.__cam_h + n_y), 20, RED)
        if len(self.__indici) > 1:
            draw_circle(int(self.__indici[1][0] * self.__cam_w + n_x), int(self.__indici[1][1] * self.__cam_h + n_y), 20, RED)
        for i in range(0, get_screen_height(), 80):
            l = 6
            draw_rectangle(int((get_screen_width() - l) / 2), i, l, 40, self.__colore.get_colore())
        self.__pallina.disegna(self.__colore)
        self.__giocatori[0].disegna(get_screen_width() * 0.25, 50, self.__colore.get_colore())
        self.__giocatori[1].disegna(get_screen_width() * 0.75, 50, self.__colore.get_colore())

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

    def get_frame_count(self):
        return self.__frame_count
