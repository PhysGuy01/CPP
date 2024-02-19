#include "funzioni.h"

int main() {

    // --------------------------------------
    //   1&2. Caricamento e stampa cilindri
    // --------------------------------------

    int nCil = contaRighe("cilindri.dat");
    cilindro* cil = new cilindro[nCil];
    cil = loadCil(cil, nCil);

    int nBlu, nGial, nRos;
    contaCol(cil, nCil, nBlu, nRos, nGial);
    stampaCil(cil, nCil);

    stringstream sout;
    sout << "\nNumero di cilindri: " << nCil << endl <<
            "Numero di rossi: " << nRos << endl <<
            "Numero di gialli: " << nGial << endl <<
            "Numero di blu: " << nBlu << endl << endl <<
            "-----------------------------------------" << endl << endl;
    print(sout);


    // ---------------------------------------
    //   3. Ordina cilindri per colore b g r
    // ---------------------------------------

    cil = ordinaCil(cil, nCil);

    stampaCil(cil, nCil);

    
    // ---------------------------
    //   4. Analisi cilindri blu
    // ---------------------------

    int nBluAgg = 0;
    for (int i = 0; i < nCil; i++)
        if (cil[i].col == 'b')
            if (abs(cil[i].diam - cil[i].exact) > cil[i].atoll)
                nBluAgg++;
            
    cilindro *cilBlu = new cilindro[nBluAgg]; 
    cilBlu = scremaBlu(cil, cilBlu, nCil, nBlu, nBluAgg);

    sout <<  "\n-----------------------------------------" << endl << endl;
    print(sout);
    stampaCil(cilBlu, nBluAgg);

    sout << "\n-----------------------------------------" << endl << endl <<
            "Numero di blu rimasti: " << nBluAgg << endl <<
            "Numero di blu scartati: " << nBlu - nBluAgg << endl << endl;
    print(sout);

    delete[] cilBlu;
    cilBlu = nullptr;

    delete[] cil;
    cil = nullptr;

    return 0;
}