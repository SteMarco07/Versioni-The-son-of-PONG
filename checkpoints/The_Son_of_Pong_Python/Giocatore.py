from raylib import *
from pyray import *


class Giocatore:

    def __init__(self, barretta, nome):
        self.__barretta = barretta
        self.__punteggio = 0
        self.__nome = nome

    def reset(self):
        self.__barretta.set_y((get_screen_height() - self.__barretta.get_h()) / 2)
        self.__punteggio = 0

    def aggiungi_punto(self):
        self.__punteggio += 1

    def sta_per_vincere(self, PUNTI_FINALI):
        return self.__punteggio == PUNTI_FINALI - 1

    def disegna_punteggio(self, screen_width):
        draw_text(str(self.__punteggio), screen_width / 5, 20, 30, BLACK)

    def get_punteggio(self):
        return self.__punteggio

    def aggiorna_barretta(self, v):
        self.__barretta.set_y(self.__barretta.get_y() + v)
        y = self.__barretta.get_y()
        if y < 0:
            self.__barretta.set_y(0)
        elif y + self.__barretta.get_h() > get_screen_height():
            self.__barretta.set_y(get_screen_height() - self.__barretta.get_h())

    def get_barretta(self):
        return self.__barretta

    def disegna(self, x, y, colore):
        x = int(x)
        y = int(y)
        self.__barretta.disegna(colore)
        draw_text(str(self.__punteggio), int(x), int(y), 30, colore.get_colore())
