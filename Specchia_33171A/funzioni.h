#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct rilev {
    double loang;   // Latitudine
    char lodir;     // Emisfero ('N' o 'S')
    double laang;   // Longitudine
    char ladir;     // Direzione ('W' o 'E')
    int conc;       // Concentrazione inquinanti
};


struct strip {
    double anginf;  // Ang di inizio fascia
    double angsup;  // Ang di fine fascia
    int prev;       // Media precedente
    double m;       // Media attuale
    int nrilev;     // Numero di rilev nella fascia
};


int contaRighe(string filename);

rilev *loadRil(rilev *ril, int nRil, int &nN, int &nS);
void stampaPrUltTre(rilev *ril, int nRil);

rilev *scremaRil(rilev *ril, rilev *rilBor, int nRil);
rilev maxLat(rilev *rilBor, int nN);
rilev minLat(rilev *rilBor, int nN);

strip *loadSt(strip *st, int nSt);
void stampaStrips(strip *st, int nSt);

strip *calcMediaSt(strip *st, int nSt, rilev *rilBor, int nN);
strip* sortSt(strip *st, strip *ordSt, int nSt);

void salvaGoodBad(strip *st, int nSt);