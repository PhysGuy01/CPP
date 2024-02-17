#include "funzioni.h"

// Conta le righe in un file
int contaRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);

    string riga;
    int count = 0;
    while(getline(f, riga)) 
        count++;
    
    return count;
}

// Carica i dati da un file in un array di misure m
misura *loadData(misura *m, int &nMis, string filename) {
    fstream file;
    file.open(filename, ios::in);

    if (!file.is_open()) 
        throw runtime_error("Could not open file");
    
    
    for (int i = 0; i < nMis; i++) {
        m[i].v = new double[4];
        file >> m[i].t >> m[i].v[0] >> m[i].v[1] >> m[i].v[2] >> m[i].v[3] >> m[i].K;
        m[i].massa = 0;
    }

    return m;
}


// Stampa su schermo e su file "risultati.dat"
void print(stringstream &v) {
    cout << v.str();

    fstream res;
    res.open("risultati.out", ios::app);
    res << v.str();

    v.str("");
    v.clear();
}

// Stampa la descrizione di n misure
void stampaMisure(misura *m, int &nMis) {
    stringstream sout;
    for (int i = 0; i < nMis; i++) {
        sout << "Misura #" << i + 1 << endl <<
                "\tIstante t: " << m[i].t << endl <<
                "\tCoord velocità: " << "(" << m[i].v[0] << ", "
                                            << m[i].v[1] << ", "
                                            << m[i].v[2] << ", "
                                            << m[i].v[3] << ", "
                                            << ")" << endl <<
                "\tEnergia cinetica: " << m[i].K << endl <<
                "\tMassa: " << m[i].massa  << endl;
        print(sout);

    }
}

// Ordina le misure in ordine di tempo crescente
misura *sortMisure(misura *m, int &nMis) {
    for (int i = 0; i < nMis; i++) 
        for (int j = i; j < nMis; j++)
            if (m[i].t > m[j].t) {
                misura tmp = m[i];
                m[i] = m[j];
                m[j] = tmp;
            }
    return m;
}

// Calcola la massa di una misura
double calcMassa(misura m) {
    double sumQuad = 0;

    for (int i = 0; i < 4; i++)
        sumQuad += pow(m.v[i], 2);

    return 2 * m.K / sumQuad;
}

// Aggiorna l'array di misure con le masse calcolate
misura *aggMasse(misura *m, int &nMis) {
    for (int i = 0; i < nMis; i++)
        m[i].massa = calcMassa(m[i]);

    return m;
}

// Calcola la media delle masse in un array di misure
double calcMedia( misura *m, int &nMis) {
    double sum = 0;
    for (int i = 0; i < nMis; i++)
        sum += m[i].massa;
    
    return sum / nMis;
}

// Calcola la deviazione standard delle masse in un array
double calcDevStd( misura *m, int &nMis) {
    double sumDiffQuad = 0;
    double mean = calcMedia(m, nMis);

    for (int i = 0; i < nMis; i++) 
        sumDiffQuad += m[i].massa - mean;

    return sqrt(sumDiffQuad / nMis);
}

// Calcola la posizione da una misura
void calcPosizione(misura m, double &x, double &y, double &z, double &w) {
    x = m.v[0] * m.t;
    y = m.v[1] * m.t + pow(m.t, 2) / 2;
    z = m.t * sqrt(m.v[2]);
    w = m.v[3] * log(m.t);
}

// Stampa le posizioni delle misure in t = 5, 10, 15 (s)
void posInCinDieQuind(misura *m, int &nMis) {
    double x, y, z, w;
    stringstream sout;
    for (int i = 0; i < nMis; i++) 
        if (m[i].t == 5 || m[i].t == 10 || m[i].t == 15){
            calcPosizione(m[i], x, y, z, w);
            sout << "Coordinate misura #" << i + 1 << ": " << "(" << x << ", " <<
                                                                     y << ", " <<
                                                                     z << ", " <<
                                                                     w << ")" << endl;
            print(sout);
        }
}