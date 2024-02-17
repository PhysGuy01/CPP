#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct evento {
    double p1[4]; // energia-momento particella 1 (E1, p1x, p1y, p1z)
    double p2[4]; // energia-momento particella 2 (E2, p2x, p2y, p2z)
    bool segnale; // Segnale se 1|true, background se 0|false
    double massainv; // Massa invariante
    double eta; // Pseudo-rapidita'
};

int contaRighe(string filename);
evento *loadData(evento *ev, int &nMis, string filename, int &nSeg);
void print(stringstream &v);
double calcMassaInv(evento ev);
evento *aggMassaInv(evento *ev, int &nMis);
void stampaPrimeUltimeCinque(evento *ev, int &nMis);
evento *sortMasse(evento* ev, int &nMis);
void stampaPrimUltQuattro(evento *ev, int &nMis);
double calcMediaMassa(evento *ev, int &nMis);
double calcDevStdMassa(evento *ev, int &nMis);
double pseudoRap(evento ev);
evento *aggPseudoRap(evento *ev, int &nMis);
double calcMediaRap(evento *ev, int &nMis);
double calcDevStdRap(evento *ev, int &nMis);