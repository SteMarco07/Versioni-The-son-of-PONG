import raylib
from numpy import unsignedinteger
from raylib import colors
from raylibpy import WHITE


class Colore:

    def __init__(self, normale, rgb_attivo):
        self.__normale = normale
        self.__rgb = WHITE
        self.__rgb_attivo = rgb_attivo

    def get_rgb(self):
        return self.__rgb

    def cambia_stato_rgb(self):
        self.__rgb_attivo = not self.__rgb_attivo

    def aggiorna_rgb(self, velocita=5):
        if not self.__rgb_attivo:
            velocita = -velocita
        if 0 < self.__rgb.r < 250:
            self.__rgb.r += velocita
        elif 0 < self.__rgb.g < 250:
            self.__rgb.g += velocita
        elif 0 < self.__rgb.b < 250:
            self.__rgb.b += velocita
        else:
            self.__rgb_attivo = not self.__rgb_attivo

    def get_colore(self):
        if self.__rgb_attivo:
            return list(self.__normale)
        else:
            return list(self.__rgb)
