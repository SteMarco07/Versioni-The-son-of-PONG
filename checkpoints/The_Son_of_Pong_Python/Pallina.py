import math

from pyray import *
import random

from Funzioni_Varie import scrivi_messaggio

class Pallina:

    def __init__(self, x, y, raggio, v0, vx, vy, colore, suono):
        self.__pos = {"x": x, "y": y}
        self.__raggio = raggio
        self.__rimbalzo = True
        self.__v = {"v0":v0, "vx":vx, "vy":vy}
        self.colore = colore
        self.__suono = suono

    def reset(self):
        self.set_pos(get_screen_width()/2, get_screen_height()/2)
        self.reset_vx()
        self.reset_vy()

    def reset_vx(self):
        if get_random_value(1,2) == 1:
            self.__v["vx"] = -self.__v["v0"]
            self.__rimbalzo = True
        else:
            self.__v["vx"] = self.__v["v0"]
            self.__rimbalzo = False

    def reset_vy(self):
        moltiplicatore = int( self.__v["v0"] * random.randrange(50,100)/100)
        if random.choice([1,2]) == 1:
            self.__v["vy"] = -moltiplicatore
        else:
            self.__v["vy"] = moltiplicatore

    def set_x(self, x):
        self.__pos["x"] = x

    def set_y(self, y):
        self.__pos["y"] = y

    def set_pos(self, x, y):
        self.__pos["x"] = x
        self.__pos["y"] = y

    def get_pos(self):
        return self.__pos["x"], self.__pos["y"]

    def aggiorna_y(self, screen_height):
        if self.__pos["y"] - self.__raggio <= 0:
            self.__v["vy"] = abs(self.__v["vy"] )
            play_sound(self.__suono)
        elif self.__pos["y"] + self.__raggio >= screen_height:
            self.__v["vy"]  = -self.__v["vy"]
            play_sound(self.__suono)

        self.__pos["y"]  += self.__v["vy"]

    def __calcola_rimbalzo(self, barretta):
        # Calcola la posizione relativa del punto di contatto
        distanza_relativa = (self.__pos["y"] - (barretta.get_y() + barretta.get_h() / 2)) / (barretta.get_h() / 2)
        distanza_relativa = max(-1, min(1, distanza_relativa))  # Verifica che sia compresa tra -1 e 1

        # Angolo massimo (45 gradi)
        angolo_massimo = math.radians(45)
        angolo = distanza_relativa * angolo_massimo

        # Velocità totale della pallina
        velocita = math.sqrt(self.__v["vx"] ** 2 + self.__v["vy"] ** 2)

        # Nuove componenti di velocità
        self.__v["vx"] = velocita * math.cos(angolo) * (-1 if self.__v["vx"] > 0 else 1)
        self.__v["vy"] = velocita * math.sin(angolo)

    def __aggiorna(self, barretta, direzione):
        self.__pos["x"] += direzione
        self.__calcola_rimbalzo(barretta)
        play_sound(self.__suono)

    def aggiorna_x(self, barretta1, barretta2):
        # Rileva collisioni con le barrette

        rec1 = tuple(barretta1.get_rettangolo().values())
        rec2 = tuple(barretta2.get_rettangolo().values())
        if check_collision_circle_rec(self.get_pos(), self.__raggio, rec1) and self.__rimbalzo:
            self.__aggiorna(barretta1, 10)
            self.__rimbalzo = False
        elif check_collision_circle_rec(self.get_pos(), self.__raggio, rec2) and not self.__rimbalzo:
            self.__aggiorna(barretta2, -10)
            self.__rimbalzo = True

        # Aggiorna la posizione orizzontale
        self.__pos["x"] += self.__v["vx"]

    def disegna(self):
        draw_circle(int(self.__pos["x"]), int(self.__pos["y"]), self.__raggio, self.colore)

    def assegna_punto(self):
        if self.__pos["x"] < 0:
            return 1
        elif self.__pos["x"] > get_screen_width():
            return 0
        else:
            return -1