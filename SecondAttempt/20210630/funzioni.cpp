#include "funzioni.h"

// Fa letteralmente quello che dice il nome, conta le righe di un file
// ...Duh...
int contaRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);

    int count = 0;
    string line;
    while(getline(f, line))
        count++;

    return count;
}

// Stampa a video e su file 'risultati.dat'
void print(stringstream &v) {
    fstream f;
    f.open("risultati.dat", ios::app);

    cout << v.str();
    f << v.str();

    v.clear();
    v.str("");
}

// Carica i dati dei linfociti da linfociti.dat in un array di linfociti
linfocita* loadLinf(linfocita* linf, int nLinf) {
    fstream f;
    f.open("linfociti.dat", ios::in);

    for (int i = 0; i < nLinf; i++) {
        f >> linf[i].x >> linf[i].y >> linf[i].cap >> linf[i].r >> linf[i].id;
        linf[i].n_bact = 0;
    }

    return linf;
}

// Stampa a video e sul file i parametri di ogni linfocita
void stampaLinf(linfocita* linf, int nLinf) {
   
    stringstream sout;
    for (int i = 0; i < nLinf; i++) {
        sout << " Linfocita #" << i + 1 << endl <<
                "   Posizione: " << linf[i].x << ", " << linf[i].y << endl <<
                "   Capacità: " << linf[i].cap << endl <<
                "   Raggio: " << linf[i].r << endl <<
                "   Identità: " << linf[i].id << endl <<
                "   Batteri uccisi: " << linf[i].n_bact << endl << endl;
        print(sout);
    }
}

// Carica i dati da batteri.dat in un array di battery
batterio* loadBatt(batterio* batt, int nBat) {
    fstream f;
    f.open("batteri.dat", ios::in);

    for (int i = 0; i < nBat; i++){
        f >> batt[i].x >> batt[i].y;
        batt[i].killed_by = 'n';
    }

    return batt;
}

// 3... 2... 1... FIGHT!

// Calcola la distanza tra due punti nel piano
float calcDist(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Aggiorna i campi dei batteri e dei linfociti e dei batteri a seconda che abbiano ucciso/siano stati uccisi
void fight(batterio* batt, int nBat, linfocita* linf, int nLinf) {
    for (int i = 0; i < nLinf; i++) 
        for (int j = 0; j < nBat; j++) 
            if (calcDist(linf[i].x, linf[i].y, batt[j].x, batt[j].y) <= linf[i].r) {
                linf[i].cap -= 1;
                linf[i].n_bact += 1;
                batt[j].killed_by = linf[i].id;
            }
}

// Riordina i linfociti in ordine di capacità decrescente
linfocita* sortLinf(linfocita* linf, int nLinf) {
    for (int i = 0; i < nLinf; i++)
        for (int j = i; j < nLinf; j++)
            if (linf[i].cap < linf[j].cap) {
                linfocita tmp = linf[i];
                linf[i] = linf[j];
                linf[j] = tmp;
            }
            
    return linf;
}

// Stampa i valori di ascisse minimi e massimi dei soli batteri vivi
void stampaMinMaxX(batterio* batt, int nBatt) {
    float max = batt[0].x;
    for (int i = 0; i < nBatt; i++) 
        if (batt[i].x > max && batt[i].killed_by == 'n')
            max = batt[i].x;
    
    float min = batt[0].x;
    for (int i = 0; i < nBatt; i++) 
        if (batt[i].x < min && batt[i].killed_by == 'n')
            min = batt[i].x;

    stringstream sout;
    sout << endl << "----------------------" << endl << endl <<
        " Ascissa massima dei batteri vivi: " << max << endl <<
        " Ascissa minima dei batteri vivi: " << min << endl << endl;
    print(sout);
}