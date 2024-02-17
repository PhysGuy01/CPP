#include "funzioni.h"

int main() {

    // -----------------------
    //   1. Caricamento dati
    // -----------------------

    int nMis = contaRighe("data.dat");
    misura *m = new misura[nMis];

    m = loadData(m, nMis, "data.dat");

    stringstream sout;

    sout << "\nNumero di misurazioni: " << nMis << endl <<
            "Misure:" << endl;
    print(sout);

    stampaMisure(m, nMis);

    // -------------------------
    //   2. Ordinamento misure
    // -------------------------

    m = sortMisure(m, nMis);

    sout << "\nMisure in ordine di tempo crescente:" << endl;
    print(sout);

    stampaMisure(m, nMis);


    // --------------------------
    //   3. Calcolo della massa
    // --------------------------

    m = aggMasse(m, nMis);

    stampaMisure(m, nMis);

    sout << "\n\nMedia delle masse: " << calcMedia(m, nMis) << endl
            << "Deviazione standard: " << calcDevStd(m, nMis) << endl;
    print(sout);


    // -----------
    //   4. ????
    // -----------

    // ?????

    // ------------------------
    //   5. Calcolo posizione
    // ------------------------

    posInCinDieQuind(m, nMis);
    /*
    for (int i = 0; i < nMis; i++) {
        delete[] m[i].v;
    }
    */
    delete[] m;

    return 0;
}