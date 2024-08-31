#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

struct misura {
    double tempo;
    char unita;
    double x;
};

struct modello {
    double a, b, c;
    double chi2;
};

int contaRighe(string filename);
misura* loadMis(misura* mis, int nMis);
modello* loadMod(modello* mod, int nMod);
void print(stringstream &v);
misura* ordinaMis(misura* mis, int nMis);
void printaPrimeUltimeTreMis(misura* mis, int nMis);
double calcPred(double t, modello mod);
modello* aggChiQuad(modello* mod, int nMod, misura* mis, int nMis);
modello* ordinaModelli(modello* mod, int nMod);