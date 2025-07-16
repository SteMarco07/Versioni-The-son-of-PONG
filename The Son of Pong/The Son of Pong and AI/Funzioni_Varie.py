from raylib import *


def scrivi_messaggio(messaggio, colore, FONT_SIZE=40):
    pos_x = int((GetScreenWidth() - MeasureText(messaggio.encode('utf-8'), int(FONT_SIZE))) // 2)
    pos_y = int((GetScreenHeight() - int(FONT_SIZE)) / 2)
    DrawText(messaggio.encode('utf-8'), pos_x, pos_y, FONT_SIZE, colore.get_colore())
