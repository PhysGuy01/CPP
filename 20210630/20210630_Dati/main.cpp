#include "funzioni.h"

int main() {

    // ----------------------------
    //   1. Caricamento linfociti
    // ----------------------------

    int nLinf = contaRighe("linfociti.dat");
    linfocita* linf = new linfocita[nLinf];

    linf = loadLinf(linf, nLinf);

    stringstream sout;
    sout << "Numero di linfociti caricati: " << nLinf << endl << endl <<
            "----------------------------------------------" << endl << endl <<
            "Linfociti caricati: " << endl << endl;
    print(sout);

    stampaLinf(linf, nLinf);

    sout << "\n----------------------------------------------" << endl << endl;
    print(sout);


    // --------------------------
    //   2. Caricamento batteri
    // --------------------------

    int nBatt = contaRighe("batteri.dat");
    batterio *batt = new batterio[nBatt];
    batt = loadBatt(batt, nBatt);


    // ----------------------------
    //   3. Aggiornamento batteri
    // ----------------------------
    
    // Conta i batteri fagocitati, aggiorna il numero di batteri fagocitati da ogni linfocita 
    // e la sua capacità rimasta
    double d;
    int countBatt = 0;
    for (int i = 0; i < nBatt; i++)
        for (int j = 0; j < nLinf; j++) {

            d = calcDist(linf[j], batt[i]);

            if (d < linf[j].r){
                batt[i].killed_by = linf[j].id;
                linf[j].n_bact++;
                linf[j].cap--;
                countBatt++;
            }
        }

    linf = sortLinf(linf, nLinf);
    
    sout << "\nLinfociti aggiornati in ordine decrescente di capacità: " << endl << endl;
    print(sout);

    stampaLinf(linf, nLinf);


    // -------------------------------------------
    //   4. Analisi dei batteri uccisi e rimasti
    // -------------------------------------------

    sout << "\n----------------------------------------------" << endl << endl <<
            "Batteri uccisi: " << endl << endl;
    print(sout);

    stampaBattAgg(batt, nBatt);


    int minx, maxx;
    ascBattVivi(batt, nBatt, minx, maxx);

    sout << "\n----------------------------------------------" << endl << endl <<
            "Minima ascissa dei batteri: " << minx << endl <<
            "Massima ascissa dei batteri: " << maxx << endl << endl;
    print(sout);



    delete[] batt;
    batt = nullptr;

    delete[] linf;
    linf = nullptr;

    return 0;
}