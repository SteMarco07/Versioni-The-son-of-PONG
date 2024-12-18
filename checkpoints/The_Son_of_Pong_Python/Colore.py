import raylib
from numpy import unsignedinteger
from raylib import colors



class Colore:

    def __init__(self, normale, rgb_attivo):
        self.__normale = {
            'r' : 255,
            'g' : 255,
            'b' : 255,
            'A' : 255
        } #BIANCO
        self.__rgb = {
            'r' : 255,
            'g' : 255,
            'b' : 255,
            'A' : 255
        } #RGB
        self.__rgb_attivo = rgb_attivo
        self.__velocita = 10


    def get_rgb(self):
        return self.__rgb


    def set_rgb_attivi(self):
        self.__rgb_attivo = True

    def set_rgb_disattivi(self):
        self.__rgb_attivo = False

    def aggiorna_rgb(self):
        if self.__rgb_attivo:
            for chiave, valore in self.__rgb.items():
                if chiave != 'A':
                    if (self.__velocita > 0 and self.__rgb[chiave] + self.__velocita < 255) or (
                            self.__velocita < 0 < 20 < self.__rgb[chiave] + self.__velocita):
                        self.__rgb[chiave] = valore + self.__velocita
                        return
            self.__velocita = -self.__velocita


    def get_colore(self):
        if not self.__rgb_attivo:
            return tuple(self.__normale.values())
        else:
            print(f"{tuple(self.__rgb.values())}  V = {self.__velocita}")
            return tuple(self.__rgb.values())
