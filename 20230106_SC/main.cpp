#include "funzioni.h"

int main(){

    // -----------------------
    //   1. Caricamento dati
    // -----------------------

    // Conta il numero di misurazioni e crea un array di eventi
    int nMis = contaRighe("eventi.dat");
    evento *mis = new evento[nMis];

    fstream f;
    f.open("eventi.dat", ios::in);

    int nSeg = 0;
    for (int i = 0; i < nMis; i++) {
        f >> mis[i].p1[0] >> mis[i].p1[1] >> mis[i].p1[2] >> mis[i].p1[3] >> 
             mis[i].p2[0] >> mis[i].p2[1] >> mis[i].p2[2] >> mis[i].p2[3] >> mis[i].segnale;
        if (mis[i].segnale) nSeg++;
    }
    
    f.close();

    stringstream datEventi;
    datEventi << "\nNumero di misurazioni: " << nMis << endl << 
                    "Numero di segnali: " << nSeg << endl <<
                    "\tPerc. sul tot: " << static_cast<float>(nSeg) * 100 / nMis << "%" << endl << 
                    "Numero di eventi di background: " << nMis - nSeg << endl <<
                    "\tPerc. sul tot: " << static_cast<float>(nMis - nSeg) * 100 / nMis << "%" << endl;

    print(datEventi);


    // ------------------------------------------
    //   2. Calcola e aggiorna massa invariante
    // ------------------------------------------

    // Aggiorna la massa inv sull'array di eventi
    mis = aggMassInv(mis, nMis);

    // Stampa i primi dieci eventi
    stampaPrimeDieciMasse(mis);


    // -------------------
    //   3. Ordina array
    // -------------------

    // Riordina gli eventi in ordine di massa crescente
    mis = sortMasse(mis, nMis);

    // Stampa le prime e le ultime quattro misure
    stampaPrimeUltimeQuattro(mis, nMis);


    // ------------------------------------
    //   4. Analisi dati masse invarianti
    // ------------------------------------

    int nBack = 0;

    // Crea due array di eventi segnale e di background
    evento *evSeg = eventiSegnale(mis, nMis, nSeg);
    evento *evBack = eventiBackground(mis, nMis, nBack);

    stringstream anMasse;
    anMasse << "\nAnalisi di tutte le masse invarianti:" << endl
            << "Media totale: " << calcMedia(mis, nMis) << endl
            << "Dev Std Tot: " << calcDevStd(mis, nMis) << endl
            << "Max totale: " << maxMassa(mis, nMis) << endl
            << "Min totale: " << minMassa(mis, nMis) << endl
            << "\nAnalisi delle masse invarianti dei segnali:" << endl
            << "Media ev. Segnale: " << calcMedia(evSeg, nSeg) << endl
            << "Dev Std ev. Segnale: " << calcDevStd(evSeg, nSeg) << endl
            << "Max ev. Segnale: " << maxMassa(evSeg, nSeg) << endl
            << "Min ev. Segnale: " << minMassa(evSeg, nSeg) << endl
            << "\nAnalisi delle masse invarianti del background:" << endl
            << "Media ev. background: " << calcMedia(evBack, nBack) << endl
            << "Dev Std ev. background: " << calcDevStd(evBack, nBack) << endl
            << "Max ev. background: " << maxMassa(evBack, nBack) << endl
            << "Min ev. background: " << minMassa(evBack, nBack) << endl;
    print(anMasse);

    delete[] mis;
    delete[] evSeg;
    delete[] evBack;

    return 0;
}