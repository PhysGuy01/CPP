#include "funzioni.h"

// Conta le righe di un file
int contaRighe(string filename) {
    // Apre il file con il nome dato
    fstream file;
    file.open(filename, ios::in);

    // Conta le righe 
    int nRighe = 0;
    string riga;
    while(getline(file, riga)) {
        nRighe++;
    }
    
    return nRighe;
}
// Stampa a video e su file results.out
void print(stringstream &v) {
    // apre un file di nome results.out in modalià 'append'
    fstream res;
    res.open("results.out", ios::app);
    
    cout << v.str();
    res << v.str();
    
    // pulisce la stringa per uso futuro
    v.str("");
    v.clear();
}

// Calcola la massa invariante di una misura
float calcMassInv(evento mis) {
    // Calcola il quadrato della somma delle energie
    float sumEn = pow(mis.p1[0] + mis.p2[0], 2);

    // Calcola la somma dei quadrati della somma dei momenti
    float sumXYZ = 0;
    for (int i = 1; i < 4; i++)
        sumXYZ += pow(mis.p1[i] + mis.p2[i], 2);

    return sqrt(sumEn - sumXYZ);
}

// Aggiorna la massa invariante su un array di misure
evento *aggMassInv(evento *mis, int &nMis) {
    for (int i = 0; i < nMis; i++) 
        mis[i].massainv = calcMassInv(mis[i]);
    
    return mis;
}

// Stampa i primi dieci eventi
void stampaPrimeDieciMasse(evento *mis) {
    stringstream ev;
    for (int i = 0; i < 10; i++) {
        ev << "\nEvento #" << i + 1 << endl
            << "\tMassa invariante: " << mis[i].massainv;
        print(ev);
    }
}

// Ordina un array di eventi in ordine di masse invarianti crescente
evento *sortMasse(evento *mis, int &nMis) {
    for (int i = 0; i < nMis; i++) 
        for (int j = i; j < nMis; j++) 
            if (mis[i].massainv > mis[j].massainv) {
                evento tmp = mis[i];
                mis[i] = mis[j];
                mis[j] = tmp;
            }        
    return mis;
}

// Stampa la descrizione delle prime e ultime quattro misurazioni
void stampaPrimeUltimeQuattro(evento *mis, int &nMis) {
    stringstream misure;
    misure << "\n\nPrime quattro misure: " << endl;
    print(misure);

    for (int i = 0; i < 4; i++) {
        misure << "Misura #" << i + 1 << endl 
                << "Energia-momento part 1 (E1, p1x, p1y, p1z): " << "(" << mis[i].p1[0]
                                                                  << ", "<< mis[i].p1[1]
                                                                  << ", "<< mis[i].p1[2]
                                                                  << ", "<< mis[i].p1[3]
                                                                  << ")" << endl 
                << "Energia-momento part 2 (E2, p2x, p2y, p2z): " << "(" << mis[i].p2[0]
                                                                  << ", "<< mis[i].p2[1]
                                                                  << ", "<< mis[i].p2[2]
                                                                  << ", "<< mis[i].p2[3]
                                                                  << ")" << endl 
                << "Segnale: " << mis[i].segnale << endl 
                << "Massa Invariante: " << mis[i].massainv << endl << endl;
        print(misure);
    }

    misure << "\n\nUltime quattro misure: " << endl;
    print(misure);
    for (int i = nMis - 4; i < nMis; i++) {
        misure << "Misura #" << i + 1 << endl 
                << "Energia-momento part 1 (E1, p1x, p1y, p1z): " << "(" << mis[i].p1[0]
                                                                  << ", "<< mis[i].p1[1]
                                                                  << ", "<< mis[i].p1[2]
                                                                  << ", "<< mis[i].p1[3]
                                                                  << ")" << endl 
                << "Energia-momento part 2 (E2, p2x, p2y, p2z): " << "(" << mis[i].p2[0]
                                                                  << ", "<< mis[i].p2[1]
                                                                  << ", "<< mis[i].p2[2]
                                                                  << ", "<< mis[i].p2[3]
                                                                  << ")" << endl 
                << "Segnale: " << mis[i].segnale << endl 
                << "Massa Invariante: " << mis[i].massainv << endl << endl;
        print(misure);
    }
}

// Returna un array di eventi di segnale
evento *eventiSegnale(evento *mis, int &nMis, int &nSeg) {
    // Conta quanti sono gli eventi di segnale
    nSeg = 0;
    for (int i = 0; i < nMis; i++) 
        if (mis[i].segnale)
            nSeg++;

    evento *evSeg = new evento[nSeg];
    int jSeg = 0;
    for (int i = 0; i < nMis; i++) 
        if (mis[i].segnale){
            evSeg[jSeg] = mis[i];
            jSeg++; 
        }
    return evSeg;
}

// Returna un array di eventi di background
evento *eventiBackground(evento *mis, int &nMis, int &nBack) {
    // Conta quanti sono gli eventi di background
    nBack = 0;
    for (int i = 0; i < nMis; i++) 
        if (!mis[i].segnale)
            nBack++;

    evento *evBack = new evento[nBack];
    int jBack = 0;
    for (int i = 0; i < nMis; i++) 
        if (!mis[i].segnale){
            evBack[jBack] = mis[i];
            jBack++; 
        }
    return evBack;
}

// Calcola la media di massa invariante in un array di eventi
float calcMedia(evento *mis, int &nMis) {
    float sum = 0;
    for (int i = 0; i < nMis; i++) 
        sum += mis[i].massainv;
    
    return sum / nMis;
}

// Calcola la deviazione standard della massa in un array di misure
float calcDevStd(evento *mis, int &nMis) {
    float mean = calcMedia(mis, nMis);
    float sommaQuad = 0;

    // Calcola la sommatoria della differenza quadra tra la massa e la media
    for (int i = 0; i < nMis; i++) 
        sommaQuad += pow(mis[i].massainv - mean, 2);
    
    return sqrt(sommaQuad / nMis);
}

// Returna la massima massa invariante in un array di eventi
float maxMassa(evento *mis, int &nMis) {
    float max = mis[0].massainv;

    for (int i = 0; i < nMis; i++) 
        if (mis[i].massainv > max)
            max = mis[i].massainv;
    
    return max;
}

// Returna la minima massa invariante in un array di eventi
float minMassa(evento *mis, int &nMis) {
    float min = mis[0].massainv;

    for (int i = 0; i < nMis; i++) 
        if (mis[i].massainv < min)
            min = mis[i].massainv;
    
    return min;
}