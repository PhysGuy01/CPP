#include "funzioni.h"

// Stampa a video e su file risultati.dat
void print(stringstream &v) {
    cout << v.str();

    fstream f;
    f.open("risultati.dat", ios::app);
    f << v.str();

    v.str("");
    v.clear();
}

// Conta le righe in un file
int contaRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);

    if (!f)
        throw runtime_error("Cound not open file.");

    string riga;
    int count = 0;

    while(getline(f, riga))
        count++;
    
    return count;
}

// Stampa le misure
void stampaMisure(const misure *m, int &nMis) {
    stringstream sout;
    for (int i = 0; i < nMis; i++) {
        sout << "\nMisura #" << i + 1 << endl <<
                "\tIstante della misura: " << m[i].t << endl << 
                "\tCoord (x, y, z): " << "(" << m[i].vx << ", " << m[i].vy << ", " << m[i].vz << ")" << endl <<
                "\tEnergia Cinetica: " << m[i].K << endl <<
                "\tMassa: " << m[i].massa;
        print(sout);
    }
}

// Ordina le misure in ordine crescente di tempo
misure *sortMisure(misure *m, int &nMis) {
    for (int i = 0; i < nMis; i++) 
        for(int j = i; j < nMis; j++) 
            if (m[i].t > m[j].t) {
                misure tmp = m[i];
                m[i] = m[j];
                m[j] = tmp;
            } 
    return m;
}

// Calcola le coordinate spaziali di una misura
void calcolaPosizione(const misure m, double &x, double &y, double &z) {
    // Calcola x
    x = m.vx * m.t;
    // Calcola y
    y = m.vy * m.t + pow(m.t, 2) / 2;
    // Calcola z
    z = m.t * sqrt(m.vz);
} 

// Calcola la massa di una misura
double calcolaMassa(misure m) {
    double sumV = pow(m.vx, 2) + pow(m.vy, 2) + pow(m.vz, 2);
    return (2 * m.K / sumV);
}

// Calcola la media della massa in un array di misure
double meanM(misure *m, int &nMis) {
    double sum = 0;
    for (int i = 0; i < nMis; i++)
        sum += m[i].massa;

    return sum / nMis;
}

// Calcola la deviazione standard delle masse
double calcDevStdM(misure *m, int &nMis) {
    double mean = meanM(m, nMis);
    double diffQuad = 0;

    for (int i = 0; i < nMis; i++)
        diffQuad += pow(m[i].massa - mean, 2);
    
    return sqrt(diffQuad / nMis);
}