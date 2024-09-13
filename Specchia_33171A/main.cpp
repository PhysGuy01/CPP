#include "funzioni.h"

int main() {

    // ------------------------------
    //   1. Caricamento rilevazioni
    // ------------------------------

    // Crea un array di rilev della misura opportuna
    int nRil = contaRighe("measPM10.dat");
    rilev *ril = new rilev[nRil];

    // Carica l'array con tutte le misurazioni e aggiornando
    // il numero di ril nell'emisfero boreale e australe
    int nN, nS;
    ril = loadRil(ril, nRil, nN, nS);
    

    cout << "\nNumero di rilevazioni: " << nRil << endl <<
            "Numero di ril nell'emisfero boreale: " << nN << endl <<
            "Numero di ril nell'emisfero australe: " << nS << endl << endl <<
            "Prime e ultime tre rilevazioni: " << endl << endl;

    stampaPrUltTre(ril, nRil);


    // ------------------------
    //   2. Scrematura misure
    // ------------------------

    // Salva tutte e sole le rilevazioni ottenute 
    // nell'emisfero boreale in un array di rilev
    rilev *rilBor = new rilev[nN];
    rilBor = scremaRil(ril, rilBor, nRil);


    cout << "---------------------------------------------" << endl << endl;

    // Stampa la rilevazione di latitudine massima
    rilev max = maxLat(rilBor, nN);
    cout << "Rilevazione di latitudine massima: " << endl <<
            "\tLatitudine: " << max.loang << " " << max.lodir << endl <<
            "\tLongitudine: " << max.laang << " " << max.ladir << endl <<
            "\tConcentrazione: " << max.conc << endl << endl; 
    

    // Stampa la rilevazione di latitudine minima
    rilev min = minLat(rilBor, nN);
    cout << "Rilevazione di latitudine minima: " << endl <<
            "\tLatitudine: " << min.loang << " " << min.lodir << endl <<
            "\tLongitudine: " << min.laang << " " << min.ladir << endl <<
            "\tConcentrazione: " << min.conc << endl << endl << 
            "---------------------------------------------" << endl << endl;

    
    // -------------------------
    //   3. Caricamento strips
    // -------------------------

    // Crea un array di fasce della misura opportuna
    int nSt = contaRighe("strips.dat");
    strip *st = new strip[nSt];

    st = loadSt(st, nSt);

    cout << "Numero di strips caricate: " << nSt << endl << endl <<
            "Fasce caricate: " << endl << endl;
    
    stampaStrips(st, nSt);

    cout << "---------------------------------------------" << endl << endl;


    // -----------------------------------
    //   4&5. Media inquinanti per fasce
    // -----------------------------------

    // Calcola la media per ogni fascia e il numero di rilevazioni
    st = calcMediaSt(st, nSt, rilBor, nN);

    // Crea un nuovo array di strip della stessa misura dell'originale 
    // e lo ordina per media di inquinanti crescente
    strip *ordSt = new strip[nSt];
    ordSt = sortSt(st, ordSt, nSt);

    cout << "Fasce in ordine di media di inquinanti crescente: " << endl << endl;

    // Stampa le fasce ordinate per media
    stampaStrips(ordSt, nSt);


    // --------------------------------------------------
    //   6. Catalogazione strip migliorate e peggiorate
    // --------------------------------------------------

    // Salva nel file appropriato le fasce in cui 
    // l'inquinamento e' migliorato o peggiorato
    salvaGoodBad(ordSt, nSt);



    delete[] ril;
    ril = nullptr;

    delete[] rilBor;
    rilBor = nullptr;

    delete[] st;
    st = nullptr;

    delete[] ordSt;
    ordSt = nullptr;

    return 0;
}