#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct misura {
    int t;      // istante della misura
    double *v;  // array per le coordinate del vettore velocita'
    double K;   // energia cinetica totale dell'oggetto
    double massa; // massa dell'oggetto in moto
};

int contaRighe(string filename);
void print(stringstream &v);
misura *loadData(misura *m, int &nMis, string filename);
void stampaMisure(misura *m, int &nMis);
misura *sortMisure(misura *m, int &nMis);
double calcMassa(misura m);
misura *aggMasse(misura *m, int &nMis);
double calcMedia(misura *m, int &nMis);
double calcDevStd(misura *m, int &nMis);
void calcPosizione(misura m, double &x, double &y, double &z, double &w);
void posInCinDieQuind(misura *m, int &nMis);
