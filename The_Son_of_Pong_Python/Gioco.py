from pyray import *

from Funzioni_Varie import scrivi_messaggio

class Gioco:
    def __init__(self, g1, g2, pallina):
        self.__giocatori = [g1,g2]
        self.__pallina = pallina
        self.__stato = 0
        #0) inizio partita
        #1) nel corso dell partita
        #2) pausa come interruzione del giocatore
        #3) pausa dovuta a un giocatore che segna un punto
        #4) vittoria
        #5) menu vari che aggiungeremo prima o poi

    def aggiorna_giocatori(self):
        self.__giocatori[0].aggiorna_barretta(1)
        self.__giocatori[1].aggiorna_barretta(2)

        barretta1 = self.__giocatori[0].get_barretta()
        barretta2 = self.__giocatori[1].get_barretta()

        self.__pallina.aggiorna_y(get_screen_height())
        self.__pallina.aggiorna_x(barretta1, barretta2)

    def aggiungi_punto(self, indice):
        self.__giocatori[indice].aggiungi_punto(indice)

    def aggiorna(self):
        self.aggiorna_giocatori()

    def reset_pallina(self):
        self.__pallina.reset()

    def controlla_pallina(self):
        return  self.__pallina.assegna_punto()

    def pallina_off_screen(self):
        self.__pallina.set_x(-1000)
        self.__pallina.set_y(-1000)

    def get_stato(self):
        return self.__stato

    def reset(self):
        self.__pallina.reset()
        self.__giocatori[0].reset()
        self.__giocatori[1].reset()
        self.__stato = 0

    def set_stato(self, stato):
        self.__stato = stato

    def disegna_fine_partita(self, punteggio_fine_partita):
        if self.__giocatori[0].get_punteggio() == punteggio_fine_partita:
            scrivi_messaggio("IL GIOCATORE 1 HA VINTO", 40)

        elif self.__giocatori[1].get_punteggio() == punteggio_fine_partita:
            scrivi_messaggio("IL GIOCATORE 2 HA VINTO", 40)

    def get_punteggio_giocatore(self, indice):
        return self.__giocatori[indice].get_punteggio()

    def get_vincitore(self):
        if self.__giocatori[0].get_punteggio() > self.__giocatori[1].get_punteggio():
            return 0
        else:
            return 1

    def disegna(self):
        for i in range(0,get_screen_height(),80):
            l = 6
            draw_rectangle(int((get_screen_width() -l)/2), i, l, 40, WHITE)

        self.__pallina.disegna()
        self.__giocatori[0].disegna(get_screen_width()*0.25,50)
        self.__giocatori[1].disegna(get_screen_width()*0.75,50)

    def carica_musica(self):
        self.__musica = [load_sound('assets/chill.mp3'.encode('utf-8')),
                         load_sound('assets/partita.mp3'.encode('utf-8')),
                         load_sound('assets/vittoria.mp3'.encode('utf-8'))]

    def __gestisci_musiche(self, target):
        for OST in self.__musica:
            if is_sound_playing(OST) and OST != target:
                stop_sound(OST)
        if not is_sound_playing(target):
            play_sound(target)

    def riproduci_musica(self):
        target = Sound
        if self.__stato == 0: #play chill
            target = self.__musica[0] #seleziona chill
        if self.__stato != 4:
            target = self.__musica[1]
        else:
            target = self.__musica[2]
        self.__gestisci_musiche(target)

    def disegna_pausa(self):
        scrivi_messaggio("IL GIOCO E' IN PAUSA",40)