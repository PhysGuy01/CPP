#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct misura {
    int t;      // istante della misura in secondi
    int mis;    // 0 o 1 rilevato dagli strumenti
    float temp; // temperatura del qubit in Kelvin
    char stato; // nome della configurazione
};

int contaRighe(string filename);
void print(stringstream &ss);
misura* loadMis(misura* mis, int nMis);
void stampaPrimeUltimeTreMis(misura* mis, int nMis);
misura* cleanMis(misura* mis, misura* misClean, int nMis);
misura* sortMis(misura* mis, int nMis);
misura* aggStatoQubit(misura* misClean, int nCleanMis);
void stampaPrimeUltimeTreMisPrimoStatoPiu(misura* misClean, int nCleanMis);