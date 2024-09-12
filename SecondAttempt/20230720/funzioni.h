#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

struct misura {
    double p[4]; // energia-momento (E, px, py, pz)
    int carica; // carica elettrica
    double eta; // rapidita'
};

// Funzioni
int contaRighe(string filename);
misura* loadMis(misura* mis, int nMis, int &nPos, int &nNeg, int &nNeu);
void print(stringstream &ss);
double calcEta(misura mis);
misura* aggEta(misura* mis, int nMis);
misura* sortMis(misura* mis, int nMis);
void stampaPrimeUltimeTreMisure(misura* mis, int nMis);
double calcMedia(misura* mis, int nMis);
double calcSigma(misura* mis, int nMis);
double maxEta(misura* mis, int nMis);
double minEta(misura* mis, int nMis);
void loadPosNegNeu(misura*mis, misura* pos, misura* neg, misura* neu, int nMis, int nPos, int nNeg, int nNeu);