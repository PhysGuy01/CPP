#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

struct misura {
    double p[4]; // energia-momento (E, px, py, pz)
    int carica;  // carica elettrica
    double eta;  // rapidità 
};

int numeroRighe(string filename);
void print(stringstream &v);
double calcEta(misura mis);
misura *misureOrdinate(misura *mis, int &nMis);
void stampaPrimeUltimeTre(misura *mis, int &nMis);
double media(misura *mis, int &nMis);
double devStd(misura *mis, int &nMis);
double min(misura *mis, int &nMis);
double max(misura *mis, int &nMis);
void stampaAnalisiMisure(misura *mis, int numDati);