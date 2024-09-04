#include "funzioni.h"

// Stampa a video e su file risultati.out
void print(stringstream &v) {
    fstream f;
    f.open("risultati.out", ios::app);

    cout << v.str();
    f << v.str();

    v.str("");
    v.clear();
}

// Carica su w i dati degli walkers
walker *loadWalker(walker *w, int &K, int &n) {
    fstream f;
    f.open("walkers.dat", ios::in);

    if (!f.good())
        throw runtime_error("Could not open file.");

    for (int i = 0; i < K; i++) {
        w[i].moves = new char[n];
        
        f >> w[i].x >> w[i].y; // Coords iniziali
        
        for(int j = 0; j < n; j++)
            f >> w[i].moves[j]; // Carica le n mosse

        f >> w[i].s; // Messaggero o no
    }

    return w;
}

// Conta i messaggeri in un array
int contaMess(walker *w, int &K) {
    double nMess = 0;
    for (int i = 0; i < K; i++) 
        if (w[i].s)
            nMess++;
    return nMess;
}

// Carica un array di disp messaggeri
walker *loadMess(walker *w, int &K, int &nMess) {

    nMess = contaMess(w, K);

    walker *wMess = new walker[nMess];
    
    int jMess = 0;
    for (int i = 0; i < K; i++) 
        if (w[i].s) {
            wMess[jMess] = w[i];
            jMess++;
        }
    return wMess;
}

// Calcola la distanza tra due dispositivi
double calcDist(walker w1, walker w2) {
    double wx = pow(w1.x - w2.x, 2);
    double wy = pow(w1.y - w2.y, 2);

    return sqrt(wx + wy);
}

// Calcola la massima distanza tra walkers in un array
double calcMaxDist(walker *w, int &K){
    double max = calcDist(w[0], w[1]);
    for (int i = 0; i < K; i++)
        for (int j = 0; j < K; j++) 
            if (calcDist(w[j], w[i]) > max)
                max = calcDist(w[j], w[i]);
    return max;
}

// Aggiorna la posizione all'n-esimo passo
walker *aggPos(walker *w, int &K, int &n) {
    for (int j = 0; j < K; j++){
        char card = w[j].moves[n];
        switch (card) {
            case 'N':
                w[j].y++;
                break;
            
            case 'S':
                w[j].y--;
                break;

            case 'O':
                w[j].x--;
                break;
            
            case 'E':
                w[j].x++;
                break;
        }

        
    }
    return w;
}

walker *aggMess(walker *w, int &K, float &dist) {
    for (int i = 0; i < K; i++) 
        for (int j = 0; j < K; j++)
            // Se la distanza tra due walker è minore della max dist di trasmissione
            // e uno dei due è messaggero, aggiorna lo status di entrambi
            if (calcDist(w[i], w[j]) < dist && (w[i].s == 1 || w[j].s == 1)) {
                w[i].s = 1;
                w[j].s = 1;
            }

    return w;    
}