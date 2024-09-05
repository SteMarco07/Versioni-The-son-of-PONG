#include "include/raylib.h"
#include <iostream>
#include <vector>

struct Ball {
    int raggio;
    float x;
    float y ;
    bool rimbalzo;
};

struct Player {
    int punteggio;
    Rectangle barretta;
};

struct Players {
    Player giocatore_1;
    Player giocatore_2;
};

struct Speeds {
    float v0;
    float v_ball_x;
    float v_ball_y;
    float v_barretta_1;
    float v_barretta_2;
};


struct Game {
    int stato;
    int stato_successivo;
    int gioco;
    float h_iniz;
    int tempo;
    int tempo_partita;
    int difficolta;
    int incremento;
    int inserimento_nome;
    bool pausa;
};

struct String {
    std::vector<std::vector<std::string>> frasi;
    std::vector<float> dim_stringhe;
};

struct Colors {
    std::vector<unsigned char> rgb1_canali_colore;
    std::vector<unsigned char> rgb2_canali_colore;
    Color RGB1;
    Color RGB2;
    bool cresci_1;
    bool cresci_2;
    bool RGB_Yes_No;
    std::vector<Color> colore_elementi;
    std::vector<int> scelta_elemento;
    std::vector<Color> colori_partenza;
    std::vector<unsigned char> canali_colori;
    std::vector<Color> colore_temp;
    bool colorare;
    int elemento_da_colorare;
};

struct Triangle {
    Vector2 punto_1;
    Vector2 punto_2;
    Vector2 punto_3;
};

void dis_colori0 (const String &stringhe, const Colors &colori){
    float x = GetScreenWidth() * 0.02, y = GetScreenHeight(), dimensione = stringhe.dim_stringhe.at(2);
    Color colore = colori.colore_elementi.at(colori.scelta_elemento.at(2));
    DrawText(stringhe.frasi.at(21).at(0).c_str(), (GetScreenWidth() - MeasureText(stringhe.frasi.at(21).at(0).c_str(), stringhe.dim_stringhe.at(1)))/2, GetScreenHeight()*0.02, stringhe.dim_stringhe.at(1),colore);
    DrawText(stringhe.frasi.at(21).at(1).c_str(), x, y/2-180, dimensione,colore);
    DrawText(stringhe.frasi.at(21).at(2).c_str(), x, y/2 - 80, dimensione,colore);
    DrawText(stringhe.frasi.at(21).at(3).c_str(), x, y/2 + 20, dimensione,colore);
    DrawText(stringhe.frasi.at(21).at(4).c_str(), x, y/2+ 120, dimensione,colore);
}

void dis_colori( const String &stringhe, const Colors &colori){
    int a = 0;
    int b = 0;
    float x = GetScreenWidth(), y = GetScreenHeight();
    std::string numero;
    DrawText( stringhe.frasi.at(22).at(0).c_str(), (x - MeasureText(stringhe.frasi.at(22).at(0).c_str(),stringhe.dim_stringhe.at(1)))/2,y*0.02,stringhe.dim_stringhe.at(1),colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    for (int i = 0; i <= colori.colore_elementi.size() + 1; ++i) {
        if (i >= 4)
            b = GetScreenHeight() / 2 - 50;

        if (i==4)
            a=0;
        DrawRectangle(x / 18 + a, GetScreenHeight() / 9 + 100 + b, x / 7.2, y / 3.6, DARKGRAY);
        if (i <= colori.colore_elementi.size()) {
            DrawRectangle(x / 18 + 5 + a, y / 9 + 105 + b, x / 7.2-10, y / 3.6-10, colori.colori_partenza.at(i));
        } else {
            DrawRectangle(x / 18 + 5 + a, y / 9 + 105 + b, x / 7.2-10, y / 3.6-10, colori.colore_temp.at(colori.elemento_da_colorare));
        }
        a += x / 4;
    }
    DrawRectangle(x / 18 + a, y / 9 + 100 + b, x / 7.2, y / 3.6, DARKGRAY);
    a=0;
    b=0;
    DrawText("1",x / 18 + 20,y / 9 + 105, 100, WHITE);
    for (int i = 2 ; i <= colori.colori_partenza.size() + 1 ; i++ ){
        a += x/4;
        if ( i == 5){
            a=0;
            b=y / 2 - 50;
        }
        numero = std::to_string(i);
        DrawText(numero.c_str(),x / 18 + 20 + a,y / 9 + 105 + b, 100, BLACK);
    }

}

void selezione_colore (Game &game, Colors &colori) {
    int a = 0, b = 0;
    int lunghezza = GetScreenWidth(), altezza = GetScreenHeight();
    float lato = lunghezza / 7.2-10, x, y;
    for (int i = 0; i <= colori.colori_partenza.size(); ++i) {
        if (i >= 4)
            b = GetScreenHeight() / 2 - 50;

        if (i==4)
            a=0;

        x = lunghezza / 18 + 5 + a, y = altezza / 9 + 105 + b;
        if (i < colori.colori_partenza.size()) {
            if (CheckCollisionPointRec(GetMousePosition(), {x, y, lato, lato}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                game.stato = 21;
                colori.scelta_elemento.at(colori.elemento_da_colorare) = colori.elemento_da_colorare;
                colori.colore_elementi.at(colori.elemento_da_colorare) = colori.colori_partenza.at(i);
            }
        } else{
            if (CheckCollisionPointRec(GetMousePosition(), {x, y, lato, lato}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                game.stato = 23;
            }
        }

        a += lunghezza / 4;
    }

}

void pbx1(const Speeds &velocita, Players &giocatori) {
    int x = GetScreenWidth();
    if (IsKeyDown(KEY_A) && giocatori.giocatore_1.barretta.x > 0) {
        giocatori.giocatore_1.barretta.x -= velocita.v_barretta_1;
    } else if (IsKeyDown(KEY_D) && giocatori.giocatore_1.barretta.x + giocatori.giocatore_1.barretta.width < x/3) {
        giocatori.giocatore_1.barretta.x += velocita.v_barretta_1;
    }
}

void pbx2(const Speeds &velocita, Players &giocatori) {
    int x = GetScreenWidth();
    float l = giocatori.giocatore_1.barretta.width;
    if (IsKeyDown(KEY_LEFT) && giocatori.giocatore_2.barretta.x > x*2/3 + l) {
        giocatori.giocatore_2.barretta.x -= velocita.v_barretta_2;
    } else if (IsKeyDown(KEY_RIGHT) && giocatori.giocatore_2.barretta.x + l < x + l) {
        giocatori.giocatore_2.barretta.x += velocita.v_barretta_2;
    }
}

void pby1(const Speeds &velocita, Players &giocatori) {
    if (IsKeyDown(KEY_W) && giocatori.giocatore_1.barretta.y > 0) {
        giocatori.giocatore_1.barretta.y -= velocita.v_barretta_1;
    } else if (IsKeyDown(KEY_S) && giocatori.giocatore_1.barretta.y + giocatori.giocatore_1.barretta.height < GetScreenHeight()) {
        giocatori.giocatore_1.barretta.y += velocita.v_barretta_2;
    }
}

void pby2(const Speeds &velocita, Players &giocatori) {
    if (IsKeyDown(KEY_UP) && giocatori.giocatore_2.barretta.y > 0) {
        giocatori.giocatore_2.barretta.y -= velocita.v_barretta_2;
    } else if (IsKeyDown(KEY_DOWN) && giocatori.giocatore_2.barretta.y + giocatori.giocatore_2.barretta.height < GetScreenHeight()) {
        giocatori.giocatore_2.barretta.y += velocita.v_barretta_2;
    }
}

void py( Ball &pallina, Speeds &velocita){
    if ( pallina.y - pallina.raggio <= 0 ) {
        velocita.v_ball_y = abs(velocita.v_ball_y);
    } else if (pallina.y + pallina.raggio >= GetScreenHeight()) {
        velocita.v_ball_y = -velocita.v_ball_y;
    }
    pallina.y += velocita.v_ball_y;
}

void reset_v (const Game &game, Speeds &velocita){
    if (velocita.v_ball_y > 0) {
        velocita.v_ball_y = velocita.v0 + game.incremento;
    } else {
        velocita.v_ball_y = -velocita.v0 - game.incremento;
    }
}

void px(Game &game ,Ball &pallina, Players &giocatori, Speeds &velocita){
    float h = giocatori.giocatore_1.barretta.height;
    if  (CheckCollisionCircleRec ({pallina.x, pallina.y}, pallina.raggio, giocatori.giocatore_1.barretta) && pallina.rimbalzo) {
        velocita.v_ball_x = abs(velocita.v0) + game.incremento;
        pallina.rimbalzo = false;
        pallina.x += 10;
        reset_v(game, velocita);
        velocita.v_ball_y *= (pallina.y - (giocatori.giocatore_1.barretta.y+h/2))/(h/2);

    } else if (CheckCollisionCircleRec({pallina.x, pallina.y}, pallina.raggio, giocatori.giocatore_2.barretta) && !pallina.rimbalzo) {
        velocita.v_ball_x = -velocita.v0 - game.incremento;
        pallina.rimbalzo = true;
        pallina.x-= 10;
        reset_v(game, velocita);
        velocita.v_ball_y *= (pallina.y - (giocatori.giocatore_2.barretta.y+h/2))/(h/2);
    }
    pallina.x += velocita.v_ball_x;
}

void vi_X (Speeds &velocita){
    if (GetRandomValue(1,2) == 1){
        velocita.v_ball_x = -velocita.v0;
    } else {
        velocita.v_ball_x = velocita.v0;
    }
}

void vi_y (Speeds &velocita){
    if (GetRandomValue(1,2) == 1){
        velocita.v_ball_y = -velocita.v0;
    } else {
        velocita.v_ball_y = velocita.v0;
    }
}

void dis_punteggio (int p, float pos, const Colors &colori) {
    std::string punteggio;
    punteggio = std::to_string(p);
    DrawText(punteggio.c_str(), pos, 30, 40, colori.colore_elementi.at(colori.scelta_elemento.at(2)));

}

void interruzioni (Game &game, const Players &giocatori, const Colors &colori, const String &stringhe) {
    int x = GetScreenWidth(), y = GetScreenHeight();
    float dimensione_1 = stringhe.dim_stringhe.at(2), dimensione_2 = stringhe.dim_stringhe.at(3);
    Color colore = colori.colore_elementi.at(colori.scelta_elemento.at(2));
    if (game.gioco == 2 && giocatori.giocatore_1.punteggio != 10) {
        std::string frase = stringhe.frasi.at(25).at(3) + stringhe.frasi.at(3).at(4);
        DrawText(frase.c_str(), (x - MeasureText(frase.c_str(), dimensione_1))/2, y/2 - 35, dimensione_1, colore);
        DrawText(stringhe.frasi.at(3).at(1).c_str(), (x - MeasureText(stringhe.frasi.at(3).at(1).c_str(), dimensione_2))/2, y/2 + 35, dimensione_2, colore);
    } else  if (game.gioco == 3 && giocatori.giocatore_2.punteggio != 10) {
        std::string frase = stringhe.frasi.at(25).at(4) + stringhe.frasi.at(3).at(4);
        DrawText(frase.c_str(), (x - MeasureText(frase.c_str(), dimensione_1))/2, y/2 - 35, dimensione_1, colore);
        DrawText(stringhe.frasi.at(3).at(1).c_str(), (x - MeasureText(stringhe.frasi.at(3).at(1).c_str(), dimensione_2))/2, y/2 + 35, dimensione_2, colore);
    } else if (game.gioco == 0) {
        DrawText(stringhe.frasi.at(3).at(0).c_str(), (x - MeasureText(stringhe.frasi.at(3).at(0).c_str(), dimensione_1))/2, y/2, dimensione_1, colore);
    } else if ( giocatori.giocatore_1.punteggio == 10 || giocatori.giocatore_2.punteggio == 10 || game.pausa) {
        if (giocatori.giocatore_1.punteggio == 10) {
            std::string frase = stringhe.frasi.at(25).at(3) + stringhe.frasi.at(3).at(5);
            DrawText(frase.c_str(), (x - MeasureText(frase.c_str(), dimensione_1))/2, y/2 - 35, dimensione_1, colore);
        } else if (giocatori.giocatore_2.punteggio == 10) {
            std::string frase = stringhe.frasi.at(25).at(4) + stringhe.frasi.at(3).at(5);
            DrawText(frase.c_str(), (x - MeasureText(frase.c_str(), dimensione_1)) / 2, y / 2 - 35, dimensione_1,
                     colore);
        } else {
            DrawText(stringhe.frasi.at(3).at(7).c_str(), (x - MeasureText(stringhe.frasi.at(3).at(7).c_str(), dimensione_1)) / 2, y /2 - 35, dimensione_1,colore);
        }
        DrawText(stringhe.frasi.at(3).at(2).c_str(), (x - MeasureText(stringhe.frasi.at(3).at(2).c_str(), dimensione_2))/2, y/2 + 45, dimensione_2, colore);
        DrawText(stringhe.frasi.at(3).at(3).c_str(), (x - MeasureText(stringhe.frasi.at(3).at(3).c_str(), dimensione_2))/2, y/2 + 105, dimensione_2, colore);

    }
}

void inc_v (Speeds &velocita) {
    if (velocita.v_ball_x > 0) {
        velocita.v_ball_x += 0.001;
    } else {
        velocita.v_ball_x -= 0.001;
    }
    if (velocita.v_ball_y > 0) {
        velocita.v_ball_y += 0.001;
    } else {
        velocita.v_ball_y -= 0.001;
    }
}

void repet (Game &game, Players &giocatori) {
    game.gioco = 4;
    game.tempo_partita = 0;
    giocatori.giocatore_1.barretta.height = game.h_iniz;
    giocatori.giocatore_1.barretta.height = game.h_iniz;
}

void dis_caricamento (Rectangle &caricamento, Game &game, const String &stringhe, const Colors &colori) {
    int x = GetScreenWidth(), y = GetScreenHeight();
    Color colore = colori.colore_elementi.at(colori.scelta_elemento.at(2));
    caricamento.width += GetRandomValue(0, 50);
    if (caricamento.width >= x) {
        game.stato = game.stato_successivo;
        caricamento.width= 0;
    }
    DrawRectangleRec(caricamento,  colori.colore_elementi.at(colori.scelta_elemento.at(1)));
    if (game.tempo < 20) {
        DrawText(stringhe.frasi.at(1).at(0).c_str(), x*0.05, y-2*caricamento.height, stringhe.dim_stringhe.at(3), colore);
    } else if (game.tempo < 40) {
        DrawText(stringhe.frasi.at(1).at(1).c_str(), x*0.05, y-2*caricamento.height, stringhe.dim_stringhe.at(3), colore);
    } else if (game.tempo < 60) {
        DrawText(stringhe.frasi.at(1).at(2).c_str(), x*0.05, y-2*caricamento.height, stringhe.dim_stringhe.at(3), colore);
    }
}

void dis_stato_0 (const Colors &colori, const String &stringhe){
    int x = GetScreenWidth(), y = GetScreenHeight();
    Color colore = colori.colore_elementi.at(colori.scelta_elemento.at(2));
    DrawText(stringhe.frasi.at(0).at(0).c_str(), x*0.40, y*0.02, stringhe.dim_stringhe.at(0), colore);
    DrawText(stringhe.frasi.at(0).at(1).c_str(), x*0.02, y*0.70, stringhe.dim_stringhe.at(1), colore);
    DrawText(stringhe.frasi.at(0).at(2).c_str(), x*0.02, y*0.80, stringhe.dim_stringhe.at(1), colore);
}

void stato_0 (Game &game, const String &stringhe){
    int altezza = GetScreenHeight();
    float dimnsione =  stringhe.dim_stringhe.at(1);
    float x = GetScreenWidth() * 0.02, y1 = altezza*0.70, y2 = altezza*0.80;
    if (CheckCollisionPointRec(GetMousePosition(), {x, y1, (float)MeasureText(stringhe.frasi.at(0).at(1).c_str(), dimnsione), dimnsione}) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.stato = 1;
        game.stato_successivo = 2;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x , y2, (float)MeasureText(stringhe.frasi.at(0).at(2).c_str(), dimnsione), dimnsione}) &&
               IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.stato = 1;
        game.stato_successivo = 20;
    }
    game.gioco = 0;
}

void stato_3 (Game &game, Players &giocatori, Ball &pallina, Speeds &velocita, const String &stringhe) {
    float h = giocatori.giocatore_1.barretta.height;
    float x = GetScreenWidth(), y = GetScreenHeight();

    if (!game.pausa) {
        if (game.gioco == 0) {
            giocatori.giocatore_1.punteggio = 0;
            giocatori.giocatore_2.punteggio = 0;
            game.tempo_partita = 0;
            giocatori.giocatore_1.barretta = {50, y / 2 - h / 2, giocatori.giocatore_1.barretta.width, game.h_iniz};
            giocatori.giocatore_2.barretta = {(float)(x - 50), y / 2 - h / 2, giocatori.giocatore_1.barretta.width, game.h_iniz};
            if (pallina.x != x/2) {
                pallina.x = x/2;
                pallina.y = (float)(GetRandomValue(pallina.raggio, y - pallina.raggio));
            }
            h = game.h_iniz;
            if (IsKeyPressed(KEY_SPACE)) {
                game.gioco = 4;
                vi_X(velocita);
                vi_y(velocita);
                if (velocita.v_ball_x < 0) {
                    pallina.rimbalzo = true;
                } else {
                    pallina.rimbalzo = false;
                }
            }
        } else if (game.gioco > 1) {

            py(pallina, velocita);
            px(game, pallina, giocatori, velocita );
            pby1(velocita, giocatori);
            pby2(velocita, giocatori);

            if (pallina.x <= 0 || pallina.x >= x) {
                if (pallina.x <= 0) {
                    giocatori.giocatore_2.punteggio++;
                    game.gioco = 3;
                } else if (pallina.x >= x) {
                    giocatori.giocatore_1.punteggio++;
                    game.gioco = 2;
                }
                pallina.x = GetRandomValue(pallina.raggio, y - pallina.raggio);
                pallina.x = x / 2;
                velocita.v_ball_x = 0;
                velocita.v_ball_y = 0;
            }
            if (IsKeyPressed(KEY_SPACE) && game.gioco == 3 && giocatori.giocatore_1.punteggio < 10 && giocatori.giocatore_2.punteggio < 10) {
                vi_y(velocita);
                velocita.v_ball_x = velocita.v0;
                repet(game, giocatori);
                pallina.rimbalzo = false;
            } else if (IsKeyPressed(KEY_SPACE) && game.gioco == 2 && giocatori.giocatore_1.punteggio < 10 && giocatori.giocatore_2.punteggio < 10) {
                vi_y(velocita);
                velocita.v_ball_x = -velocita.v0;
                repet(game, giocatori);
                pallina.rimbalzo = true;
            }

            game.tempo_partita++;
            if (game.tempo_partita > 2000 && game.gioco != 2 && game.gioco != 3) {
                inc_v(velocita);
                game.incremento += 0.001;
                if (game.tempo_partita > 3000 && h > 30) {
                    h -= 0.05;

                }
            }
            giocatori.giocatore_1.barretta.height = h;
            giocatori.giocatore_2.barretta.height = h;

        }
    }


    if (giocatori.giocatore_1.punteggio == 10 || giocatori.giocatore_2.punteggio == 10 || game.pausa) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), {(x - MeasureText(stringhe.frasi.at(3).at(2).c_str(), stringhe.dim_stringhe.at(3)))/2, y/2 + 45, (float)MeasureText(stringhe.frasi.at(3).at(2).c_str(), stringhe.dim_stringhe.at(3)), stringhe.dim_stringhe.at(3)})) {
            game.gioco = 0;
            game.pausa = false;
        } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), {(x - MeasureText(stringhe.frasi.at(3).at(3).c_str(), stringhe.dim_stringhe.at(3)))/2, y/2 + 105, (float)MeasureText(stringhe.frasi.at(3).at(2).c_str(), stringhe.dim_stringhe.at(3)), stringhe.dim_stringhe.at(3)})) {
            game.stato = 1;
            game.stato_successivo = 0;
            game.pausa = false;
        }
    }
}

void dis_stato_3 (Game &game, const Ball &pallina,  Players &giocatori, const Colors &colori, const String &stringhe) {
    int x = GetScreenWidth(), y = GetScreenHeight();
    giocatori.giocatore_1.barretta.x -= giocatori.giocatore_1.barretta.width;
    interruzioni(game, giocatori, colori, stringhe);
    DrawCircle(pallina.x, pallina.y, pallina.raggio, colori.colore_elementi.at(colori.scelta_elemento.at(0)));
    DrawRectangleRec(giocatori.giocatore_1.barretta, colori.colore_elementi.at(colori.scelta_elemento.at(1)));
    DrawRectangleRec(giocatori.giocatore_2.barretta, colori.colore_elementi.at(colori.scelta_elemento.at(1)));
    dis_punteggio(giocatori.giocatore_1.punteggio, x / 4, colori);
    dis_punteggio(giocatori.giocatore_2.punteggio, x  * 0.75, colori);
    if (!(game.gioco == 0 || game.gioco == 2 || game.gioco == 3 || game.pausa)) {
        for (int i = 20; i <= y; i += 100) {
            DrawRectangle((x/2)-3,i, 6, 40, colori.colore_elementi.at(colori.scelta_elemento.at(1)));
        }
    }
    giocatori.giocatore_1.barretta.x += giocatori.giocatore_1.barretta.width;

}

void dis_stato_2(const Colors &colori, const String &stringhe) {
    int x = GetScreenWidth(), y = GetScreenHeight();
    Color colore = colori.colore_elementi.at(colori.scelta_elemento.at(2));
    DrawText(stringhe.frasi.at(2).at(0).c_str(), (x - MeasureText(stringhe.frasi.at(2).at(0).c_str(), stringhe.dim_stringhe.at(1)))/2, y*0.02, stringhe.dim_stringhe.at(1),colore);
    DrawText(stringhe.frasi.at(2).at(1).c_str(), x*0.02, y/2 - 280, stringhe.dim_stringhe.at(2),colore);
    DrawText(stringhe.frasi.at(2).at(2).c_str(), x*0.02, y/2 - 180, stringhe.dim_stringhe.at(2),colore);
    DrawText(stringhe.frasi.at(2).at(3).c_str(), x*0.02, y/2 - 80, stringhe.dim_stringhe.at(2),colore);
    DrawText(stringhe.frasi.at(2).at(4).c_str(), x*0.02, y/2 + 20, stringhe.dim_stringhe.at(2),colore);
    DrawText(stringhe.frasi.at(2).at(5).c_str(), x*0.02, y/2 + 120, stringhe.dim_stringhe.at(2),colore);
    DrawText(stringhe.frasi.at(2).at(6).c_str(), x*0.02, y/2 + 220, stringhe.dim_stringhe.at(2),colore);
}


void dis_stato_4 (Game &game, const Ball &pallina,  Players &giocatori, const Colors &colori, const String &stringhe) {
    dis_stato_3(game, pallina, giocatori, colori, stringhe);
    int lunghezza = GetScreenWidth(), altezza = GetScreenHeight();
    if (!(game.gioco == 0 || game.gioco == 2 || game.gioco == 3 || game.pausa)) {
        for (int i = 0; i < altezza; i += 80) {
            DrawRectangle((lunghezza/3)-3,i, 6, 20, colori.colore_elementi.at(colori.scelta_elemento.at(1)));
        }
        for (int i = 0; i < altezza; i += 80) {
            DrawRectangle((lunghezza*2/3)-3,i, 6, 20, colori.colore_elementi.at(colori.scelta_elemento.at(1)));
        }
    }
}

void scelta_difficolta(Ball &pallina, Speeds &velocita, Game &game) {
    if (game.difficolta == 0) {
        velocita.v0 = 9;
        velocita.v_barretta_1 = 7;
        velocita.v_barretta_2 = 7;
        game.h_iniz = 200;
        pallina.raggio = 15;
    } else if (game.difficolta == 1) {
        velocita.v0 = 11;
        velocita.v_barretta_1 = 9;
        velocita.v_barretta_2 = 9;
        game.h_iniz = 180;
        pallina.raggio = 13;
    } else {
        velocita.v0 = 15;
        velocita.v_barretta_1 = 11;
        velocita.v_barretta_2 = 11;
        game.h_iniz = 160;
        pallina.raggio = 10;
    }
}

void stato_2 (float x, float y, Game &game , const String &stringhe) {
    float dimensione = stringhe.dim_stringhe.at(2);
    if (CheckCollisionPointRec(GetMousePosition(), {x, y - 280, (float)MeasureText(stringhe.frasi.at(2).at(1).c_str(), dimensione), dimensione}) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.stato= 1;
        game.stato_successivo = 3;
        game.difficolta = 0;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x, y - 180, (float)MeasureText(stringhe.frasi.at(2).at(2).c_str(), dimensione), dimensione}) &&
               IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.stato= 1;
        game.stato_successivo = 4;
        game.difficolta = 0;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x, y - 80, (float)MeasureText(stringhe.frasi.at(2).at(3).c_str(), dimensione), dimensione}) &&
               IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.stato= 1;
        game.stato_successivo = 3;
        game.difficolta = 1;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x, y + 20, (float)MeasureText(stringhe.frasi.at(2).at(4).c_str(), dimensione), dimensione}) &&
               IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.stato= 1;
        game.stato_successivo = 4;
        game.difficolta = 1;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x, y + 120, (float)MeasureText(stringhe.frasi.at(2).at(5).c_str(), dimensione), dimensione}) &&
               IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.stato= 1;
        game.stato_successivo = 3;
        game.difficolta = 2;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x, y + 220, (float)MeasureText(stringhe.frasi.at(2).at(6).c_str(), dimensione), dimensione}) &&
               IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.stato= 1;
        game.stato_successivo = 4;
        game.difficolta = 2;
    }
}

void stato_4 (Game &game,Players &giocatori,Ball &pallina,Speeds &velocita, const String &stringhe) {
    stato_3(game, giocatori, pallina, velocita, stringhe);

    if (game.gioco > 1 && !game.pausa) {
        pbx1(velocita, giocatori);
        pbx2(velocita, giocatori);
    }
}



void scelta_elemento_colorare(const String &stringhe, Game &game, Colors &colori, float x, float y){

    float dimensione = stringhe.dim_stringhe.at(2);
    if (CheckCollisionPointRec(GetMousePosition(), {x, y - 180, (float)MeasureText(stringhe.frasi.at(21).at(1).c_str(), dimensione), dimensione}) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.stato = 22;
        colori.elemento_da_colorare = 0;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x, y - 80, (float)MeasureText(stringhe.frasi.at(21).at(2).c_str(), dimensione), dimensione}) &&
               IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.stato = 22;
        colori.elemento_da_colorare = 1;
    }else if (CheckCollisionPointRec(GetMousePosition(), {x, y + 20, (float)MeasureText(stringhe.frasi.at(21).at(3).c_str(), dimensione), dimensione}) &&
              IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.stato = 22;
        colori.elemento_da_colorare = 2;
    }else if (CheckCollisionPointRec(GetMousePosition(), {x, y + 120, (float)MeasureText(stringhe.frasi.at(21).at(4).c_str(), dimensione), dimensione}) &&
              IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.stato = 22;
        colori.elemento_da_colorare = 3;
    }
    if (IsKeyDown(KEY_R) && IsKeyDown(KEY_G) && IsKeyDown(KEY_B) && !IsKeyDown(KEY_N)&&!colori.RGB_Yes_No) {
        colori.scelta_elemento = {4, 4, 4, 5};
        colori.RGB_Yes_No = true;
    } else if (IsKeyDown(KEY_R) && IsKeyDown(KEY_G) && IsKeyDown(KEY_B) && IsKeyDown(KEY_N)&&colori.RGB_Yes_No) {
        colori.scelta_elemento = {0, 1, 2, 3};
        colori.RGB_Yes_No = false;
    }
}



void rgb (Colors &colori) {

    int velocita = 3;
    if (colori.cresci_1) {
        if (colori.rgb1_canali_colore.at(0) < 250) { colori.rgb1_canali_colore.at(0) += velocita; }
        else if (colori.rgb1_canali_colore.at(1) < 250) { colori.rgb1_canali_colore.at(1) += velocita; }
        else if (colori.rgb1_canali_colore.at(2) < 250) { colori.rgb1_canali_colore.at(2) += velocita; } else {colori.cresci_1 = false;}
    }
    else {
        if (colori.rgb1_canali_colore.at(0) > 10) { colori.rgb1_canali_colore.at(0) -= velocita; }
        else if (colori.rgb1_canali_colore.at(1) > 10) { colori.rgb1_canali_colore.at(1) -= velocita; }
        else if (colori.rgb1_canali_colore.at(2) > 10) { colori.rgb1_canali_colore.at(2) -= velocita; } else { colori.cresci_1 =true;}
    }
    colori.RGB1 = {colori.rgb1_canali_colore.at(0), colori.rgb1_canali_colore.at(1), colori.rgb1_canali_colore.at(2), 255};
    colori.colore_elementi.at(4) = colori.RGB1;

    if (colori.cresci_2) {
        if (colori.rgb2_canali_colore.at(0) < 250) { colori.rgb2_canali_colore.at(0) += velocita; }
        else if (colori.rgb2_canali_colore.at(1) < 250) { colori.rgb2_canali_colore.at(1) += velocita; }
        else if (colori.rgb2_canali_colore.at(2) < 250) { colori.rgb2_canali_colore.at(2) += velocita; } else {colori.cresci_2 = false;}
    }
    else {
        if (colori.rgb2_canali_colore.at(0) > 10) { colori.rgb2_canali_colore.at(0) -= velocita; }
        else if (colori.rgb2_canali_colore.at(1) > 10) { colori.rgb2_canali_colore.at(1) -= velocita; }
        else if (colori.rgb2_canali_colore.at(2) > 10) { colori.rgb2_canali_colore.at(2) -= velocita; } else { colori.cresci_2 =true;}
    }
    colori.RGB2 = {colori.rgb2_canali_colore.at(0), colori.rgb2_canali_colore.at(1), colori.rgb2_canali_colore.at(2), 255};
    colori.colore_elementi.at(5) = colori.RGB2;
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

void colori_custom (float x, float pos_partenza, const Game &game, Colors &colori) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), {x , pos_partenza, 40, 255})){
        colori.canali_colori.at(colori.elemento_da_colorare*3) = GetMouseY() - pos_partenza;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), {x + 80 , pos_partenza, 40, 255})){
        colori.canali_colori.at(colori.elemento_da_colorare*3 + 1) = GetMouseY() - pos_partenza;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), {x + 160 , pos_partenza, 40, 255})){
        colori.canali_colori.at(colori.elemento_da_colorare*3 + 2) = GetMouseY() - pos_partenza;
    }

    colori.colore_temp.at(colori.elemento_da_colorare) = {colori.canali_colori.at(colori.elemento_da_colorare*3), colori.canali_colori.at(colori.elemento_da_colorare*3 + 1), colori.canali_colori.at(colori.elemento_da_colorare*3 + 2), 255};
}

void dis_colori_custom (const Colors &colori, const String &stringhe, const Game &game, float x, float pos_partenza) {
    int lunghezza = GetScreenWidth(), y = GetScreenHeight();
    DrawRectangle(x - 10, pos_partenza-10, 220, 286, GRAY);
    DrawRectangle(x, pos_partenza, 40, 256 + 10, RED);
    DrawRectangle(x + 5, colori.canali_colori.at(colori.elemento_da_colorare*3) + pos_partenza, 30, 10, BLACK);
    DrawRectangle(x + 80, pos_partenza, 40, 256 + 10, GREEN);
    DrawRectangle(x + 85, colori.canali_colori.at(colori.elemento_da_colorare*3+1) + pos_partenza, 30, 10, BLACK);
    DrawRectangle(x + 160, pos_partenza, 40, 256 + 10, BLUE);
    DrawRectangle(x + 165, colori.canali_colori.at(colori.elemento_da_colorare*3+2) + pos_partenza, 30, 10, BLACK);

    DrawRectangle(x - 10, pos_partenza + 306, 220, 50, GRAY);
    std::string rosso;
    rosso = std::to_string(colori.canali_colori.at(colori.elemento_da_colorare*3));
    DrawText(rosso.c_str(), x - 5, pos_partenza + 316, 30, RED);
    std::string verde;
    verde = std::to_string(colori.canali_colori.at(colori.elemento_da_colorare*3+1));
    DrawText(verde.c_str(), x + 75, pos_partenza + 316, 30, GREEN);
    std::string blu;
    blu = std::to_string(colori.canali_colori.at(colori.elemento_da_colorare*3+2));
    DrawText(blu.c_str(), x + 155, pos_partenza + 316, 30, BLUE);

    DrawRectangle(lunghezza*4/5 - 266, pos_partenza-10, 276, 276, GRAY);
    DrawRectangle(lunghezza*4/5 - 256, pos_partenza, 256, 256, colori.colore_temp.at(colori.elemento_da_colorare));
    DrawText(stringhe.frasi.at(23).at(0).c_str(), (lunghezza - MeasureText(stringhe.frasi.at(23).at(0).c_str(), stringhe.dim_stringhe.at(2)))/2, y*0.80, stringhe.dim_stringhe.at(2),colori.colore_elementi.at(colori.scelta_elemento.at(2)));
}

void riempi_colore_temp (Colors &colori){
    for (int i = 0; i < colori.canali_colori.size()/3; ++i) {
        colori.colore_temp.at(i) = {colori.canali_colori.at(i*3), colori.canali_colori.at(i*3 + 1), colori.canali_colori.at(i * 3 + 2), 255};
    }

}

void dis_stato_20 (const String &stringhe, const Colors &colori) {
    float x = GetScreenWidth(), y = GetScreenHeight();
    Color colore = colori.colore_elementi.at(colori.scelta_elemento.at(2));
    DrawText(stringhe.frasi.at(20).at(0).c_str(), (x - MeasureText(stringhe.frasi.at(20).at(0).c_str(), stringhe.dim_stringhe.at(1)))/2, y*0.02, stringhe.dim_stringhe.at(1),colore);
    DrawText(stringhe.frasi.at(20).at(1).c_str(), x*0.02, y/2 - 80, stringhe.dim_stringhe.at(2),colore);
    DrawText(stringhe.frasi.at(20).at(2).c_str(), x*0.02, y/2 + 20, stringhe.dim_stringhe.at(2),colore);
    DrawText(stringhe.frasi.at(20).at(3).c_str(), x*0.02, y/2 + 120, stringhe.dim_stringhe.at(2),colore);
}

void stato_20 (Game &game, const String &stringhe) {
    float x = GetScreenWidth() * 0.02, y = GetScreenHeight();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), {x, y/2 - 80, (float)MeasureText(stringhe.frasi.at(20).at(1).c_str(), stringhe.dim_stringhe.at(2)), stringhe.dim_stringhe.at(2)})){
        game.stato = 1;
        game.stato_successivo = 25;
    } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), {x, y/2 + 20, (float)MeasureText(stringhe.frasi.at(20).at(2).c_str(), stringhe.dim_stringhe.at(2)), stringhe.dim_stringhe.at(2)})){
        game.stato = 1;
        game.stato_successivo = 21;
    } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), {x, y/2 + 120, (float)MeasureText(stringhe.frasi.at(20).at(3).c_str(), stringhe.dim_stringhe.at(2)), stringhe.dim_stringhe.at(2)})){
        game.stato = 1;
        game.stato_successivo = 26;
    }
}

void dis_stato_25 (const Colors &colori, const String &stringhe, const Game &game) {
    float x = GetScreenWidth(), y = GetScreenHeight();
    DrawText(stringhe.frasi.at(25).at(0).c_str(),  x/2 - MeasureText(stringhe.frasi.at(25).at(0).c_str(), stringhe.dim_stringhe.at(1))/2, y * 0.02, stringhe.dim_stringhe.at(1), colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    DrawText(stringhe.frasi.at(25).at(1).c_str(), x/2 - MeasureText(stringhe.frasi.at(25).at(1).c_str(), stringhe.dim_stringhe.at(2))/2, y *0.30, stringhe.dim_stringhe.at(2), colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    DrawText(stringhe.frasi.at(25).at(2).c_str(),  x/2 - MeasureText(stringhe.frasi.at(25).at(2).c_str(), stringhe.dim_stringhe.at(2))/2, y * 0.60, stringhe.dim_stringhe.at(2), colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    DrawText(stringhe.frasi.at(25).at(3).c_str(), x/2 - MeasureText(stringhe.frasi.at(25).at(3).c_str(), stringhe.dim_stringhe.at(3))/2, y *0.40 , stringhe.dim_stringhe.at(3), colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    DrawText(stringhe.frasi.at(25).at(4).c_str(), x/2 - MeasureText(stringhe.frasi.at(25).at(4).c_str(), stringhe.dim_stringhe.at(3))/2, y * 0.70, stringhe.dim_stringhe.at(3), colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    if (game.inserimento_nome == 1) {
        if (game.tempo > 30) {
            DrawText("_", x/2 + MeasureText(stringhe.frasi.at(25).at(3).c_str(), stringhe.dim_stringhe.at(3))/2 + 10, y *0.40, stringhe.dim_stringhe.at(3), colori.colore_elementi.at(colori.scelta_elemento.at(2)));
        }
    } else if (game.inserimento_nome == 2) {
        if (game.tempo > 30) {
            DrawText("_", x/2 + MeasureText(stringhe.frasi.at(25).at(4).c_str(), stringhe.dim_stringhe.at(3))/2 + 10, y *0.70, stringhe.dim_stringhe.at(3), colori.colore_elementi.at(colori.scelta_elemento.at(2)));
        }
    }
}

void modifica_nome(String &stringhe, int limite, int n_stato, int n_frase){
    char c = GetCharPressed();
    if (c > 0 && stringhe.frasi.at(n_stato).at(n_frase).size() < limite) {
        stringhe.frasi.at(n_stato).at(n_frase) += c;
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (!stringhe.frasi.at(n_stato).at(n_frase).empty())
            stringhe.frasi.at(n_stato).at(n_frase).pop_back();
    }
}

void stato_25 (String &stringhe, Game &game) {
    int limite = 20;
    float x = GetScreenWidth(), y = GetScreenHeight() * 0.30 + stringhe.dim_stringhe.at(1), dimensione = stringhe.dim_stringhe.at(2);
    float incremento = GetScreenHeight() * 0.30;
    if (CheckCollisionPointRec(GetMousePosition(), {x/2 - MeasureText(stringhe.frasi.at(25).at(3).c_str(), dimensione)/2, y, (float)MeasureText(stringhe.frasi.at(1).at(0).c_str(), dimensione), dimensione}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.inserimento_nome = 1;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x/2 - MeasureText(stringhe.frasi.at(25).at(4).c_str(), dimensione)/2, y + incremento, (float)MeasureText(stringhe.frasi.at(1).at(1).c_str(), dimensione), dimensione}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.inserimento_nome = 2;
    } else if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.inserimento_nome = 0;
    }
    if (game.inserimento_nome == 1) {
        modifica_nome(stringhe, limite, 25, 3);
    } else if (game.inserimento_nome == 2) {
        modifica_nome(stringhe, limite, 25, 4);
    }

}

void dis_stato_26 (const String &stringhe, const Colors &colori) {
    float x = GetScreenWidth(), y = GetScreenHeight();
    DrawText(stringhe.frasi.at(26).at(0).c_str(),  x/2 - MeasureText(stringhe.frasi.at(26).at(0).c_str(), stringhe.dim_stringhe.at(1))/2, y*0.02, stringhe.dim_stringhe.at(1), colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    DrawText(stringhe.frasi.at(26).at(1).c_str(),  x/2 - MeasureText(stringhe.frasi.at(26).at(1).c_str(), stringhe.dim_stringhe.at(2))/2, y/4, stringhe.dim_stringhe.at(2), colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    DrawText(stringhe.frasi.at(26).at(2).c_str(),  x/2 - MeasureText(stringhe.frasi.at(26).at(2).c_str(), stringhe.dim_stringhe.at(1))/2, y/2, stringhe.dim_stringhe.at(1), colori.colore_elementi.at(colori.scelta_elemento.at(1)));
    DrawText(stringhe.frasi.at(26).at(3).c_str(),  x/2 - MeasureText(stringhe.frasi.at(26).at(3).c_str(), stringhe.dim_stringhe.at(2))/2, y*0.75, stringhe.dim_stringhe.at(2), colori.colore_elementi.at(colori.scelta_elemento.at(2)));
}

void dis_torna_indietro(const Triangle &triangolo, const Colors &colori) {
    DrawTriangle(triangolo.punto_1, triangolo.punto_2, triangolo.punto_3, colori.colore_elementi.at(colori.scelta_elemento.at(1)));
}

void torna_indietro (const Triangle &triangolo, Game &game, int stato_to_return, bool caricamento) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointTriangle(GetMousePosition(), triangolo.punto_1, triangolo.punto_2, triangolo.punto_3)) {
        if (caricamento) {
            game.stato = 1;
            game.stato_successivo = stato_to_return;
        } else {
            game.stato = stato_to_return;
        }
    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Pong");

    SetTargetFPS(60);
    float h_iniz = 200, l = 15;



    Game game = {0, 0, 0, h_iniz, 0, 0,0, 0, 0, false};

    Ball pallina= {15, screenWidth / 2.0,  (float)(GetRandomValue(pallina.raggio, screenHeight - pallina.raggio)), true};

    Players giocatori = {
            {0, {50, screenWidth - 50, l, h_iniz}},
            {0, {screenHeight / 2 - h_iniz / 2, screenHeight / 2 - h_iniz / 2, l, h_iniz}}
    };

    Rectangle caricamento = {0,  screenHeight - screenHeight/20.0, 0 , screenHeight/20.0};

    Speeds velocita = {9,0,0, 7, 7};

    Colors colori = {{0, 0, 0},
                     {250, 250, 250},
                     {colori.rgb1_canali_colore.at(0), colori.rgb1_canali_colore.at(1), colori.rgb1_canali_colore.at(2), 255},
                     {colori.rgb2_canali_colore.at(0), colori.rgb2_canali_colore.at(1), colori.rgb2_canali_colore.at(2), 255},
                     true,
                     false,
                     false,
                     {WHITE, WHITE, WHITE, BLACK, colori.RGB1, colori.RGB2},
                     {0, 1, 2, 3},
                     {BLACK, WHITE, RED, ORANGE,YELLOW,GREEN,SKYBLUE},
                     {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100},
                     {WHITE, WHITE, WHITE, WHITE},
                     false,
                     0
    };

    String stringhe {
            {
                    {"PONG", "Modalita'", "Impostazioni"},
                    {"Caricamento.", "Caricamento..", "Caricamento..."},
                    {"Modalita'" , "1)     Pong classico", "2)    Pong libero","3)    Pong classico medio","4)    Pong libero medio","5)    Pong classico difficile","6)    Pong libero difficile"},
                    {"Premi spazio per iniziare", "Premere spazio per continuare", "Ricomincia","Esci"," ha fatto punto"," ha vinto!", "Pausa", "Il gioco è in pausa"},
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
                    {"Impostazioni", "1)     Modifica i nomi","2)    Colori", "3)    Informazioni"},
                    {"Colori","1)    Colore della pallina","2)   Colore della barretta","3)   Colore delle scritte","4)   Colore dello sfondo"},
                    {"Seleziona un colore"},
                    {"Premi ENTER per confermare il colore"},
                    {},
                    {"Nomi", "Inserisci il nome del giocatore 1", "Inserisci il nome del giocatore 2", "Giocatore 1", "Giocatore 2"},
                    {"Crediti", "Realizzato da Stellino Marco", "Versione", "3.2"}
            },
            { 150, 100, 60, 45}
    };

    Vector2 punto = {screenWidth*0.95, screenHeight*0.9};
    Triangle triangolo = {
            {punto.x + 40, punto.y-40},
            {punto},
            {punto.x + 40, punto.y + 40}

    };



    riempi_colore_temp(colori);

    while (!WindowShouldClose()) {
        full_screen(screenWidth);
        game.tempo++;
        if (game.tempo >= 60)
            game.tempo = 0;



        if (game.stato == 0) {

            stato_0(game, stringhe);


        } else if (game.stato == 2) {

            stato_2( 190, screenHeight/2, game, stringhe);
            torna_indietro(triangolo, game, 0, true);

        } else if (game.stato == 3 ) {

            if (IsKeyPressed(KEY_P) && giocatori.giocatore_1.punteggio != 10 && giocatori.giocatore_2.punteggio != 10 && game.gioco != 2 && game.gioco != 3 && game.gioco != 0) {
                game.pausa = !game.pausa;
            }

            scelta_difficolta(pallina, velocita, game);
            stato_3 (game, giocatori, pallina, velocita, stringhe);



        } else if (game.stato == 4) {

            if (IsKeyPressed(KEY_P) && giocatori.giocatore_1.punteggio != 10 && giocatori.giocatore_2.punteggio != 10 && game.gioco != 2 && game.gioco != 3 && game.gioco != 0) {
                game.pausa = !game.pausa;
            }
            scelta_difficolta(pallina, velocita, game);
            stato_4(game, giocatori, pallina, velocita, stringhe);


        } else if (game.stato == 20) {

            stato_20(game, stringhe);
            torna_indietro(triangolo, game, 0, true);

        } else if (game.stato == 21) {
            torna_indietro(triangolo, game, 20, false);
            scelta_elemento_colorare(stringhe, game, colori, screenWidth*0.02 + 190, screenHeight/2);
            if (colori.colorare) {
                colori.colore_elementi.at(colori.elemento_da_colorare) = colori.colore_temp.at(colori.elemento_da_colorare);
                colori.colorare = false;
                colori.scelta_elemento.at(colori.elemento_da_colorare) = colori.elemento_da_colorare;

            }

        } else if (game.stato == 22) {

            selezione_colore(game, colori);
            torna_indietro(triangolo, game, 21, false);

        } else if (game.stato == 23) {

            colori_custom(screenWidth/5, screenHeight/2 - 256 , game, colori);
            torna_indietro(triangolo, game, 22, false);

            if (IsKeyDown(KEY_ENTER)) {
                game.stato = 1;
                game.stato_successivo = 21;
                colori.colorare = true;
            }
        } else if (game.stato == 25) {
            stato_25(stringhe, game);
            torna_indietro(triangolo, game, 20, true);
        } else if (game.stato == 26) {
            torna_indietro(triangolo, game, 20, true);
        }

        rgb(colori);


        BeginDrawing();


        if (game.stato == 0) {
            dis_stato_0(colori, stringhe);
        } else if (game.stato == 1) {

            dis_caricamento(caricamento, game, stringhe, colori);


        } else if (game.stato == 2) {

            dis_stato_2(colori, stringhe);
            dis_torna_indietro(triangolo, colori);

        } else if (game.stato == 3) {

            dis_stato_3(game, pallina, giocatori, colori, stringhe);

        } else if (game.stato == 4) {

            dis_stato_4(game, pallina, giocatori, colori, stringhe);

        } else if (game.stato == 20) {

            dis_stato_20(stringhe, colori);
            dis_torna_indietro(triangolo, colori);

        } else if (game.stato == 21) {

            dis_colori0(stringhe, colori);
            dis_torna_indietro(triangolo, colori);

        } else if (game.stato == 22) {

            dis_colori( stringhe, colori);
            dis_torna_indietro(triangolo, colori);
        } else if (game.stato == 23) {
            dis_colori_custom(colori, stringhe, game, screenWidth/5, screenHeight/2 - 256 );
            dis_torna_indietro(triangolo, colori);

        } else if (game.stato == 25) {
            dis_stato_25(colori, stringhe, game);
            dis_torna_indietro(triangolo, colori);

        } else if (game.stato == 26) {
            dis_stato_26(stringhe, colori);
            dis_torna_indietro(triangolo, colori);
        }
        ClearBackground(colori.colore_elementi.at(colori.scelta_elemento.at(3)));


        EndDrawing();
    }

    CloseWindow();
    return 0;
}