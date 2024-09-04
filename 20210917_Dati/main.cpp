#include "funzioni.h"

int main() {

    // ------------------------
    //   1. Caricamento xgrid
    // ------------------------

    int N;
    double max, min;
    double *xgrid = loadXgrid(N, max, min);

    stringstream sout;
    sout << "\n-------------------------------------" << endl << endl << 
            "Numero di elementi caricati: " << N << endl <<
            "Massimo elemento caricato: " << max << endl <<
            "Minimo elemento caricato: " << min << endl << endl <<
            "-------------------------------------" << endl << endl;
    print(sout);


    // ---------------------------
    //   2. Caricamento repliche
    // ---------------------------

    int M;
    replica *gl = loadData(N, M);

    sout << "Numero di repliche caricate: " << M << endl;
    print(sout);

    stampPrimeUltimeTre(gl, N, M);


    // --------------------------------------
    //   3. Aggiornamento dei dati negativi
    // --------------------------------------

    gl = aggNegData(gl, N, M);

    sout << "\n\n-------------------------------------" << endl << endl;
    print(sout);
    
    // Stampa il numero di dati negativi per ogni replica
    for (int i = 0; i < M; i++) {
        sout << "Dati negativi della replica #" << i + 1 << ": " << gl[i].negdata << endl;
        print(sout);
    }


    // --------------------------------------------------
    //   4. Calcolo della lunghezza di replica su xgrid
    // --------------------------------------------------

    gl = aggArcLen(gl, N, M, xgrid);

    sout << "\n-------------------------------------" << endl << endl;
    print(sout);

    for (int i = 0; i < M; i++) {
        sout << "Lunghezza della replica #" << i + 1 << ": " << gl[i].arclength << endl;
        print(sout);
    }


    // ------------------------------
    //   5. Analisi delle lunghezze
    // ------------------------------

    double mean = calcMediaLen(gl, M);
    double sigma = calcDevStdLen(gl, M, sigma);

    sout << "\n-------------------------------------" << endl << endl <<
            "Media delle lunghezze: " << mean << endl <<
            "Deviazione standard: " << sigma << endl << 
            "Valore massimo: " << maxLen(gl, M) << endl << endl <<
            "Repliche rilevanti rimaste: " << endl;
    print(sout);

    int nGlAgg = 0;
    replica *glAgg = aggRepliche(gl, M, nGlAgg, mean, sigma);

    for (int i = 0; i < nGlAgg; i++) {
        sout << "Replica #" << i + 1 << ": " << endl <<
                "\tLunghezza dell'arco: " << glAgg[i].arclength << endl <<
                "\tNumero di valori negativi: " << glAgg[i].negdata << endl <<
                "\tDati: ";
        print(sout);
        for (int j = 0; j < N; j++) {
            sout << glAgg[i].data[j] << " ";
            print(sout);
        }
        sout << endl << endl;
        print(sout);
    }


    delete[] xgrid;
    xgrid = nullptr;

    for (int i = 0; i < M; i++){
        delete[] gl[i].data; 
        gl[i].data = nullptr;
    }

    delete[] gl;
    gl = nullptr;

    delete[] glAgg;
    glAgg = nullptr; 

    return 0;
}