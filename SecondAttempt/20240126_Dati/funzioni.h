#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct giocatore {
    int cod; //codice giocatore
    bool is_pro; //true per professionista, false per amatore
    int tot_punt; //punteggio ottenuto al torneo del Palio di Masnago
    int nmani; //mani giocate al torneo del Palio di Masnago
};

struct mano {
    int cod; //codice giocatore
    int punti; //punti mano al torneo del Palio/punti classifica nazionale.
};

// funzioni
int contaRighe(string filename);
giocatore* loadGioc(giocatore* gioc, int nIscr);
void print(stringstream &ss);
mano* loadPunteggi(mano* man, int nMan);
giocatore* updateGioc(giocatore* gioc, mano* man, int nMan, int nIscr);
giocatore* updateClassifTempor(giocatore* gioc, int nIscr);
mano* loadClassif(mano* classif, int nClassificati);
mano* updateClassTot(mano* classif, int nClassificati, giocatore* gioc, int nIscr);