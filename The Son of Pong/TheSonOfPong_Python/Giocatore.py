from pyray import *

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

