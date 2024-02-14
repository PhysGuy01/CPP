#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct misure {
    int t;      // instante della misura
    double vx;  // coordinata vx dell'oggetto
    double vy;  // coordinata vy dell'oggetto
    double vz;  // coordinata vz dell'oggetto
    double K;   // energia cinetica totale dell'oggetto
    double massa; // massa dell'oggetto in moto
};


void print(stringstream &v);
int contaRighe(string filename);
void stampaMisure(const misure *m, int &nMis);
misure *sortMisure(misure *m, int &nMis);
void calcolaPosizione(const misure m, double &x, double &y, double &z);
double calcolaMassa(misure m);
double meanM(misure *m, int &nMis);
double calcDevStdM(misure *m, int &nMis);