#include "funzioni.h"

int main() {

    // -------------------------
    //  1. Caricamento bersagli
    // -------------------------

    int nBers = contaRighe("bersagli.dat");
    int nDistr = 0;
    bersaglio* bers = new bersaglio[nBers];

    bers = loadBers(bers, nBers, nDistr);

    stampaPrimiTreBers(bers, nBers);


    // -------------------------
    //   2. Caricamento colpi
    // -------------------------

    int nCol = contaRighe("alzo_angolo.dat");
    colpo* colpi = new colpo[nCol];

    colpi = loadColpi(colpi, nCol);
    
    stringstream sout;

    sout << endl << endl << "--------------------------------------" << endl << endl <<
            "Numero di colpi sparati: " << nCol << endl << endl;
    print(sout);

    stampaPrimiUltimiTreColpi(colpi, nCol);
    
    // -------------------------
    //   3. Aggiorna bersagli
    // -------------------------

    int colpiti = 0;
    int distrutti = 0;
    float dannoTOT = 0;
    
    bers = updateBers(bers, nBers, colpi, nCol, colpiti, distrutti, dannoTOT);
    
    colpo maxDist = colpoMaxDist(colpi, nCol);
    colpo minDist = colpoMinDist(colpi, nCol);

    sout << endl << endl << "--------------------------------------" << endl << endl << 
            "Numero di bersaglli distrutti: " << distrutti << endl <<
            "Numero di colpi andati a segno: " << colpiti << endl <<
            "Danno totale: " << dannoTOT << endl << endl <<
            "Colpo più lontano: " << endl <<
            "   Alzo e angolo (θ, φ): " << "(" << maxDist.theta << ", " << maxDist.phi << ")" << endl << 
            "   Coordinate (x, y): " << "(" << maxDist.xf << ", " << maxDist.yf << ")" << endl << endl << 
            "Colpo più vicino: " << endl <<
            "   Alzo e angolo (θ, φ): " << "(" << minDist.theta << ", " << minDist.phi << ")" << endl << 
            "   Coordinate (x, y): " << "(" << minDist.xf << ", " << minDist.yf << ")" << endl << endl;
    print(sout);

    delete[] bers;
    delete[] colpi;

    bers = nullptr;
    colpi = nullptr;

    return 0;
}