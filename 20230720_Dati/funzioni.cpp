#include "funzioni.h"

// Calcola il numero di righe in un file
int numeroRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);

    string linea;
    int count = 0;
    while(getline(f, linea)){
        count++;
    }
    return count;
}

// Stampa a video e su file una stringstream
void print(stringstream &v) {
    // Stampa su schermo
    cout << v.str();
    fstream f;
    f.open("results.out", ios::app);
    // Stampa su file results.out
    f << v.str();
}

// Returna eta
double calcEta(misura mis) {
    return (log((mis.p[0] + mis.p[3]) / (mis.p[0] - mis.p[3])) / 2);
}


// Returna un array di misure ordinate in ordine di eta crescente
misura *misureOrdinate(misura *mis, int &nMis) {
    for (int i = 0; i < nMis; i++) 
        for (int j = i; j < nMis; j++) 
            if (mis[i].eta > mis[j].eta) {
                misura tmp = mis[i];
                mis[i] = mis[j];
                mis[j] = tmp;
            }
    return mis;
}

// Stampa le prime e ultime tre misure
void stampaPrimeUltimeTre(misura *mis, int &nMis) {
    stringstream stampaMisure;
    for (int i = 0; i < 3; i++) {
        stampaMisure.str("");
        stampaMisure.clear();
        stampaMisure << "\n\nMisura #" << i + 1 << endl << 
                        "\tQuadrimpulso (E,px,py,pz): " << "(" << mis[i].p[0] << ", " 
                                                               << mis[i].p[1] << ", "
                                                               << mis[i].p[2] << ", "
                                                               << mis[i].p[3] << ")" << endl <<
                        "\tCarica: " << mis[i].carica << endl << 
                        "\tEta: " << mis[i].eta << endl;
        print(stampaMisure);
    }
    for (int i = nMis - 3; i < nMis; i++) {
        stampaMisure.str("");
        stampaMisure.clear();
        stampaMisure << "\nMisura #" << i + 1 << endl << 
                        "\tQuadrimpulso (E,px,py,pz): " << "(" << mis[i].p[0] << ", " 
                                                               << mis[i].p[1] << ", "
                                                               << mis[i].p[2] << ", "
                                                               << mis[i].p[3] << ")" << endl <<
                        "\tCarica: " << mis[i].carica << endl << 
                        "\tEta: " << mis[i].eta << endl;
        print(stampaMisure);
    }
}

// Returna la media della eta delle misure
double media(misura *mis, int &nMis) {
    double somma = 0;
    for (int i = 0; i < nMis; i++) 
        somma += mis[i].eta;
    return somma / nMis;
}

// Returna la dev std della eta delle misure
double devStd(misura *mis, int &nMis) {
    double S = 0;
    double vMedia = media(mis, nMis);
    for (int i = 0; i < nMis; i++) 
        S += pow((mis[i].eta - vMedia), 2);
    
    return sqrt(S / nMis);
}

// Returna il massimo eta tra le misure
double max(misura *mis, int &nMis) {
    double max = mis[0].eta;
    for (int i = 0; i < nMis; i++) 
        if (mis[i].eta > max) 
            max = mis[i].eta;
    return max;
}

// Returna il minimo eta tra le misure
double min(misura *mis, int &nMis) {
    double min = mis[0].eta;
    for (int i = 0; i < nMis; i++) 
        if (mis[i].eta < min) 
            min = mis[i].eta;
    return min;
}

// Stampa media, dev std, min e max delle misure
void stampaAnalisiMisure(misura *mis, int numDati) {
    double mediaTot = media(mis, numDati);
    double devStdTot= devStd(mis, numDati);
    double maxTot = max(mis, numDati);
    double minTot = min(mis, numDati);

    stringstream analisi;
    analisi << "\nMedia: " << mediaTot << endl
            << "Dev Std: " << devStdTot << endl
            << "Massimo: " << maxTot << endl
            << "Minimo: " << minTot << endl;
    print(analisi);
}