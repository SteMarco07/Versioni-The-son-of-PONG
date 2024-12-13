from pyray import *


def scrivi_messaggio(messaggio, FONT_SIZE):
    pos_x = int((get_screen_width() - measure_text(messaggio, FONT_SIZE)) / 2)
    pos_y = int((get_screen_height() - FONT_SIZE) / 2)
    draw_text(messaggio, pos_x, pos_y, FONT_SIZE, WHITE)
