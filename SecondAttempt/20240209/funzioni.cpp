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
        stud[i].is_out = (stud[i].nfails >= 5) ? true : false;
    }   

    return stud;
}

// Screma l'array studenti da quelli espulsi e li mette in ordine di matricola
studente* scremaStud(studente* stud, int nStud, studente* newStud, int nAmmessi) {
    int count = 0;
    for (int i = 0; i < nStud; i++) 
        if (!stud[i].is_out) {
            newStud[count] = stud[i];
            count++;
        }

    for (int i = 0; i < nAmmessi; i++)
        for (int j = i + 1; j < nAmmessi; j++)
            if (newStud[i].matr >  newStud[j].matr) {
                studente tmp = newStud[i];
                newStud[i] = newStud[j];
                newStud[j] = tmp;
            }

    return newStud;
} 

// Aggiorna gli studenti in base ai voti in voti.dat
studente* updateStud(studente* newStud, int nAmmessi, voto* vot, int nVoti, int &nEspulsi) {
    for (int i = 0; i < nVoti; i++) 
        for (int j = 0; j < nAmmessi; j++) 
            if (newStud[j].matr == vot[i].matr) 
                if (vot[i].val >= 18) {
                    newStud[j].cre += vot[i].cre;
                    newStud[j].wm = ((vot[i].val * vot[i].cre + newStud[j].wm * newStud[j].cre)/(newStud[j].cre + vot[i].cre));
                } else {
                    newStud[j].nfails++;
                    if (newStud[j].nfails >= 5) newStud[j].is_out = true;
                }

    for (int i = 0; i < nAmmessi; i++)
        if (newStud[i].is_out)
            nEspulsi++;

    return newStud;
}

void savePassedStuds(studente* newStud, int nAmmessi) {
    fstream f;
    f.open("studenti_GF.dat", ios::out);
    for (int i = 0; i < nAmmessi; i++) 
        if (!newStud[i].is_out) {
            f << newStud[i].matr << "\t" << newStud[i].cre << "\t" << newStud[i].wm << "\t" << newStud[i].nfails << "\t" << newStud[i].is_out << endl;
        }

    f.close();
}