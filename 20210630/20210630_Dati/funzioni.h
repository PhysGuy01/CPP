#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

struct linfocita {
    float x;
    float y;
    int cap; // capacità, numero di batteri fagocitabili
    float r;
    char id;
    int n_bact;
};

struct batterio {
float x;
float y;
char killed_by;
};

int contaRighe(string filename);
linfocita *loadLinf(linfocita* linf, int nLinf);
void print(stringstream &v);
void stampaLinf(linfocita* linf, int nLinf);
batterio *loadBatt(batterio *batt, int nBatt);
double calcDist(linfocita linf, batterio batt);
linfocita* sortLinf(linfocita* linf, int nLinf);
void stampaBattAgg(batterio* batt, int nBatt);
void ascBattVivi(batterio *batt, int nBatt, int &minx, int &maxx);