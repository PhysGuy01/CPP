#include "funzioni.h"

// Conta le righe di un file 
int contaRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);

    string riga;
    int count = 0;
    while (getline(f, riga)) 
        count++;
    
    return count;
}

// Carica i dati da misure.dat su un array di misura
misura *loadMis(misura* mis, int nMis) {
    fstream f;
    f.open("misure.dat", ios::in);

    for (int i = 0; i < nMis; i++)
        f >> mis[i].tempo >> mis[i].unita >> mis[i].x;
    

    return mis;
}

// Carica i modelli da file su array modello
modello *loadMod(modello *mod, int nMod) {
    fstream f;
    f.open("modelli.dat", ios::in);

    for (int i = 0; i < nMod; i++)
        f >> mod[i].a >> mod[i].b >> mod[i].c;
    
    return mod;
}

// Stampa a video e su file 
void print(stringstream &v) {
    fstream f;
    f.open("risultati.dat", ios::app);

    f << v.str();
    cout << v.str();

    v.str("");
    v.clear();
}

// Stampa le prime e ultime tre misure 
void stampaPrimUltTreMis(misura *mis, int nMis){
    stringstream sout;
    for (int i = 0; i < 3; i++) {
        sout << "Misura #" << i + 1 << endl << 
                "\tIstante: " << mis[i].tempo << endl << 
                "\tUnità: " << mis[i].unita << endl <<
                "\tPosizione: " << mis[i].x << endl << endl;
        print(sout);
    }

    for (int i = nMis - 3; i < nMis; i++) {
        sout << "Misura #" << i + 1 << endl << 
                "\tIstante: " << mis[i].tempo << endl << 
                "\tUnità: " << mis[i].unita << endl <<
                "\tPosizione: " << mis[i].x << endl << endl;
        print(sout);
    }
}

// Ordina le misure in ordine crescente di tempo
misura *sortMis(misura *mis, int nMis) {

    // Converte tutte le misure di tempo in secondi
    for (int i = 0; i < nMis; i++) {
        if (mis[i].unita == 'm'){
            mis[i].tempo /= 1000;
            mis[i].unita == 's';
        }
        else if (mis[i].unita == 'n'){
            mis[i].tempo /= 1E+09;
            mis[i].unita == 's';
        }
    }

    for (int i = 0; i < nMis; i++) 
        for (int j = i; j < nMis; j++)
            if (mis[i].tempo > mis[j].tempo) {
                misura tmp = mis[i];
                mis[i] = mis[j];
                mis[j] = tmp;
            }
    
    return mis;
}

// Calcola la predizione di un modello dato un tempo
double calcPred(double tempo, modello mod) {
    return mod.a * pow(tempo, 2) + mod.b * tempo + mod.c;
}

// Aggiorna i valori del chi quadro di ogni modello 
modello *aggChiQuadMod(modello *mod, int nMod, misura *mis, int nMis) {
    double sum;
    for (int i = 0; i < nMod; i++){
        sum = 0;

        for (int j = 0; j < nMis; j++)
            sum += pow((mis[j].x - calcPred(mis[j].tempo, mod[i])) / 0.5 , 2);

        mod[i].chi2 = sum / nMis;
    }
    return mod;
}

// Ordina i modelli per chi2 crescente
modello *sortModChi2(modello *mod, int nMod) {
    for (int i = 0; i < nMod; i++)
        for (int j = i; j < nMod; j++)
            if (mod[i].chi2 > mod[j].chi2) {
                modello tmp = mod[i];
                mod[i] = mod[j];
                mod[j] = tmp;
            }
    return mod;
}