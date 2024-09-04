#include "funzioni.h"

int main() {

    // ---------------------------
    //   1. Caricamento bersagli 
    // ---------------------------

    // Calcoliamo il numero di bersagli e definiamo 
    // un array di bersagli di quella dimensione
    int nbersagli = nRighe("bersagli.dat");
    bersaglio *b = new bersaglio[nbersagli];

    fstream bersagli;
    bersagli.open("bersagli.dat", ios::in);

    // Carica i dati da bersagli.dat sull'array di bersagli
    for (int i = 0; i < nbersagli; i++) {
        bersagli >> b[i].x >> b[i].y >> b[i].c;
        if (b[i].c < 0) 
            b[i].distr = true;
        else 
            b[i].distr = false;
    }

    bersagli.close();

    // i. Calcola il numero di bersagli distutti e stampa i risultati
    int nBerDistr= nDistrutti(b, nbersagli);
    stringstream datiBers;
    datiBers << "Bersagli caricati: " << nbersagli << 
            "\nBersagli distrutti: " << nBerDistr << 
            "\nBersagli non distrutti: " << nbersagli - nBerDistr << endl;

    print(datiBers);

    // ii. Stampa i primi tre bersagli distutti e non
    stampaPrimiTreBers(b, nbersagli);


    // --------------------
    //   2. Analisi colpi
    // --------------------

    int ncolpi = nRighe("alzo_angolo.dat");
    colpo *c = new colpo[ncolpi];

    fstream angoli;
    angoli.open("alzo_angolo.dat", ios::in);

    // Carica i dati da alzo_angolo.dat sull'array di colpo
    for (int i = 0; i < ncolpi; i++) {
        // Carica i valori degli angoli dal file su theta(alzo) e phi(angolo di tiro)
        angoli >> c[i].theta >> c[i].phi; 
        c[i].xf = xImpatto(c[i].theta, c[i].phi);
        c[i].yf = yImpatto(c[i].theta, c[i].phi);
        c[i].hit = false;
    }

    angoli.close();

    stampaPrimiUltTreColpi(c, ncolpi);


    // -------------------------
    //   3. Stato dei bersagli
    // -------------------------

    double colpiti = 0;
    double distrutti = 0;
    double dannoTOT = 0;
    aggStatoBers(b, nbersagli, c, ncolpi, colpiti, distrutti, dannoTOT);

    // Array di distanze
    double *dist = new double[ncolpi];
    dist = distArray(c, dist, ncolpi);

    stringstream aggbers;
    aggbers << "\n\nBersagli distrutti: " << distrutti << endl
            << "Danno totale inflitto: " << dannoTOT << endl
            << "Colpi andati a segno: " << colpiti << endl
            << "Distanza max: " << maxD(dist, ncolpi) << endl
            << "Distanza min: " << minD(dist, ncolpi) << endl;
    print(aggbers);

    stampaLontVic(dist, ncolpi, c);

    delete[] dist;
    delete[] b;
    delete[] c;

    return 0;
}