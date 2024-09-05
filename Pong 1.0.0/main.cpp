#include "include/raylib.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

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


struct Speeds {
    float v0;
    float v_ball_x;
    float v_ball_y;
    float v_barretta_1;
    float v_barretta_2;
};


struct Game {
    const int screenWidth;
    const int screenHeight;
    int stato;
    int stato_successivo;
    int gioco;
    float h_iniz;
    int tempo;
    int tempo_partita;
    int incremento;
    int inserimento_nome;
    bool pausa;
    int pagina_tasti;
    Vector2 pos_mouse;
};

struct String {
    std::vector<std::vector<std::string>> frasi;
    std::vector<float> dim_stringhe;
};

struct RGB {
    std::vector<unsigned char> canali_colore;
    Color colore;
    bool cresci;
};

struct Colors {
    RGB rgb_1;
    RGB rgb_2;
    bool RGB_Yes_No;
    std::vector<Color> colore_elementi;
    std::vector<int> scelta_elemento;
    std::vector<Color> colori_partenza;
    std::vector<Color> colori_custom;
    Color colore_temporaneo;
    int colorare;
    int elemento_da_colorare;
};

struct Triangle {
    Vector2 punto_1;
    Vector2 punto_2;
    Vector2 punto_3;
};

bool is_clicked (const Game &game,const String &stringhe ,float x, float y, int stato, int n_frase,float n_font, bool centrato) {
    if (centrato && CheckCollisionPointRec(game.pos_mouse, {game.screenWidth/2 - (float)(MeasureText(stringhe.frasi.at(stato).at(n_frase).c_str(), stringhe.dim_stringhe.at(n_font)))/2, y, float(MeasureText(stringhe.frasi.at(stato).at(n_frase).c_str(), stringhe.dim_stringhe.at(n_font))), stringhe.dim_stringhe.at(n_font)})) {
        return true;
    } else if (!centrato && CheckCollisionPointRec(game.pos_mouse, {x, y, (float)(MeasureText(stringhe.frasi.at(stato).at(n_frase).c_str(), stringhe.dim_stringhe.at(n_font))), stringhe.dim_stringhe.at(n_font)})) {
        return true;
    } else {
        return false;
    }
}

float valore_scalato(const Game &game, float valore, bool x ) {
    if (x) {
        return valore * game.screenWidth / 1920;
    } else {
        return valore * game.screenHeight / 1080;
    }
}


void stampa_elenco (const Game &game, const String &stringhe, const Colors &colori,int stato, int inizio, int fine) {
    int pos = game.screenHeight/2 - valore_scalato(game, 80, false) - valore_scalato(game, 100, false)*((fine-inizio)/2-1);
    Color colore = colori.colore_elementi.at(colori.scelta_elemento.at(2));
    for (int i = inizio; i < fine; ++i) {
        DrawText(stringhe.frasi.at(stato).at(i).c_str(), game.screenWidth * 0.02, pos, stringhe.dim_stringhe.at(2), colore);
        pos += valore_scalato(game, 100, false);
    }
}

int interazione_elenco (const Game &game, const String &stringhe,int stato, int inizio, int fine) {
    int pos = game.screenHeight/2 - valore_scalato(game, 80, false) - valore_scalato(game, 100, false)*((fine-inizio)/2-1);
    for (int i = inizio; i < fine; ++i) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && is_clicked(game, stringhe,game.screenWidth*0.02, pos, stato, i, 2, false)) {
            return i;
        }
        pos += valore_scalato(game, 100, false);
    }
    return 0;
}

void sposta_tra_stati (const Triangle &triangolo, Game &game, int stato_a_cui_andare, bool caricamento) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointTriangle(GetMousePosition(), triangolo.punto_1, triangolo.punto_2, triangolo.punto_3)) {
        if (caricamento) {
            game.stato = 1;
            game.stato_successivo = stato_a_cui_andare;
        } else {
            game.stato = stato_a_cui_andare;
        }
    }
}

void dis_scelta_elemento_colorare_stato_21 (const Game &game, const String &stringhe, const Colors &colori){
    Color colore = colori.colore_elementi.at(colori.scelta_elemento.at(2));
    DrawText(stringhe.frasi.at(21).at(0).c_str(), (GetScreenWidth() - MeasureText(stringhe.frasi.at(21).at(0).c_str(), stringhe.dim_stringhe.at(1)))/2, GetScreenHeight()*0.02, stringhe.dim_stringhe.at(1),colore);
    stampa_elenco(game, stringhe, colori, 21, 1, 5);
}

void dis_colori(const Game &game, const String &stringhe, const Colors &colori){
    int a = 0;
    int b = 0;
    std::string numero;
    DrawText( stringhe.frasi.at(22).at(0).c_str(), (game.screenWidth - MeasureText(stringhe.frasi.at(22).at(0).c_str(),stringhe.dim_stringhe.at(1)))/2,game.screenHeight*0.02,stringhe.dim_stringhe.at(1),colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    for (int i = 0; i <= colori.colore_elementi.size() + 1; ++i) {
        if (i >= 4)
            b = GetScreenHeight() / 2 - 50;

        if (i==4)
            a=0;
        DrawRectangle(game.screenWidth / 18 + a, GetScreenHeight() / 9 + 100 + b, game.screenWidth / 7.2, game.screenWidth / 7.2, DARKGRAY);
        if (i <= colori.colore_elementi.size()) {
            DrawRectangle(game.screenWidth / 18 + 5 + a, game.screenHeight / 9 + 105 + b, game.screenWidth / 7.2-10, game.screenWidth / 7.2-10, colori.colori_partenza.at(i));
        } else {
            DrawRectangle(game.screenWidth / 18 + 5 + a, game.screenHeight / 9 + 105 + b, game.screenWidth / 7.2-10, game.screenWidth / 7.2-10, colori.colori_custom.at(colori.elemento_da_colorare));
        }
        a += game.screenWidth / 4;
    }
    DrawRectangle(game.screenWidth / 18 + a, game.screenHeight / 9 + 100 + b, game.screenWidth / 7.2, game.screenHeight / 3.6, DARKGRAY);
    a=0;
    b=0;
    DrawText("1",game.screenWidth / 18 + 20,game.screenHeight / 9 + 105, 100, WHITE);
    for (int i = 2 ; i <= colori.colori_partenza.size() + 1 ; i++ ){
        a += game.screenWidth/4;
        if ( i == 5){
            a=0;
            b=game.screenHeight / 2 - 50;
        }
        if ( i <= colori.colori_partenza.size()) {
            numero = std::to_string(i);
            DrawText(numero.c_str(),game.screenWidth / 18 + 20 + a,game.screenHeight / 9 + 105 + b, 100, BLACK);
        } else {
            DrawText("custom",game.screenWidth / 18 + 20 + a,game.screenHeight / 9 + 105 + b, 70, BLACK);
        }
    }
}

void selezione_colore_stato_22 (Game &game, Colors &colori) {
    int a = 0, b = 0;
    float lato = game.screenWidth / 7.2-10, x, y;
    for (int i = 0; i <= colori.colori_partenza.size(); ++i) {
        if (i >= 4)
            b = GetScreenHeight() / 2 - 50;

        if (i==4)
            a=0;

        x = game.screenWidth / 18 + 5 + a, y = game.screenHeight / 9 + 105 + b;
        if (i < colori.colori_partenza.size()) {
            if (CheckCollisionPointRec(game.pos_mouse, {x, y, lato, lato}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                game.stato = 1;
                game.stato_successivo = 21;
                colori.colore_temporaneo = colori.colori_partenza.at(i);
                colori.colorare = 2;
            }
        } else{
            if (CheckCollisionPointRec(game.pos_mouse, {x, y, lato, lato}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                game.stato = 23;
            }
        }

        a += game.screenWidth / 4;
    }

}

void agg_pos_barretta_x_1(const Game &game, const Speeds &velocita, std::vector<Player> &giocatori) {
    float l = giocatori.at(0).barretta.width;
    if (IsKeyDown(KEY_A) && giocatori.at(0).barretta.x - l/2> 0) {
        giocatori.at(0).barretta.x -= velocita.v_barretta_1;
    } else if (IsKeyDown(KEY_D) && giocatori.at(0).barretta.x + giocatori.at(0).barretta.width < game.screenWidth/3) {
        giocatori.at(0).barretta.x += velocita.v_barretta_1;
    }
}

void agg_pos_barretta_x_2(const Game &game, const Speeds &velocita, std::vector<Player> &giocatori) {
    float l = giocatori.at(1).barretta.width;
    if (IsKeyDown(KEY_LEFT) && giocatori.at(1).barretta.x > game.screenWidth*2/3) {
        giocatori.at(1).barretta.x -= velocita.v_barretta_2;
    } else if (IsKeyDown(KEY_RIGHT) && giocatori.at(1).barretta.x + l < game.screenWidth) {
        giocatori.at(1).barretta.x += velocita.v_barretta_2;
    }
}

void agg_pos_barretta_y_1(const Speeds &velocita, std::vector<Player> &giocatori) {
    if (IsKeyDown(KEY_W) && giocatori.at(0).barretta.y > 0) {
        giocatori.at(0).barretta.y -= velocita.v_barretta_1;
    } else if (IsKeyDown(KEY_S) && giocatori.at(0).barretta.y + giocatori.at(0).barretta.height < GetScreenHeight()) {
        giocatori.at(0).barretta.y += velocita.v_barretta_2;
    }
}

void agg_pos_barretta_y_2(const Speeds &velocita, std::vector<Player> &giocatori) {
    if (IsKeyDown(KEY_UP) && giocatori.at(1).barretta.y > 0) {
        giocatori.at(1).barretta.y -= velocita.v_barretta_2;
    } else if (IsKeyDown(KEY_DOWN) && giocatori.at(1).barretta.y + giocatori.at(1).barretta.height < GetScreenHeight()) {
        giocatori.at(1).barretta.y += velocita.v_barretta_2;
    }
}

void agg_pos_pallina_y( Ball &pallina, Speeds &velocita, const std::vector<Sound> &suoni){
    if ( pallina.y - pallina.raggio <= 0 ) {
        velocita.v_ball_y = abs(velocita.v_ball_y);
        PlaySound(suoni.at(2));
    } else if (pallina.y + pallina.raggio >= GetScreenHeight()) {
        velocita.v_ball_y = -velocita.v_ball_y;
        PlaySound(suoni.at(2));
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

void agg_pos_pallina_x(Game &game ,Ball &pallina,std::vector<Player> &giocatori, Speeds &velocita, const std::vector<Sound> &suoni){
    float h = giocatori.at(0).barretta.height;
    if  (CheckCollisionCircleRec ({pallina.x, pallina.y}, pallina.raggio, giocatori.at(0).barretta) && pallina.rimbalzo) {
        velocita.v_ball_x = -velocita.v_ball_x;
        pallina.rimbalzo = false;
        pallina.x += 10;
        reset_v(game, velocita);
        velocita.v_ball_y *= (pallina.y - (giocatori.at(0).barretta.y+h/2))/(h/2);
        PlaySound(suoni.at(2));
    } else if (CheckCollisionCircleRec({pallina.x, pallina.y}, pallina.raggio, giocatori.at(1).barretta) && !pallina.rimbalzo) {
        velocita.v_ball_x = -velocita.v_ball_x;
        pallina.rimbalzo = true;
        pallina.x-= 10;
        reset_v(game, velocita);
        velocita.v_ball_y *= (pallina.y - (giocatori.at(1).barretta.y+h/2))/(h/2);
        PlaySound(suoni.at(2));
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
    float moltiplicatpre = velocita.v0* float(GetRandomValue(70, 100))/100;
    if (GetRandomValue(1,2) == 1){
        velocita.v_ball_y = -moltiplicatpre;
    } else {
        velocita.v_ball_y = moltiplicatpre;
    }
}

void dis_punteggio (int p, float pos, const Colors &colori) {
    std::string punteggio;
    punteggio = std::to_string(p);
    DrawText(punteggio.c_str(), pos, 30, 40, colori.colore_elementi.at(colori.scelta_elemento.at(2)));

}

void interruzioni (Game &game, const std::vector<Player> &giocatori, const Colors &colori, const String &stringhe) {
    int screenWidth = game.screenWidth, screenHeight = game.screenHeight;
    float dimensione_1 = stringhe.dim_stringhe.at(2), dimensione_2 = stringhe.dim_stringhe.at(3);
    Color colore = colori.colore_elementi.at(colori.scelta_elemento.at(2));
    //TODO: interruzzione per il punto del giocatore 1
    if (game.gioco == 2) {
        std::string frase = stringhe.frasi.at(25).at(3) + stringhe.frasi.at(3).at(4);
        DrawText(frase.c_str(), (screenWidth - MeasureText(frase.c_str(), dimensione_1))/2, screenHeight/2 - 35, dimensione_1, colore);
        DrawText(stringhe.frasi.at(3).at(1).c_str(), (screenWidth - MeasureText(stringhe.frasi.at(3).at(1).c_str(), dimensione_2))/2, screenHeight/2 + 35, dimensione_2, colore);
    }
    //TODO: interruzzione per il punto del giocatore 2
    else if (game.gioco == 3) {
        std::string frase = stringhe.frasi.at(25).at(4) + stringhe.frasi.at(3).at(4);
        DrawText(frase.c_str(), (screenWidth - MeasureText(frase.c_str(), dimensione_1))/2, screenHeight/2 - 35, dimensione_1, colore);
        DrawText(stringhe.frasi.at(3).at(1).c_str(), (screenWidth - MeasureText(stringhe.frasi.at(3).at(1).c_str(), dimensione_2))/2, screenHeight/2 + 35, dimensione_2, colore);
    }
    //TODO: interruzzione per l'inizio della partita
    else if (game.gioco == 0) {
        DrawText(stringhe.frasi.at(3).at(0).c_str(), (screenWidth - MeasureText(stringhe.frasi.at(3).at(0).c_str(), dimensione_1))/2, screenHeight/2, dimensione_1, colore);
    } else if ( game.gioco == 4 || game.gioco== 5 || game.pausa) {
        //TODO: interruzzione per la vittoria del giocatore 1
        if (game.gioco == 4) {
            std::string frase = stringhe.frasi.at(25).at(3) + stringhe.frasi.at(3).at(5);
            DrawText(frase.c_str(), (screenWidth - MeasureText(frase.c_str(), dimensione_1))/2, screenHeight/2 - 35, dimensione_1, colore);
        }
        //TODO: interruzzione per la vittoria del giocatore 2
        else if (game.gioco == 5) {
            std::string frase = stringhe.frasi.at(25).at(4) + stringhe.frasi.at(3).at(5);
            DrawText(frase.c_str(), (screenWidth - MeasureText(frase.c_str(), dimensione_1)) / 2, screenHeight / 2 - 35, dimensione_1,
                     colore);
        }
        //TODO: interruzzione per la pausa
        else {
            DrawText(stringhe.frasi.at(3).at(7).c_str(), (screenWidth - MeasureText(stringhe.frasi.at(3).at(7).c_str(), dimensione_1)) / 2, screenHeight /2 - 35, dimensione_1,colore);
        }
        //TODO: interruzzione esci e riavvia
        DrawText(stringhe.frasi.at(3).at(2).c_str(), (screenWidth - MeasureText(stringhe.frasi.at(3).at(2).c_str(), dimensione_2))/2, screenHeight/2 + 45, dimensione_2, colore);
        DrawText(stringhe.frasi.at(3).at(3).c_str(), (screenWidth - MeasureText(stringhe.frasi.at(3).at(3).c_str(), dimensione_2))/2, screenHeight/2 + 105, dimensione_2, colore);

    }
}

void inc_v (Speeds &velocita) {
    if (velocita.v_ball_x > 0) {
        velocita.v_ball_x += 0.005;
    } else {
        velocita.v_ball_x -= 0.005;
    }
    if (velocita.v_ball_y > 0) {
        velocita.v_ball_y += 0.005;
    } else {
        velocita.v_ball_y -= 0.005;
    }
}

void repet (Game &game, std::vector<Player> &giocatori) {
    game.gioco = 4;
    game.tempo_partita = 0;
    giocatori.at(0).barretta.height = game.h_iniz;
    giocatori.at(1).barretta.height = game.h_iniz;
}

void dis_caricamento (Rectangle &caricamento, Game &game, const String &stringhe, const Colors &colori) {
    int screenWidth = game.screenWidth, screenHeight = game.screenHeight;
    Color colore = colori.colore_elementi.at(colori.scelta_elemento.at(2));
    caricamento.width += GetRandomValue(0, 75);

    if (caricamento.width >= screenWidth) {
        game.stato = game.stato_successivo;
        caricamento.width= 0;
    }
    DrawRectangleRec(caricamento,  colori.colore_elementi.at(colori.scelta_elemento.at(1)));
    if (game.tempo < 20) {
        DrawText(stringhe.frasi.at(1).at(0).c_str(), screenWidth * 0.05, screenHeight - 2 * caricamento.height, stringhe.dim_stringhe.at(3), colore);
    } else if (game.tempo < 40) {
        DrawText(stringhe.frasi.at(1).at(1).c_str(), screenWidth * 0.05, screenHeight - 2 * caricamento.height, stringhe.dim_stringhe.at(3), colore);
    } else if (game.tempo < 60) {
        DrawText(stringhe.frasi.at(1).at(2).c_str(), screenWidth * 0.05, screenHeight - 2 * caricamento.height, stringhe.dim_stringhe.at(3), colore);
    }
}

void dis_home_stato_0 (const Game &game, const Colors &colori, const String &stringhe){
    int screenWidth = game.screenWidth, screenHeight = game.screenHeight;
    Color colore = colori.colore_elementi.at(colori.scelta_elemento.at(2));
    DrawText(stringhe.frasi.at(0).at(0).c_str(), screenWidth/2 - (float)(MeasureText(stringhe.frasi.at(0).at(0).c_str(), stringhe.dim_stringhe.at(0)))/2, screenHeight * 0.04, stringhe.dim_stringhe.at(0), colore);
    DrawText(stringhe.frasi.at(0).at(1).c_str(), screenWidth * 0.02, screenHeight * 0.7, stringhe.dim_stringhe.at(1), colore);
    DrawText(stringhe.frasi.at(0).at(2).c_str(), screenWidth * 0.02, screenHeight * 0.8, stringhe.dim_stringhe.at(1), colore);
}

void home_stato_0 (Game &game, const String &stringhe){
    int screenHeight = game.screenHeight;
    float x = GetScreenWidth() * 0.02, y1 = screenHeight * 0.7, y2 = screenHeight * 0.8;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && is_clicked(game, stringhe,x, y1, 0, 1, 1,false)) {
        game.stato = 1;
        game.stato_successivo = 2;
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && is_clicked(game, stringhe,x, y2, 0, 2, 1,false)) {
        game.stato = 1;
        game.stato_successivo = 20;
    }
    game.gioco = 0;
}

void partita_classica_stato_3 (Game &game, std::vector<Player> &giocatori, Ball &pallina, Speeds &velocita, const String &stringhe, const std::vector<Sound> &suoni) {
    float screenWidth = game.screenWidth, screenHeight = game.screenHeight;
    if (!game.pausa) {
        if (game.gioco == 0) {
            giocatori.at(0).punteggio = 9;
            giocatori.at(1).punteggio = 9;
            game.tempo_partita = 0;
            giocatori.at(0).barretta = {valore_scalato(game, 50, true), screenHeight / 2 - game.h_iniz / 2, giocatori.at(0).barretta.width, game.h_iniz};
            giocatori.at(1).barretta = {(screenWidth - valore_scalato(game, 50, true)), screenHeight / 2 - game.h_iniz / 2, giocatori.at(0).barretta.width, game.h_iniz};
            if (pallina.x != screenWidth / 2) {
                pallina.x = screenWidth / 2;
                pallina.y = GetRandomValue(pallina.raggio, screenHeight - pallina.raggio);
            }

            if (IsKeyPressed(KEY_SPACE)) {
                game.gioco = 1;
                vi_X(velocita);
                vi_y(velocita);
                if (velocita.v_ball_x < 0) {
                    pallina.rimbalzo = true;
                } else {
                    pallina.rimbalzo = false;
                }
            }
        } else if (game.gioco == 1 || game.gioco == 2 || game.gioco == 3) {

            agg_pos_pallina_y(pallina, velocita, suoni);
            agg_pos_pallina_x(game, pallina, giocatori, velocita, suoni );
            agg_pos_barretta_y_1(velocita, giocatori);
            agg_pos_barretta_y_2(velocita, giocatori);

            if (pallina.x <= 0 || pallina.x >= screenWidth) {
                if (pallina.x <= 0) {
                    giocatori.at(1).punteggio++;
                    if (giocatori.at(1).punteggio < 10) {
                        game.gioco = 3;
                        PlaySound(suoni.at(3));
                    } else {
                        game.gioco = 5;
                        PlaySound(suoni.at(4));
                    }
                } else if (pallina.x >= screenWidth) {
                    giocatori.at(0).punteggio++;
                    if (giocatori.at(0).punteggio < 10) {
                        game.gioco = 2;
                        PlaySound(suoni.at(3));
                    } else {
                        game.gioco = 4;
                        PlaySound(suoni.at(4));
                    }
                }
                pallina.x = GetRandomValue(pallina.raggio, screenHeight - pallina.raggio);
                pallina.x = screenWidth / 2;
                velocita.v_ball_x = 0;
                velocita.v_ball_y = 0;
            }

            if ((game.gioco == 2 || game.gioco == 3) && IsKeyPressed(KEY_SPACE)){
                if (game.gioco == 2) {
                    velocita.v_ball_x = -velocita.v0;
                    pallina.rimbalzo = true;
                } else if (game.gioco == 3){
                    velocita.v_ball_x = velocita.v0;
                    pallina.rimbalzo = false;
                }
                if (IsSoundPlaying(suoni.at(3))) {
                    StopSound(suoni.at(3));
                }
                vi_y(velocita);
                repet(game, giocatori);
                game.gioco = 1;
            }
            game.tempo_partita++;
            if (game.tempo_partita > 1500 && game.gioco != 2 && game.gioco != 3) {
                inc_v(velocita);
                game.incremento += valore_scalato(game, 0.005, true);
                if (game.tempo_partita > 2000 && giocatori.at(0).barretta.height > valore_scalato(game, 30, false)) {
                    giocatori.at(0).barretta.height -= valore_scalato(game, 0.05, true);
                    giocatori.at(1).barretta.height -= valore_scalato(game, 0.05, true);
                }
            }
        }
    }
    if (game.gioco == 4 || game.gioco == 5 ||game.pausa) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && is_clicked(game, stringhe,0, screenHeight / 2 + 45, 3, 2, 3,true)) {
            game.gioco = 0;
            game.pausa = false;
            if (IsSoundPlaying(suoni.at(4))) {
                StopSound(suoni.at(4));
            }
        } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && is_clicked(game, stringhe,0, screenHeight / 2 + 105, 3, 3, 3,true)) {
            game.stato = 1;
            game.stato_successivo = 0;
            game.pausa = false;
            if (IsSoundPlaying(suoni.at(4))) {
                StopSound(suoni.at(4));
            }
        }
    }
}

void dis_partita_classica_stato_3 (Game &game, const Ball &pallina,  std::vector<Player> &giocatori, const Colors &colori, const String &stringhe) {
    int screenWidth = game.screenWidth, ScreenHeight = game.screenHeight;
    interruzioni(game, giocatori, colori, stringhe);
    DrawCircle(pallina.x, pallina.y, pallina.raggio, colori.colore_elementi.at(colori.scelta_elemento.at(0)));
    DrawRectangleRec(giocatori.at(0).barretta, colori.colore_elementi.at(colori.scelta_elemento.at(1)));
    DrawRectangleRec(giocatori.at(1).barretta, colori.colore_elementi.at(colori.scelta_elemento.at(1)));
    dis_punteggio(giocatori.at(0).punteggio, screenWidth / 4, colori);
    dis_punteggio(giocatori.at(1).punteggio, screenWidth * 0.75, colori);
    if (!(game.gioco == 0 || game.gioco == 2 || game.gioco == 3 || game.pausa)) {
        for (int i = 20; i <= ScreenHeight; i += 100) {
            DrawRectangle((screenWidth / 2) - 3, i, 6, 40, colori.colore_elementi.at(colori.scelta_elemento.at(1)));
        }
    }


}

void dis_modalita_stato_2(const Game &game, const Colors &colori, const String &stringhe) {
    int screenWidth = game.screenWidth, screenHeight = game.screenHeight / 2 - 280;
    Color colore = colori.colore_elementi.at(colori.scelta_elemento.at(2));
    DrawText(stringhe.frasi.at(2).at(0).c_str(), (screenWidth - MeasureText(stringhe.frasi.at(2).at(0).c_str(), stringhe.dim_stringhe.at(1))) / 2, screenHeight * 0.02, stringhe.dim_stringhe.at(1), colore);
    stampa_elenco(game, stringhe, colori, 2, 1, 8);

}


void dis_partita_libera_stato_4 (Game &game, const Ball &pallina,  std::vector<Player> &giocatori, const Colors &colori, const String &stringhe) {
    dis_partita_classica_stato_3(game, pallina, giocatori, colori, stringhe);
    int screenWidth =game.screenWidth, screenHeight = game.screenHeight;
    if (!(game.gioco == 0 || game.gioco == 2 || game.gioco == 3 || game.pausa)) {
        for (int i = 0; i < screenHeight; i += 80) {
            DrawRectangle((screenWidth / 3) - 3, i, 6, 20, colori.colore_elementi.at(colori.scelta_elemento.at(1)));
        }
        for (int i = 0; i < screenHeight; i += 80) {
            DrawRectangle((screenWidth * 2 / 3) - 3, i, 6, 20, colori.colore_elementi.at(colori.scelta_elemento.at(1)));
        }
    }
}

void scelta_difficolta(Ball &pallina, Speeds &velocita, Game &game, int difficolta) {
    if (difficolta == 0) {
        velocita.v0 = valore_scalato(game, 9, true);
        velocita.v_barretta_1 = valore_scalato(game, 7, true);
        velocita.v_barretta_2 = valore_scalato(game, 7, true);
        game.h_iniz = valore_scalato(game, 200, false);
        pallina.raggio = valore_scalato(game, 15, false);
    } else if (difficolta == 1) {
        velocita.v0 = valore_scalato(game, 11, true);
        velocita.v_barretta_1 = valore_scalato(game, 9, true);
        velocita.v_barretta_2 = valore_scalato(game, 9, true);
        game.h_iniz = valore_scalato(game, 180, false);
        pallina.raggio = valore_scalato(game, 13, false);
    } else {
        velocita.v0 = valore_scalato(game, 15, true);
        velocita.v_barretta_1 = valore_scalato(game, 11, true);
        velocita.v_barretta_2 = valore_scalato(game, 11, true);
        game.h_iniz = valore_scalato(game, 160, false);
        pallina.raggio = valore_scalato(game, 10, false);
    }
}

void modalita_stato_2 (Ball &pallina, Speeds &velocita, Game &game , const String &stringhe) {
    int valore = interazione_elenco(game, stringhe, 2, 1, 8);
    if (valore > 0) {
        if (valore< 3) {
            scelta_difficolta(pallina, velocita, game, 0);
        } else if (valore< 5) {
            scelta_difficolta(pallina, velocita, game, 1);
        } else if (valore< 7) {
            scelta_difficolta(pallina, velocita, game, 2);
        }
        if (valore% 2 != 0 && valore!= 7) {
            game.stato_successivo = 3;
            game.stato= 1;
        } else if (valore!= 7) {
            game.stato_successivo = 4;
            game.stato= 1;
        } else {
            game.stato = 19;
        }
    }
}

void partita_libera_stato_4 (Game &game,std::vector<Player> &giocatori,Ball &pallina,Speeds &velocita, const String &stringhe, const std::vector<Sound> &suoni) {
    partita_classica_stato_3(game, giocatori, pallina, velocita, stringhe, suoni);
    if (game.gioco >= 1 && !game.pausa) {
        agg_pos_barretta_x_1(game, velocita, giocatori);
        agg_pos_barretta_x_2(game, velocita, giocatori);
    }
}

void scelta_elemento_colorare_stato_21(const String &stringhe, Game &game, Colors &colori){
    int valore = interazione_elenco(game, stringhe, 21, 1, 5);

    if (valore != 0) {
        game.stato = 22;
        if (valore == 1) {
            colori.elemento_da_colorare = 0;
        } else if (valore == 2) {
            colori.elemento_da_colorare = 1;
        } else if (valore == 3) {
            colori.elemento_da_colorare = 2;
        } else if (valore == 4) {
            colori.elemento_da_colorare = 3;
        }
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
    if (colori.rgb_1.cresci) {
        if (colori.rgb_1.canali_colore.at(0) < 250) { colori.rgb_1.canali_colore.at(0) += velocita; }
        else if (colori.rgb_1.canali_colore.at(1) < 250) { colori.rgb_1.canali_colore.at(1) += velocita; }
        else if (colori.rgb_1.canali_colore.at(2) < 250) { colori.rgb_1.canali_colore.at(2) += velocita; } else {colori.rgb_1.cresci = false;}
    }
    else {
        if (colori.rgb_1.canali_colore.at(0) > 10) { colori.rgb_1.canali_colore.at(0) -= velocita; }
        else if (colori.rgb_1.canali_colore.at(1) > 10) { colori.rgb_1.canali_colore.at(1) -= velocita; }
        else if (colori.rgb_1.canali_colore.at(2) > 10) { colori.rgb_1.canali_colore.at(2) -= velocita; } else { colori.rgb_1.cresci =true;}
    }
    colori.rgb_1.colore = {colori.rgb_1.canali_colore.at(0), colori.rgb_1.canali_colore.at(1), colori.rgb_1.canali_colore.at(2), 255};
    colori.colore_elementi.at(4) = colori.rgb_1.colore;

    if (colori.rgb_2.cresci) {
        if (colori.rgb_2.canali_colore.at(0) < 250) { colori.rgb_2.canali_colore.at(0) += velocita; }
        else if (colori.rgb_2.canali_colore.at(1) < 250) { colori.rgb_2.canali_colore.at(1) += velocita; }
        else if (colori.rgb_2.canali_colore.at(2) < 250) { colori.rgb_2.canali_colore.at(2) += velocita; } else {colori.rgb_2.cresci = false;}
    }
    else {
        if (colori.rgb_2.canali_colore.at(0) > 10) { colori.rgb_2.canali_colore.at(0) -= velocita; }
        else if (colori.rgb_2.canali_colore.at(1) > 10) { colori.rgb_2.canali_colore.at(1) -= velocita; }
        else if (colori.rgb_2.canali_colore.at(2) > 10) { colori.rgb_2.canali_colore.at(2) -= velocita; } else { colori.rgb_2.cresci =true;}
    }
    colori.rgb_2.colore = {colori.rgb_2.canali_colore.at(0), colori.rgb_2.canali_colore.at(1), colori.rgb_2.canali_colore.at(2), 255};
    colori.colore_elementi.at(5) = colori.rgb_2.colore;
}


void full_screen (const int screenWidth) {
    if (IsKeyPressed(KEY_F11))
    {
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

void colori_custom_stato_23 (const Game &game, float pos_partenza, Colors &colori) {
    float x = game.screenWidth/5;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(game.pos_mouse, {x , pos_partenza, 40, 255})){
        colori.colori_custom.at(colori.elemento_da_colorare).r = GetMouseY() - pos_partenza;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(game.pos_mouse, {x + 80 , pos_partenza, 40, 255})){
        colori.colori_custom.at(colori.elemento_da_colorare).g = GetMouseY() - pos_partenza;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(game.pos_mouse, {x + 160 , pos_partenza, 40, 255})){
        colori.colori_custom.at(colori.elemento_da_colorare).b = GetMouseY() - pos_partenza;
    }
}

void dis_colori_custom_stato_23 (const Colors &colori, const String &stringhe, const Game &game) {
    int screenWidth = game.screenWidth, screenHeight = game.screenHeight;
    float x = screenWidth/5, pos_partenza = screenHeight/2 - 256;
    DrawRectangle(x - 10, pos_partenza-10, 220, 286, GRAY);
    DrawRectangle(x, pos_partenza, 40, 256 + 10, RED);
    DrawRectangle(x + 5, colori.colori_custom.at(colori.elemento_da_colorare).r + pos_partenza, 30, 10, BLACK);
    DrawRectangle(x + 80, pos_partenza, 40, 256 + 10, GREEN);
    DrawRectangle(x + 85, colori.colori_custom.at(colori.elemento_da_colorare).g + pos_partenza, 30, 10, BLACK);
    DrawRectangle(x + 160, pos_partenza, 40, 256 + 10, BLUE);
    DrawRectangle(x + 165, colori.colori_custom.at(colori.elemento_da_colorare).b + pos_partenza, 30, 10, BLACK);

    DrawRectangle(x - 10, pos_partenza + 306, 220, 50, GRAY);
    std::string rosso;
    rosso = std::to_string(colori.colori_custom.at(colori.elemento_da_colorare).r);
    DrawText(rosso.c_str(), x - 5, pos_partenza + 316, 30, RED);
    std::string verde;
    verde = std::to_string(colori.colori_custom.at(colori.elemento_da_colorare).g);
    DrawText(verde.c_str(), x + 75, pos_partenza + 316, 30, GREEN);
    std::string blu;
    blu = std::to_string(colori.colori_custom.at(colori.elemento_da_colorare).b);
    DrawText(blu.c_str(), x + 155, pos_partenza + 316, 30, BLUE);

    DrawRectangle(screenWidth * 4 / 5 - 266, pos_partenza - 10, 276, 276, GRAY);
    DrawRectangle(screenWidth * 4 / 5 - 256, pos_partenza, 256, 256, colori.colori_custom.at(colori.elemento_da_colorare));
    DrawText(stringhe.frasi.at(23).at(0).c_str(), (screenWidth - MeasureText(stringhe.frasi.at(23).at(0).c_str(), stringhe.dim_stringhe.at(2))) / 2, screenHeight * 0.80, stringhe.dim_stringhe.at(2), colori.colore_elementi.at(colori.scelta_elemento.at(2)));
}


void dis_impostazioni_stato_20 (const Game &game, const String &stringhe, const Colors &colori) {
    float x = game.screenWidth, y = game.screenHeight;
    Color colore = colori.colore_elementi.at(colori.scelta_elemento.at(2));
    DrawText(stringhe.frasi.at(20).at(0).c_str(), (x - MeasureText(stringhe.frasi.at(20).at(0).c_str(), stringhe.dim_stringhe.at(1)))/2, y*0.02, stringhe.dim_stringhe.at(1),colore);
    stampa_elenco(game, stringhe, colori, 20, 1, 5);

}

void impostazioni_stato_20 (Game &game, const String &stringhe) {
    int valore;
    valore = interazione_elenco(game, stringhe, 20, 1, 5);
    if (valore != 0) {
        if (valore == 1) {
            game.stato_successivo = 25;
        } else if (valore == 2) {
            game.stato_successivo = 21;
        } else if (valore == 3) {
            game.stato_successivo = 27;
        } else if (valore == 4){
            game.stato_successivo = 26;
        }
        game.stato = 1;
    }


}

void dis_nomi_stato_25 (const Colors &colori, const String &stringhe, const Game &game) {
    float x = game.screenWidth, y = game.screenHeight;
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

void nomi_stato_25 (String &stringhe, Game &game) {
    int limite = 20;
    float x = game.screenWidth, y = game.screenHeight * 0.30 + stringhe.dim_stringhe.at(1), dimensione = stringhe.dim_stringhe.at(2);
    float incremento = GetScreenHeight() * 0.30;
    if (CheckCollisionPointRec(GetMousePosition(), {x/2 - MeasureText(stringhe.frasi.at(25).at(3).c_str(), dimensione)/2, y, (float)MeasureText(stringhe.frasi.at(25).at(3).c_str(), dimensione), dimensione}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.inserimento_nome = 1;
    } else if (CheckCollisionPointRec(GetMousePosition(), {x/2 - MeasureText(stringhe.frasi.at(25).at(4).c_str(), dimensione)/2, y + incremento, (float)MeasureText(stringhe.frasi.at(25).at(4).c_str(), dimensione), dimensione}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
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

void dis_crediti_stato_26 (const Game &game, const String &stringhe, const Colors &colori) {
    float x = game.screenWidth, y =game.screenHeight;
    DrawText(stringhe.frasi.at(26).at(0).c_str(),  x/2 - MeasureText(stringhe.frasi.at(26).at(0).c_str(), stringhe.dim_stringhe.at(1))/2, y*0.02, stringhe.dim_stringhe.at(1), colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    DrawText(stringhe.frasi.at(26).at(1).c_str(),  x/2 - MeasureText(stringhe.frasi.at(26).at(1).c_str(), stringhe.dim_stringhe.at(2))/2, y/4, stringhe.dim_stringhe.at(2), colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    DrawText(stringhe.frasi.at(26).at(2).c_str(),  x/2 - MeasureText(stringhe.frasi.at(26).at(2).c_str(), stringhe.dim_stringhe.at(2))/2, y/2, stringhe.dim_stringhe.at(2), colori.colore_elementi.at(colori.scelta_elemento.at(1)));

}

void dis_sposta_tra_stati(const Triangle &triangolo, const Colors &colori) {
    DrawTriangle(triangolo.punto_1, triangolo.punto_2, triangolo.punto_3, colori.colore_elementi.at(colori.scelta_elemento.at(1)));
}



void dis_tasti_stato_27 (const Game &game, const String &stringhe, const Colors &colori) {
    float x = game.screenWidth, y = game.screenHeight;
    Color colore = colori.colore_elementi.at(colori.scelta_elemento.at(2));
    int incremento_pag = game.pagina_tasti * 5;
    if (game.pagina_tasti == 0) {
        DrawText(stringhe.frasi.at(27).at(0).c_str(), (x - MeasureText(stringhe.frasi.at(27).at(0).c_str(), stringhe.dim_stringhe.at(1)))/2, y*0.02, stringhe.dim_stringhe.at(1),colore);
    } else if (game.pagina_tasti == 1) {
        DrawText(stringhe.frasi.at(25).at(3).c_str(), (x - MeasureText(stringhe.frasi.at(25).at(3).c_str(), stringhe.dim_stringhe.at(1)))/2, y*0.02, stringhe.dim_stringhe.at(1),colore);
    } else if (game.pagina_tasti == 2) {
        DrawText(stringhe.frasi.at(25).at(4).c_str(), (x - MeasureText(stringhe.frasi.at(25).at(4).c_str(), stringhe.dim_stringhe.at(1)))/2, y*0.02, stringhe.dim_stringhe.at(1),colore);
    }
    stampa_elenco(game, stringhe, colori, 27, 1 + incremento_pag, 4 + incremento_pag + 1);
}

int stato_27_cambia_pagina (const Game &game, const Triangle &triangolo_indietro, const Triangle &triangolo_avanti) {
    if (game.pagina_tasti > 0) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointTriangle(GetMousePosition(), triangolo_indietro.punto_1, triangolo_indietro.punto_2, triangolo_indietro.punto_3)) {
            return -1;
        }
    }
    if (game.pagina_tasti < 2) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointTriangle(GetMousePosition(), triangolo_avanti.punto_1, triangolo_avanti.punto_2, triangolo_avanti.punto_3)) {
            return 1;
        }
    }
    return 0;
}

void dis_info_modalita_stato_19 (const Game &game, const String &stringhe, const Colors &colori) {
    float x = game.screenWidth, y = game.screenHeight;
    float dimensione_3 = stringhe.dim_stringhe.at(3);
    DrawText(stringhe.frasi.at(19).at(0).c_str(),  x/2 - MeasureText(stringhe.frasi.at(19).at(0).c_str(), stringhe.dim_stringhe.at(1))/2, y * 0.02, stringhe.dim_stringhe.at(1), colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    DrawText(stringhe.frasi.at(19).at(1).c_str(), x/2 - MeasureText(stringhe.frasi.at(19).at(1).c_str(), dimensione_3)/2, y *0.15 + dimensione_3, dimensione_3, colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    DrawText(stringhe.frasi.at(19).at(2).c_str(),  x/2 - MeasureText(stringhe.frasi.at(19).at(2).c_str(), dimensione_3)/2, y *0.15 + dimensione_3*2, dimensione_3, colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    DrawText(stringhe.frasi.at(19).at(3).c_str(), x/2 - MeasureText(stringhe.frasi.at(19).at(3).c_str(), dimensione_3)/2, y *0.32 , dimensione_3, colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    DrawText(stringhe.frasi.at(19).at(4).c_str(), x/2 - MeasureText(stringhe.frasi.at(19).at(4).c_str(), dimensione_3)/2, y *0.32 + dimensione_3, dimensione_3, colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    DrawText(stringhe.frasi.at(19).at(5).c_str(), x/2 - MeasureText(stringhe.frasi.at(19).at(5).c_str(), stringhe.dim_stringhe.at(1))/2, y/2 , stringhe.dim_stringhe.at(1), colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    DrawText(stringhe.frasi.at(19).at(6).c_str(), x/2 - MeasureText(stringhe.frasi.at(19).at(6).c_str(), dimensione_3)/2, y * 0.65, dimensione_3, colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    DrawText(stringhe.frasi.at(19).at(7).c_str(), x/2 - MeasureText(stringhe.frasi.at(19).at(7).c_str(), dimensione_3)/2, y * 0.65 + dimensione_3, dimensione_3, colori.colore_elementi.at(colori.scelta_elemento.at(2)));
    DrawText(stringhe.frasi.at(19).at(8).c_str(), x/2 - MeasureText(stringhe.frasi.at(19).at(8).c_str(), dimensione_3)/2, y * 0.65 + dimensione_3*2, dimensione_3, colori.colore_elementi.at(colori.scelta_elemento.at(2)));
}


void disegna_cursore ( const std::vector<Texture> &cursore){
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        DrawTexture(cursore.at(0), GetMouseX() - 7.5, GetMouseY(), WHITE);
    } else {
        DrawTexture(cursore.at(1), GetMouseX() - 7.5, GetMouseY(), WHITE);
    }
}

std::vector<std::string> split(const std::string& s, char delimiter = ' ') {
    std::stringstream in(s);
    std::string temp;
    std::vector<std::string> v;
    while(getline(in, temp, delimiter)){
        v.push_back(temp);
    }
    return v;
}

void carica_nomi (String &stringhe) {
    std::vector<std::string> temp;
    std::string riga;
    std::ifstream in ("file/nomi.csv");
    if (in) {
        std::getline(in, riga);
        temp = split(riga, ';');
        stringhe.frasi.at(25).at(3) = temp.at(0);
        stringhe.frasi.at(25).at(4) = temp.at(1);
    } else {
        std::cout << "Errore nel caricamento dei nomi, sono stati caricati i nomi di base" << std::endl;
    }
    in.close();
}

void salva_nomi (const String &stringhe) {
    std::ofstream nomi ("file/nomi.csv");
    if (nomi) {
        nomi << stringhe.frasi.at(25).at(3) << ';' << stringhe.frasi.at(25).at(4) << ';';
    } else {
        std::cout << "Errore nel salvataggio dei nomi" << std::endl;
    }

    nomi.close();
}

void carica_colori (Colors &colori){
    std::vector<std::string> temp;
    std::string riga;
    std::ifstream in ("file/colori.csv");

    if (in) {
        for (int j = 0; j < 2; ++j) {
            std::getline(in, riga);
            temp = split(riga, ';');
            for (int i = 0; i < 4; ++i) {
                if (j == 0) {
                    colori.colore_elementi.at(i).r = (unsigned char)(std::stoi(temp.at(i*3)));
                    colori.colore_elementi.at(i).g = (unsigned char)(std::stoi(temp.at(i*3+1)));
                    colori.colore_elementi.at(i).b = (unsigned char)(std::stoi(temp.at(i*3+2)));
                } else {
                    colori.colori_custom.at(i).r = (unsigned char)(std::stoi(temp.at(i*3)));
                    colori.colori_custom.at(i).g = (unsigned char)(std::stoi(temp.at(i*3+1)));
                    colori.colori_custom.at(i).b = (unsigned char)(std::stoi(temp.at(i*3+2)));
                }
            }
        }
    } else {
        std::cout << "Errore nel caricamento dei colori, quindi sono stati caricati i colori base" << std::endl;
    }
    in.close();
}

void salva_colori (const Colors &colori) {
    std::ofstream out ("file/colori.csv");
    if (out) {
        for (int i = 0; i < 4; ++i) {
            out << (int)(colori.colore_elementi.at(i).r) << ';' << (int)(colori.colore_elementi.at(i).g) << ';' <<  (int)(colori.colore_elementi.at(i).b) << ';';
        }
        out << std::endl;
        for (int i = 0; i < 4; ++i) {
            out << (int)(colori.colori_custom.at(i).r) << ';' << (int)(colori.colori_custom.at(i).g) << ';' <<  (int)(colori.colori_custom.at(i).b) << ';';
        }
    } else {
        std::cout << "Errore nel salvataggio dei colori" << std::endl;
    }

    out.close();
}

void unload_assets (std::vector<Texture> &cursore, std::vector<Sound> &suoni) {
    for (int i = 0; i < cursore.size(); ++i) {
        UnloadTexture(cursore.at(i));
    }
    for (int i = 0; i < suoni.size(); ++i) {
        UnloadSound(suoni.at(i));
    }
}

void riproduci_suoni_sottofondo (const Game &game,const std::vector<Player> &giocatori,const std::vector<Sound> &suoni) {
    if (game.stato == 3 || game.stato == 4) {
        if (game.gioco == 2 || game.gioco == 3 || game.gioco == 4 || game.gioco == 5) {
            StopSound(suoni.at(1));
        } else  if (!IsSoundPlaying(suoni.at(1)) ){
                PlaySound(suoni.at(1));
        }
        if (IsSoundPlaying(suoni.at(0))){
            StopSound(suoni.at(0));
        }
    } else {
        if (!IsSoundPlaying(suoni.at(0))){
            PlaySound(suoni.at(0));
        }
        if (IsSoundPlaying(suoni.at(1))){
            StopSound(suoni.at(1));
        }
    }
}

void caricamento_vero (const Game &game, const Colors &colori,const String &stringhe, Rectangle &caricamento, int i) {
    caricamento.width += game.screenWidth/7;
    BeginDrawing();
    ClearBackground(colori.colore_elementi.at(colori.scelta_elemento.at(3)));
    DrawText(stringhe.frasi.at(1).at(i).c_str(), game.screenWidth * 0.05, game.screenHeight - 2 * caricamento.height, stringhe.dim_stringhe.at(3), colori.colore_elementi.at(colori.scelta_elemento.at(1)));
    DrawRectangleRec(caricamento,  colori.colore_elementi.at(colori.scelta_elemento.at(1)));
    EndDrawing();
}

int main(void)
{

    InitWindow(0, 0, "Pong");
    InitAudioDevice();

    SetTargetFPS(60);


    Game game = {GetScreenWidth(), GetScreenHeight(),0, 0, 0, valore_scalato(game, 200, false)
            , 0,0, 0, 0, false, 0, GetMousePosition()};
    float l = valore_scalato(game, 15, true);

    Ball pallina= {15, (float)(game.screenWidth / 2.0),  (float)(GetRandomValue(pallina.raggio, game.screenHeight - pallina.raggio)), true};

    std::vector<Player> giocatori = {
            {0, {valore_scalato(game, 50, true), game.screenHeight / 2 - game.h_iniz / 2, l, game.h_iniz}},
            {0, {(game.screenWidth - valore_scalato(game, 50, true)), game.screenHeight / 2 - game.h_iniz / 2, l, game.h_iniz}}
    };

    Rectangle caricamento = {0,  (float)(game.screenHeight - game.screenHeight/20), float(game.screenWidth/7) , (float)(game.screenHeight/20)};

    Speeds velocita = {9,0,0, 7, 7};

    Colors colori = {
            {{0, 0, 0},
             {colori.rgb_1.canali_colore.at(0), colori.rgb_1.canali_colore.at(1), colori.rgb_1.canali_colore.at(2), 255},
             true,
            },
            {{250, 250, 250},
             {colori.rgb_2.canali_colore.at(0), colori.rgb_2.canali_colore.at(1), colori.rgb_2.canali_colore.at(2), 255},
             false,
            },
            false,
            {WHITE, WHITE, WHITE, BLACK, colori.rgb_1.colore, colori.rgb_2.colore},
            {0, 1, 2, 3},
            {BLACK, WHITE, RED, ORANGE,YELLOW,GREEN,SKYBLUE},
            {WHITE, WHITE, WHITE, WHITE},
            WHITE,
            0,
            0
    };



    String stringhe {
            {
                    {"The son of PONG", "Modalita'", "Impostazioni"},
                    {"Caricamento.", "Caricamento..", "Caricamento..."},
                    {"Modalita'" , "1)     Pong classico", "2)    Pong libero","3)    Pong classico medio","4)    Pong libero medio","5)    Pong classico difficile","6)    Pong libero difficile", "Informazioni"},
                    {"Premi spazio per iniziare", "Premere spazio per continuare", "Ricomincia da capo","Esci"," ha fatto punto"," ha vinto!", "Pausa", "Il gioco è in pausa"},
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
                    {"Modalita'", "In pong classico le barrette possono","solo salire e scendere", "In pong libero le barrette si possono","muovere in ogni direzione", "Difficolta'",
                            "Con l'aumentare della difficoltà la velocita' aumenta,", "la dimensione delle barrette diminuisce", "e il raggio della pallina diminuisce"},
                    {"Impostazioni", "1)     Modifica i nomi","2)    Colori", "4)    Associazione tasti","4)    Informazioni"},
                    {"Colori","1)    Colore della pallina","2)   Colore della barretta","3)   Colore delle scritte","4)   Colore dello sfondo"},
                    {"Seleziona un colore"},
                    {"Premi ENTER per confermare il colore"},
                    {},
                    {"Nomi", "Inserisci il nome del giocatore 1", "Inserisci il nome del giocatore 2", "Giocatore 1", "Giocatore 2"},
                    {"Crediti", "Realizzato da Stellino Marco", "Versione numero 4"},
                    {"Generali","P      attivare o disattivare la pausa", "F11    per mettere a schermo intero", "", "", "Giocatore 1", "W      per andare verso l'alto", "S      per andare verso il basso", "A      per andare verso sinistra", "D      per verso destra", "Giocatore 2", "Freccia su            per andare verso l'alto",
                            "Freccia giu'          per andare verso il basso", "Freccia sinstra     per andare verso sinistra", "Freccia destra      per verso destra"}
            },
            { valore_scalato(game, 140, false), valore_scalato(game, 100, false), valore_scalato(game, 60, false), valore_scalato(game, 45, false)}
    };

    Vector2 punto = {float(game.screenWidth*0.95), float(game.screenHeight*0.9)};

    Triangle triangolo_avanti = {
        {punto.x + valore_scalato(game, 50, true), punto.y-valore_scalato(game, 40, true)},
        {punto.x + valore_scalato(game, 50, true), punto.y + valore_scalato(game, 40, true)},
        {punto.x + valore_scalato(game, 90, true), punto.y}

    };
    Triangle triangolo_indietro = {
        {punto.x + valore_scalato(game, 40, true), punto.y-valore_scalato(game, 40, true)},
        {punto},
        {punto.x + valore_scalato(game, 40, true), punto.y + valore_scalato(game, 40, true)}

    };

    SetWindowIcon(LoadImage("assets/PONG.png"));
    ToggleFullscreen();

    carica_colori(colori);
    caricamento_vero(game, colori,stringhe, caricamento, 0);

    std::vector<Sound> suoni = {
        LoadSound("assets/chill.mp3"),
        LoadSound("assets/partita.mp3")
    };
    caricamento_vero(game, colori,stringhe, caricamento, 1);

    carica_nomi(stringhe);
    caricamento_vero(game, colori,stringhe, caricamento, 2);

    suoni.push_back(LoadSound("assets/rimbalzo.wav"));
    caricamento_vero(game, colori,stringhe, caricamento, 0);

    suoni.push_back(LoadSound("assets/punto.mp3"));
    suoni.push_back(LoadSound("assets/vittoria.mp3"));
    caricamento_vero(game, colori,stringhe, caricamento, 1);

    std::vector<Texture> cursore = {
        LoadTexture("assets/cliccato.png"),
        LoadTexture("assets/non_cliccato.png")
    };
    caricamento_vero(game, colori,stringhe, caricamento, 2);

    caricamento.width = 0;

    while (!WindowShouldClose()) {
        game.pos_mouse = GetMousePosition();
        riproduci_suoni_sottofondo(game, giocatori,suoni);

        game.tempo++;
        if (game.tempo >= 60)
            game.tempo = 0;

        if (game.stato == 0) {

            home_stato_0(game, stringhe);

        } else if (game.stato == 2) {

            modalita_stato_2(pallina, velocita, game, stringhe);

            sposta_tra_stati(triangolo_indietro, game, 0, true);

        } else if (game.stato == 3 || game.stato == 4) {

            if (IsKeyPressed(KEY_P) && giocatori.at(0).punteggio != 10 && giocatori.at(1).punteggio != 10 && game.gioco != 2 && game.gioco != 3 && game.gioco != 0) {
                game.pausa = !game.pausa;
            }

            if (game.stato == 3) {
                partita_classica_stato_3 (game, giocatori, pallina, velocita, stringhe, suoni);
            } else {
                partita_libera_stato_4(game, giocatori, pallina, velocita, stringhe, suoni);
            }


        } else if (game.stato == 19) {

            sposta_tra_stati(triangolo_indietro, game, 2, false);

        } else if (game.stato == 20) {

            impostazioni_stato_20(game, stringhe);
            sposta_tra_stati(triangolo_indietro, game, 0, true);

        } else if (game.stato == 21) {
            sposta_tra_stati(triangolo_indietro, game, 20, true);

            scelta_elemento_colorare_stato_21(stringhe, game, colori);
            if (colori.colorare == 1) {
                colori.colore_elementi.at(colori.elemento_da_colorare) = colori.colori_custom.at(colori.elemento_da_colorare);
                colori.colorare = 0;
                colori.scelta_elemento.at(colori.elemento_da_colorare) = colori.elemento_da_colorare;

            }else if (colori.colorare == 2) {
                colori.colorare = 0;
                colori.scelta_elemento.at(colori.elemento_da_colorare) = colori.elemento_da_colorare;
                colori.colore_elementi.at(colori.elemento_da_colorare) = colori.colore_temporaneo;
            }

        } else if (game.stato == 22) {

            selezione_colore_stato_22(game, colori);
            sposta_tra_stati(triangolo_indietro, game, 21, false);

        } else if (game.stato == 23) {

            colori_custom_stato_23(game, game.screenHeight/2 - 256, colori);
            sposta_tra_stati(triangolo_indietro, game, 22, false);

            if (IsKeyDown(KEY_ENTER)) {
                game.stato = 1;
                game.stato_successivo = 21;
                colori.colorare = 1;
            }

        } else if (game.stato == 25) {

            nomi_stato_25(stringhe, game);
            sposta_tra_stati(triangolo_indietro, game, 20, true);

        } else if (game.stato == 26) {

            sposta_tra_stati(triangolo_indietro, game, 20, true);

        } else if (game.stato == 27) {

            if (game.pagina_tasti == 0) {
                sposta_tra_stati(triangolo_indietro, game, 20, true);
            }
            game.pagina_tasti += stato_27_cambia_pagina(game, triangolo_indietro, triangolo_avanti);
        }

        rgb(colori);


        BeginDrawing();
        HideCursor();

        if (game.stato == 0) {
            dis_home_stato_0(game,colori, stringhe);
        } else if (game.stato == 1) {

            dis_caricamento(caricamento, game, stringhe, colori);

        } else if (game.stato == 2) {

            dis_modalita_stato_2(game,colori, stringhe);


        } else if (game.stato == 3) {

            dis_partita_classica_stato_3(game, pallina, giocatori, colori, stringhe);
        } else if (game.stato == 4) {

            dis_partita_libera_stato_4(game, pallina, giocatori, colori, stringhe);

        } else if (game.stato == 19) {
            dis_info_modalita_stato_19 (game,stringhe, colori);
        } else if (game.stato == 20) {

            dis_impostazioni_stato_20(game,stringhe, colori);

        } else if (game.stato == 21) {

            dis_scelta_elemento_colorare_stato_21(game,stringhe, colori);

        } else if (game.stato == 22) {

            dis_colori( game, stringhe, colori);

        } else if (game.stato == 23) {
            dis_colori_custom_stato_23(colori, stringhe, game);

        } else if (game.stato == 25) {

            dis_nomi_stato_25(colori, stringhe, game);

        } else if (game.stato == 26) {
            dis_crediti_stato_26(game, stringhe, colori);
        } else if (game.stato == 27) {
            dis_tasti_stato_27 (game, stringhe, colori);
            if (game.pagina_tasti < 2) {
                dis_sposta_tra_stati(triangolo_avanti, colori);
            }
        }

        if (game.stato != 0 && game.stato != 1 && game.stato != 3 && game.stato != 4) {
            dis_sposta_tra_stati(triangolo_indietro, colori);
        }


        if (game.stato != 1 && game.stato != 3 && game.stato != 4 || game.pausa || giocatori.at(0).punteggio == 10 || giocatori.at(1).punteggio == 10) {
            disegna_cursore(cursore);
        }

        ClearBackground(colori.colore_elementi.at(colori.scelta_elemento.at(3)));

        EndDrawing();
    }

    unload_assets(cursore, suoni);

    salva_nomi(stringhe);
    salva_colori(colori);
    CloseWindow();

    return 0;
}