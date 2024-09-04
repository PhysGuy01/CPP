#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

struct misura {
    int t;      // istante della misura in secondi
    int mis;    // 0 o 1 rilevato dagli studenti
    float temp; // temperatura del qubit in Kelvin
    char stato; // nome della configurazione
};

int contaRighe(string filename);
void print(stringstream &v);
void stampaPrimeUltimeTre(misura *m, int &nMis);
misura *scremaMisure(misura *m, int &nMis, int &nMisGiuste);
misura *ordinaMisure(misura *m, int &nMis);
void contaMisureInter(misura *m, int &nMis, int &misPrimoSet, int &misSecSet, int &misTerSet,
                                            int &zeroPrSet, int &zeroSecSet, int &zeroTerSet,
                                            int &unPrSet, int &unSecSet, int &unTerSet);
char detStato(double &freqZero, double &freqUno);
misura *aggMisureStato(misura *m, int &nMis, char &statoPrimSet, char &statoSecSet, char &statoTerSet);
misura *statoPiu(misura *m, int &nMis, int &nMisPiu);