from pyray import *

def scrivi_messaggio(messaggio, colore, FONT_SIZE=40):
    pos_x = int((get_screen_width() - measure_text(messaggio, int(FONT_SIZE))) // 2)
    pos_y = int((get_screen_height() - int(FONT_SIZE))/ 2)
    draw_text(messaggio, pos_x, pos_y, FONT_SIZE, colore.get_colore())
