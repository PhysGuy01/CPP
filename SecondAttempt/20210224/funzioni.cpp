#include "funzioni.h"

int contaRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);

    string riga;
    int count = 0;
    while(getline(f, riga)) 
        count++;
    
    return count;
}

misura* loadMis(misura* mis, int nMis) {
    fstream f;
    f.open("misure.dat", ios::in);
    
    for (int i = 0; i < nMis; i++) 
        f >> mis[i].tempo >> mis[i].unita >> mis[i].x;
    
    return mis;
}

modello* loadMod(modello* mod, int nMod) {
    fstream f;
    f.open("modelli.dat", ios::in);

    for (int i = 0; i < nMod; i++)
        f >> mod[i].a >> mod[i].b >> mod[i].c;

    return mod;
}

void print(stringstream &v) {
    fstream f;
    f.open("risultati.dat", ios::app);

    f << v.str();
    cout << v.str();

    v.str("");
    v.clear();
}

void printaPrimeUltimeTreMis(misura* mis, int nMis) {
    stringstream sout;

    for (int i = 0; i < 3; i++) {
        sout << "Misura #" << i + 1 << endl <<
                "   Tempo: " << mis[i].tempo << endl <<
                "   UdM: " << mis[i].unita << endl <<
                "   Posizione: " << mis[i].x << endl << endl;
        print(sout);
    }

    for (int i = nMis - 3; i < nMis; i++) {
        sout << "Misura #" << i + 1 << endl <<
                "   Tempo: " << mis[i].tempo << endl <<
                "   UdM: " << mis[i].unita << endl <<
                "   Posizione: " << mis[i].x << endl << endl;
        print(sout);
    }
}

misura* ordinaMis(misura* mis, int nMis) {
    for (int i = 0; i < nMis; i++) {
        
        if (mis[i].unita == 'm') {
            mis[i].tempo /= 1000;
            mis[i].unita = 's';
        } else if (mis[i].unita == 'n') { 
            mis[i].tempo /= 1E+09;
            mis[i].unita = 's';
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

double calcPred(double t, modello mod) {
    return mod.a * pow(t, 2) + mod.b * t + mod.c;
}

modello* aggChiQuad(modello* mod, int nMod, misura* mis, int nMis) {
    for (int j = 0; j < nMod; j++) {
        double sum = 0;

        for (int i = 0; i < nMis; i++) {
            sum += pow((mis[i].x - calcPred(mis[i].tempo, mod[j])) * 0.5, 2);
        }

        mod[j].chi2 = sum / nMis;
    }

    return mod;
}

modello* ordinaModelli(modello* mod, int nMod) {
    for (int i = 0; i < nMod; i++)
        for (int j = i; j < nMod; j++) 
            if (mod[j].chi2 < mod[i].chi2) {
                modello tmp = mod[i];
                mod[i] = mod[j];
                mod[j] = tmp;
            }        
    return mod;
}
