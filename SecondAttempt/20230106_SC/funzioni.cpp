#include "funzioni.h"

// Calcola il numero di righe in un file 
int contaRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);
    if (!f) throw runtime_error("File non trovato");

    string line;
    int count = 0;
    while (getline(f, line)) 
        count++;
    
    return count;
}

// Stampa a video e su results.out
void print(stringstream &ss) {
    fstream f;
    f.open("results.out", ios::app);

    f << ss.str();
    cout << ss.str();

    ss.str("");
    ss.clear();
}

evento* loadEventi(evento*ev, int nEv) {
    fstream f;
    f.open("eventi.dat", ios::in);

    for (int i = 0; i < nEv;  i++) {
        for (int j = 0; j < 4; j++)
            f >> ev[i].p1[j];

        for (int j = 0; j < 4; j++)
            f >> ev[i].p2[j];
        
        f >> ev[i].segnale;
    }

    return ev;
}

// Calcola il numero di eventi segnale
int nEventiSegnale(evento* ev, int nEv) {
    int nSegnali = 0;
    for (int i = 0; i < nEv; i++)
        if (ev[i].segnale)
            nSegnali++;

    return nSegnali;
}

// Calcola la massa invariante per un generico evento
double calcMassaInv(evento ev) {
    return sqrt(pow(ev.p1[0] + ev.p2[0], 2) - ( pow(ev.p1[1] + ev.p2[1], 2) + pow(ev.p1[2] + ev.p2[2], 2) + pow(ev.p1[3] + ev.p2[3], 2)));
}

// Aggiorna la massa invariante di tutti gli eventi
evento* aggMassaInv(evento* ev, int nEv) {
    for (int i = 0; i < nEv; i++)
        ev[i].massainv = calcMassaInv(ev[i]);

    return ev;
}

// Ordina gli eventi per massa invariante crescente
evento* sortEvPerMassa(evento* ev, int nEv) {
    for (int i = 0; i < nEv; i++)
        for (int j = i; j < nEv; j++)
            if (ev[j].massainv < ev[i].massainv) {
                evento tmp = ev[i];
                ev[i] = ev[j];
                ev[j] = tmp;
            }
            
    return ev;
}

void stampaPrimiUltimiQuattroEv(evento* ev, int nEv) {
    stringstream sout;
    for (int i = 0; i < 4; i++) {
        sout << "Evento #" << i + 1 << ": " << endl <<
                "   Quadrimpulso p1: (" << ev[i].p1[0] << ", "<< ev[i].p1[2] << ", "<< ev[i].p1[1] << ", "<< ev[i].p1[3] << ")" << endl <<
                "   Quadrimpulso p2: (" << ev[i].p2[0] << ", "<< ev[i].p2[2] << ", "<< ev[i].p2[1] << ", "<< ev[i].p2[3] << ")" << endl <<
                "   Segnale: " << ((ev[i].segnale) ? "sì" : "no") << endl <<
                "   Massa invariante: " << ev[i].massainv << endl << endl;
        print(sout);
    }

    for (int i = nEv - 4; i < nEv; i++) {
        sout << "Evento #" << i + 1 << ": " << endl <<
                "   Quadrimpulso p1: (" << ev[i].p1[0] << ", "<< ev[i].p1[2] << ", "<< ev[i].p1[1] << ", "<< ev[i].p1[3] << ")" << endl <<
                "   Quadrimpulso p2: (" << ev[i].p2[0] << ", "<< ev[i].p2[2] << ", "<< ev[i].p2[1] << ", "<< ev[i].p2[3] << ")" << endl <<
                "   Segnale: " << ((ev[i].segnale) ? "sì" : "no") << endl <<
                "   Massa invariante: " << ev[i].massainv << endl << endl;
        print(sout);
    }
}

// Divide gli eventi segnale e backgrounf nei relativi array
void dividiEventiSegnale(evento *ev, int nEv, evento* seg, int nSeg, evento* bg, int nBg) {
    int countSeg = 0;
    int countBg = 0;
    for (int i = 0; i < nEv; i++){
        if (ev[i].segnale){
            seg[countSeg] = ev[i];
            countSeg++;
        } else {
            bg[countBg] = ev[i];
            countBg++;
        }
    }
}

// Calcola la media della massa invariante di un set di eventi
double calcMedia(evento* ev, int nEv) {
    double sum = 0;
    for (int i = 0; i < nEv; i++) 
        sum += ev[i].massainv;
    
    return sum / nEv;
}

// Calcola la dev std della massa invariante di un set di eventi
double calcDevStd(evento *ev, int nEv) {
    double media = calcMedia(ev, nEv);
    double S = 0;
    for (int i = 0; i < nEv; i++) 
        S += pow(ev[i].massainv - media, 2);
    
    return sqrt(S / nEv);
}

// Calcola la massima massa invariante da un set di eventi
double calcMaxMassa(evento* ev, int nEv) {
    double max = ev[0].massainv;
    for (int i = 1; i < nEv; i++) 
        if (ev[i].massainv > max)
            max = ev[i].massainv;
    
    return max;
}

// Calcola la minima massa invariante da un set di eventi
double calcMinMassa(evento* ev, int nEv) {
    double min = ev[0].massainv;
    for (int i = 1; i < nEv; i++) 
        if (ev[i].massainv < min)
            min = ev[i].massainv;
    
    return min;
}