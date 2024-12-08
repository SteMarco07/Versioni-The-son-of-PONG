from pyray import *
from raylib import *

import Pallina
import Colore
import Barretta
import Giocatore
import Gioco

init_audio_device()
rgb = Color(255, 255, 255)
colore = Colore.Colore(BLUE, rgb, rgb, True)
pallina = Pallina.Pallina(1000, 500, 10, 7, -3, 3, RED, LoadSound('assets/rimbalzo.wav'.encode('utf-8')))

LUNGHEZZA_BARRETTA = 15
ALTEZZA_BARRETTA = 200

barretta1 = Barretta.Barretta(20,200, LUNGHEZZA_BARRETTA, ALTEZZA_BARRETTA, 10, BLACK)
barretta2 = Barretta.Barretta(1920 - LUNGHEZZA_BARRETTA - 20,200, LUNGHEZZA_BARRETTA, ALTEZZA_BARRETTA, 10, BLACK)

g1 = Giocatore.Giocatore(barretta1,0,"G1")
g2 = Giocatore.Giocatore(barretta2,0,"G2")

gioco = Gioco.Gioco(g1,g2,pallina)

pallina.reset_vy()
pallina.reset_vx()

set_target_fps(60)
init_window(0, 0, "test")
toggle_fullscreen()

while not window_should_close():

    if is_key_pressed(KEY_P):
        gioco.alterna_stato_pausa()

    if not gioco.get_stato_pausa():
        gioco.aggiorna()
        gioco.controlla_pallina()
        if is_key_pressed(KEY_R):
            gioco.reset_pallina()
    else:
        messaggio_pausa = "IL GIOCO E' IN PAUSA"
        pos_x = int((get_screen_width() - measure_text(messaggio_pausa,40))/2)
        pos_y = int((get_screen_height() - measure_text(messaggio_pausa,40))/2)
        draw_text(messaggio_pausa,pos_x,pos_y, 40,BLACK)

    begin_drawing()
    clear_background(WHITE)

    gioco.disegna()

    end_drawing()

close_audio_device()
close_window()