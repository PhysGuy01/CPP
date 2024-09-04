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

// Carica i dati da file su un array di eventi contando il numero di eventi di tipo segnale
evento *loadData(evento *ev, int &nMis, string filename, int &nSeg) {
    fstream f;
    f.open(filename, ios::in);

    nSeg = 0;
    for (int i = 0; i < nMis; i++){
        f >> ev[i].p1[0] >> ev[i].p1[1] >> ev[i].p1[2] >> ev[i].p1[3] >>
            ev[i].p2[0] >> ev[i].p2[1] >> ev[i].p2[2] >> ev[i].p2[3] >> ev[i].segnale;
        ev[i].eta = 0;
        if (ev[i].segnale)
            nSeg++;
    }
    return ev;
}

// Stampa a video e su file risultati.dat
void print(stringstream &v) {
    fstream res;
    res.open("risultati.dat", ios::app);

    cout << v.str();
    res << v.str();

    v.str("");
    v.clear();
}

// Calcola la massa invariante di una misura
double calcMassaInv(evento ev) {
    double sumQuadMom = 0;
    for (int i = 1; i < 4; i++)
        sumQuadMom += pow(ev.p1[i] + ev.p2[i], 2);
    
    double sumEn = pow(ev.p1[0] + ev.p2[0], 2);
    return sqrt(sumEn - sumQuadMom);
}

// Aggiorna le masse invarianti di tutti gli eventi
evento *aggMassaInv(evento *ev, int &nMis) {
    for (int i = 0; i < nMis; i++) 
        ev[i].massainv = calcMassaInv(ev[i]);
    
    return ev;
}

// Stampa le prime e le ultime cinque masse invarianti 
void stampaPrimeUltimeCinque(evento *ev, int &nMis) {
    stringstream sout;
    for (int i = 0; i < 5; i++) {
        sout << "\nMassa invariante evento #" << i + 1 << ": " << ev[i].massainv;
        print(sout);
    }

    for (int i = nMis - 5; i < nMis; i++) {
        sout << "\nMassa invariante evento #" << i + 1 << ": " << ev[i].massainv;
        print(sout);
    }
}

// Ordina gli eventi per massa crescente
evento *sortMasse(evento* ev, int &nMis) {
    for (int i = 0; i < nMis; i++)
        for (int j = 0; j < nMis; j++)
            if (ev[i].massainv < ev[j].massainv) {
                evento tmp = ev[i];
                ev[i] = ev[j];
                ev[j] = tmp;
            }
    return ev;
}

// Stampa la descrizione dei primi e ultimi quattro eventi
void stampaPrimUltQuattro(evento *ev, int &nMis) {
    stringstream sout;
    for (int i = 0; i < 4; i++) {
        sout << "\nEvento #" << i + 1 << endl <<
                "\tEnergia-momento p1: " << "(" << ev[i].p1[0] << 
                                         ", " << ev[i].p1[1] << 
                                         ", " << ev[i].p1[2] <<
                                         ", " << ev[i].p1[3] << ")" << endl <<
                "\tEnergia-momento p2: " << "(" << ev[i].p2[0] << 
                                         ", " << ev[i].p2[1] << 
                                         ", " << ev[i].p2[2] <<
                                         ", " << ev[i].p2[3] << ")" << endl <<
                "\tSegnale: " << ev[i].segnale << endl <<
                "\tMassa invariante: " << ev[i].massainv << endl <<
                "\tPseudo-rapiditià: " << ev[i].eta;
        print(sout);
    }

    for (int i = nMis - 4; i < nMis; i++) {
        sout << "\nEvento #" << i + 1 << endl <<
                "\tEnergia-momento p1: " << "(" << ev[i].p1[0] << 
                                         ", " << ev[i].p1[1] << 
                                         ", " << ev[i].p1[2] <<
                                         ", " << ev[i].p1[3] << ")" << endl <<
                "\tEnergia-momento p2: " << "(" << ev[i].p2[0] << 
                                         ", " << ev[i].p2[1] << 
                                         ", " << ev[i].p2[2] <<
                                         ", " << ev[i].p2[3] << ")" << endl <<
                "\tSegnale: " << ev[i].segnale << endl <<
                "\tMassa invariante: " << ev[i].massainv << endl <<
                "\tPseudo-rapiditià: " << ev[i].eta;
        print(sout);
    }
}

// Calcola la media e la deviazione standard sulla massa
double calcMediaMassa(evento *ev, int &nMis) {
    double sum = 0;
    for (int i = 0; i < nMis; i++) 
        sum += ev[i].massainv;
    
    return sum / nMis;
}

// Calcola la deviazione standard sulle masse
double calcDevStdMassa(evento *ev, int &nMis) {
    double sumDiffQuad = 0;
    double mean = calcMediaMassa(ev, nMis);
    for (int i = 0; i < nMis; i++) 
        sumDiffQuad += pow(ev[i].massainv - mean, 2);
    
    return sqrt(sumDiffQuad / (nMis - 1));
}

// Calcola la pseudo rapidità di un evento
double pseudoRap(evento ev) {
    double num = (ev.p1[0] + ev.p2[0]) + (ev.p1[3] + ev.p2[3]);
    double den = (ev.p1[0] + ev.p2[0]) - (ev.p1[3] + ev.p2[3]);
    return log(num / den) / 2;
}

// Aggiorna la pseudorapidità di ogni evento in un array
evento *aggPseudoRap(evento *ev, int &nMis) {
    for (int i = 0; i < nMis; i++)
        ev[i].eta = pseudoRap(ev[i]);

    return ev;
}

// Calcola la media della pseudo rapidità
double calcMediaRap(evento *ev, int &nMis) {
    double sum = 0;
    for (int i = 0; i < nMis; i++) 
        sum += ev[i].eta;
    
    return sum / nMis;
}

// Calcola la deviazione standard sulla pseudo-rapidità
double calcDevStdRap(evento *ev, int &nMis) {
    double sumDiffQuad = 0;
    double mean = calcMediaRap(ev, nMis);
    for (int i = 0; i < nMis; i++) 
        sumDiffQuad += pow(ev[i].eta - mean, 2);
    
    return sqrt(sumDiffQuad / (nMis - 1));
}
