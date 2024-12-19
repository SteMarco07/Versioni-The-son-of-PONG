#include "include/raylib.h"
#include <iostream>
#include <vector>

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

void pbx1(std::vector<float> &barretta, std::vector<float> velocita, float l, int screenWidth) {
    if (IsKeyDown(KEY_A) && barretta[0] > 0) {
        barretta[0] -= velocita[3];
    } else if (IsKeyDown(KEY_D) && barretta[0] + l < screenWidth/3) {
        barretta[0] += velocita[3];
    }
}

void pbx2(std::vector<float> &barretta, std::vector<float> velocita, float l, int screenWidth) {
    if (IsKeyDown(KEY_LEFT) && barretta[2] > screenWidth*2/3 + l) {
        barretta[2] -= velocita[4];
    } else if (IsKeyDown(KEY_RIGHT) && barretta[2] + l < screenWidth + l) {
        barretta[2] += velocita[4];
    }
}

void pby1(std::vector<float> &barretta, std::vector<float> velocita, float h, int screenHeight) {
    if (IsKeyDown(KEY_W) && barretta[1] > 0) {
        barretta[1] -= velocita[3];
    } else if (IsKeyDown(KEY_S) && barretta[1] + h < screenHeight) {
        barretta[1] += velocita[3];
    }
}

void pby2(std::vector<float> &barretta, std::vector<float> velocita, float h, int screenHeight) {
    if (IsKeyDown(KEY_UP) && barretta[3] > 0) {
        barretta[3] -= velocita[4];
    } else if (IsKeyDown(KEY_DOWN) && barretta[3] + h < screenHeight) {
        barretta[3] += velocita[4];
    }
}

void py( std::vector<float> &pallina, int raggio, std::vector<float> &velocita, int screenHeight){
    if ( pallina[1] - raggio <= 0 ) {
        velocita[2] = abs(velocita[2]);
    } else if (pallina[1] + raggio >= screenHeight) {
        velocita[2] = -velocita[2];
    }
    pallina[1] += velocita[2];
}

void reset_v (std::vector<float> &velocita, float incremento){
    if (velocita[2] > 0) {
        velocita[2] = velocita[0] + incremento;
    } else {
        velocita[2] = -velocita[0] - incremento;
    }
}

void px( std::vector<float> &pallina, int raggio, std::vector<float> &velocita, std::vector<float> barretta, float h, float l, bool  &rimbalzo,float incremento){

    if  (CheckCollisionCircleRec ({pallina[0], pallina[1]}, raggio, {barretta[0], barretta[1], l, h}) && rimbalzo) {
        velocita[1] = abs(velocita[0]) + incremento;
        rimbalzo = false;
        pallina[0] += 10;
        reset_v( velocita, incremento);
        velocita[2] *= (pallina[1] - (barretta[1]+h/2))/(h/2);

    } else if (CheckCollisionCircleRec({pallina[0], pallina[1]}, raggio, {barretta[2]-l, barretta[3], l, h}) && !rimbalzo) {
        velocita[1] = -velocita[0] - incremento;
        rimbalzo = true;
        pallina[0] -= 10;
        reset_v( velocita, incremento);
        velocita[2] *= (pallina[1] - (barretta[3]+h/2))/(h/2);
    }
    pallina[0] += velocita[1];
}

void vi_X (std::vector<float> &velocita){
    if (GetRandomValue(1,2) == 1){
        velocita[1] = -velocita[0];
    } else {
        velocita[1] = velocita[0];
    }
}

void vi_y (std::vector<float> &velocita){
    if (GetRandomValue(1,2) == 1){
        velocita[2] = -velocita[0];
    } else {
        velocita[2] = velocita[0];
    }
}

void dis_punteggio (int p, float pos) {
    std::string punteggio;
    punteggio = std::to_string(p);
    DrawText(punteggio.c_str(), pos, 30, 40, WHITE);

}

void partenza (int &gioco, int screenHeight, int screenWidth, std::vector<int> punteggio, int &stato) {
    if (gioco == 2 && punteggio[1] != 10) {
        DrawText("Il giocatore 2 ha fatto punto", screenWidth/2.7, screenHeight/2 - 25, 40, WHITE);
        DrawText("Premere spazio per continuare", screenWidth/2.7, screenHeight/2 + 25, 40, WHITE);
    } else  if (gioco == 3 && punteggio[0] != 10) {
        DrawText("Il giocatore 1 ha fatto punto", screenWidth/2.7, screenHeight/2 - 25, 40, WHITE);
        DrawText("Premere spazio per continuare", screenWidth/2.7, screenHeight/2 + 25, 40, WHITE);
    } else if (gioco == 0) {
        DrawText("Premi spazio per iniziare", screenWidth/2.8, screenHeight/2, 40, WHITE);
    } else if ( punteggio[0] == 10 || punteggio[1] == 10 ) {
        if (punteggio[0] == 10) {
            DrawText("Il giocatore 1 ha vinto!", screenWidth/2.7, screenHeight/2 - 20, 40, WHITE);
        } else if (punteggio[1] == 10) {
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

void inc_v (std::vector<float> &velocita) {
    if (velocita[1] > 0) {
        velocita[1] += 0.001;
    } else {
        velocita[1] -= 0.001;
    }
    if (velocita[2] > 0) {
        velocita[2] += 0.001;
    } else {
        velocita[2] -= 0.001;
    }
}

void repet (int &gioco, int &tempo, float &h, float h_iniz) {
    gioco = 4;
    h = h_iniz;
    tempo = 0;
}

void caricamento_dis (std::vector<float> &caricamento, int &tempo, int screenWidth, int screenHeight, int temp, int &stato) {
    caricamento[0] += GetRandomValue(7, 25);
    if (caricamento[0] >= screenWidth) {
        stato = temp;
        caricamento[0] = 0;
    }
    DrawRectangle(0, screenHeight-caricamento[1], caricamento[0], caricamento[1], WHITE);
    tempo++;
    if (tempo < 15) {
        DrawText("Caricamento.", screenWidth*0.05, screenHeight-2*caricamento[1], 40, WHITE);
    } else if (tempo < 30) {
        DrawText("Caricamento..", screenWidth*0.05, screenHeight-2*caricamento[1], 40, WHITE);
    } else if (tempo < 45) {
        DrawText("Caricamento...", screenWidth*0.05, screenHeight-2*caricamento[1], 40, WHITE);
    } else {
        tempo = 0;
    }
}

void stato_0 (int screenWidth, int screenHeight){
    DrawText("PONG", screenWidth*0.45, screenHeight/3, 100, WHITE);
    DrawText("Premi M per scegliere la modalita' della partita", screenWidth*0.02, screenHeight*0.70, 50, WHITE);
    DrawText("Premi I per vedere le impostazioni", screenWidth*0.02, screenHeight*0.80, 50, WHITE);
}

void stato_4 (int &gioco, std::vector <int> &punteggio, std::vector<float> &pallina, int raggio, std::vector<float> &velocita, std::vector<float> &barretta, float &h_iniz, float &h, float &l, int &tempo, int screenWidth, int screenHeight, bool &rimbalzo, float &incremento) {
    if (gioco == 0) {
        punteggio = {0,0};
        tempo = 0;
        barretta = {50, screenHeight / 2 - h / 2, static_cast<float>(screenWidth - 50), screenHeight / 2 - h / 2};
        h = h_iniz;
        if (IsKeyPressed(KEY_SPACE)) {
            gioco = 4;
            vi_X(velocita);
            vi_y(velocita);
            if (velocita[1] < 0) {
                rimbalzo = true;
            } else {
                rimbalzo = false;
            }
        }
    } else if (gioco > 1) {

        py(pallina, raggio, velocita, screenHeight);
        px(pallina, raggio,velocita, barretta, h, l, rimbalzo, incremento);
        pby1(barretta, velocita, h, screenHeight);
        pby2(barretta, velocita, h, screenHeight);

        if (pallina[0] <= 0 || pallina[0] >= screenWidth) {
            if (pallina[0] <= 0) {
                punteggio[1]++;
                gioco = 2;
            } else if (pallina[0] >= screenWidth) {
                punteggio[0]++;
                gioco = 3;
            }
            pallina[1] = GetRandomValue(raggio, screenHeight - raggio);
            pallina[0] = screenWidth / 2;
            velocita[1] = 0;
            velocita[2] = 0;
        }
        if (IsKeyDown(KEY_SPACE) && gioco == 2) {
            vi_y(velocita);
            velocita[1] = velocita[0];
            repet(gioco, tempo, h, h_iniz);
            rimbalzo = false;
        } else if (IsKeyDown(KEY_SPACE) && gioco == 3) {
            vi_y(velocita);
            velocita[1] = -velocita[0];
            repet(gioco, tempo, h, h_iniz);
            rimbalzo = true;
        }

        tempo++;
        if (tempo > 2000 && gioco != 2 && gioco != 3) {
            inc_v(velocita);
            incremento += 0.001;
            if (tempo > 3000 && h > 30) {
                h -= 0.05;
            }
        }
    }
}

void dis_stato_4 ( int &stato, int &gioco, std::vector<int> punteggio, std::vector<float> pallina, float raggio, std::vector<float> barretta, float l, float h,
                   int screenWidth, int screenHeight, int colore, int stato_colori) {
    partenza(gioco, screenHeight, screenWidth, punteggio, stato);

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
    DrawCircle(pallina[0], pallina[1], raggio, a);
    DrawRectangle(barretta[0], barretta[1] , l, h, b);
    DrawRectangle(barretta[2]-l, barretta[3] , l, h, b);
    dis_punteggio(punteggio[0], screenWidth / 4);
    dis_punteggio(punteggio[1], screenWidth  * 0.75);
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


void dis_stato_6 (int &stato,int &gioco, std::vector<int> punteggio, std::vector<float> pallina, float raggio, std::vector<float> barretta, float l, float h,
                  float screenWidth, float screenHeight, int colori, int stato_colori) {
    dis_stato_4(stato, gioco, punteggio, pallina, raggio, barretta, l, h, screenWidth, screenHeight, colori, stato_colori);
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

void stato_6 (int &gioco, std::vector<int> &punteggio, std::vector<float> &pallina, float raggio, std::vector<float> &velocita, std::vector<float> &barretta,
              float &h_iniz, float &h, float &l, int &tempo, int screenWidth, int screenHeight, bool &rimbalzo_x, float &incremento) {
    stato_4(gioco, punteggio, pallina, raggio, velocita, barretta, h_iniz, h, l, tempo,
            screenWidth, screenHeight, rimbalzo_x, incremento);

    if (gioco > 1 ) {
        pbx1(barretta, velocita, l, screenWidth);
        pbx2(barretta, velocita, l, screenWidth);
    }
}

void difficolta(int difficolta, std::vector<float> &velocita, float &h_iniz, int & raggio) {
    if (difficolta == 0) {
        velocita[0] = 9;
        velocita[3] = 7;
        velocita[4] = 7;
        h_iniz = 200;
        raggio = 15;
    } else if (difficolta == 1) {
        velocita[0] = 11;
        velocita[3] = 9;
        velocita[4] = 9;
        h_iniz = 180;
        raggio = 13;
    } else {
        velocita[0] = 14;
        velocita[3] = 10;
        velocita[4] = 10;
        h_iniz = 160;
        raggio = 10;
    }
}


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1800;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "pong");

    SetTargetFPS(60);

    int raggio = 15, gioco = 0, tempo = 0, stato = 0;
    float h_iniz = 200, h = h_iniz, l = 15, incremento = 0;
    bool rimbalzo;
    int  stato_colori, colori=0;


    std::vector<int> punteggio = {0,0};                                                                                                   //p1,p2

    std::vector<float> pallina = {screenWidth / 2.0,  static_cast<float>(GetRandomValue(raggio, screenHeight - raggio))};       //x,y

    std::vector<float> velocita = {9,0,0, 7, 7};                                                                                          //v, vx, vy, vb1, vb2

    std::vector<float> caricamento = { 0, screenHeight/20.0};                                                                             //x_caricamento, h_caricamento

    std::vector<float>barretta = {50,  screenHeight / 2 - h / 2, screenWidth - 50, screenHeight / 2 - h / 2};                             //bx1, by1, bx2, by2


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
            stato_4 (gioco, punteggio, pallina, raggio, velocita, barretta, h_iniz, h, l, tempo, screenWidth, screenHeight, rimbalzo, incremento);
        } else if (stato == 6) {

            stato_6(gioco, punteggio, pallina, raggio, velocita, barretta, h_iniz, h, l, tempo, screenWidth, screenHeight, rimbalzo, incremento);

        } else if (stato == 8) {
            stato_4(gioco, punteggio, pallina, raggio, velocita, barretta, h_iniz, h, l, tempo, screenWidth, screenHeight, rimbalzo, incremento);
        } else if (stato == 10) {
            stato_6(gioco, punteggio, pallina, raggio, velocita, barretta, h_iniz, h, l, tempo, screenWidth, screenHeight, rimbalzo, incremento);
        } else if (stato == 12) {
            stato_4(gioco, punteggio, pallina, raggio, velocita, barretta, h_iniz, h, l, tempo, screenWidth, screenHeight, rimbalzo, incremento);
        } else if (stato == 14) {
            stato_6(gioco, punteggio, pallina, raggio, velocita, barretta, h_iniz, h, l, tempo, screenWidth, screenHeight, rimbalzo, incremento);
        } else if (stato == 21) {
            dis_colori0(screenWidth, screenHeight);
            if (IsKeyDown(KEY_A)) {
                stato_colori = 1;
                stato = 22;
            } else if (IsKeyDown(KEY_B)) {
                stato_colori = 2;
                stato = 22;
            } else if (IsKeyDown(KEY_Q)) {
                stato = 25;
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
            pallina = {screenWidth / 2.0,  static_cast<float>(GetRandomValue(raggio, screenHeight - raggio))};
        }

        BeginDrawing();

        if (stato == 0) {
            stato_0(screenWidth, screenHeight);
        } else if (stato == 1) {
            caricamento_dis(caricamento, tempo, screenWidth, screenHeight, 2, stato);
        } else if (stato == 2) {
            dis_stato_2(screenWidth, screenHeight);
        } else if (stato == 3) {
            caricamento_dis(caricamento, tempo, screenWidth, screenHeight, 4, stato);
            difficolta(0, velocita, h_iniz,raggio);
        } else if (stato == 4) {
            dis_stato_4(stato, gioco, punteggio, pallina, raggio, barretta, l, h, screenWidth, screenHeight, colori,
                        stato_colori);
        } else if (stato == 5) {
            caricamento_dis(caricamento, tempo, screenWidth, screenHeight, 6, stato);
            difficolta(0, velocita, h_iniz,raggio);
        } else if (stato == 6) {
            dis_stato_6(stato, gioco, punteggio, pallina, raggio, barretta, l, h, screenWidth, screenHeight, colori,
                        stato_colori);
        } else if (stato == 7) {
            caricamento_dis(caricamento, tempo, screenWidth, screenHeight, 8, stato);
            difficolta(1, velocita, h_iniz,raggio);
        } else if (stato == 8) {
            dis_stato_4(stato, gioco, punteggio, pallina, raggio, barretta, l, h, screenWidth, screenHeight, colori,
                        stato_colori);
        } else if (stato == 9) {
            caricamento_dis(caricamento, tempo, screenWidth, screenHeight, 10, stato);
            difficolta(1, velocita, h_iniz,raggio);
        } else if (stato == 10) {
            dis_stato_6(stato, gioco, punteggio, pallina, raggio, barretta, l, h, screenWidth, screenHeight, colori,
                        stato_colori);
        } else if (stato == 11) {
            caricamento_dis(caricamento, tempo, screenWidth, screenHeight, 12, stato);
            difficolta(2, velocita, h_iniz,raggio);
        } else if (stato == 12) {
            dis_stato_4(stato, gioco, punteggio, pallina, raggio, barretta, l, h, screenWidth, screenHeight, colori,
                        stato_colori);
        } else if (stato == 13){
            caricamento_dis(caricamento, tempo, screenWidth, screenHeight, 14, stato);
            difficolta(2, velocita, h_iniz,raggio);
        } else if (stato == 14) {
            dis_stato_6(stato, gioco, punteggio, pallina, raggio, barretta, l, h, screenWidth, screenHeight, colori, stato_colori);
        } else if (stato == 20){
            stato_0(screenWidth, screenHeight);
            stato = 0;
        } else if (stato == 21) {
            dis_colori0(screenWidth, screenHeight);
        } else if (stato == 22) {
            dis_colori(screenWidth, screenHeight,colori);
        }
        if (stato == 25)
            caricamento_dis(caricamento, tempo, screenWidth, screenHeight, 0, stato);
        ClearBackground(BLACK);


        EndDrawing();
    }

    CloseWindow();
    return 0;
}