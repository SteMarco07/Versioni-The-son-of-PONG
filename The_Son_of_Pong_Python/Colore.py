from pyray import *

class Colore:

    def __init__(self, attuale, rgb, custom, rgb_attivo):
        self.__attuale = attuale
        self.__rgb = rgb
        self.__custom = custom
        self.__rgb_attivo = rgb_attivo

    def set_attuale(self, attuale):
        self.__attuale = attuale

    def set_rgb(self, rgb):
        self.__rgb = rgb

    def set_custom(self, custom):
        self.__custom = custom

    def attiva_rgb(self):
        self.__rgb_attivo = True

    def desattiva_rgb(self):
        self.__rgb_attivo = False

    def get_colore(self):
        if self.__rgb_attivo:
            return self.__attuale
        else:
            return self.__rgb

    def get_custom(self):
        return self.__custom
