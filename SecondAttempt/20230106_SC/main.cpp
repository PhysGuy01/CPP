#include "funzioni.h"

int main() {

    // -------------------------
    //   1. Caricamento eventi
    // -------------------------

    int nEv = contaRighe("eventi.dat");  // Numero di eventi
    evento* ev = new evento[nEv];

    ev = loadEventi(ev, nEv);
    int nSegn = nEventiSegnale(ev, nEv);

    int nBg = nEv - nSegn;

    stringstream sout;
    sout << endl << "Numero di eventi: " << nEv << endl <<
            "Numero di eventi di tipo segnale: " << nSegn << " " << (double)nSegn * 100 /nEv << "%" << endl <<
            "Numero di eventi di background: " << nBg<< " " << ((double)nEv - nSegn) * 100 / nEv << "%"  << endl << endl <<
            "--------------------------------------------------" << endl << endl;
    print(sout);


    // -------------------------
    //    2. Massa invariante
    // -------------------------

    ev = aggMassaInv(ev, nEv);

    // Stampa le masse invarianti dei primi dieci eventi
    for (int i = 0; i < 10; i++) {
        sout << "Massa invariante dell'evento #" << i + 1 << ": " << ev[i].massainv << endl;
        print(sout);
    }


    // -------------------------
    //   3. Ordinamento eventi
    // -------------------------
    
    ev = sortEvPerMassa(ev, nEv);

    sout << endl << "--------------------------------------------------" << endl << endl << 
            "Primi e ultimi quattro eventi in ordine: " << endl << endl;
    print(sout);    

    stampaPrimiUltimiQuattroEv(ev, nEv);


    // ------------------------
    //    4. Analisi eventi
    // ------------------------

    evento* seg = new evento[nSegn];
    evento* bg = new evento[nBg];

    dividiEventiSegnale(ev, nEv, seg, nSegn, bg, nBg);

    // i wish there was a better method
    sout <<  endl << "--------------------------------------------------" << endl << endl << 
            "Massa invariante media tra tutte le misure: " << calcMedia(ev, nEv) << endl <<
            "Massa invariante media tra le misure di segnale: " << calcMedia(seg, nSegn) << endl <<
            "Massa invariante media tra le misure di background: " << calcMedia(bg, nBg) << endl << endl <<
            "Dev std tra tutte le misure: " << calcDevStd(ev, nEv) << endl <<
            "Dev std tra le misure di segnale: " << calcDevStd(seg, nSegn) << endl <<
            "Dev std tra le misure di background: " << calcDevStd(bg, nBg) << endl << endl <<
            "Massa invariante massima e minima di tutte le misure: " << calcMaxMassa(ev, nEv) << ", " << calcMinMassa(ev, nEv) << endl <<
            "Massa invariante massima e minima delle misure di segnale: " << calcMaxMassa(seg, nSegn) << ", " << calcMinMassa(seg, nSegn) << endl <<
            "Massa invariante massima e minima delle misure di background: " << calcMaxMassa(bg, nBg) << ", " << calcMinMassa(bg, nBg) << endl << endl;
    print(sout);


    delete[] ev;
    delete[] seg;
    delete[] bg;

    ev = nullptr;
    seg = nullptr;
    bg = nullptr;


    return 0;
}