#include "funzioni.h"

int main() {

    // -------------------------
    //   1. Caricamento misure
    // -------------------------

    // Conta il numero di misurazioni e crea un array di quelle dimensioni
    int nMis = contaRighe("dati.dat");
    misura* mis =  new misura[nMis];

    fstream data;
    data.open("dati.dat", ios::in);

    // Carica le misure dal file dati sull'array
    for (int i = 0; i < nMis; i++)
        data >> mis[i].t >> mis[i].mis >> mis[i].temp;
    
    data.close();

    // Stampa il numero di misure lette
    stringstream out;
    out << "Numero di misure lette: " << nMis << endl;
    print(out);

    stampaPrimeUltimeTre(mis, nMis);


    // -------------------------------------
    //   2. Scrematura misure inaffidabili
    // -------------------------------------

    // Screma le misure e aggiorna il numero di misure rimaste
    int nMisGiuste = 0;
    mis = scremaMisure(mis, nMis, nMisGiuste);

    // Calcola il numero di misure con valore 1 e 0
    int nUno = 0;
    int nZero= 0;
    for (int i = 0; i < nMisGiuste; i++) {
        if (mis[i].mis == 0) 
            nZero++;
        else if (mis[i].mis == 1)
            nUno++;
    }

    // Stampa il numero di misure affidabili e le frequenze di 1 e 0
    stringstream misAffid;
    misAffid << "\n\nNumero di misure affidabili: " << nMisGiuste << endl <<
                "Numero di misure con valore 0: " << nZero << endl <<
                "Frequenza: " << static_cast<double>(nZero) / nMisGiuste << endl << 
                "Numero di misure con valore 1: " << nUno << endl << 
                "Frequenza: " << static_cast<double>(nUno) / nMisGiuste << endl;
    print(misAffid);


    // --------------------------------
    //   3. Ordinamento e stato qubit
    // --------------------------------

    // Aggiorna l'array ordinandolo in ordine crescente di t
    mis = ordinaMisure(mis, nMisGiuste);

    // Stampa le prime e le ultime tre misure ordinate
    stringstream misOrdinate;
    misOrdinate << "\n\nPrime e ultime tre misure ordinate:" << endl;
    print(misOrdinate);

    stampaPrimeUltimeTre(mis, nMisGiuste);


    // Aggiornamento stato qubit

    // Conta le misure nel primo secondo set e gli zero e gli uno in ciascun set
    int misPrimoSet, misSecSet, misTerSet;
    int zeroPrSet, zeroSecSet, zeroTerSet;
    int unPrSet, unSecSet, unTerSet;

    contaMisureInter(mis, nMisGiuste, misPrimoSet, misSecSet, misTerSet,
                                    zeroPrSet, zeroSecSet, zeroTerSet,
                                    unPrSet, unSecSet, unTerSet);
    
    // Calcola la frequenza di zeri nel primo, secondo e terzo set
    double freqZPrSet = static_cast<double>(zeroPrSet) / misPrimoSet;
    double freqZSecSet = static_cast<double>(zeroSecSet) / misSecSet;
    double freqZTerSet = static_cast<double>(zeroTerSet) / misTerSet;

    // Calcola la frequenza di uno nel primo, secondo e terzo set
    double freqUPrSet = static_cast<double>(unPrSet) / misPrimoSet;
    double freqUSecSet = static_cast<double>(unSecSet) / misSecSet;
    double freqUTerSet = static_cast<double>(unTerSet) / misTerSet;

    // Assegna lo stato corrispondente al primo, secondo e terzo set
    char statoPrimSet= detStato(freqZPrSet, freqUPrSet);
    char statoSecSet = detStato(freqZSecSet, freqUSecSet);
    char statoTerSet = detStato(freqZTerSet, freqUTerSet);

    // Aggiorna lo stato delle misure del qubit
    mis = aggMisureStato(mis, nMisGiuste, statoPrimSet, statoSecSet, statoTerSet);


    // Crea un nuovo array con solo le misure di stato |+>
    int nMisPiu;
    misura *misPiu = statoPiu(mis, nMisGiuste, nMisPiu);

    // Stampa le prime e le ultime tre misure dal nuovo array 
    stringstream strStatoPiu;
    strStatoPiu << "\nPrime e ultime tre misure con stato |+>";
    print(strStatoPiu);

    stampaPrimeUltimeTre(misPiu, nMisPiu);


    delete[] mis;
    delete[] misPiu;

    return 0;
}