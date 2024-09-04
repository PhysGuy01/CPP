#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

struct misura {
    double tempo; // instante della misura.
    char unita; // unita per conversione del tempo in secondi.
    double x; // posizione.
};
    
struct modello {
    double a, b, c; // parametri del modello polinomiale di secondo grado.
    double chi2; // funzione chi2 tra modello e dati.
};


int contaRighe(string filename);
misura *loadMis(misura* mis, int nMis);
modello *loadMod(modello *mod, int nMod);
void print(stringstream &v);
void stampaPrimUltTreMis(misura *mis, int nMis);
misura *sortMis(misura *mis, int nMis);
double calcPred(double tempo, modello mod);
modello *aggChiQuadMod(modello *mod, int nMod, misura *mis, int nMis);
modello *sortModChi2(modello *mod, int nMod);