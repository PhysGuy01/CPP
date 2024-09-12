#include "funzioni.h"


// Conta le righe di un file
int contaRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);

    string line;
    int count = 0;
    while(getline(f, line))
    count++;

    return count;
} 

// Stampa a video e su file risultati.dat
void print(stringstream &ss) {
    fstream f;
    f.open("risultati.dat", ios::app);

    cout << ss.str();
    f << ss.str();

    ss.clear();
    ss.str("");
}

// Carica i codici dei giocatori in un array di giocatore
giocatore* loadGioc(giocatore* gioc, int nIscr) {
    fstream f;
    f.open("iscritti.dat");

    for (int i = 0; i < nIscr; i++) {
        f >> gioc[i].cod;
        gioc[i].is_pro = (gioc[i].cod <= 1000) ? true : false;
        gioc[i].tot_punt = 0;
        gioc[i].nmani = 0;
    }

    return gioc;
}

// Carica i punteggi su un array di mano dal file punteggi.dat
mano* loadPunteggi(mano* man, int nMan) {
    fstream f;
    f.open("punteggi.dat", ios::in);

    for (int i = 0; i < nMan; i++) 
        f >> man[i].cod >> man[i].punti;
    
    return man;
}

// Aggiorna i dati dei giocatori del torneo
giocatore* updateGioc(giocatore* gioc, mano* man, int nMan, int nIscr) {
    for (int i = 0; i < nMan; i++) 
        for (int j = 0; j < nIscr; j++)
            if (man[i].cod == gioc[j].cod) {
                gioc[j].tot_punt += man[i].punti;
                gioc[i].nmani++;
            }

    return gioc;
}

// Riordina la classifica dei giocatori del tonreo di Masnago
giocatore* updateClassifTempor(giocatore* gioc, int nIscr) {
    for (int i = 0; i < nIscr; i++)
        for(int j = i + 1; j < nIscr; j++)
            if (gioc[j].tot_punt > gioc[i].tot_punt) {
                giocatore tmp = gioc[i];
                gioc[i] = gioc[j];
                gioc[j] = tmp;
            }

    return gioc;
}

// Carica la classifica da classifica.dat
mano* loadClassif(mano* classif, int nClassificati) {
    fstream f;
    f.open("classifica.dat", ios::in);

    for (int i = 0; i < nClassificati; i++) 
        f >> classif[i].cod >> classif[i].punti;
    
    return classif;
}

// Aggiorna la classifica generale
mano* updateClassTot(mano* classif, int nClassificati, giocatore* gioc, int nIscr) {
    // Aggiorna la classifica con i punteggi del torneo
    for (int i = 0; i < nClassificati; i++)
        for (int j = 0; j < nIscr; j++)
            if (gioc[j].cod == classif[i].cod && gioc[j].nmani > 5) {
                classif[i].punti += gioc[j].tot_punt;
                break;
            }

    // Ordina calssifica in ordine decrescente
    for (int i = 0; i < nClassificati; i++)
        for (int j = i; j < nClassificati; j++)
            if (classif[j].punti > classif[i].punti) {
                mano tmp = classif[i];
                classif[i] = classif[j];
                classif[j] = tmp;
            }

    return classif;
}
