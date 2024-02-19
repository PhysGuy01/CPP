#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct cilindro{
    float diam; //Diametro reale
    char col; //Colore
    float exact; //Diametro nominale
    float atoll; //tolleranza (limite sup valore assoluto scarto)
    float discr; //Scarto tra diam e exact
};

int contaRighe(string filename);
cilindro* loadCil(cilindro *cil, int &nCil);
void print(stringstream &v);
void stampaCil(cilindro *cil, int &nCil);
cilindro *ordinaCil(cilindro *cil, int &nCil);
void contaCol(cilindro *cil, int &nCil, int &nBlu, int &nRos, int &nGial);
cilindro *scremaBlu(cilindro *cil, cilindro *cilBlu, int &nCil, int &nBlu, int &nBluAgg);