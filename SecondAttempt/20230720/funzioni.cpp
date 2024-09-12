#include "funzioni.h"

// Conta il numero di righe in un file
int contaRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);
    if (!f) {
        throw runtime_error("File non trovato");
    }

    string line;
    int count = 0;
    while(getline(f, line)) {
        count++;
    }
    
    f.close();

    return count;
}

// Stampa a schermo e su un file results.out
void print(stringstream &ss) {
    fstream f;
    f.open("results.out", ios::app);

    f << ss.str();
    cout << ss.str();

    ss.str("");
    ss.clear();
}

// Carica le misure su un array dinamico di misura e calcola il numero di cariche pos, neg e neutre
misura* loadMis(misura* mis, int nMis, int &nPos, int &nNeg, int &nNeu) {
    fstream f;
    f.open("dati.dat", ios::in);
    if (!f) {
        throw runtime_error("File non trovato");
    }

    for (int i = 0; i < nMis; i++) {
        f >> mis[i].p[0] >> mis[i].p[1] >> mis[i].p[2] >> mis[i].p[3] >> mis[i].carica;
        if (mis[i].carica > 0) nPos++;
        if (mis[i].carica == 0) nNeu++;
        if (mis[i].carica < 0) nNeg++;
    }

    return mis;
}

// Calcola la rapidita' di una particella
double calcEta(misura mis) {
    return log((mis.p[0] + mis.p[3])/(mis.p[0] - mis.p[3])) / 2;
}

// Aggiorna il campo eta di ogni misura
misura* aggEta(misura* mis, int nMis) {
    for (int i = 0; i < nMis; i++)
        mis[i].eta = calcEta(mis[i]);
    
    return mis;
}

// Riordina le misure in ordine di eta crescente
misura* sortMis(misura* mis, int nMis) {
    for (int i = 0; i < nMis; i++)
        for (int j = i; j < nMis; j++) 
            if (mis[j].eta < mis[i].eta) {
                misura tmp = mis[i];
                mis[i] = mis[j];
                mis[j] = tmp;
            }

    return mis;
}

// Letteralmente stampa le prime tre e le ultime tre misure bruh
void stampaPrimeUltimeTreMisure(misura* mis, int nMis) {
    stringstream sout;
    for (int i = 0; i < 3; i++) {
        sout << "Misura #" << i + 1 << endl <<
                "   Quadrimpulso: (" << mis[i].p[0] << ", " << mis[i].p[1] << ", " << mis[i].p[2] << ", " << mis[i].p[3] << ")" << endl <<
                "   Carica: " << mis[i].carica << endl <<
                "   Eta: " << mis[i].eta << endl << endl;
        print(sout);
    }

    for (int i = nMis - 3; i < nMis; i++) {
        sout << "Misura #" << i + 1 << endl <<
                "   Quadrimpulso: (" << mis[i].p[0] << ", " << mis[i].p[1] << ", " << mis[i].p[2] << ", " << mis[i].p[3] << ")" << endl <<
                "   Carica: " << mis[i].carica << endl <<
                "   Eta: " << mis[i].eta << endl << endl;
        print(sout);
    }
}

// Calcola la media delle rapidita delle misure
double calcMedia(misura* mis, int nMis) {
    double sum = 0;
    for (int i = 0; i < nMis; i++)
        sum += mis[i].eta;
    
    return sum / nMis;
}

// Calcola la deviazione standard delle eta
double calcSigma(misura* mis, int nMis) {
    double S = 0;
    double mu = calcMedia(mis, nMis);

    for (int i = 0; i < nMis; i++)
        S += pow(mis[i].eta - mu, 2);

    return sqrt(S/nMis);
}

// Calcola la massima rapidita'
double maxEta(misura* mis, int nMis) {
    double max = mis[0].eta;
    for (int i = 0; i < nMis; i++)
       if (mis[i].eta > max) max = mis[i].eta;
    
    return max;
}

// Calcola la minima rapidita'
double minEta(misura* mis, int nMis) {
    double min = mis[0].eta;
    for (int i = 0; i < nMis; i++)
       if (mis[i].eta < min) min = mis[i].eta;
    
    return min;
}
 
// Carica le misure con carica positiva, negativa e neutra
void loadPosNegNeu(misura*mis, misura* pos, misura* neg, misura* neu, int nMis, int nPos, int nNeg, int nNeu) {
    int countPos = 0, countNeg = 0, countNeu = 0;
    for (int i = 0; i < nMis; i++)
        if (mis[i].carica > 0) {
            pos[countPos] = mis[i];
            countPos++;
        } else if (mis[i].carica == 0) {
            neu[countNeu] = mis[i];
            countNeu++;
        } else {
            neg[countNeg] = mis[i];
            countNeu++;
        }
}