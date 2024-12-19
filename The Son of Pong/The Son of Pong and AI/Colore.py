from random import randint


class Colore:

    def __init__(self, rgb_attivo=False):
        self.__normale = {
            'r': 255,
            'g': 255,
            'b': 255,
            'A': 255
        }  # BIANCO
        value = randint(50, 205)
        self.__rgb = {
            'r': value,
            'g': value,
            'b': value,
            'A': 255
        }  # RGB
        self.__rgb_attivo = rgb_attivo
        self.__velocita = 5

    def get_stato_rgb(self):
        return self.__rgb_attivo

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
            # print(f"{tuple(self.__rgb.values())}  V = {self.__velocita}")
            return tuple(self.__rgb.values())

    def get_colore_invertito(self):
        if not self.__rgb_attivo:
            new_color = {
                'r': 255 - self.__normale['r'],
                'g': 255 - self.__normale['g'],
                'b': 255 - self.__normale['b'],
                'A': 255
            }
        else:
            new_color = {
                'r': 255 - self.__rgb['r'],
                'g': 255 - self.__rgb['g'],
                'b': 255 - self.__rgb['b'],
                'A': 255
            }
        return tuple(new_color.values())
