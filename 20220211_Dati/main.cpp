#include "funzioni.h"

int main() {

    // --------------------------------------
    //   1. Caricamento schema di soluzione
    // --------------------------------------

    int N;
    val *schema = loadVal(N);

    cout << "Numero di domande: " << N << endl;

    // Per ogni domanda stampa la risposta corretta e il numero di punti
    // assegnati a tale risposta, poi aggiunge i punti al conteggio totale
    int puntiTot = 0;
    for (int i = 0; i < N; i++){
        cout << "Domanda #" << i + 1 << ": " 
            << "(" << schema[i].r << ", " << schema[i].p << ")" << endl;
        puntiTot += schema[i].p;
    }

    cout << "Punti totali assegnabili: " << puntiTot << endl;
    

    // ----------------------------
    //   2. Caricamento elaborati
    // ----------------------------

    int nElab = contaElab();

    elaborato *elabs = new elaborato[nElab]; 
    elabs = loadElaborati(elabs, nElab, N);

    stampaPrimiUltimiCinque(elabs, nElab, N);


    // -----------------------
    //   3. Calcolo dei voti
    // -----------------------

    elabs = aggPuntElabs(elabs, nElab, schema, N);

    stampaPrimiUltimiCinque(elabs, nElab, N);


    // -----------------------------------
    //   4&5. Stampa esiti e statistiche
    // -----------------------------------

    elabs = ordinaMatrElab(elabs, nElab);

    stampaEsiti(elabs, nElab);

    stampaStatistiche(elabs, nElab);


    delete[] schema;
    schema = nullptr;

    delete[] elabs;
    elabs = nullptr;

    return 0;
}