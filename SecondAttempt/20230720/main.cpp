#include "funzioni.h"

int main() {

    // -------------------------
    //   1. Caricamento misure
    // -------------------------

    int nMis = contaRighe("dati.dat");
    misura* mis = new misura[nMis];

    int nPos = 0, nNeg = 0, nNeu = 0;

    mis = loadMis(mis, nMis, nPos, nNeg, nNeu);

    stringstream sout;
    sout << endl << "Numero di misure lette: " << nMis << endl <<
            "Numero di misure con carica positiva: " << nPos << " (" << static_cast<double>(nPos) * 100/nMis << "%)" << endl <<
            "Numero di misure con carica neutra: " << nNeu << " (" << static_cast<double>(nNeu) * 100/nMis << "%)" << endl <<
            "Numero di misure con carica negativa: " << nNeg << " (" << static_cast<double>(nNeg) * 100/nMis << "%)" << endl << endl;
    print(sout);


    // ------------------------
    //   2. Calcolo rapidita'
    // ------------------------

    mis = aggEta(mis, nMis);

    sout << endl << "----------------------------------------------------" << endl << endl << 
            "Rapidita' delle prime cinque misure:" << endl << endl;
    print(sout);

    for(int i = 0; i < 5; i++) {
        sout << "Carica #" << i + 1 << ": " << mis[i].carica << endl << endl;
        print(sout);
    } 


    // --------------------------------
    //  3. Riordinamento e analisi eta
    // --------------------------------

    mis = sortMis(mis, nMis);

    sout << endl << "----------------------------------------------------" << endl << endl;
    print(sout);

    stampaPrimeUltimeTreMisure(mis, nMis);
    
    misura* pos = new misura[nPos];
    misura* neu = new misura[nNeu];
    misura* neg = new misura[nNeg];

    loadPosNegNeu(mis, pos, neg, neu, nMis, nPos, nNeg, nNeu);

    sout << endl << "----------------------------------------------------" << endl << endl <<
            "Media della rapidita' di tutte le misure: " << calcMedia(mis, nMis) << endl <<
            "Media della rapidita' delle misure di carica positiva: " << calcMedia(pos, nPos) << endl <<
            "Media della rapidita' delle misure di carica neutra: " << calcMedia(neu, nNeu) << endl <<
            "Media della rapidita' delle misure di carica negativa: " << calcMedia(neg, nNeg) << endl << endl <<
            "Deviazione standard della rapidita' di tutte le misure: " << calcSigma(mis, nMis) << endl <<
            "Deviazione standard della rapidita' delle misure di carica positiva: " << calcSigma(pos, nPos) << endl <<
            "Deviazione standard della rapidita' delle misure di carica neutra: " << calcSigma(neu, nNeu) << endl <<
            "Deviazione standard della rapidita' delle misure di carica negativa: " << calcSigma(neg, nNeg) << endl << endl << 
            "Valore massimo e minimo delle rapidita' di tutte le misure: " << maxEta(mis, nMis) << ", " << minEta(mis, nMis) << endl <<
            "Valore massimo e minimo delle rapidita' delle misure di carica positiva: " << maxEta(pos, nPos) << ", " << minEta(pos, nPos) << endl <<
            "Valore massimo e minimo delle rapidita' delle misure di carica neutra: " << maxEta(neu, nNeu) << ", " << minEta(neu, nNeu) << endl <<
            "Valore massimo e minimo delle rapidita' delle misure di carica negativa: " << maxEta(neg, nNeg) << ", " << minEta(neg, nNeg) << endl << endl;
    print(sout);

    delete[] mis;
    delete[] pos;
    delete[] neu;
    delete[] neg;

    mis = nullptr;    
    pos = nullptr;    
    neu = nullptr;    
    neg = nullptr;    

    return 0;
}