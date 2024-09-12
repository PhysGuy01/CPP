#pragma once

#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct giocatore {
    int cod; 
    bool is_pro;
    int tot_punt;
    int nmani;
};

struct mano
{
    int cod;
    int punti;
};

void print(stringstream &v);
int numeroPro(giocatore *g, int &n);
string isProAma(giocatore g);
void stampaGiocatori(giocatore *g, int &n);
void ordinaGiocatori(giocatore *g, int &n);
int codiceAGiocatore(giocatore *g, int codice, int &n);
void stampaClassifica(mano *classificati, int &p);
void ordinaClassificati(mano *classificati, int &p);