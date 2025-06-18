from raylibpy import *

class Barretta:
    def __init__(self, x, y, l, h, v):
        self.__rec = {
            "x": x,
            "y": y,
            "l": l,
            "h": h,
        }
        self.__v = v

    def set_x(self, x):
        self.__rec[x] = x

    def set_y(self, y):
        self.__rec["y"] = y

    def set_v(self, v):
        self.__v = v

    def get_x(self):
        return self.__rec["x"]

    def get_y(self):
        return self.__rec["y"]

    def get_h(self):
        return self.__rec["h"]

    def get_rettangolo(self):
        return self.__rec

    def disegna(self, colore):
        x = int(self.__rec["x"])
        y = int(self.__rec["y"])
        l = int(self.__rec["l"])
        h = int(self.__rec["h"])
        draw_rectangle(x, y, l, h, colore)

    def aggiorna_x(self, limite1, limite2, tasto_destra, tasto_sinistra):
        x = self.__rec["x"]
        if is_key_down(tasto_sinistra) and limite1 <= x <= limite2:
            self.__rec["x"] -= self.__v
        elif is_key_down(tasto_destra) and limite1 <= x <= limite2:
            self.__rec["x"] += self.__v
