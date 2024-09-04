#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#define delta 10

using namespace std;

struct bersaglio {
    float x,y; // coordinate bersaglio
    float c; // corazza
    bool distr; // stato (distrutto?)
};

struct colpo {
    float theta, phi; // alzo e angolo di tiro
    float xf, yf; // coords di impatto
    bool hit; // colpito
};

int nRighe(string filename);
int nDistrutti(bersaglio *b, int n);
void print(stringstream &v);
void stampaPrimiTreBers(bersaglio *b, int n);
double xImpatto(double theta, double phi);
double yImpatto(double theta, double phi);
void stampaPrimiUltTreColpi(colpo *c, int &n);
void aggStatoBers(bersaglio *b, int &nbersagli, colpo *c, int &ncolpi, double &colpiti, double &distrutti, double &dannoTOT);
double *distArray(colpo *c, double *dist, int &ncolpi);
double maxD(double *dist, int &ndist);
double minD(double *dist, int &ndist);
void stampaLontVic(double *dist, int &ncolpi, colpo *c);