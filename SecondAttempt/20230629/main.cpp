#include "funzioni.h"

int main() {

    // -------------------------
    //   1. Caricamento misure
    // -------------------------

    int nMis = contaRighe("dati.dat");
    misura* mis = new misura[nMis];

    mis = loadMis(mis, nMis);

    stringstream sout;
    sout << endl << "------------------------------------------------" << endl << endl <<
            "Prime e ultime tre misure caricate" << endl << endl;
    print(sout);

    stampaPrimeUltimeTreMis(mis, nMis);

    // --------------------------
    //   2. Pulizia misurazioni
    // --------------------------

    int nCleanMis = 0;
    for (int i = 0; i < nMis; i++) 
        if (mis[i].temp < 30) 
            nCleanMis++;

    misura* misClean = new misura[nCleanMis];
    misClean = cleanMis(mis, misClean, nMis);

    int N1 = 0, N0 = 0;
    for (int i = 0; i < nCleanMis; i++){
        if (misClean[i].mis == 0)
            N0++;
        else 
            N1++;
    }

    sout << endl << "------------------------------------------------" << endl << endl << 
            "Numero di misure rimaste: " << nCleanMis << endl <<
            "Frequenza di 0: " << N0 << endl <<
            "Frequenza di 1: " << N1 << endl << endl;
    print(sout);

    
    // --------------------------
    //   3. Aggiornamento stato
    // --------------------------

    misClean = sortMis(misClean, nCleanMis);

    sout << endl << "------------------------------------------------" << endl << endl <<
            "Prime e ultime tre misure in ordine di tempo" << endl << endl;
    print(sout);
    
    stampaPrimeUltimeTreMis(misClean, nCleanMis);

    sout << endl << "------------------------------------------------" << endl << endl << 
            "Prime e ultime tre misure riferite al primo stato +: " << endl << endl;
    print(sout);

    misClean = aggStatoQubit(misClean, nCleanMis);

    stampaPrimeUltimeTreMisPrimoStatoPiu(misClean, nCleanMis);
    
    delete[] mis;
    delete[] misClean;

    mis = nullptr;
    misClean = nullptr;

    return 0;
}