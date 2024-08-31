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
    float r;
    int cap;
    char id;
    int n_bact;
};

struct batterio {
    float x;
    float y;
    char killed_by;
};

// Dichiarazione delle funzioni
int contaRighe(string filename);
linfocita* loadLinf(linfocita* linf, int nLinf);
void print(stringstream &v);
void stampaLinf(linfocita* linf, int nLinf);
batterio* loadBatt(batterio* batt, int nBat);
void fight(batterio* batt, int nBat, linfocita* linf, int nLinf);
linfocita* sortLinf(linfocita* linf, int nLinf);
void stampaMinMaxX(batterio* batt, int nBatt);