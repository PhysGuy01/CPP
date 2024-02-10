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

// stampa su schermo e su un file txt separato
void print(stringstream v);