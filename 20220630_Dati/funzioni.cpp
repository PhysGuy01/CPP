#include "funzioni.h"

// Ritorna il numero di righe di un file
int contaRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);
    
    if (!f.good())
        throw runtime_error("Could not open file");
    
    string riga;
    int count = 0;
    
    while(getline(f, riga))
        count++;
    
    return count;
}

// Carica i dati dal file su un array di tipo double 
// aggiornando il numero di valori positivi e negativi
double *loadData(double* num, int &nVal, int &nPos, int &nNeg) {
    fstream f;
    f.open("data.dat", ios::in);
    
    if (!f.good())
        throw runtime_error("Could not open file");
    
    nPos = nNeg = 0;
    for (int i = 0; i < nVal; i++){
        f >> num[i];
        if (num[i] >= 0) 
            nPos++;
        else 
            nNeg++;
    }
    return num;
}

// Stampa a video e su file risultadi.dat
void print(stringstream &v) {
    fstream f;
    f.open("risultati.dat", ios::app);

    cout << v.str();
    f << v.str();

    v.str("");
    v.clear();
}

// Carica parametri
neuralnet* loadParams(neuralnet *nn, int &nPar) {
    fstream f;
    f.open("params.dat", ios::in);
    
    if (!f.good())
        throw runtime_error("Could not open file");
    
    for (int i = 0; i < nPar; i++)
        f >> nn[i].w1 >> nn[i].w2 >> nn[i].w3;
    
    return nn;
}

// Stampa la descr delle prime e le ultime cinque terne caricate
void stampaPrimUltCin(neuralnet *nn, int &nPar) {
    stringstream sout;
    for (int i = 0; i < 5; i++) {
        sout << "\nTerna #" << i + 1 << endl <<
                "\tParametro 1: " << nn[i].w1 << endl <<
                "\tParametro 2: " << nn[i].w2 << endl <<
                "\tParametro 3: " << nn[i].w3;
        print(sout);
    }

    for (int i = nPar - 5; i < nPar; i++) {
        sout << "\nTerna #" << i + 1 << endl <<
                "\tParametro 1: " << nn[i].w1 << endl <<
                "\tParametro 2: " << nn[i].w2 << endl <<
                "\tParametro 3: " << nn[i].w3;
        print(sout);
    }
}

// Returna la funzione non lineare sigmoide
double g(double x) {
    return 1 / (1 + exp(-x));
}

// true se v è classificato come positivo, false altrimenti 
bool NN(double v, neuralnet pars){
    double g1 = g(pars.w3 * g(pars.w2 * (pars.w1 * v)));
    //cout <<"is g >= 0.5 : " << (g3 >= 0.5) << endl;
    return g1 >= 0.5;
}

// Calcola le predizioni di una rete neurale per tutti i valori
// e restituisce 1 se è positivo, -1 se è negativo
int *pred(neuralnet nn, int &nVal, double *num) {
    int *preds = new int[nVal];
    for (int i = 0; i < nVal; i++){
        if (NN(num[i], nn))
            preds[i] = 1;
        else 
            preds[i] = -1;
    }

    return preds;
    delete[] preds;
}

// Restituisce un array con il numero di errori compiuti 
// da ciascuna rete neurale
int *nErrori(neuralnet *nn, int &nPar, int &nVal, double *num) {
    int *err = new int[nPar];

    // Per ogni rete neurale calcola le predizioni per ciascun valore
    for (int i = 0; i < nPar; i++) {
        int contaErrori = 0;
        int *preds = pred(nn[i], nVal, num);

        // e per ciascun valore, se differisce dal numero reale, segna un err
        for (int j = 0; j < nVal; j++) 
            if (num[j] * preds[j] < 0)
                contaErrori++;  
        

        err[i] = contaErrori;  
        
        delete[] preds;
    }
    return err;
    delete[] err;
}

// Stampa la percetnuale di errori commessi da ciascuna rete neurale
void stampaErrNN(int &nPar, int *err, int &nVal) {
    stringstream sout;
    for (int i = 0; i < nPar; i++) {
        sout << "\nPercentuale errori rete neurale #" << i + 1 << ": " 
                << static_cast<double>(err[i]) * 100 / nVal << "%";

        print(sout);
    }
}

// Restituisce la rete neurale con i migliori risultati
neuralnet minErrori(neuralnet *nn, int &nPar, int *err) {
    // Partendo da j = 0 (prima rete neurale)
    int j = 0;

    // Per ogni errore controlla se esso è minore dell'errore considerato
    // e nel caso lo rende il minimo
    for (int i = 0; i < nPar; i++) 
        if (err[i] < err[j])
            j = i;

    // Restituisce la rete neurale corrispondente al minor numero di errori
    return nn[j];
}