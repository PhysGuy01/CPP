#include "funzioni.h"

// Calcola il numero di righe in un file
int nrighe(string filename){
    fstream file;
    file.open(filename, ios::in);

    int n = 0;
    string linea;
    while (getline(file, linea)) {
        n++;
    }

    return n;
}

// Numero di voti sufficienti in un array di voto
int nSuff(voto *v, int &n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (v[i].val >= 18) count++;
    }
    return count;
}

// True se è bocciato False altrimenti
bool Bocciato(studente s) {
    if (s.nfails >= 5) return true;
    else return false;
}

// Calcola il numero di studenti espulsi
int nEspulsi(studente *s, int &n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (s[i].is_out) count++;
    }
    return count;
}

// Stampa tutti gli studenti espulsi
void stampaEspulsi(studente *s, int &n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (s[i].is_out) {
            count++;
            cout << "\nStudente bocciato #" << count << 
                    "\n\tMatricola: " << s[i].matr << 
                    "\n\tCrediti: " << s[i].cre <<
                    "\n\tMedia pesata: " << s[i].wm << endl;
        }
    }
}

// Returna un nuovo array senza i bocciati
studente *scremaEspulsi(studente *s, int size) {
    int countEspulsi = 0;
    for (int i = 0; i < size; i++)
        if (s[i].is_out) {
            for (int j = i + 1; j < size; j++) {
                s[j - 1] = s[j];
            } 
            countEspulsi++;
        }
    
    // Calcolo nuova dimensione dell'array (numero studenti originali - numero studenti espulsi)
    int newSize = size - countEspulsi;
    // Esplicito un nuovo array di tipo studente delle dimensioni giuste
    studente *sNew = new studente[newSize]; 

    // Copio i valori degli elementi dell'array originale in quello nuovo
    for (int i = 0; i < newSize; i++)
        sNew[i] = s[i];
        
    return sNew;
    
}

// Riordina gli studenti in ordine crescente di matricola
studente *sortStudenti(studente *s, int &size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (s[j].matr < s[i].matr) {
                studente tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
        }
    }
    return s;
}

// Stampa i primi e gli ultimi tre studenti della lista ordinata 
// prendendo un array studente, e la dimensione di esso
void stampaPrimiUltimiTre(studente *s, int &NewSize) {
    s = sortStudenti(s, NewSize);
    
    // Primi tre
    for (int i = 0; i < 3; i++)
        cout << "\nStudente #" << i + 1 <<
                "\n\tMatricola: " << s[i].matr <<
                "\n\tCrediti: " << s[i].cre <<
                "\n\tMedia pesata: " << s[i].wm <<
                "\n\tNumero esami falliti: " << s[i].nfails << endl;

    // Ultimi tre
    for (int i = NewSize - 3; i < NewSize; i++) {
        cout << "\nStudente #" << i + 1 <<
                "\n\tMatricola: " << s[i].matr <<
                "\n\tCrediti: " << s[i].cre <<
                "\n\tMedia pesata: " << s[i].wm <<
                "\n\tNumero esami falliti: " << s[i].nfails << endl;
    }
}

// Aggiorna i dati dopo la sessione di Gennaio-Febbraio
studente *nuoviDatiStudGF(voto *v, studente *sNew, int &nvoti, int &numPromossi) {
    for (int i = 0; i < numPromossi; i++)
        for (int j = 0; j < nvoti; j++) 
            if (v[j].matr == sNew[i].matr) {
                if (v[i].val >=18) {
                    sNew[i].wm = (v[j].cre * v[j].val + sNew[i].wm * sNew[i].cre) / (sNew[i].cre + v[j].cre);
                    sNew[i].cre += v[j].cre;
                } else {
                    sNew[i].nfails++;
                    if (sNew[i].nfails >= 5) 
                        sNew[i].is_out = true;
                }
            }
    return sNew; 
}

// Stampa su file gli studenti promossi dalla nuova sessione in ordine di matricola crescente 
void stampaPromossiGF(studente *s, int &numNuoviPromossi) {
    // Riordiniamo l'array di studenti per ordine di matricola crescente
    studente *sSort = sortStudenti(s, numNuoviPromossi);

    fstream f;
    f.open("studenti_GF.dat", ios::app);

    stringstream promossi;
    for (int i = 0; i < numNuoviPromossi; i++) {
        promossi.str("");
        promossi.clear();
        promossi << sSort[i].matr << "\t\t" << sSort[i].cre << "\t\t"  << sSort[i].wm << "\t\t" << sSort[i].nfails << "\t\t" << endl;
        f << promossi.str();
    }
}