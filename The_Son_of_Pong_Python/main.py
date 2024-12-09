from pyray import *
from raylib import *

#from TheSonofPong import *
import Barretta
import Pallina
import Giocatore
import Gioco
import Colore

from Funzioni_Varie import scrivi_messaggio

init_audio_device()

pallina = Pallina.Pallina(0,0, 10, 7, -3, 3, WHITE, LoadSound('assets/rimbalzo.wav'.encode('utf-8')))

LARGHEZZA_BARRETTA = 20
ALTEZZA_BARRETTA = 200

rimbalzo = load_sound('assets/rimbalzo.wav'.encode('utf-8'))

barretta1 = Barretta.Barretta(LARGHEZZA_BARRETTA,200, LARGHEZZA_BARRETTA, ALTEZZA_BARRETTA, 10, WHITE)
barretta2 = Barretta.Barretta(1920 - LARGHEZZA_BARRETTA - 20,200, LARGHEZZA_BARRETTA, ALTEZZA_BARRETTA, 10, WHITE)

g1 = Giocatore.Giocatore(barretta1,"G1")
g2 = Giocatore.Giocatore(barretta2,"G2")

gioco = Gioco.Gioco(g1,g2,pallina)

PUNTI_FINALI = 3

set_target_fps(60)
init_window(0, 0, "test")
toggle_fullscreen()

gioco.carica_musica()

chi = -1

while not window_should_close():

    gioco.riproduci_musica()
    stato = gioco.get_stato()

    if is_key_pressed(KEY_H):
        play_sound(rimbalzo)

    if stato == 1 or stato == 2:
        gioco.disegna()

    match stato:
        case 0: #si deve ancora selezionare la partita
            scrivi_messaggio("Premere SPAZIO per iniziare la partita", 50)
            if is_key_pressed(KEY_SPACE):
                gioco.reset_pallina()
                gioco.set_stato(1)

        case 1: #si sta giocando la partita
            gioco.aggiorna()
            if is_key_pressed(KEY_P):
                gioco.set_stato(2)
            if gioco.controlla_pallina() != -1:
                gioco.set_stato(3)

        case 2: #pausa dal giocatore
            gioco.disegna_pausa()
            if is_key_pressed(KEY_P):
                gioco.set_stato(1)

        case 3: #pausa da uno che fa punto
            chi = (gioco.controlla_pallina())
            scrivi_messaggio("Punto del Giocatore " + str(chi + 1) + '!', 50)
            if gioco.get_punteggio_giocatore(0) + 1 < PUNTI_FINALI and gioco.get_punteggio_giocatore(1) + 1 < PUNTI_FINALI:
                if is_key_pressed(KEY_SPACE):
                    gioco.reset_pallina()
                    gioco.controlla_pallina()
                    gioco.aggiungi_punto(chi)
                    gioco.set_stato(1)
            else:
                chi = gioco.get_vincitore()
                gioco.set_stato(4)

        case 4: #vittoria di uno dei due giocatori
            scrivi_messaggio("VITTORIA DEL GI0CATORE " + str(chi + 1) + '!', 50)
            gioco.reset_pallina()


    begin_drawing()
    clear_background(BLACK)
    end_drawing()

close_audio_device()
close_window()