#include <algorithm> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>


using namespace std;

struct evento {
    float p1[4];   // Energia-momento particella 1 (E, p1x, p1y, p1z)
    float p2[4];   // Energia-momento particella 2 (E, p2x, p2y, p2z)
    bool segnale;   // Segnale 1 true, 0 false = background
    float massainv;// Massa inv
};

int contaRighe(string filename);
void print(stringstream &v);
float calcMassInv(evento mis);
evento *aggMassInv(evento *mis, int &nMis);
void stampaPrimeDieciMasse(evento *mis);
evento *sortMasse(evento *mis, int &nMis);
void stampaPrimeUltimeQuattro(evento *mis, int &nMis);
evento *eventiSegnale(evento *mis, int &nMis, int &nSeg);
evento *eventiBackground(evento *mis, int &nMis, int &nBack);
float calcMedia(evento *mis, int &nMis);
float calcDevStd(evento *mis, int &nMis);
float maxMassa(evento *mis, int &nMis);
float minMassa(evento *mis, int &nMis);