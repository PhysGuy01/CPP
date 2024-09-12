#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

struct bersaglio {
    float x,y;  // coord
    float c;    // capacita'
    bool distr; // stato
};

struct colpo {
    float theta, phi;   // alzo e angolo
    float xf, yf;       // coord
    bool hit;           // a segno
};

// Funzioni
int contaRighe(string filename);
void print(stringstream &ss);
bersaglio* loadBers(bersaglio* bers, int nBers, int &nDistr);
void stampaPrimiTreBers(bersaglio* bers, int nBers);
colpo* loadColpi(colpo *colpi, int nCol);
float calcXf(colpo colpi);
float calcYf(colpo colpi);
colpo* loadColpi(colpo *colpi, int nCol);
void stampaPrimiUltimiTreColpi(colpo* colpi, int nCol);
float calcDist(bersaglio bers, colpo colpi);
float calcH(bersaglio bers, colpo colpi);
bersaglio* updateBers(bersaglio* bers, int nBers, colpo* colpi, int nCol, int &colpiti, int &distrutti, float &dannoTOT);
colpo colpoMaxDist(colpo* colpi, int nCol);
colpo colpoMinDist(colpo* colpi, int nCol);