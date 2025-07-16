
from raylib import *
import cv2
# import mediapipe as mp
from mediapipe.tasks import python
from mediapipe.tasks.python import vision
import Barretta
import Pallina
import Giocatore
import Gioco
from Colore import Colore
from Funzioni_Varie import scrivi_messaggio


def carica_modello():
    base_options = python.BaseOptions(model_asset_path='file/gesture_recognizer.task')
    options = vision.GestureRecognizerOptions(base_options=base_options)
    recognizer = vision.GestureRecognizer.create_from_options(options)
    return recognizer

colore = Colore()

pallina = Pallina.Pallina(10, 15, LoadSound("assets/rimbalzo.wav".encode('utf-8')))
InitAudioDevice()

LARGHEZZA_BARRETTA = 20
ALTEZZA_BARRETTA = 200

rimbalzo = LoadSound("assets/rimbalzo.wav".encode('utf-8'))
punto = LoadSound("assets/punto.mp3".encode('utf-8'))

barretta1 = Barretta.Barretta(LARGHEZZA_BARRETTA, 200, LARGHEZZA_BARRETTA, ALTEZZA_BARRETTA, 10)
barretta2 = Barretta.Barretta(1920 - LARGHEZZA_BARRETTA - 20, 200, LARGHEZZA_BARRETTA, ALTEZZA_BARRETTA, 10)

g1 = Giocatore.Giocatore(barretta1, "G1")
g2 = Giocatore.Giocatore(barretta2, "G2")

gioco = Gioco.Gioco(g1, g2, pallina, colore, carica_modello())

PUNTI_FINALI = 5

SetTargetFPS(60)
InitWindow(0, 0, b"The Son of Pong")
ToggleFullscreen()

gioco.carica_musica()

chi = -1

cam = cv2.VideoCapture(0)

while not WindowShouldClose():

    gioco.riproduci_musica()
    stato = gioco.get_stato()

    match stato:
        case 0:  # si deve ancora selezionare la partita
            scrivi_messaggio('Apri la mano per iniziare la partita', gioco.get_colore(), FONT_SIZE=50)
            gesto = gioco.get_gesto()
            if IsKeyPressed(KEY_G):
                gioco.forza_rgb()
            if gesto == "Open_Palm" or IsKeyPressed(KEY_SPACE):
                gioco.reset_pallina()
                gioco.set_stato(1)

        case 1:  # si sta giocando la partita
            gioco.aggiorna()
            if IsKeyPressed(KEY_P):
                gioco.cambia_valore_pausa()
            if gioco.controlla_pallina() != -1:
                gioco.set_stato(3)
                PlaySound(punto)

        case 2:  # pausa dal giocatore
            scrivi_messaggio("Il gioco e' in pausa", gioco.get_colore())
            if IsKeyPressed(KEY_P):
                gioco.cambia_valore_pausa()

        case 3:  # pausa da uno che fa punto
            chi = (gioco.controlla_pallina())

            if gioco.qualcuno_sta_per_vincere(chi, PUNTI_FINALI) == -1:
                scrivi_messaggio("\t\t\tPunto del Giocatore " + str(chi + 1) + '!\n\tApri la mano per continuare',
                                 colore, FONT_SIZE=50)
                gesto = gioco.get_gesto()
                if gesto == "Open_Palm" or IsKeyPressed(KEY_SPACE):
                    gioco.set_stato(1)
                    gioco.reset_pallina()
                    gioco.aggiungi_punto(chi)
            else:
                gioco.set_stato(4)

        case 4:  # vittoria di uno dei due giocatori
            scrivi_messaggio("VITTORIA DEL GI0CATORE " + str(chi + 1) + '!\n\tChiudi il pugno per Resettare', colore,
                             FONT_SIZE=50)
            gioco.reset_pallina()
            gesto = gioco.get_gesto()
            if IsKeyPressed(KEY_R) or gesto == "Closed_Fist":
                gioco.reset()

    BeginDrawing()
    if stato == 1 or stato == 2:
        gioco.disegna()
    DrawFPS(0, 0)
    ClearBackground(gioco.get_colore_invertito())

    EndDrawing()
    CloseAudioDevice()

CloseWindow()
