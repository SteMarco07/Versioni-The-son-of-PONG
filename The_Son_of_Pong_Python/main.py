from pyray import *
from raylib import *

#from TheSonofPong import *
import Barretta
import Pallina
import Giocatore
import Gioco
import Colore
import Messaggio


init_audio_device()

pallina = Pallina.Pallina(0,0, 10, 7, -3, 3, WHITE, LoadSound('assets/rimbalzo.wav'.encode('utf-8')))

LARGHEZZA_BARRETTA = 20
ALTEZZA_BARRETTA = 200

barretta1 = Barretta.Barretta(LARGHEZZA_BARRETTA,200, LARGHEZZA_BARRETTA, ALTEZZA_BARRETTA, 10, WHITE)
barretta2 = Barretta.Barretta(1920 - LARGHEZZA_BARRETTA - 20,200, LARGHEZZA_BARRETTA, ALTEZZA_BARRETTA, 10, WHITE)

g1 = Giocatore.Giocatore(barretta1,"G1")
g2 = Giocatore.Giocatore(barretta2,"G2")

gioco = Gioco.Gioco(g1,g2,pallina)

inizia_gioco = False

set_target_fps(60)
init_window(0, 0, "test")
toggle_fullscreen()

while not window_should_close():

    if not inizia_gioco:
        gioco.pallina_off_screen()
        Messaggio.scrivi_messaggio("Premi SPAZIO per iniziare", 40)
        if is_key_pressed(KEY_SPACE):
            inizia_gioco = True
            gioco.reset_pallina()
    else:

        if gioco.controlla_pallina() == -1:
            gioco.disegna()
            if is_key_pressed(KEY_P):
                gioco.alterna_stato_pausa()

            if not gioco.get_stato_pausa():
                gioco.aggiorna()
                gioco.controlla_pallina()
                if is_key_pressed(KEY_R):
                    gioco.reset_pallina()

            else:
                gioco.disegna_pausa()
        else:
            if not gioco.controlla_fine_partita(1):
                gioco.pallina_off_screen()
                chi_ha_fatto_punto = gioco.controlla_pallina()
                if is_key_pressed(KEY_SPACE):
                    gioco.aggiungi_punto(chi_ha_fatto_punto)
                    gioco.reset_pallina()
                    gioco.play()
            else:
                clear_background(BLACK)
                gioco.disegna_pausa()


    begin_drawing()
    clear_background(BLACK)
    end_drawing()

close_audio_device()
close_window()