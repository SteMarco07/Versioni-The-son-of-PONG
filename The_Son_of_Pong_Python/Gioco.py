from pyray import *

from Messaggio import scrivi_messaggio

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

    def aggiungi_punto(self, indice, punteggio_fine_partita):
        self.__giocatori[indice].aggiungi_punto(self.controlla_fine_partita(punteggio_fine_partita),indice)

    def aggiorna(self):
        self.aggiorna_giocatori()

    def reset_pallina(self):
        self.__pallina.reset()

    def controlla_pallina(self):
        return  self.__pallina.assegna_punto()

    def pallina_off_screen(self):
        self.__pallina.set_x(-1000)
        self.__pallina.set_y(-1000)

    def get_stato_pausa(self):
        return self.__stato_pausa

    def reset(self):
        self.__pallina.reset()
        self.__giocatori[0].reset()
        self.__giocatori[1].reset()

    def alterna_stato_pausa(self):
        self.__stato_pausa = not self.__stato_pausa

    def pausa(self):
        self.__stato_pausa = True

    def play(self):
        self.__stato_pausa = False

    def disegna_fine_partita(self, punteggio_fine_partita):
        if self.__giocatori[0].get_punteggio() == punteggio_fine_partita:
            scrivi_messaggio("IL GIOCATORE 1 HA VINTO", 40)

        elif self.__giocatori[1].get_punteggio() == punteggio_fine_partita:
            scrivi_messaggio("IL GIOCATORE 2 HA VINTO", 40)

    def controlla_fine_partita(self, punteggio_fine_partita):
        if self.__giocatori[0].get_punteggio() < punteggio_fine_partita and self.__giocatori[1].get_punteggio() < punteggio_fine_partita:
            return False
        else:
            print(1)
            return True

    def disegna(self):
        for i in range(0,get_screen_height(),80):
            l = 6
            draw_rectangle(int((get_screen_width() -l)/2), i, l, 40, WHITE)

        self.__pallina.disegna()
        self.__giocatori[0].disegna(get_screen_width()*0.25,50)
        self.__giocatori[1].disegna(get_screen_width()*0.75,50)

    def disegna_pausa(self):
        scrivi_messaggio("IL GIOCO E' IN PAUSA",40)