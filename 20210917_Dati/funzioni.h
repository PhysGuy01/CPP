#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct replica {
    string nome; // nome del partone
    double *data; // array contenten i N valori
    double arclength; // lunghezza di un arco
    int negdata; // numero di valori negativi in data
};

int contaRighe(string filename);
double *loadXgrid(int &N, double &max, double &min);
void print(stringstream &v);
replica *loadData(int &N, int &M);
void stampPrimeUltimeTre(replica *gl, int &N, int &M);
replica *aggNegData(replica *gl, int &N, int &M);
double calcArcLen(replica gl, int &N, double *xgrid);
replica *aggArcLen(replica *gl, int &N, int &M, double* xgrid);
double maxLen(replica *gl, int &M);
double calcMediaLen(replica *gl, int &M);
double calcDevStdLen(replica *gl, int& M, double &mean);
replica *aggRepliche(replica *gl, int &M, int &nGlAgg, double &mean,  double &sigma);