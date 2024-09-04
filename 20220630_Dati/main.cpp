#include "funzioni.h"

int main() {
    
    // -----------------------
    //   1. Caricamento dati
    // -----------------------

    // Conta il numero di valori contenuti nel file data.dat 
    // e crea un array di quella lunghezza
    int nVal = contaRighe("data.dat");
    double* num = new double[nVal];

    // Carica i valori sull'array e conta quelli pos e neg
    int nPos, nNeg;
    num = loadData(num, nVal, nPos, nNeg);

    // Stampa a video e su file l'analisi dei dati
    stringstream sout;
    sout << "\nNumero di valori caricati: " << nVal << endl <<
            "Numero di valori positivi: " << nPos << endl <<
            "Numero di valori negativi: " << nNeg << endl;
    print(sout);


    // ----------------------------
    //   2. Caricamento parametri
    // ----------------------------

    int nPar = contaRighe("params.dat");
    neuralnet *nn = new neuralnet[nPar];
    nn = loadParams(nn, nPar);

    sout << "\nNumero di terne caricate: " << nPar << endl << 
            "Prime e ultime cinque terne: ";
    print(sout);

    stampaPrimUltCin(nn, nPar);


    // -------------------------
    //   3. Calcolo predizioni
    // -------------------------

    int *err = nErrori(nn, nPar, nVal, num);

    stampaErrNN(nPar, err, nVal);

    neuralnet bestNN = minErrori(nn, nPar, err);

    sout << "\n\nLa migliore rete neurale è stata allenata con i seguenti parametri:" << endl <<
            "\tParametro 1: " << bestNN.w1 << endl <<
            "\tParametro 2: " << bestNN.w2 << endl <<
            "\tParametro 3: " << bestNN.w3 << endl;
    print(sout);


    delete[] num;
    num = nullptr;
    delete[] nn;
    nn = nullptr;
    delete[] err;
    err = nullptr;

    return 0;
}