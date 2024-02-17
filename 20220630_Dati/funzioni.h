#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct neuralnet{
    double w1; // parametro 1 della rete neurale
    double w2; // parametro 2 della rete neurale
    double w3; // parametro 3 della rete neurale
};

int contaRighe(string filename);
double *loadData(double* num, int &nVal, int &nPos, int &nNeg);
void print(stringstream &v);
neuralnet* loadParams(neuralnet *nn, int &nPar);
void stampaPrimUltCin(neuralnet *nn, int &nPar);
double g(double x); 
bool NN(double v, neuralnet pars);
int *pred(neuralnet nn, int &nVal, double *num);
int *nErrori(neuralnet *nn, int &nPar, int &nVal, double *num);
neuralnet minErrori(neuralnet *nn, int &nPar, int *err);
void stampaErrNN(int &nPar, int *err, int &nVal);