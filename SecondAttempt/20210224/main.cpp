#include "funzioni.h"

int main(){

    // -----------------------------
    //   1. Carica misure e modelli
    // -----------------------------

    int nMis = contaRighe("misure.dat");
    int nMod = contaRighe("modelli.dat");

    misura* mis = new misura[nMis];
    modello* mod = new modello[nMis];

    mis = loadMis(mis, nMis);
    mod = loadMod(mod, nMod);

    stringstream sout;

    sout << "-----------------" << endl <<
            "   Numero di misure: " << nMis << endl <<
            "   Numero di modelli: " << nMod << endl <<
            "-----------------" << endl << endl;
    print(sout);

    for (int i = 0; i < nMod; i++) {
        sout << " Modello #" << i + 1 << endl <<
                "   a: " << mod[i].a << endl <<
                "   b: " << mod[i].b << endl <<
                "   c: " << mod[i].c << endl << endl;
        print(sout);   
    }

    sout << "-----------------" << endl << endl <<
            " Prime e ultime tre misure: " << endl << endl;

    print(sout);

    printaPrimeUltimeTreMis(mis, nMis);

    sout << "-----------------" << endl << endl;
    print(sout);


    // -----------------------------
    //       2. Ordina misure
    // -----------------------------


    mis = ordinaMis(mis, nMis);
    
    printaPrimeUltimeTreMis(mis, nMis);


    // -----------------------------
    //          3. Chi2
    // -----------------------------

    mod = aggChiQuad(mod, nMod, mis, nMis);

    sout << "-----------------" << endl << endl;
    print(sout);

    for (int i = 0; i < nMod; i++) {
        sout << " Modello #" << i + 1 << endl <<
                "   Chi2: " << mod[i].chi2 << endl << endl;
        print(sout);
    }

    mod = ordinaModelli(mod, nMod);
    
    sout << endl << "-----------------" << endl << 
            " Miglior modello:" << endl << 
            "   Parametri: " << mod[1].a << ", " << mod[0].b << ", " << mod[0].c << endl <<
            "-----------------" << endl << endl;
    print(sout);

    return 0;
}