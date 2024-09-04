#include "funzioni.h"

int main() {

    // -------------------
    //   1. Analisi dati
    // -------------------

    fstream dati;
    dati.open("dati.dat", ios::in);

    int numDati = numeroRighe("dati.dat");
    misura *mis = new misura[numDati];

    // Carica i dati sull'array di misure
    for (int i = 0; i < numDati; i++) 
        dati >> mis[i].p[0] >> mis[i].p[1] >> mis[i].p[2] >> mis[i].p[3] >> mis[i].carica; 
    
    dati.close();

    // Calcola il numero di misure con cariche positive, neutre e negative
    int carPos = 0;
    int carNeg = 0;
    int carNeut= 0;
    for (int i = 0; i < numDati; i++) {
        if (mis[i].carica > 0)
            carPos++;
        else if (mis[i].carica == 0)
            carNeut++;
        else if (mis[i].carica < 0)
            carNeg++;
    }

    stringstream analisiMisure;
    analisiMisure << "Numero di misure: " << numDati << endl  
                    << "Numero di misure con carica positiva: " << carPos << endl
                    << "Numero di misure con carica neutra: " << carNeut << endl
                    << "Numero di misure con carica negativa: " << carNeg << endl
                    << "\n% Misure con carica positiva: " << static_cast<double>(carPos) * 100 / numDati << endl
                    << "% Misure con carica neutra: " << static_cast<double>(carNeut) * 100 / numDati << endl
                    << "% Misure con carica negativa: " << static_cast<double>(carNeg) * 100 / numDati << endl;
    print(analisiMisure);


    // ------------------
    //   2. Calcolo Eta
    // ------------------
    
    // Carica i valori di eta di ogni misura
    for (int i = 0; i < numDati; i++) 
        mis[i].eta = calcEta(mis[i]);

    // Stampa l'eta dell'i-esima misura
    stringstream stringaEta;
    for (int i = 0; i < 5; i++) {
        stringaEta.str("");
        stringaEta.clear();
        stringaEta << "\nEta della misura #" << i + 1 << ": " << mis[i].eta;
        print(stringaEta);
    }

    mis = misureOrdinate(mis, numDati);

    stampaPrimeUltimeTre(mis, numDati);


    // --------------------------------------
    //   3. Media, dev std, max, min di eta
    // --------------------------------------

    // Crea tre array dinamici diversi per le cariche positive, negative e neutre
    misura *misPos = new misura[carPos];
    misura *misNeg = new misura[carNeg];
    misura *misNeut = new misura[carNeut];

    // Carica i valori delle misure sugli array rispettivi
    int jpos = 0, jneut = 0, jneg = 0;
    for (int i = 0; i < numDati; i++) {
        
        if (mis[i].carica > 0) {
            misPos[jpos] = mis[i];
            jpos++;     // incrementa l'indice dell'array di cariche positive

        } else if (mis[i].carica == 0) {
            misNeut[jneut] = mis[i];
            jneut++;

        } else if (mis[i].carica < 0) {
            misNeg[jneg] = mis[i];
            jneg++;
        }
    }

    // Stampa analisi misure di tutti i dati
    stringstream datiGen;
    datiGen << "\n\nAnalisi dati misure generali:" << endl;
    print(datiGen);

    stampaAnalisiMisure(mis, numDati);

    // Misure cariche positive
    stringstream datiPos;
    datiPos << "\n\nAnalisi cariche positive:" << endl;
    print(datiPos);

    stampaAnalisiMisure(misPos, carPos);
    
    // Misure cariche neutre
    stringstream datiNeut;
    datiNeut << "\n\nAnalisi cariche neutre:" << endl;
    print(datiNeut);

    stampaAnalisiMisure(misNeut, carNeut);

    // Misure cariche negative
    stringstream datiNeg;
    datiNeg << "\n\nAnalisi cariche negative:" << endl;
    print(datiNeg);

    stampaAnalisiMisure(misNeg, carNeg);

        
    delete[] mis;
    delete[] misPos;
    delete[] misNeg;
    delete[] misNeut;

    return 0;
}