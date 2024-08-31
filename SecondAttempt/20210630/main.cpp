#include "funzioni.h"

int main() {

    // --------------------------------
    //     1. Caricamento linfociti
    // --------------------------------

    int nLinf = contaRighe("linfociti.dat");

    linfocita* linf = new linfocita[nLinf];
    
    linf = loadLinf(linf, nLinf);

    stringstream sout;

    sout << endl << 
            "-------------------------" << endl << endl <<
            " Linfociti caricati: " << endl << endl;

    print(sout);

    stampaLinf(linf, nLinf);


    // --------------------------------
    //     2. Caricamento batteri
    // --------------------------------

    int nBat = contaRighe("batteri.dat");

    batterio* batt = new batterio[nBat];

    batt = loadBatt(batt, nBat);
    
    sout << endl << 
            "-------------------------" << endl << endl <<
            " Batteri caricati: " << endl << endl;

    print(sout);

    // Stampa a video e sul file i parametri di ogni batterio
    for (int i = 0; i < nBat; i++) {
        sout << "Batterio #" << i + 1 << endl <<
                "   Posizione: " << batt[i].x << ", " << batt[i].y << endl <<
                "   Ucciso da: " << batt[i].killed_by << endl << endl;
        print(sout);
    }
    

    // --------------------------------
    //     3. Batteri vs Linfociti
    // --------------------------------

    fight(batt, nBat, linf, nLinf);

    linf = sortLinf(linf, nLinf);

    sout << endl << 
            "-------------------------" << endl << endl <<
            " Parametri dei linfociti aggiornati: " << endl << endl;

    print(sout);

    stampaLinf(linf, nLinf);


    // --------------------------------
    //      4. Esito dei batteri
    // --------------------------------

    sout << endl << 
            "-------------------------" << endl << endl <<
            " Parametri dei batteri fagocitati: " << endl << endl;

    print(sout);

    // Stampa a video e sul file i parametri di tutti e soli i batteri fagocitati
    for (int i = 0; i < nBat; i++) 
        if (batt[i].killed_by != 'n') {
            sout << "Batterio #" << i + 1 << endl <<
                    "   Posizione: " << batt[i].x << ", " << batt[i].y << endl <<
                    "   Ucciso da: " << batt[i].killed_by << endl << endl;
            print(sout);
        }

    stampaMinMaxX(batt, nBat);

    delete[] linf;
    delete[] batt;

    linf = nullptr;
    batt = nullptr;

    return 0;
}