from pyray import *
from raylib import *
from raylib.defines import KEY_DOWN


class Giocatore:

    def __init__(self, barretta, punteggio, nome):
        self.__barretta = barretta
        self.__punteggio = punteggio
        self.__nome = nome

    def aggiungi_punto(self):
        self.__punteggio += 1

    def disegna_punteggio(self, screen_width):
        draw_text(str(self.__punteggio), screen_width/5,20, 30,BLACK)

    def get_punteggio(self):
        return self.__punteggio

    def aggiorna_barretta(self, n_giocatore):
        if n_giocatore == 1:
            self.__barretta.aggiorna_y(get_screen_height(), KEY_W, KEY_S)
        elif n_giocatore == 2:
            self.__barretta.aggiorna_y(get_screen_height(), KEY_UP, KEY_DOWN)

    def get_barretta(self):
        return self.__barretta