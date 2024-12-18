import raylib
from numpy import unsignedinteger
from raylib import colors


class Colore:

    def __init__(self, normale, rgb_attivo):
        self.__normale = normale
        self.__rgb = self.__normale
        self.__rgb_attivo = rgb_attivo
        self.__velocita = 5

    def get_rgb(self):
        return self.__rgb

    def cambia_stato_rgb(self):
        self.__rgb_attivo = not self.__rgb_attivo

    def aggiorna_rgb(self):
        print("aggiorno rgb")
        if not self.__rgb_attivo:
            self.__velocita = -self.__velocita
        if 0 < self.__rgb[0] < 255:
            self.__rgb[0] += self.__velocita
        elif 0 < self.__rgb[1] < 255:
            self.__rgb[1] += self.__velocita
        elif 0 < self.__rgb[2] < 255:
            self.__rgb[2] += self.__velocita
        else:
            self.__rgb_attivo = not self.__rgb_attivo

    def get_colore(self):
        if self.__rgb_attivo:
            return tuple(self.__normale)
        else:
            return tuple(self.__rgb)
