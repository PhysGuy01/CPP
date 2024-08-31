#include "funzioni.h"

// Conta le righe di un file
int contaRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);

    string riga;
    int count = 0;
    while(getline(f, riga))
        count++;

    return count;
}

// Carica i voti dal file votiGF.dat
voto* loadVoti(voto* vot, int nVoti) {
    fstream f;
    f.open("votiGF.dat", ios::in);

    for (int i = 0; i < nVoti; i++) 
        f >> vot[i].cod >> vot[i].cre >> vot[i].matr >> vot[i].val;
    
    return vot;    
}

// Stampa la sstrng a video e su file 'risultati.dat'
void print(stringstream &ss) {
    fstream f;
    f.open("risultati.dat", ios::app);

    f << ss.str();
    cout << ss.str();

    ss.clear();
    ss.str("");
}

// Carica gli studenti dal file studenti.dat
studente* loadStud(studente* stud, int nStud) {
    fstream f;
    f.open("studenti.dat", ios::in);

    for (int i = 0; i < nStud; i++) {
        f >> stud[i].matr >> stud[i].cre >> stud[i].wm >> stud[i].nfails;
        if (stud[i].nfails >= 5)
            stud[i].is_out = true;
        else stud[i].is_out = false;
    }   

    return stud;
}