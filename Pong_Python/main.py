from pyray import *
from raylib import LoadSound, KEY_W, KEY_S, KEY_UP, KEY_DOWN

import Ball
import Colore
import Barretta
import Giocatore
import Gioco

init_audio_device()
rgb = Color(255,255,255)
colore = Colore.Colore( BLUE, rgb, rgb, True)
pallina = Ball.Ball(1000,500,10, 7,-3,3, RED, LoadSound('assets/rimbalzo.wav'.encode('utf-8')))

g1 = Giocatore.Giocatore()

barretta1 = Barretta.Barretta(20,200, 15, 200, 10, BLACK)
barretta2 = Barretta.Barretta(1700,200, 15, 200, 10, BLACK)

pallina.reset_vy()
pallina.reset_vx()

set_target_fps(60)
init_window(0, 0, "test")
toggle_fullscreen()
while not window_should_close():

    pallina.aggiorna_y(get_screen_height())
    pallina.aggiorna_x(barretta1, barretta2)

    barretta1.aggiorna_y(get_screen_height(), KEY_W, KEY_S)
    barretta2.aggiorna_y(get_screen_height(), KEY_UP, KEY_DOWN)

    begin_drawing()
    clear_background(WHITE)
    pallina.disegna()
    barretta1.disegna()
    barretta2.disegna()

    end_drawing()

close_audio_device()
close_window()
