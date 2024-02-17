#include "funzioni.h"

int main() {
    
    // -----------------------
    //   1. Caricamento dati
    // -----------------------

    int nMis = contaRighe("eventi.dat");
    int nSeg = 0;

    evento *ev = new evento[nMis];

    ev = loadData(ev, nMis, "eventi.dat", nSeg);

    stringstream sout;
    sout << "\nNumero di eventi tot: " << nMis << endl <<
            "Numero di eventi di tipo segnale: " << nSeg << endl <<
            "\t-Perc. sul tot: " << nSeg * 100 / nMis << endl <<
            "Numero di eventi di tipo background: " << (nMis - nSeg) << endl <<
            "\t-Perc. sul tot: " << (nMis - nSeg) * 100 / nMis << endl;
    print(sout);


    // -------------------------------
    //   2. Calcolo masse invarianti
    // -------------------------------

    ev = aggMassaInv(ev, nMis);

    stampaPrimeUltimeCinque(ev, nMis);

    
    // -------------------------------------------------
    //   3. Ordinamento per massa invariante crescente
    // -------------------------------------------------

    ev = sortMasse(ev, nMis);

    stampaPrimUltQuattro(ev, nMis);

    // Crea un array con solo eventi segnale
    evento* evSeg = new evento[nSeg]; 
    int jSeg = 0;
    for (int i = 0; i < nMis; i++) 
        if (ev[i].segnale){
            evSeg[jSeg] = ev[i];
            jSeg++;
        }

    double media = calcMediaMassa(evSeg, nSeg);
    double sigma = calcDevStdMassa(evSeg, nSeg);
    sout << "\n\nMedia delle masse di eventi di tipo segnale: " << media << endl <<
            "Deviazione std delle masse di eventi di tipo segnale: " << sigma << endl;
    print(sout);

    
    // ----------------------
    //   4. Pseudo-rapidità
    // ----------------------

    evSeg = aggPseudoRap(evSeg, nSeg);

    // Calcola il numero di eventi segnale rilevanti (con massa invariante compresa in un sigma)
    int nEvSegRil = 0;
    for (int i = 0; i < nSeg; i++) 
        if (evSeg[i].massainv > media - sigma && evSeg[i].massainv < media + sigma)
            nEvSegRil++;

    // Carica tutti gli eventi di segnale interessanti in un array separato
    evento *evSegRilevanti = new evento[nEvSegRil];
    int jSegRil = 0;
    for (int i = 0; i < nSeg; i++) 
        if (evSeg[i].massainv >  media - sigma && evSeg[i].massainv < media + sigma){
            evSegRilevanti[jSegRil] = evSeg[i];
            cout << "evSegRil: " << evSeg[i].eta << endl;
            jSegRil++;
        }
    

    sout << "\n\nMedia delle eta: " << calcMediaRap(evSegRilevanti, nEvSegRil) << endl <<
            "Deviazione std delle eta: " << calcDevStdRap(evSegRilevanti, nEvSegRil) << endl;
    print(sout);

    delete[] evSegRilevanti;
    evSegRilevanti = nullptr;
    delete[] evSeg;
    evSeg = nullptr;
    delete[] ev;
    ev = nullptr;

    return 0;
}