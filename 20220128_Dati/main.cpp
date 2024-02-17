#include "funzioni.h"

int main() {

    // ----------------------------
    //   1. Caricamento pacchetti
    // ----------------------------

    int nPacks = contaRighe("data.dat");
    netpacket *pack = new netpacket[nPacks];

    pack = loadData(pack, nPacks);

    stringstream sout;


    // ---------------------------------------------------------------------------------
    //   2&3. Screma i pacchetti corrotti e li ordina in ordine di timestamp crescente
    // ---------------------------------------------------------------------------------

    // Crea un nuovo array di pacchetti sopravvissuti
    int nGood;
    netpacket *gPack = goodPack(pack, nPacks, nGood);

    sout << "Numero di pacchetti caricati: " << nPacks << endl <<
            "Pacchetti di buona qualità: " << nGood << endl <<
            "Pacchetti corrotti: " << nPacks - nGood << endl <<
            "\n------------------------------------------" << endl;
    print(sout, "risultati.dat");

    gPack = sortPacks(gPack, nGood);
    stampaPacchetti(gPack, nGood);


    // -----------------------
    //   4. Stampa messaggio
    // -----------------------

    stampaMess(gPack, nGood);

    delete[] pack;
    pack = nullptr;
    delete[] gPack;
    gPack = nullptr;

    return 0;
}