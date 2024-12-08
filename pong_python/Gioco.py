from pyray import *
import Giocatore

class Gioco:
    def __init__(self, g1, g2, pallina):
        self.__giocatori = [g1,g2]
        self.__pallina = pallina
        self.__stato_pausa = False

    def aggiorna_giocatori(self):
        self.__giocatori[0].aggiorna_barretta(1)
        self.__giocatori[1].aggiorna_barretta(2)

        barretta1 = self.__giocatori[0].get_barretta()
        barretta2 = self.__giocatori[1].get_barretta()

        self.__pallina.aggiorna_y(get_screen_height())
        self.__pallina.aggiorna_x(barretta1, barretta2)

    def aggiorna(self):
        self.aggiorna_giocatori()

    def reset_pallina(self):
        self.__pallina.reset_pos()

    def controlla_pallina(self):
        self.__pallina.assegna_punto(get_screen_width())

    def get_stato_pausa(self):
        return self.__stato_pausa

    def alterna_stato_pausa(self):
        self.__stato_pausa = not self.__stato_pausa

    def disegna(self):
        self.__pallina.disegna()
        self.__giocatori[0].get_barretta().disegna()
        self.__giocatori[1].get_barretta().disegna()