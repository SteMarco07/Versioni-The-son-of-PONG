#include "include/raylib.h"
#include <iostream>
#include <vector>

void colorare (int &stato, int elemento_da_colorare, std::vector<Color> &colore, std::vector<int> &scelta_elemento, std::vector<Color> colori, int numero_colore) {
    stato = 21;
    scelta_elemento.at(elemento_da_colorare) = elemento_da_colorare;
    colore.at(elemento_da_colorare) = colori.at(numero_colore);
}

void dis_colori0 (std::vector<Color> colore, std::vector<int> scelta_elemento, const std::vector<std::vector<std::string>> &stringhe, const std::vector<float> &dim_stringhe){
    float x = GetScreenWidth() * 0.02, y = GetScreenHeight();
    DrawText(stringhe.at(21).at(0).c_str(), (GetScreenWidth() - MeasureText(stringhe.at(21).at(0).c_str(), dim_stringhe.at(1)))/2, GetScreenHeight()*0.02, dim_stringhe.at(1),colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(21).at(1).c_str(), x, y/2-180, dim_stringhe.at(2),colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(21).at(2).c_str(), x, y/2 - 80, dim_stringhe.at(2),colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(21).at(3).c_str(), x, y/2 + 20, dim_stringhe.at(2),colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(21).at(4).c_str(), x, y/2+ 120, dim_stringhe.at(2),colore.at(scelta_elemento.at(2)));
}

void dis_colori( std::vector<Color> colori, std::vector<Color> colore, std::vector<int> scelta_elemento, std::vector<Color> colore_temp, int elemento_da_colorare, const std::vector<std::vector<std::string>> &stringhe, const std::vector<float> &dim_stringhe){
    int a = 0;
    int b = 0;
    float x = GetScreenWidth(), y = GetScreenHeight();
    std::string numero;
    DrawText( stringhe.at(22).at(0).c_str(), (x - MeasureText(stringhe.at(22).at(0).c_str(),dim_stringhe.at(1)))/2,y*0.02,dim_stringhe.at(1),colore.at(scelta_elemento.at(2)));
    for (int i = 0; i <= colori.size(); ++i) {
        if (i >= 4)
            b = GetScreenHeight() / 2 - 50;

        if (i==4)
            a=0;
        DrawRectangle(x / 18 + a, GetScreenHeight() / 9 + 100 + b, x / 7.2, y / 3.6, DARKGRAY);
        if (i < colori.size()) {
            DrawRectangle(x / 18 + 5 + a, y / 9 + 105 + b, x / 7.2-10, y / 3.6-10, colori.at(i));
        } else {
            DrawRectangle(x / 18 + 5 + a, y / 9 + 105 + b, x / 7.2-10, y / 3.6-10, colore_temp.at(elemento_da_colorare));
        }
        a += x / 4;
    }
    DrawRectangle(x / 18 + a, y / 9 + 100 + b, x / 7.2, y / 3.6, DARKGRAY);
    a=0;
    b=0;
    DrawText("1",x / 18 + 20,y / 9 + 105, 100, WHITE);
    for (int i = 2 ; i <= colori.size() + 1 ; i++ ){
        a += x/4;
        if ( i == 5){
            a=0;
            b=y / 2 - 50;
        }
        numero = std::to_string(i);
        DrawText(numero.c_str(),x / 18 + 20 + a,y / 9 + 105 + b, 100, BLACK);
    }

}

void selezione_colore (int &stato, int &elemento_da_colorare, std::vector<Color> &colore, std::vector<int> &scelta_elemento, std::vector<Color> colori, int &stato_successivo) {
    int a = 0, b = 0;
    int lunghezza = GetScreenWidth(), altezza = GetScreenHeight();
    float lato = lunghezza / 7.2-10, x, y;
    for (int i = 0; i <= colori.size(); ++i) {
        if (i >= 4)
            b = GetScreenHeight() / 2 - 50;

        if (i==4)
            a=0;

        x = lunghezza / 18 + 5 + a, y = altezza / 9 + 105 + b;
        if (i < colori.size()) {
            if (CheckCollisionPointRec(GetMousePosition(), {x, y, lato, lato}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                colorare(stato, elemento_da_colorare, colore, scelta_elemento, colori, i);
            }
        } else{
            if (CheckCollisionPointRec(GetMousePosition(), {x, y, lato, lato}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                stato = 23;
            }
        }

        a += lunghezza / 4;
    }
    if (IsKeyDown(KEY_R) && IsKeyDown(KEY_G) && IsKeyDown(KEY_B)) {
        if (elemento_da_colorare == 3) {
            scelta_elemento.at(elemento_da_colorare) = 5;
        } else scelta_elemento.at(elemento_da_colorare) = 4;
        stato = 21;
    }
}

void pbx1(std::vector<float> &barretta, std::vector<float> velocita, float l) {
    int lunghezza = GetScreenWidth();
    if (IsKeyDown(KEY_A) && barretta.at(0) > 0) {
        barretta.at(0) -= velocita.at(3);
    } else if (IsKeyDown(KEY_D) && barretta.at(0) + l < lunghezza/3) {
        barretta.at(0) += velocita.at(3);
    }
}

void pbx2(std::vector<float> &barretta, std::vector<float> velocita, float l) {
    int lunghezza = GetScreenWidth();
    if (IsKeyDown(KEY_LEFT) && barretta.at(2) > lunghezza*2/3 + l) {
        barretta.at(2) -= velocita.at(4);
    } else if (IsKeyDown(KEY_RIGHT) && barretta.at(2) + l < lunghezza + l) {
        barretta.at(2) += velocita.at(4);
    }
}

void pby1(std::vector<float> &barretta, std::vector<float> velocita, float h) {
    if (IsKeyDown(KEY_W) && barretta.at(1) > 0) {
        barretta.at(1) -= velocita.at(3);
    } else if (IsKeyDown(KEY_S) && barretta.at(1) + h < GetScreenHeight()) {
        barretta.at(1) += velocita.at(3);
    }
}

void pby2(std::vector<float> &barretta, std::vector<float> velocita, float h) {
    if (IsKeyDown(KEY_UP) && barretta.at(3) > 0) {
        barretta.at(3) -= velocita.at(4);
    } else if (IsKeyDown(KEY_DOWN) && barretta.at(3) + h < GetScreenHeight()) {
        barretta.at(3) += velocita.at(4);
    }
}

void py( std::vector<float> &pallina, int raggio, std::vector<float> &velocita){
    if ( pallina.at(1) - raggio <= 0 ) {
        velocita.at(2) = abs(velocita.at(2));
    } else if (pallina.at(1) + raggio >= GetScreenHeight()) {
        velocita.at(2) = -velocita.at(2);
    }
    pallina.at(1) += velocita.at(2);
}

void reset_v (std::vector<float> &velocita, float incremento){
    if (velocita.at(2) > 0) {
        velocita.at(2) = velocita.at(0) + incremento;
    } else {
        velocita.at(2) = -velocita.at(0) - incremento;
    }
}

void px( std::vector<float> &pallina, int raggio, std::vector<float> &velocita, std::vector<float> barretta, float h, float l, bool  &rimbalzo,float incremento){

    if  (CheckCollisionCircleRec ({pallina.at(0), pallina.at(1)}, raggio, {barretta.at(0), barretta.at(1), l, h}) && rimbalzo) {
        velocita.at(1) = abs(velocita.at(0)) + incremento;
        rimbalzo = false;
        pallina.at(0) += 10;
        reset_v( velocita, incremento);
        velocita.at(2) *= (pallina.at(1) - (barretta.at(1)+h/2))/(h/2);

    } else if (CheckCollisionCircleRec({pallina.at(0), pallina.at(1)}, raggio, {barretta.at(2) - l, barretta.at(3), l, h}) && !rimbalzo) {
        velocita.at(1) = -velocita.at(0) - incremento;
        rimbalzo = true;
        pallina.at(0) -= 10;
        reset_v( velocita, incremento);
        velocita.at(2) *= (pallina.at(1) - (barretta.at(3)+h/2))/(h/2);
    }
    pallina.at(0) += velocita.at(1);
}

void vi_X (std::vector<float> &velocita){
    if (GetRandomValue(1,2) == 1){
        velocita.at(1) = -velocita.at(0);
    } else {
        velocita.at(1) = velocita.at(0);
    }
}

void vi_y (std::vector<float> &velocita){
    if (GetRandomValue(1,2) == 1){
        velocita.at(2) = -velocita.at(0);
    } else {
        velocita.at(2) = velocita.at(0);
    }
}

void dis_punteggio (int p, float pos, std::vector<Color> colore, std::vector<int> scelta_elemento) {
    std::string punteggio;
    punteggio = std::to_string(p);
    DrawText(punteggio.c_str(), pos, 30, 40, colore.at(scelta_elemento.at(2)));

}

void partenza (int &gioco, std::vector<int> punteggio, int &stato, int &stato_successivo, std::vector<Color> colore, std::vector<int>scelta_elemento, const std::vector<std::vector<std::string>> &stringhe, const std::vector<float> &dim_stringhe) {
    int x = GetScreenWidth(), y = GetScreenHeight();

    if (gioco == 2 && punteggio.at(0) != 10) {
        std::string frase = stringhe.at(25).at(3) + stringhe.at(3).at(4);
        DrawText(frase.c_str(), (x - MeasureText(frase.c_str(), dim_stringhe.at(2)))/2, y/2 - 35, dim_stringhe.at(2), colore.at(scelta_elemento.at(2)));
        DrawText(stringhe.at(3).at(1).c_str(), (x - MeasureText(stringhe.at(3).at(1).c_str(), dim_stringhe.at(3)))/2, y/2 + 35, dim_stringhe.at(3), colore.at(scelta_elemento.at(2)));
    } else  if (gioco == 3 && punteggio.at(1) != 10) {
        std::string frase = stringhe.at(25).at(4) + stringhe.at(3).at(4);
        DrawText(frase.c_str(), (x - MeasureText(frase.c_str(), dim_stringhe.at(2)))/2, y/2 - 35, dim_stringhe.at(2), colore.at(scelta_elemento.at(2)));
        DrawText(stringhe.at(3).at(1).c_str(), (x - MeasureText(stringhe.at(3).at(1).c_str(), dim_stringhe.at(3)))/2, y/2 + 35, dim_stringhe.at(3), colore.at(scelta_elemento.at(2)));
    } else if (gioco == 0) {
        DrawText(stringhe.at(3).at(0).c_str(), (x - MeasureText(stringhe.at(3).at(0).c_str(), dim_stringhe.at(2)))/2, y/2, dim_stringhe.at(2), colore.at(scelta_elemento.at(2)));
    } else if ( punteggio.at(0) == 10 || punteggio.at(1) == 10 ) {
        if (punteggio.at(0) == 10) {
            std::string frase = stringhe.at(25).at(3) + stringhe.at(3).at(5);
            DrawText(frase.c_str(), (x - MeasureText(frase.c_str(), dim_stringhe.at(2)))/2, y/2 - 35, dim_stringhe.at(2), colore.at(scelta_elemento.at(2)));
        } else if (punteggio.at(1) == 10) {
            std::string frase = stringhe.at(25).at(4) + stringhe.at(3).at(5);
            DrawText(frase.c_str(), (x - MeasureText(frase.c_str(), dim_stringhe.at(2)))/2, y/2 - 35, dim_stringhe.at(2), colore.at(scelta_elemento.at(2)));
        }
        DrawText(stringhe.at(3).at(2).c_str(), (x - MeasureText(stringhe.at(3).at(2).c_str(), dim_stringhe.at(3)))/2, y/2 - 35, dim_stringhe.at(3), colore.at(scelta_elemento.at(2)));
        DrawText(stringhe.at(3).at(3).c_str(), (x - MeasureText(stringhe.at(3).at(2).c_str(), dim_stringhe.at(3)))/2, y/2 + 35, dim_stringhe.at(3), colore.at(scelta_elemento.at(2)));
        if (IsKeyPressed(KEY_R)) {
            gioco = 0;
        }
        if (IsKeyPressed(KEY_U)) {
            stato = 1;
            stato_successivo = 0;
            gioco = 0;
        }
    }
}

void inc_v (std::vector<float> &velocita) {
    if (velocita.at(1) > 0) {
        velocita.at(1) += 0.01;
    } else {
        velocita.at(1) -= 0.01;
    }
    if (velocita.at(2) > 0) {
        velocita.at(2) += 0.01;
    } else {
        velocita.at(2) -= 0.01;
    }
}

void repet (int &gioco, int &tempo, float &h, float h_iniz) {
    gioco = 4;
    h = h_iniz;
    tempo = 0;
}

void dis_caricamento (std::vector<float> &caricamento, int &tempo, int temp, int &stato, std::vector<Color> colore, std::vector<int> scelta_elemento, const std::vector<std::vector<std::string>> &stringhe, const std::vector<float> &dim_stringhe) {
    int x = GetScreenWidth(), y = GetScreenHeight();
    caricamento.at(0) += GetRandomValue(7, 25);
    if (caricamento.at(0) >= x) {
        stato = temp;
        caricamento.at(0) = 0;
    }
    DrawRectangle(0, y-caricamento.at(1), caricamento.at(0), caricamento.at(1), colore.at(scelta_elemento.at(1)));
    if (tempo < 15) {
        DrawText(stringhe.at(1).at(0).c_str(), x*0.05, y-2*caricamento.at(1), dim_stringhe.at(3), colore.at(scelta_elemento.at(2)));
    } else if (tempo < 30) {
        DrawText(stringhe.at(1).at(1).c_str(), x*0.05, y-2*caricamento.at(1), dim_stringhe.at(3), colore.at(scelta_elemento.at(2)));
    } else if (tempo < 45) {
        DrawText(stringhe.at(1).at(2).c_str(), x*0.05, y-2*caricamento.at(1), dim_stringhe.at(3), colore.at(scelta_elemento.at(2)));
    }
}

void dis_stato_0 (std::vector<Color> colore, std::vector<int> scelta_elemento, const std::vector<std::vector<std::string>> &stringhe, const std::vector<float> &dim_stringhe){
    int x = GetScreenWidth(), y = GetScreenHeight();
    DrawText(stringhe.at(0).at(0).c_str(), x*0.40, y*0.02, dim_stringhe.at(0), colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(0).at(1).c_str(), x*0.02, y*0.70, dim_stringhe.at(2), colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(0).at(2).c_str(), x*0.02, y*0.80, dim_stringhe.at(2), colore.at(scelta_elemento.at(2)));
}

void stato_0 (int &stato, int &stato_successivo, const std::vector<std::vector<std::string>> &stringhe, std::vector<float> dim_stringhe){
    int altezza = GetScreenHeight();
    float x = GetScreenWidth() * 0.02, y1 = altezza*0.70, y2 = altezza*0.80;
    if (CheckCollisionPointRec(GetMousePosition(), {x, y1, (float)MeasureText(stringhe.at(0).at(1).c_str(), dim_stringhe.at(2)), dim_stringhe.at(2)}) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        stato = 1;
        stato_successivo = 2;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x , y2, (float)MeasureText(stringhe.at(0).at(1).c_str(), dim_stringhe.at(2)), dim_stringhe.at(2)}) &&
               IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        stato = 1;
        stato_successivo = 20;
    }
}

void stato_3 (int &gioco, std::vector <int> &punteggio, std::vector<float> &pallina, int raggio, std::vector<float> &velocita, std::vector<float> &barretta, float &h_iniz, float &h, float &l, int &tempo, bool &rimbalzo, float &incremento) {
    int lunghezza = GetScreenWidth(), altezza = GetScreenHeight();
    if (gioco == 0) {
        punteggio = {0,0};
        tempo = 0;
        barretta = {50, altezza / 2 - h / 2, 0, altezza / 2 - h / 2};
        barretta.at(2) = lunghezza - 50;
        h = h_iniz;
        if (IsKeyPressed(KEY_SPACE)) {
            gioco = 4;
            vi_X(velocita);
            vi_y(velocita);
            if (velocita.at(1) < 0) {
                rimbalzo = true;
            } else {
                rimbalzo = false;
            }
        }
    } else if (gioco > 1) {

        py(pallina, raggio, velocita);
        px(pallina, raggio,velocita, barretta, h, l, rimbalzo, incremento);
        pby1(barretta, velocita, h);
        pby2(barretta, velocita, h);

        if (pallina.at(0) <= 0 || pallina.at(0) >= lunghezza) {
            if (pallina.at(0) <= 0) {
                punteggio.at(1)++;
                gioco = 3;
            } else if (pallina.at(0) >= lunghezza) {
                punteggio.at(0)++;
                gioco = 2;
            }
            pallina.at(1) = GetRandomValue(raggio, altezza - raggio);
            pallina.at(0) = lunghezza / 2;
            velocita.at(1) = 0;
            velocita.at(2) = 0;
        }
        if (IsKeyPressed(KEY_SPACE) && gioco == 2) {
            vi_y(velocita);
            velocita.at(1) = velocita.at(0);
            repet(gioco, tempo, h, h_iniz);
            rimbalzo = false;
        } else if (IsKeyPressed(KEY_SPACE) && gioco == 3) {
            vi_y(velocita);
            velocita.at(1) = -velocita.at(0);
            repet(gioco, tempo, h, h_iniz);
            rimbalzo = true;
        }

        tempo++;
        if (tempo > 1500 && gioco != 2 && gioco != 3) {
            inc_v(velocita);
            incremento += 0.01;
            if (tempo > 2000 && h > 30) {
                h -= 0.05;
            }
        }
    }
}

void dis_stato_3 ( int &stato, int &stato_successivo, int &gioco, std::vector<int> punteggio, std::vector<float> pallina, float raggio, std::vector<float> barretta, float l, float h, std::vector<Color> colore, std::vector<int> scelta_elemento, const std::vector<std::vector<std::string>> &stringhe, const std::vector<float> &dim_stringhe) {
    int lunghezza = GetScreenWidth(), altezza = GetScreenHeight();
    partenza(gioco, punteggio, stato, stato_successivo, colore, scelta_elemento, stringhe, dim_stringhe);
    DrawCircle(pallina.at(0), pallina.at(1), raggio, colore.at(scelta_elemento.at(0)));
    DrawRectangle(barretta.at(0), barretta.at(1) , l, h, colore.at(scelta_elemento.at(1)));
    DrawRectangle(barretta.at(2) - l, barretta.at(3) , l, h, colore.at(scelta_elemento.at(1)));
    dis_punteggio(punteggio.at(0), lunghezza / 4, colore, scelta_elemento);
    dis_punteggio(punteggio.at(1), lunghezza  * 0.75, colore, scelta_elemento);
    if (!(gioco == 0 || gioco == 2 || gioco == 3)) {
        for (int i = 20; i <= altezza; i += 100) {
            DrawRectangle((lunghezza/2)-3,i, 6, 40, colore.at(scelta_elemento.at(1)));
        }
    }


}

void dis_stato_2(std::vector<Color> colore, std::vector<int> scelta_elemento, const std::vector<std::vector<std::string>> &stringhe, const std::vector<float> &dim_stringhe) {
    int x = GetScreenWidth(), y = GetScreenHeight();
    DrawText(stringhe.at(2).at(0).c_str(), (x - MeasureText(stringhe.at(2).at(0).c_str(), dim_stringhe.at(1)))/2, y*0.02, dim_stringhe.at(1),colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(2).at(1).c_str(), x*0.02, y/2 - 280, dim_stringhe.at(2),colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(2).at(2).c_str(), x*0.02, y/2 - 180, dim_stringhe.at(2),colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(2).at(3).c_str(), x*0.02, y/2 - 80, dim_stringhe.at(2),colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(2).at(4).c_str(), x*0.02, y/2 + 20, dim_stringhe.at(2),colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(2).at(5).c_str(), x*0.02, y/2 + 120, dim_stringhe.at(2),colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(2).at(6).c_str(), x*0.02, y/2 + 220, dim_stringhe.at(2),colore.at(scelta_elemento.at(2)));
}


void dis_stato_4 (int &stato, int &stato_successivo,int &gioco, std::vector<int> punteggio, std::vector<float> pallina, float raggio, std::vector<float> barretta, float l, float h, std::vector<Color> colore, std::vector<int> scelta_elemento, const std::vector<std::vector<std::string>> &stringhe, const std::vector<float> &dim_stringhe) {
    dis_stato_3(stato, stato_successivo, gioco, punteggio, pallina, raggio, barretta, l, h, colore, scelta_elemento, stringhe, dim_stringhe);
    int lunghezza = GetScreenWidth(), altezza = GetScreenHeight();
    if (!(gioco == 0 || gioco == 2 || gioco == 3)) {
        for (int i = 0; i < altezza; i += 80) {
            DrawRectangle((lunghezza/3)-3,i, 6, 20, colore.at(scelta_elemento.at(1)));
        }
        for (int i = 0; i < altezza; i += 80) {
            DrawRectangle((lunghezza*2/3)-3,i, 6, 20, colore.at(scelta_elemento.at(1)));
        }
    }
}

void scelta_difficolta(int difficolta, std::vector<float> &velocita, float &h_iniz, int &raggio) {
    if (difficolta == 0) {
        velocita.at(0) = 9;
        velocita.at(3) = 7;
        velocita.at(4) = 7;
        h_iniz = 200;
        raggio = 15;
    } else if (difficolta == 1) {
        velocita.at(0) = 11;
        velocita.at(3) = 9;
        velocita.at(4) = 9;
        h_iniz = 180;
        raggio = 13;
    } else {
        velocita.at(0) = 15;
        velocita.at(3) = 11;
        velocita.at(4) = 11;
        h_iniz = 160;
        raggio = 10;
    }
}

void stato_2 (int &stato, float x, float y, int &stato_successivo, int &difficolta, const std::vector<std::vector<std::string>> &stringhe, const std::vector<float> &dim_stringhe) {
    if (CheckCollisionPointRec(GetMousePosition(), {x, y - 280, (float)MeasureText(stringhe.at(2).at(1).c_str(), dim_stringhe.at(2)), dim_stringhe.at(2)}) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        stato = 1;
        stato_successivo = 3;
        difficolta = 0;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x, y - 180, (float)MeasureText(stringhe.at(2).at(2).c_str(), dim_stringhe.at(2)), dim_stringhe.at(2)}) &&
               IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        stato = 1;
        stato_successivo = 4;
        difficolta = 0;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x, y - 80, (float)MeasureText(stringhe.at(2).at(3).c_str(), dim_stringhe.at(2)), dim_stringhe.at(2)}) &&
               IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        stato = 1;
        stato_successivo = 3;
        difficolta = 1;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x, y + 20, (float)MeasureText(stringhe.at(2).at(4).c_str(), dim_stringhe.at(2)), dim_stringhe.at(2)}) &&
               IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        stato = 1;
        stato_successivo = 4;
        difficolta = 1;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x, y + 120, (float)MeasureText(stringhe.at(2).at(5).c_str(), dim_stringhe.at(2)), dim_stringhe.at(2)}) &&
               IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        stato = 1;
        stato_successivo = 3;
        difficolta = 2;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x, y + 220, (float)MeasureText(stringhe.at(2).at(6).c_str(), dim_stringhe.at(2)), dim_stringhe.at(2)}) &&
               IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        stato = 1;
        stato_successivo = 4;
        difficolta = 2;
    }
}

void stato_4 (int &gioco, std::vector<int> &punteggio, std::vector<float> &pallina, float raggio, std::vector<float> &velocita, std::vector<float> &barretta,
              float &h_iniz, float &h, float &l, int &tempo, bool &rimbalzo_x, float &incremento) {
    stato_3(gioco, punteggio, pallina, raggio, velocita, barretta, h_iniz, h, l, tempo,rimbalzo_x, incremento);

    if (gioco > 1 ) {
        pbx1(barretta, velocita, l);
        pbx2(barretta, velocita, l);
    }
}



void scelta_elemento_colorare(std::vector<std::vector<std::string>> &stringhe, const std::vector<float> &dimensione,int &stato, int &elemento_da_colorare, std::vector<int> &scelta_elemento, bool &RGB_YES_NO, float x, float y){

    if (CheckCollisionPointRec(GetMousePosition(), {x, y - 180, 600, 60}) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        stato = 22;
        elemento_da_colorare = 0;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x, y - 80, 670, 60}) &&
               IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        stato = 22;
        elemento_da_colorare = 1;
    }else if (CheckCollisionPointRec(GetMousePosition(), {x, y + 20, 600, 60}) &&
              IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        stato = 22;
        elemento_da_colorare = 2;
    }else if (CheckCollisionPointRec(GetMousePosition(), {x, y + 120, 600, 60}) &&
              IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        stato = 22;
        elemento_da_colorare = 3;
    }
    if (IsKeyDown(KEY_R) && IsKeyDown(KEY_G) && IsKeyDown(KEY_B) && !IsKeyDown(KEY_N)&&!RGB_YES_NO) {
        scelta_elemento = {4, 4, 4, 5};
        RGB_YES_NO = true;
    } else if (IsKeyDown(KEY_R) && IsKeyDown(KEY_G) && IsKeyDown(KEY_B) && IsKeyDown(KEY_N)&&RGB_YES_NO) {
        scelta_elemento = {0, 1, 2, 3};
        RGB_YES_NO = false;
    }
}



void rgb (std::vector<unsigned char> &canali_colore, std::vector<Color> &colore, bool &cresci, Color &RGB, int punto_colore) {

    int velocita = 3;
    if (cresci) {
        if (canali_colore.at(0) < 250) { canali_colore.at(0) += velocita; }
        else if (canali_colore.at(1) < 250) { canali_colore.at(1) += velocita; }
        else if (canali_colore.at(2) < 250) { canali_colore.at(2) += velocita; } else {cresci = false;}
    }
    else {
        if (canali_colore.at(0) > 10) { canali_colore.at(0) -= velocita; }
        else if (canali_colore.at(1) > 10) { canali_colore.at(1) -= velocita; }
        else if (canali_colore.at(2) > 10) { canali_colore.at(2) -= velocita; } else { cresci =true;}
        }
    RGB = {canali_colore.at(0), canali_colore.at(1), canali_colore.at(2), 255};
    colore.at(punto_colore) =RGB;
}


void full_screen (const int screenWidth) {
    if (IsKeyPressed(KEY_F11))
    {
        // see what display we are on right now
        int display = GetCurrentMonitor();


        if (IsWindowFullscreen())
        {
            // if we are full screen, then go back to the windowed size
            SetWindowSize(screenWidth, GetScreenHeight());
        }
        else
        {
            // if we are not full screen, set the window size to match the monitor we are on
            SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
        }

        // toggle the state
        ToggleFullscreen();
    }
}

void colori_custom (std::vector<unsigned char> &canali_colori, float x, float pos_partenza, std::vector<Color> &colore_temp, int elemento_da_colorare) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), {x , pos_partenza, 40, 255})){
        canali_colori.at(elemento_da_colorare*3) = GetMouseY() - pos_partenza;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), {x + 80 , pos_partenza, 40, 255})){
        canali_colori.at(elemento_da_colorare*3 + 1) = GetMouseY() - pos_partenza;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), {x + 160 , pos_partenza, 40, 255})){
        canali_colori.at(elemento_da_colorare*3 + 2) = GetMouseY() - pos_partenza;
    }

    colore_temp.at(elemento_da_colorare) = {canali_colori.at(elemento_da_colorare*3), canali_colori.at(elemento_da_colorare*3 + 1), canali_colori.at(elemento_da_colorare*3 + 2), 255};
}

void dis_colori_custom (std::vector<unsigned char> canali_colore, float x, float pos_partenza, int n_elemento, std::vector<Color> colore_temp, std::vector<Color> colore, std::vector<int> scelta_elemento, const std::vector<std::vector<std::string>> &stringhe, const std::vector<float> &dim_stringhe) {
    int lunghezza = GetScreenWidth(), y = GetScreenHeight();
    DrawRectangle(x - 10, pos_partenza-10, 220, 286, GRAY);
    DrawRectangle(x, pos_partenza, 40, 256 + 10, RED);
    DrawRectangle(x + 5, canali_colore.at(n_elemento*3) + pos_partenza, 30, 10, BLACK);
    DrawRectangle(x + 80, pos_partenza, 40, 256 + 10, GREEN);
    DrawRectangle(x + 85, canali_colore.at(n_elemento*3+1) + pos_partenza, 30, 10, BLACK);
    DrawRectangle(x + 160, pos_partenza, 40, 256 + 10, BLUE);
    DrawRectangle(x + 165, canali_colore.at(n_elemento*3+2) + pos_partenza, 30, 10, BLACK);

    DrawRectangle(x - 10, pos_partenza + 306, 220, 50, GRAY);
    std::string rosso;
    rosso = std::to_string(canali_colore.at(n_elemento*3));
    DrawText(rosso.c_str(), x - 5, pos_partenza + 316, 30, RED);
    std::string verde;
    verde = std::to_string(canali_colore.at(n_elemento*3+1));
    DrawText(verde.c_str(), x + 75, pos_partenza + 316, 30, GREEN);
    std::string blu;
    blu = std::to_string(canali_colore.at(n_elemento*3+2));
    DrawText(blu.c_str(), x + 155, pos_partenza + 316, 30, BLUE);

    DrawRectangle(lunghezza*4/5 - 266, pos_partenza-10, 276, 276, GRAY);
    DrawRectangle(lunghezza*4/5 - 256, pos_partenza, 256, 256, colore_temp.at(n_elemento));
    DrawText(stringhe.at(23).at(0).c_str(), (lunghezza - MeasureText(stringhe.at(23).at(0).c_str(), dim_stringhe.at(2)))/2, y*0.80, dim_stringhe.at(2),colore.at(scelta_elemento.at(2)));
}

void riempi_colore_temp (std::vector<Color> &colore_temp, std::vector<unsigned char> canali_colori){
    Color temp;
    for (int i = 0; i < canali_colori.size()/3; ++i) {
        temp = {canali_colori.at(i*3), canali_colori.at(i*3 + 1), canali_colori.at(i * 3 + 2), 255};
        colore_temp.push_back(temp);
    }

}

void dis_stato_20 (const std::vector<std::vector<std::string>> &stringhe, const std::vector<float> &dim_stringhe, const std::vector<Color> &colore, std::vector<int> scelta_elemento) {
    float x = GetScreenWidth(), y = GetScreenHeight();
    DrawText(stringhe.at(20).at(0).c_str(), (x - MeasureText(stringhe.at(20).at(0).c_str(), dim_stringhe.at(1)))/2, y*0.02, dim_stringhe.at(1),colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(20).at(1).c_str(), x*0.02, y/2 - 80, dim_stringhe.at(2),colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(20).at(2).c_str(), x*0.02, y/2 + 20, dim_stringhe.at(2),colore.at(scelta_elemento.at(2)));
}

void stato_20 (const std::vector<std::vector<std::string>> &stringhe, const std::vector<float> &dim_stringhe, int &stato, int &stato_successivo) {
    float x = GetScreenWidth() * 0.02, y = GetScreenHeight();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), {x, y/2 - 80, (float)MeasureText(stringhe.at(20).at(1).c_str(), dim_stringhe.at(2)), dim_stringhe.at(2)})){
        stato = 1;
        stato_successivo = 25;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), {x, y/2 + 20, (float)MeasureText(stringhe.at(20).at(2).c_str(), dim_stringhe.at(2)), dim_stringhe.at(2)})){
        stato = 1;
        stato_successivo = 21;
    }
}

void dis_stato_25 (const std::vector<std::vector<std::string>> &stringhe, const std::vector<float> &dimensione, const std::vector<Color> &colore, std::vector<int> scelta_elemento, int tempo, int inserimento) {
    float x = GetScreenWidth(), y = GetScreenHeight();
    DrawText(stringhe.at(25).at(0).c_str(),  x/2 - MeasureText(stringhe.at(25).at(0).c_str(), dimensione.at(1))/2, y * 0.02, dimensione.at(1), colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(25).at(1).c_str(), x/2 - MeasureText(stringhe.at(25).at(1).c_str(), dimensione.at(2))/2, y *0.30, dimensione.at(2), colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(25).at(2).c_str(),  x/2 - MeasureText(stringhe.at(25).at(2).c_str(), dimensione.at(2))/2, y * 0.60, dimensione.at(2), colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(25).at(3).c_str(), x/2 - MeasureText(stringhe.at(25).at(3).c_str(), dimensione.at(3))/2, y *0.40 , dimensione.at(3), colore.at(scelta_elemento.at(2)));
    DrawText(stringhe.at(25).at(4).c_str(), x/2 - MeasureText(stringhe.at(25).at(4).c_str(), dimensione.at(3))/2, y * 0.70, dimensione.at(3), colore.at(scelta_elemento.at(2)));
    if (inserimento == 1) {
        if (tempo > 30) {
            DrawText("_", x/2 + MeasureText(stringhe.at(25).at(3).c_str(), dimensione.at(3))/2 + 10, y *0.40, dimensione.at(3), colore.at(scelta_elemento.at(2)));
        }
    } else if (inserimento == 2) {
        if (tempo > 30) {
            DrawText("_", x/2 + MeasureText(stringhe.at(25).at(4).c_str(), dimensione.at(3))/2 + 10, y *0.70, dimensione.at(3), colore.at(scelta_elemento.at(2)));
        }
    }
}

void modifica_nome(std::vector<std::vector<std::string>> &stringhe, int limite, int n_stato, int n_frase){
    char c = GetCharPressed();
    if (c > 0 && stringhe.at(n_stato).at(n_frase).size() < limite) {
        stringhe.at(n_stato).at(n_frase) += c;
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (!stringhe.at(n_stato).at(n_frase).empty())
            stringhe.at(n_stato).at(n_frase).pop_back();
    }
}

void stato_25 (std::vector<std::vector<std::string>> &stringhe, const std::vector<float> &dimensione, int &inserimento) {
    int limite = 20;
    float x = GetScreenWidth(), y = GetScreenHeight() * 0.30 + dimensione.at(1);
    float incremento = GetScreenHeight() * 0.30;
    if (CheckCollisionPointRec(GetMousePosition(), {x/2 - MeasureText(stringhe.at(25).at(3).c_str(), dimensione.at(3))/2, y, (float)MeasureText(stringhe.at(1).at(0).c_str(), dimensione.at(2)), dimensione.at(2)}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        inserimento = 1;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x/2 - MeasureText(stringhe.at(25).at(4).c_str(), dimensione.at(3))/2, y + incremento, (float)MeasureText(stringhe.at(1).at(1).c_str(), dimensione.at(2)), dimensione.at(2)}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        inserimento = 2;
    } else if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        inserimento = 0;
    }
    if (inserimento == 1) {
        modifica_nome(stringhe, limite, 25, 3);
    } else if (inserimento == 2) {
        modifica_nome(stringhe, limite, 25, 4);
    }

}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "pong");

    SetTargetFPS(60);
    int raggio = 15, gioco = 0, tempo = 0, stato = 0, elemento_da_colorare, stato_successivo, difficolta;
    float h_iniz = 200, h = h_iniz, l = 15, incremento = 0;
    bool rimbalzo, cresci1 = true, cresci2 = false, RGB_Yes_NO = false, colorare = false;


    std::vector<int> punteggio = {0,0};                                                                                                   //p1,p2

    std::vector<float> pallina = {screenWidth / 2.0,  static_cast<float>(GetRandomValue(raggio, screenHeight - raggio))};       //x,y

    std::vector<float> velocita = {9,0,0, 7, 7};                                                                                          //v, vx, vy, vb1, vb2

    std::vector<float> caricamento = { 0, screenHeight/20.0};                                                                             //x_caricamento, h_caricamento

    std::vector<float>barretta = {50,  screenHeight / 2 - h / 2, screenWidth - 50, screenHeight / 2 - h / 2};                             //bx1, by1, bx2, by2

    std::vector<unsigned char> canali_colore1 = {0, 0, 0};
    std::vector<unsigned char> canali_colore2 = {250, 250, 250};

    Color RGB1 {canali_colore1.at(0), canali_colore1.at(1), canali_colore1.at(2), 255};
    Color RGB2 {canali_colore2.at(0), canali_colore2.at(1), canali_colore2.at(2), 255};

    std::vector<Color> colore {WHITE, WHITE, WHITE, BLACK, RGB1, RGB2};                                                                          //pallina, barrette + linee, scritte + punti, sfondo, rgb

    std::vector<int> scelta_elemento {0, 1, 2, 3};

    std::vector<Color> colori = {BLACK, WHITE, RED, ORANGE,YELLOW,GREEN,SKYBLUE};

    std::vector<unsigned char> canali_colori = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

    std::vector<Color> colore_temp;

    std::vector<std::vector<std::string>> stringhe = {
            {"PONG", "Modalita'", "Impostazioni"},
            {"Caricamento.", "Caricamento..", "Caricamento..."},
            {"Modalita'" , "1)     Pong classico", "2)    Pong libero","3)    Pong classico medio","4)    Pong libero medio","5)    Pong classico difficile","6)    Pong libero difficile"},
            {"Premi spazio per iniziare", "Premere spazio per continuare", "Premere R per ricominciare","Premere U per uscire"," ha fatto punto"," ha vinto!"},
            {""},
            {""},
            {""},
            {""},
            {""},
            {""},
            {""},
            {""},
            {""},
            {""},
            {""},
            {""},
            {""},
            {""},
            {""},
            {""},
            {"Impostazioni", "1)     Modifica i nomi","2)    Colori"},
            {"Colori","1)    Colore della pallina","2)   Colore della barretta","3)   Colore delle scritte","4)   Colore dello sfondo"},
            {"Seleziona un colore"},
            {"Premi ENTER per confermare il colore"},
            {},
            {"Nomi", "Inserisci il nome del giocatore 1", "Inserisci il nome del giocatore 2", "Giocatore 1", "Giocatore 2"},
    };
    std::vector<float> dim_stringhe = { 150, 100, 60, 50};
    int inserimento = 0;
    riempi_colore_temp(colore_temp, canali_colori);
    int tempo_partita = 0;
    while (!WindowShouldClose()) {
        full_screen(screenWidth);
        tempo++;
        if (tempo >= 45)
            tempo = 0;
        if (stato == 0) {

            stato_0(stato, stato_successivo, stringhe, dim_stringhe);

        } else if (stato == 2) {

            stato_2(stato, 190, screenHeight/2, stato_successivo, difficolta, stringhe, dim_stringhe);

        } else if (stato == 3 ) {

            stato_3 (gioco, punteggio, pallina, raggio, velocita, barretta, h_iniz, h, l, tempo_partita, rimbalzo, incremento);
            scelta_difficolta(difficolta, velocita, h_iniz, raggio);

        } else if (stato == 4) {

            stato_4(gioco, punteggio, pallina, raggio, velocita, barretta, h_iniz, h, l, tempo_partita, rimbalzo, incremento);
            scelta_difficolta(difficolta, velocita, h_iniz, raggio);

        } else if (stato == 20) {
            stato_20(stringhe, dim_stringhe, stato, stato_successivo);
        } else if (stato == 21) {

            scelta_elemento_colorare(stringhe, dim_stringhe, stato, elemento_da_colorare, scelta_elemento, RGB_Yes_NO, screenWidth*0.02 + 190, screenHeight/2);
            if (colorare) {
                colore.at(elemento_da_colorare) = colore_temp.at(elemento_da_colorare);
                colorare = false;
                scelta_elemento.at(elemento_da_colorare) = elemento_da_colorare;

            }

        } else if (stato == 22) {

            selezione_colore(stato, elemento_da_colorare, colore, scelta_elemento, colori, stato_successivo);

        } else if (stato == 23) {

            colori_custom(canali_colori, screenWidth/5, screenHeight/2 - 256 , colore_temp, elemento_da_colorare);

            if (IsKeyDown(KEY_ENTER)) {
                stato = 1;
                stato_successivo = 21;
                colorare = true;
            }
        } else if (stato == 25) {
            stato_25(stringhe, dim_stringhe, inserimento);
        }
        if (IsKeyPressed(KEY_T)) {
            stato = 1;
            stato_successivo = 0;
            gioco = 0;
            pallina = {screenWidth / 2.0,  static_cast<float>(GetRandomValue(raggio, screenHeight - raggio))};
        }
        rgb(canali_colore1, colore, cresci1, RGB1, 4);
        rgb(canali_colore2, colore, cresci2, RGB2, 5);

        BeginDrawing();

        if (stato == 0) {
            dis_stato_0(colore, scelta_elemento, stringhe, dim_stringhe);
        } else if (stato == 1) {

            dis_caricamento(caricamento, tempo, stato_successivo, stato, colore, scelta_elemento, stringhe, dim_stringhe);

        } else if (stato == 2) {

            dis_stato_2(colore, scelta_elemento, stringhe, dim_stringhe);

        } else if (stato == 3) {

            dis_stato_3(stato, stato_successivo, gioco, punteggio, pallina, raggio,barretta, l, h, colore, scelta_elemento, stringhe, dim_stringhe);

        } else if (stato == 4) {

            dis_stato_4(stato, stato_successivo, gioco, punteggio, pallina, raggio,barretta, l, h, colore, scelta_elemento, stringhe, dim_stringhe);

        } else if (stato == 20) {

            dis_stato_20(stringhe, dim_stringhe, colore, scelta_elemento);

        } else if (stato == 21) {

            dis_colori0(colore, scelta_elemento, stringhe, dim_stringhe);

        } else if (stato == 22) {

            dis_colori(colori, colore, scelta_elemento, colore_temp, elemento_da_colorare, stringhe, dim_stringhe);
        } else if (stato == 23) {
            dis_colori_custom(canali_colori, screenWidth/5, screenHeight/2 - 256 , elemento_da_colorare, colore_temp, colore, scelta_elemento, stringhe, dim_stringhe);
        } else if (stato == 25) {
            dis_stato_25(stringhe, dim_stringhe, colore, scelta_elemento, tempo, inserimento);
        }
        ClearBackground(colore.at(scelta_elemento.at(3)));


        EndDrawing();
    }

    CloseWindow();
    return 0;
}