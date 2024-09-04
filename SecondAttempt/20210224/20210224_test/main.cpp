#include "funzioni.h"

int main() {
    
    // ----------------------------------------
    //   1. Caricamento misurazioni e modelli
    // ----------------------------------------

    // Conta le misure e le carica su un array di misura
    int nMis = contaRighe("misure.dat");
    misura *mis = new misura[nMis];

    mis = loadMis(mis, nMis);


    // Conta il numero di modelli e li carica su un array di modello
    int nMod = contaRighe("modelli.dat");
    modello *mod = new modello[nMod];

    mod = loadMod(mod, nMod);


    // Stampa il numero di misure e modelli caricati
    stringstream sout;

    sout << "\nNumero di misure caricate: " << nMis << endl <<
            "Numero di modelli: " << nMod << endl << endl <<
            "--------------------------------------------" << endl << endl <<
            "Modelli: " << endl << endl;

    print(sout);


    // Stampa i parametri di ogni modello
    for (int i = 0; i < nMod; i++) {
        sout << "Modello #" << i + 1 << endl <<
                "\tParametri: " << mod[i].a << ", " << mod[i].b << ", " << mod[i].c << endl << endl;
        print(sout);
    }


    sout << "--------------------------------------------" << endl << endl <<
            "Prime e ultime tre misure: " << endl << endl;

    print(sout);

    stampaPrimUltTreMis(mis, nMis);

    
    // ----------------------------
    //   2. Ordinamento per tempo
    // ----------------------------

    mis = sortMis(mis, nMis);

    sout << "--------------------------------------------" << endl << endl <<
            "Prime e ultime tre misure riordinate per tempo: " << endl << endl;

    print(sout);

    stampaPrimUltTreMis(mis, nMis);

        
    // -------------------------
    //   3. Calcola chi quadro
    // -------------------------

    mod = aggChiQuadMod(mod, nMod, mis, nMis);

    sout << "--------------------------------------------" << endl << endl <<
            "Chi2 di ogni modello: " << endl << endl;

    print(sout);

    for (int i = 0; i < nMod; i++) {
        sout << "Chi2 del modello #" << i + 1 << ": " << mod[i].chi2 << endl;
        print(sout);
    }

    mod = sortModChi2(mod, nMod);

    sout << "\n--------------------------------------------" << endl << endl <<
            "Parametri del modello migliore: " << mod[0].a << " " << mod[0].b << " " << mod[0].c << endl << endl;
    print(sout);


    delete[] mis;
    mis = nullptr;

    delete[] mod;
    mod = nullptr;

    return 0;
}