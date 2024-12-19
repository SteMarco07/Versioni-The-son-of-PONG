#include "include/raylib.h"
#include <iostream>

void dis_colori0 (int screenWidth,int screenHeight){
    int a;
    DrawText("A)      Colore della pallina", screenWidth/6, screenHeight/2-250, 90,WHITE);
    DrawText("B)   Colore della barretta", screenWidth/6, screenHeight/2+250, 90,WHITE);
}

void dis_colori(int screenWidth, int screenHeight, int &colori){
    Color Colori[] = {WHITE, RED, ORANGE,YELLOW,GREEN,SKYBLUE,PINK, VIOLET};
    int a = 0;
    int b = 0;
    std::string numero;
    DrawText( "Seleziona un colore", 500,50,80,WHITE);
    for (int i = 0; i < 8; ++i) {
        if (i < 4)
            b = 0;
        else
            b = screenHeight / 2 - 50;
        if (i==4)
            a=0;
        DrawRectangle(screenWidth / 18 + a, screenHeight / 9 + 100 + b, screenWidth / 7.2, screenHeight / 3.6, DARKGRAY);
        DrawRectangle(screenWidth / 18 + 5 + a, screenHeight / 9 + 105 + b, screenWidth / 7.2-10, screenHeight / 3.6-10, Colori[i]);
        a += screenWidth / 4;
    }
    a=0;
    b=0;
    DrawText("1",screenWidth / 18 + 20 + a,screenHeight / 9 + 105 + b, 100, BLACK);
    for (int i = 2 ; i <= 8 ; i++ ){
        a += screenWidth/4;
        if ( i == 5){
            a=0;
            b=450;
        }
        numero = std::to_string(i);
        DrawText(numero.c_str(),screenWidth / 18 + 20 + a,screenHeight / 9 + 105 + b, 100, BLACK);
    }
}

void pbx1(float &bx1, float vb1, float l, int screenWidth) {
    if (IsKeyDown(KEY_A) && bx1 > 0) {
        bx1 -= vb1;
    } else if (IsKeyDown(KEY_D) && bx1 + l < screenWidth/3) {
        bx1 += vb1;
    }
}

void pbx2(float &bx2, float vb2, float l, int screenWidth) {
    if (IsKeyDown(KEY_LEFT) && bx2 > screenWidth*2/3 + l) {
        bx2 -= vb2;
    } else if (IsKeyDown(KEY_RIGHT) && bx2 + l < screenWidth + l) {
        bx2 += vb2;
    }
}

void pby1(float &by1, float vb1, float h, int screenHeight) {
    if (IsKeyDown(KEY_W) && by1 > 0) {
        by1 -= vb1;
    } else if (IsKeyDown(KEY_S) && by1 + h < screenHeight) {
        by1 += vb1;
    }
}

void pby2(float &by2, float vb2, float h, int screenHeight) {
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

float reset_vy (float vy, float v, float incremento){
    if (vy > 0) {
        return v + incremento;
    } else {
        return -v - incremento;
    }
}

void px( float &x, float raggio, float &vx, float y, float by1, float bx1, float bx2, float by2, float h, float l, bool  &rimbalzo, float &vy, float v,
         float incremento){

    if  (CheckCollisionCircleRec({x,y}, raggio, {bx1, by1, l, h}) && rimbalzo) {
        vx = abs(vx);
        rimbalzo = false;
        x += 7;
        vy = reset_vy( vy,v, incremento);
        vy *= (y - (by1+h/2))/(h/2);
    } else if (CheckCollisionCircleRec({x,y}, raggio, {bx2-l, by2, l, h}) && !rimbalzo) {
        vx = -vx;
        rimbalzo = true;
        x -= 7;
        vy = reset_vy( vy,v, incremento);
        vy *= (y - (by2+h/2))/(h/2);
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
            stato = 25;
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
    x_caricamento += 17;
    if (x_caricamento >= screenWidth) {
        stato = temp;
        x_caricamento = 0;
    }
    DrawRectangle(0, screenHeight-h_caricamento, x_caricamento, h_caricamento, WHITE);
    tempo++;
    if (tempo < 15) {
        DrawText("Caricamento.", screenWidth*0.05, screenHeight-2*h_caricamento, 40, WHITE);
    } else if (tempo < 30) {
        DrawText("Caricamento..", screenWidth*0.05, screenHeight-2*h_caricamento, 40, WHITE);
    } else if (tempo < 45) {
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

void stato_4 (int &gioco, int &p1, int &p2, float &x, float &y, float raggio, float &v, float &vx, float &vy, float &bx1, float &bx2, float &by1, float &by2,
              float &vb1, float &vb2, float &h_iniz, float &h, float &l, int &tempo, int screenWidth, int screenHeight, bool &rimbalzo, float &incremento) {
    if (gioco == 0) {
        p1 = 0;
        p2 = 0;
        tempo = 0;
        bx2 = screenWidth - 50;
        bx1 = 50;
        by2 = screenHeight / 2 - h / 2;
        by1 = screenHeight / 2 - h / 2;
        if (IsKeyPressed(KEY_SPACE)) {
            gioco = 4;
            vx = vi(v);
            vy = vi(v);
            if (vx < 0) {
                rimbalzo = true;
            } else {
                rimbalzo = false;
            }
        }
    } else if (gioco > 1) {
        py(y, raggio, vy, screenHeight);
        px(x, raggio, vx, y, by1, bx1, bx2, by2, h, l, rimbalzo, vy, v,incremento);
        pby1(by1, vb1, h, screenHeight);
        pby2(by2, vb2, h, screenHeight);
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
            rimbalzo = false;
        } else if (IsKeyDown(KEY_SPACE) && gioco == 3) {
            vy = vi(v);
            vx = -v;
            repet(gioco, tempo, h, h_iniz);
            rimbalzo = true;
        }

        tempo++;
        if (tempo > 2000 && gioco != 2 && gioco != 3) {
            inc_v(vx);
            inc_v(vy);
            incremento += 0.001;
            if (tempo > 3000 && h > 30) {
                h -= 0.05;
            }
        }
    }
}

void dis_stato_4 ( int &stato, int &gioco, int p1, int p2, float x, float y, float raggio, float bx1, float bx2, float by1, float by2, float l, float h,
                   int screenWidth, int screenHeight, int colore, int stato_colori) {
    partenza(gioco, screenHeight, screenWidth, p1, p2, stato);

    Color Colori[] = {WHITE, RED, ORANGE, YELLOW, GREEN, SKYBLUE, PINK, VIOLET,};

    Color a , b ;
    static Color ap=WHITE, bp=WHITE;

    if (stato_colori == 1) {
        a = Colori[colore];
        ap = a;
    }else {
        a = ap;
    } if (stato_colori == 2) {
        b = Colori[colore];
        bp = b;
    } else {
        b = bp;
    }
    DrawCircle(x, y, raggio, a);
    DrawRectangle(bx1, by1 , l, h, b);
    DrawRectangle(bx2-l, by2 , l, h, b);
    dis_punteggio(p1, screenWidth / 4);
    dis_punteggio(p2, screenWidth  * 0.75);
    for (int i = 0; i < screenHeight; i += 60) {
        DrawRectangle((screenWidth/2)-3,i, 6, 20, WHITE);
    }
}

void dis_stato_2(int screenWidth, int screenHeight) {
    DrawText("Modalita'", screenWidth*0.40, screenHeight*0.02, 100,WHITE);
    DrawText("1)     Pong classico", screenWidth*0.02, screenHeight/2 - 200, 60,WHITE);
    DrawText("2)    Pong libero", screenWidth*0.02, screenHeight/2 - 120, 60,WHITE);
    DrawText("3)    Pong classico medio", screenWidth*0.02, screenHeight/2 - 40, 60,WHITE);
    DrawText("4)    Pong libero medio", screenWidth*0.02, screenHeight/2 + 40, 60,WHITE);
    DrawText("5)    Pong classico difficile", screenWidth*0.02, screenHeight/2 + 120, 60,WHITE);
    DrawText("6)    Pong libero difficile", screenWidth*0.02, screenHeight/2 + 200, 60,WHITE);
}


void dis_stato_6 (int &stato,int &gioco, int p1, int p2, float x, float y, float raggio, float bx1, float bx2, float by1, float by2, float l, float h,
                  float screenWidth, float screenHeight, int colori, int stato_colori) {
    dis_stato_4(stato, gioco, p1, p2, x, y, raggio, bx1, bx2, by1, by2, l, h, screenWidth, screenHeight, colori, stato_colori);
    for (int i = 0; i < screenHeight; i += 80) {
        DrawRectangle((screenWidth/3)-3,i, 6, 20, WHITE);
    }
    for (int i = 0; i < screenHeight; i += 80) {
        DrawRectangle((screenWidth*2/3)-3,i, 6, 20, WHITE);
    }
}

void stato_2 (int &stato) {
    if (IsKeyDown(KEY_ONE)) {
        stato = 3;
    } else if (IsKeyDown(KEY_TWO)) {
        stato = 5;
    } else if (IsKeyDown(KEY_THREE)) {
        stato = 7;
    } else if (IsKeyDown(KEY_FOUR)) {
        stato = 9;
    } else if (IsKeyDown(KEY_FIVE))
        stato = 11;
    else if (IsKeyDown(KEY_SIX))
        stato = 13;
}

void stato_6 (int &gioco, int &p1, int &p2, float &x, float &y, float raggio, float &v, float &vx, float &vy, float &bx1, float &bx2, float &by1, float &by2,
              float &vb1, float &vb2, float &h_iniz, float &h, float &l, int &tempo, int screenWidth, int screenHeight, bool &rimbalzo_x, float &incremento) {
    stato_4(gioco, p1, p2, x, y, raggio, v, vx, vy, bx1, bx2, by1, by2, vb1, vb2, h_iniz, h, l, tempo, screenWidth, screenHeight, rimbalzo_x, incremento);

    if (gioco > 1 ) {
        pbx1(bx1, vb1, l, screenWidth);
        pbx2(bx2, vb2, l, screenWidth);
    }
}

void stato_8 (int &gioco, int &p1, int &p2, float &x, float &y, float raggio, float &v, float &vx, float &vy, float &bx1, float &bx2, float &by1, float &by2,
              float &vb1, float &vb2, float &h_iniz, float &h, float &l, int &tempo, int screenWidth, int screenHeight, bool &rimbalzo_x, float &incremento) {
    stato_4(gioco, p1, p2, x, y, raggio, v, vx, vy, bx1, bx2, by1, by2, vb1, vb2, h_iniz, h, l, tempo,
            screenWidth, screenHeight, rimbalzo_x, incremento);
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1800;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "pong");

    SetTargetFPS(60);

    float raggio = 15, x = screenWidth / 2, y = GetRandomValue(raggio, screenHeight - raggio),v = 9, vx, vy;
    float h_iniz = 200, h = h_iniz, bx1 = 50, l = 15, vb1 = 7, by1 = screenHeight / 2 - h / 2;
    float bx2 = screenWidth - 50,vb2 = 7, by2 = screenHeight / 2 - h / 2, incremento;
    int p1, p2;
    int gioco = 0, tempo = 0, stato = 0;
    float x_caricamento = 0, h_caricamento = screenHeight/20;
    bool rimbalzo_x;
    int  stato_colori, colori=0;

    while (!WindowShouldClose()) {

        if (stato == 0) {
            if (IsKeyDown(KEY_M)) {
                stato = 1;
            } else if (IsKeyDown(KEY_I)) {
                stato = 21;
            }
        } else if (stato == 2) {
            stato_2(stato);
        } else if (stato == 4) {

            stato_4(gioco, p1, p2, x, y, raggio, v, vx, vy, bx1, bx2, by1, by2, vb1, vb2, h_iniz, h, l, tempo,
                    screenWidth, screenHeight, rimbalzo_x, incremento);
        } else if (stato == 6) {

            stato_6(gioco, p1, p2, x, y, raggio, v, vx, vy, bx1, bx2, by1, by2, vb1, vb2, h_iniz, h, l, tempo,
                    screenWidth, screenHeight, rimbalzo_x, incremento);

        } else if (stato == 8) {
            stato_8(gioco, p1, p2, x, y, raggio, v, vx, vy, bx1, bx2, by1, by2, vb1, vb2, h_iniz, h, l, tempo,
                    screenWidth, screenHeight, rimbalzo_x, incremento);
        } else if (stato == 10) {
            stato_6(gioco, p1, p2, x, y, raggio, v, vx, vy, bx1, bx2, by1, by2, vb1, vb2, h_iniz, h, l, tempo,
                    screenWidth, screenHeight, rimbalzo_x, incremento);
        } else if (stato == 12) {
            stato_4(gioco, p1, p2, x, y, raggio, v, vx, vy, bx1, bx2, by1, by2, vb1, vb2, h_iniz, h, l, tempo,
                    screenWidth, screenHeight, rimbalzo_x, incremento);
        } else if (stato == 14) {
            stato_6(gioco, p1, p2, x, y, raggio, v, vx, vy, bx1, bx2, by1, by2, vb1, vb2, h_iniz, h, l, tempo,
                    screenWidth, screenHeight, rimbalzo_x, incremento);
        } else if (stato == 21) {
            dis_colori0(screenWidth, screenHeight);
            if (IsKeyDown(KEY_A)) {
                stato_colori = 1;
                stato = 22;
            } else if (IsKeyDown(KEY_B)) {
                stato_colori = 2;
                stato = 22;
            } else if (IsKeyDown(KEY_Q)) {
                stato = 0;
            }
        } else if (stato == 22) {
            dis_colori(screenWidth, screenHeight, colori);
            if (IsKeyDown(KEY_ONE)) {
                stato = 0;
                colori = 0;
            } else if (IsKeyDown(KEY_TWO)) {
                stato = 0;
                colori = 1;
            } else if (IsKeyDown(KEY_THREE)) {
                stato = 0;
                colori = 2;
            } else if (IsKeyDown(KEY_FOUR)) {
                stato = 0;
                colori = 3;
            } else if (IsKeyDown(KEY_FIVE)) {
                stato = 0;
                colori = 4;
            } else if (IsKeyDown(KEY_SIX)) {
                stato = 0;
                colori = 5;
            } else if (IsKeyDown(KEY_SEVEN)) {
                stato = 0;
                colori = 6;
            } else if (IsKeyDown(KEY_EIGHT)) {
                stato = 0;
                colori = 7;
            } else if (IsKeyDown(KEY_Q))
                stato = 0;
        }
        if (IsKeyPressed(KEY_T)) {
            stato = 25;
            gioco = 0;
        }

        BeginDrawing();

        if (stato == 0) {
            stato_0(screenWidth, screenHeight);
        } else if (stato == 1) {
            caricamento_dis(x_caricamento, h_caricamento, tempo, screenWidth, screenHeight, 2, stato);
        } else if (stato == 2) {
            dis_stato_2(screenWidth, screenHeight);
        } else if (stato == 3) {
            caricamento_dis(x_caricamento, h_caricamento, tempo, screenWidth, screenHeight, 4, stato);
            v = 9;
            vb1 = 7;
            vb2 = 7;
            h = 200;
        } else if (stato == 4) {
            dis_stato_4(stato, gioco, p1, p2, x, y, raggio, bx1, bx2, by1, by2, l, h, screenWidth, screenHeight, colori,
                        stato_colori);
        } else if (stato == 5) {
            caricamento_dis(x_caricamento, h_caricamento, tempo, screenWidth, screenHeight, 6, stato);
            v = 9;
            vb1 = 7;
            vb2 = 7;
            h = 200;
        } else if (stato == 6) {
            dis_stato_6(stato, gioco, p1, p2, x, y, raggio, bx1, bx2, by1, by2, l, h, screenWidth, screenHeight, colori,
                        stato_colori);
        } else if (stato == 7) {
            caricamento_dis(x_caricamento, h_caricamento, tempo, screenWidth, screenHeight, 8, stato);
            v = 11;
            vb1 = 9;
            vb2 = 9;
            h = 180;
        } else if (stato == 8) {
            dis_stato_4(stato, gioco, p1, p2, x, y, raggio, bx1, bx2, by1, by2, l, h, screenWidth, screenHeight, colori,
                        stato_colori);
        } else if (stato == 9) {
            caricamento_dis(x_caricamento, h_caricamento, tempo, screenWidth, screenHeight, 10, stato);
            v = 11;
            vb1 = 9;
            vb2 = 9;
            h = 180;
        } else if (stato == 10) {
            dis_stato_6(stato, gioco, p1, p2, x, y, raggio, bx1, bx2, by1, by2, l, h, screenWidth, screenHeight, colori,
                        stato_colori);
        } else if (stato == 11) {
            caricamento_dis(x_caricamento, h_caricamento, tempo, screenWidth, screenHeight, 12, stato);
            v = 14;
            vb1 = 10;
            vb2 = 10;
            h = 160;
            raggio = 10;
        } else if (stato == 12) {
            dis_stato_4(stato, gioco, p1, p2, x, y, raggio, bx1, bx2, by1, by2, l, h, screenWidth, screenHeight, colori,
                        stato_colori);
        } else if (stato == 13){
            caricamento_dis(x_caricamento, h_caricamento, tempo, screenWidth, screenHeight, 14, stato);
            v = 14;
            vb1 = 10;
            vb2 = 10;
            h = 160;
            raggio = 10;
        } else if (stato == 14) {
            dis_stato_6(stato, gioco, p1, p2, x, y, raggio, bx1, bx2, by1, by2, l, h, screenWidth, screenHeight, colori, stato_colori);
        } else if (stato == 20){
            stato_0(screenWidth, screenHeight);
            stato = 0;
        } else if (stato == 21) {
            dis_colori0(screenWidth, screenHeight);
        } else if (stato == 22) {
            dis_colori(screenWidth, screenHeight,colori);
        }
        if (stato == 25)
            caricamento_dis(x_caricamento, h_caricamento, tempo, screenWidth, screenHeight, 0, stato);
        ClearBackground(BLACK);


        EndDrawing();
    }

    CloseWindow();
    return 0;
}


