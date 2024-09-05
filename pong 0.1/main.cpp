#include "include/raylib.h"
#include <iostream>

void pb1(float &by1, float vb1, float h, int screenHeight) {
    if (IsKeyDown(KEY_W) && by1 > 0) {
        by1 -= vb1;
    } else if (IsKeyDown(KEY_S) && by1 + h < screenHeight) {
        by1 += vb1;
    }
}
void pb2(float &by2, float vb2, float h, int screenHeight) {
    if (IsKeyDown(KEY_UP) && by2 > 0) {
        by2 -= vb2;
    } else if (IsKeyDown(KEY_DOWN) && by2 + h < screenHeight) {
        by2 += vb2;
    }
}
void py( float &y, float raggio, float &vy, int screenHeight){
    if ( y - raggio <= 0 ) {
        vy = abs(vy);
    } else if (y + raggio >= screenHeight) {
        vy = -vy;
    }
    y += vy;
}

bool controllo (float y, float by, float h, float raggio) {
    if (y + raggio >= by && y - raggio <= by + h) {
        return true;
    } else return false;
}


void px( float &x, float raggio, float &vx, float y, float by1, float bx1, float bx2, float by2, float h, float l){
    if ( x - raggio <= bx1 + l && x - raggio >= bx1 && controllo(y, by1, h, raggio)) {
        vx = abs(vx);
    } else if (x + raggio >= bx2 && x + raggio <= bx2 + l && controllo(y, by2, h, raggio)) {
        vx = -vx;
    }
    x += vx;
}

float vi (float v){
    if (GetRandomValue(1,2) == 1){
        return -v;
    } else {
        return v;
    }
}


void dis_punteggio (int p, float pos) {
    std::string punteggio;
    punteggio = std::to_string(p);
    DrawText(punteggio.c_str(), pos, 30, 40, WHITE);

}

void partenza (int &gioco, int screenHeight, int screenWidth, int p1, int p2, int &stato) {
    if (gioco == 2 && p2 != 10) {
        DrawText("Il giocatore 2 ha fatto punto", screenWidth/2.7, screenHeight/2 - 25, 40, WHITE);
        DrawText("Premere spazio per continuare", screenWidth/2.7, screenHeight/2 + 25, 40, WHITE);
    } else  if (gioco == 3 && p1 != 10) {
        DrawText("Il giocatore 1 ha fatto punto", screenWidth/2.7, screenHeight/2 - 25, 40, WHITE);
        DrawText("Premere spazio per continuare", screenWidth/2.7, screenHeight/2 + 25, 40, WHITE);
    } else if (gioco == 0) {
        DrawText("Premi spazio per iniziare", screenWidth/2.8, screenHeight/2, 40, WHITE);
    } else if ( p1 == 10 || p2 == 10 ) {
        if (p1 == 10) {
        DrawText("Il giocatore 1 ha vinto!", screenWidth/2.7, screenHeight/2 - 20, 40, WHITE);
        } else if (p2 == 10) {
        DrawText("Il giocatore 2 ha vinto!", screenWidth/2.7, screenHeight/2 - 25, 40, WHITE);
        }
        DrawText("Premere R per ricominciare", screenWidth/2.8, screenHeight/2 + 20, 40, WHITE);
        DrawText("Premere U per uscire", screenWidth/2.8, screenHeight/2 + 55, 40, WHITE);
        if (IsKeyDown(KEY_R)) {
            gioco = 0;
        }
        if (IsKeyDown(KEY_U)) {
            stato = 3;
            gioco = 0;
        }
    }
}

void inc_v (float &v) {
    if (v > 0) {
        v += 0.001;
    } else {
        v -= 0.001;
    }
}

void repet (int &gioco, int &tempo, float &h, float h_iniz) {
    gioco = 4;
    h = h_iniz;
    tempo = 0;
}

void caricamento_dis (float &x_caricamento, float h_caricamento, int &tempo, int screenWidth, int screenHeight, int temp, int &stato) {
    x_caricamento += 9;
    if (x_caricamento >= screenWidth) {
        stato = temp;
        x_caricamento = 0;
    }
    DrawRectangle(0, screenHeight-h_caricamento, x_caricamento, h_caricamento, WHITE);
    tempo++;
    if (tempo < 30) {
        DrawText("Caricamento.", screenWidth*0.05, screenHeight-2*h_caricamento, 40, WHITE);
    } else if (tempo < 60) {
        DrawText("Caricamento..", screenWidth*0.05, screenHeight-2*h_caricamento, 40, WHITE);
    } else if (tempo < 90) {
        DrawText("Caricamento...", screenWidth*0.05, screenHeight-2*h_caricamento, 40, WHITE);
    } else {
        tempo = 0;
    }
}

void stato_0 (int screenWidth, int screenHeight){
    DrawText("PONG", screenWidth*0.45, screenHeight/3, 100, WHITE);
    DrawText("Premi M per scegliere la modalita' della partita", screenWidth*0.02, screenHeight*0.70, 50, WHITE);
    DrawText("Premi I per vedere le impostazioni", screenWidth*0.02, screenHeight*0.80, 50, WHITE);
}

void stato_2 (int &gioco, int &p1, int &p2, float &x, float &y, float raggio, float &v, float &vx, float &vy, float &bx1, float &bx2, float &by1, float &by2, float &vb1, float &vb2, float &h_iniz, float &h, float &l, int &tempo, int screenWidth, int screenHeight) {
    if (gioco == 0) {
        p1 = 0;
        p2 = 0;
        tempo = 0;
        if (IsKeyPressed(KEY_SPACE)) {
            gioco = 4;
            vx = vi(v);
            vy = vi(v);
        }
    } else if (gioco > 1) {
        pb1(by1, vb1, h, screenHeight);
        pb2(by2, vb2, h, screenHeight);
        py(y, raggio, vy, screenHeight);
        px(x, raggio, vx, y, by1, bx1, bx2, by2, h, l);
        if (x <= 0 || x >= screenWidth) {
            if (x <= 0) {
                p2++;
                gioco = 2;
            } else if (x >= screenWidth) {
                p1++;
                gioco = 3;
            }
            y = GetRandomValue(raggio, screenHeight - raggio);
            x = screenWidth / 2;
            vx = 0;
            vy = 0;
        }
        if (IsKeyDown(KEY_SPACE) && gioco == 2) {
            vy = vi(v);
            vx = v;
            repet(gioco, tempo, h, h_iniz);
        } else if (IsKeyDown(KEY_SPACE) && gioco == 3) {
            vy = vi(v);
            vx = -v;
            repet(gioco, tempo, h, h_iniz);
        }

        tempo++;
        if (tempo > 2000 && gioco != 2 && gioco != 3) {
            inc_v(vx);
            inc_v(vy);
            if (tempo > 3000 && h > 30) {
                h -= 0.05;
            }
        }
    }
}

void dis_stato_2 ( int &stato, int &gioco, int p1, int p2, float x, float y, float raggio, float bx1, float bx2, float by1, float by2, float l, float h, int screenWidth, int screenHeight) {
    partenza(gioco, screenHeight, screenWidth, p1, p2, stato);
    DrawCircle(x, y, raggio, WHITE);
    DrawRectangle(bx1, by1 , l, h, WHITE);
    DrawRectangle(bx2, by2 , l, h, WHITE);
    dis_punteggio(p1, screenWidth / 4);
    dis_punteggio(p2, screenWidth  * 0.75);
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1800;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "pong");

    SetTargetFPS(60);

    float raggio = 15, x = screenWidth / 2, y = GetRandomValue(raggio, screenHeight - raggio),v = 7, vx = 0, vy = 0;
    float h_iniz = 150, h = h_iniz, bx1 = 50, l = 10, vb1 = 6, by1 = screenHeight / 2 - h / 2;
    float bx2 = screenWidth - 50,vb2 = 6, by2 = screenHeight / 2 - h / 2;
    int p1, p2;
    int gioco = 0, tempo = 0, stato = 0;
    float x_caricamento = 0, h_caricamento = screenHeight/20;

    while (!WindowShouldClose())
    {

        if (stato == 0) {
            if (IsKeyDown(KEY_P)){
                stato = 1;
            }
        } else if (stato == 2) {
            stato_2(gioco, p1, p2, x, y, raggio, v, vx, vy, bx1, bx2, by1, by2, vb1, vb2, h_iniz, h, l, tempo,  screenWidth, screenHeight);
        }

        BeginDrawing();

        if (stato == 0) {
            stato_0(screenWidth, screenHeight);
        } else if (stato == 1) {
            caricamento_dis(x_caricamento, h_caricamento, tempo, screenWidth, screenHeight, 2, stato);
        } else if (stato == 2) {
            dis_stato_2(stato, gioco, p1, p2, x, y, raggio, bx1, bx2, by1, by2, l, h, screenWidth, screenHeight);
        } else if (stato == 3) {
            caricamento_dis(x_caricamento, h_caricamento, tempo, screenWidth, screenHeight, 0, stato);
        }
        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}