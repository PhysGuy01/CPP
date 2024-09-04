#include "funzioni.h"

int contaRighe(string filename) {
    fstream f, toll;
    f.open(filename, ios::in);

    if (!f.good())
        throw runtime_error("Could not access file.");
    
    // Conta il numero di cilindri nel file
    string riga;
    int count = 0;
    while(getline(f, riga)) 
        count++;

    return count;
}

// Carica i dati dei cilindri su un vettore di tipo cilindro
cilindro* loadCil(cilindro *cil, int &nCil) {
    fstream f, toll;
    f.open("cilindri.dat", ios::in);
    toll.open("tolleranze.dat", ios::in);

    if (!f.good() || !toll.good())
        throw runtime_error("Could not access file.");

    // Crea un array di tipo cilindro contenente i dati da tolleranze.dat
    cilindro *tolls = new cilindro[3];
    for (int i = 0; i < 3; i++) 
        toll >> tolls[i].col >> tolls[i].exact >> tolls[i].atoll;

    // Carica i dati da cilindri.dat e dall'array di tolleranze sopra
    for (int i = 0; i < nCil; i++) {
        f >> cil[i].diam >> cil[i].col;
        for (int j = 0; j < 3; j++)
            if (cil[i].col == tolls[j].col){
                cil[i].atoll = tolls[j].atoll;
                cil[i].exact = tolls[j].exact;
            }
    }

    delete[] tolls;
    tolls = nullptr;

    return cil;
} 

// Stampa a video e su file
void print(stringstream &v){
    fstream f;
    f.open("risultati.dat", ios::app);

    cout << v.str();
    f << v.str();

    v.str("");
    v.clear();
}

// conta il numero per colore
void contaCol(cilindro *cil, int &nCil, int &nBlu, int &nRos, int &nGial) {
    nBlu = nRos = nGial = 0;
    for (int i = 0; i < nCil; i++)
        if (cil[i].col == 'b')
            nBlu++;
        else if (cil[i].col == 'r')
            nRos++;
        else  
            nGial++;
}

// Stampa le descrizioni dei cilindri cilindri
void stampaCil(cilindro *cil, int &nCil) {
    stringstream sout;
    for (int i = 0; i < nCil; i++){
        sout << "Cilindro #" << i + 1<< endl <<
                "\tDiametro reale: " << cil[i].diam << endl <<
                "\tColore: " << cil[i].col << endl <<
                "\tDiametro nominale: " << cil[i].exact << endl <<
                "\tTolleranza: " << cil[i].atoll << endl << endl;
        print(sout);
    } 
}

// Ordina i cilindri per colore b g r
cilindro *ordinaCil(cilindro *cil, int &nCil){
    for (int i = 0; i < nCil; i++) 
        for (int j = i; j < nCil; j++) 
            if (cil[i].col > cil[j].col) {
                cilindro tmp = cil[i];
                cil[i] = cil[j];
                cil[j] = tmp;
            }
    return cil;
}

// Returna un array con tutti e soli i cilindri blu con discrepanza minore della accettata
cilindro *scremaBlu(cilindro *cil, cilindro *cilBlu, int &nCil, int &nBlu, int &nBluAgg) {
    fstream f;
    f.open("diametri.dat", ios::app);

    nBluAgg = 0;
    for (int i = 0; i < nCil; i++)
        if (cil[i].col == 'b')
            if (abs(cil[i].diam - cil[i].exact) > cil[i].atoll){
                cilBlu[nBluAgg] = cil[i];
                f << cilBlu[nBluAgg].diam << endl;
                nBluAgg++;
            }

    return cilBlu;
}