#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

struct evento {
    double p1[4]; // energia-momento particella 1 (E1, p1x, p1y, p1z)
    double p2[4]; // energia-momento particella 2 (E2, p2x, p2y, p2z)
    bool segnale; // Segnale se 1|true, background se 0|false
    double massainv; // Massa invariante
};

int contaRighe(string filename);
void print(stringstream &ss);
evento* loadEventi(evento*ev, int nEv);
int nEventiSegnale(evento* ev, int nEv);
double calcMassaInv(evento ev);
evento* aggMassaInv(evento* ev, int nEv);
evento* sortEvPerMassa(evento* ev, int nEv);
void stampaPrimiUltimiQuattroEv(evento* ev, int nEv);
void dividiEventiSegnale(evento *ev, int nEv, evento* seg, int nSeg, evento* bg, int nBg);
double calcMedia(evento* ev, int nEv);
double calcDevStd(evento *ev, int nEv);
double calcMaxMassa(evento* ev, int nEv);
double calcMinMassa(evento* ev, int nEv);