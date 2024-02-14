#include "funzioni.h"

// Returna il numero di righe in un file
int contaRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);

    string riga;
    int count = 0;
    while (getline(f, riga)) {
        count++;
    }

    return count;
}

// Stampa su schermo e su un file results.out
void print(stringstream &v) {
    cout << v.str();
    fstream res;
    res.open("results.out", ios::app);
    res << v.str();
}

// Stampa le prime tre e le ultime tre misure
void stampaPrimeUltimeTre(misura *m, int &nMis) {
    stringstream out;

    out << "\n\nPrime tre misure:" << endl;
    print(out);
    
    for (int i = 0; i < 3; i++) {
        out.str("");
        out.clear();
        out << "\nMisura #" << i + 1 << endl
            << "Istante t: " << m[i].t << endl
            << "Misurazione: " << m[i].mis << endl
            << "Temperatura: " << m[i].temp << endl;
        print(out);
    }

    out.str("");
    out.clear();
    out << "\n\nUltime tre misure:" << endl;
    print(out);
    
    for (int i = nMis - 3; i < nMis; i++) {
        out.str("");
        out.clear();
        out << "\nMisura #" << i + 1 << endl
            << "Istante t: " << m[i].t << endl
            << "Misurazione: " << m[i].mis << endl
            << "Temperatura: " << m[i].temp << endl;
        print(out);
    }
}

// Screma le misure in un array con temperatura maggiore di 30K
misura *scremaMisure(misura *m, int &nMis, int &nMisGiuste) {
    
    nMisGiuste = 0;

    // Calcola il numero di misure inferiori a 30K (da tenere)
    for (int i = 0; i < nMis; i++) 
        if (m[i].temp <= 30) 
            nMisGiuste++;
    
    // Crea un array di misure giuste e le copia dall'array originale
    misura *newMis = new misura[nMisGiuste];

    int jmis = 0;
    for (int i = 0; i < nMis; i++) 
        if (m[i].temp <= 30) {
            newMis[jmis] = m[i];
            jmis++;
        }
    
    return newMis;
}

// Ordina misure in ordine di t
misura *ordinaMisure(misura *m, int &nMis) {
    for (int i = 0; i < nMis; i++) 
        for (int j = i; j < nMis; j++) 
            if (m[j].t < m[i].t) {
                misura tmp = m[i];
                m[i] = m[j];
                m[j] = tmp;
            }
        
    return m;
}


// Conta misure in ciascun intervallo
void contaMisureInter(misura *m, int &nMis, int &misPrimoSet, int &misSecSet, int &misTerSet,
                        int &zeroPrSet, int &zeroSecSet, int &zeroTerSet,
                        int &unPrSet, int &unSecSet, int &unTerSet) {
    misPrimoSet = 0;
    misSecSet = 0;
    misTerSet = 0;
    zeroPrSet = 0;
    zeroSecSet = 0;
    zeroTerSet = 0;
    unPrSet = 0;
    unSecSet = 0;
    unTerSet = 0;

    for (int i = 0; i < nMis; i++) {
        if (m[i].t < 60) {
            misPrimoSet++;
            if (m[i].mis == 0) zeroPrSet++;
            else unPrSet++;
        } else if (m[i].t >= 60 && m[i].t < 120) {
            misSecSet++;
            if (m[i].mis == 0) zeroSecSet++;
            else unSecSet++;
        } else {
            misTerSet++;
            if(m[i].mis == 0) zeroTerSet++;
            else zeroTerSet++;
        }
    }
}

// Returna 0, 1, + a seconda delle frequenze di uno e zero date
char detStato(double &freqZero, double &freqUno) {
    
    if ((freqZero < 1 && freqZero > 0.95) && (freqUno > 0 && freqUno < 0.05))
        return '0'; 
    else if ((freqZero > 0 && freqZero < 0.05) && (freqUno > 0.95 && freqUno < 1))
        return '1';
    else 
        return '+';
}

misura* aggMisureStato(misura *m, int &nMis, char &statoPrimSet, char &statoSecSet, char &statoTerSet) {
    for (int i = 0; i < nMis; i++) {
        if (m[i].t < 59)
            m[i].stato = statoPrimSet;
        else if (m[i].t >= 60 && m[i].t < 120)
            m[i].stato = statoSecSet;
        else 
            m[i].stato = statoTerSet;
    }
    return m;
}

misura *statoPiu(misura *m, int &nMis, int &nMisPiu) {
    
    // Conta quante misure con stato + ci sono
    nMisPiu = 0;
    for(int i = 0; i < nMis; i++) 
        if (m[i].stato == '+')
            nMisPiu++;

    // Crea un array lungo abbastanza
    misura* misPiu = new misura[nMisPiu];

    // Copia sul nuovo array le misure che hanno stato '+'
    int jPiu = 0;
    for (int i = 0; i < nMis; i++)
        if (m[i].stato == '+') {
            misPiu[jPiu] = m[i];
            jPiu++;
        }
    
    return misPiu;
}