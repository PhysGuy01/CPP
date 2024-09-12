#include "funzioni.h"

// Conta le righe in un file
int contaRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);
    if (!f)
        throw runtime_error("File non trovato");
    
    string line;
    int count = 0;
    while(getline(f, line))
        count++;
    
    f.close();
    return count;
}

// Stampa una sstring a video e su file "results.out"
void print(stringstream &ss) {
    fstream f;
    f.open("results.out", ios::app);
    if (!f) throw runtime_error("File non trovato");

    f << ss.str();
    cout << ss.str();

    ss.str("");
    ss.clear();
}

// Carica le misure su un array dinamico di misura
misura* loadMis(misura* mis, int nMis) {
    fstream f;
    f.open("dati.dat", ios::in);

    for (int i = 0; i < nMis; i++) {
        f >> mis[i].t >> mis[i].mis >> mis[i].temp;
        mis[i].stato = ' ';
    }
    
    f.close();
    return mis;
}

// Stampa le prime e le ultime tre misure
void stampaPrimeUltimeTreMis(misura* mis, int nMis) {
    stringstream sout;
    for (int i = 0; i < 3; i++) {
        sout << "Misura #" << i + 1 << ": " << endl <<
                "   Istante: " << mis[i].t << endl <<
                "   Valore: " << mis[i].mis << endl <<
                "   Temperatura: " << mis[i].temp << endl <<
                "   Stato: " << mis[i].stato << endl << endl;
        print(sout);
    }
    for (int i = nMis - 3; i < nMis; i++) {
        sout << "Misura #" << i + 1 << ": " << endl <<
                "   Istante: " << mis[i].t << endl <<
                "   Valore: " << mis[i].mis << endl <<
                "   Temperatura: " << mis[i].temp << endl <<
                "   Stato: " << mis[i].stato << endl << endl;
        print(sout);
    }
}

misura* cleanMis(misura* mis, misura* misClean, int nMis) {
    int count = 0;
    for (int i = 0; i < nMis; i++) 
        if (mis[i].temp < 30) {
            misClean[count] = mis[i];
            count++;
        }
    
    return misClean;
}

// Riordina un generico array di misure in ordine di t
misura* sortMis(misura* mis, int nMis) {
    for (int i = 0; i < nMis; i++)
        for (int j = i + 1; j < nMis; j++)
            if (mis[j].t < mis[i].t) {
                misura tmp = mis[i];
                mis[i] = mis[j];
                mis[j] = tmp;
            }
    return mis;
}

// Aggiorna gli stati di tutte le misurazioni
misura* aggStatoQubit(misura* misClean, int nCleanMis) {
    
    // Itera tra i set di misure
    for (int k = 1; k < 4; k++) {
        
        // Definisce l'estremo superiore e inferiore di questo set di misure
        int Inf = (60 * (k - 1));
        int Sup = (60 * k - 1);

        // Calcola le frequenze
        int N1 = 0, N0 = 0, N = 0;        
        for (int i = 0; i < nCleanMis; i++) {
            if ((misClean[i].t >= Inf) && (misClean[i].t <= Sup)) {
                if (misClean[i].mis == 0) {
                    N0++;
                } else {
                    N1++;
                }
                N++;
            }
        }

        // Aggiorna lo stato in base alla tabella delle frequenze
        // Caso I: stato = 0
        if (((double)N0/N >= 0.95 && (double)N0/N <= 1) && ((double)N1/N >= 0 && (double)N1/N <= 0.05)) {
            for (int i = 0; i < nCleanMis; i++) 
                if (misClean[i].t >= Inf && misClean[i].t <= Sup) 
                    misClean[i].stato = '0';

        // Caso II: stato = 1    
        } else if (((double)N0/N >= 0 && (double)N0/N <= 0.05) && ((double)N1/N >= 0.95 && (double)N1/N <= 1)) {
            for (int i = 0; i < nCleanMis; i++) 
                if (misClean[i].t >= Inf && misClean[i].t <= Sup) 
                    misClean[i].stato = '1';

        // Caso III: stato = +
        } else if (((double)N0/N >= 0.45 && (double)N0/N <= 0.55) && ((double)N1/N >= 0.45 && (double)N1/N <=0.55)) {
            for (int i = 0; i < nCleanMis; i++) 
                if (misClean[i].t >= Inf && misClean[i].t <= Sup) 
                    misClean[i].stato = '+';
        }
    }

    return misClean;
}

// Stampa le prime le ultime tre misure riferite al primo stato +
void stampaPrimeUltimeTreMisPrimoStatoPiu(misura* misClean, int nCleanMis) {
    // Flag per verificare se sia gia' avvenuta una iterazione di +
    bool flagPrimoPiu = false;
    stringstream sout;

    // Itera dentro i set di misure
    for (int k = 1; k < 4; k++) {

        // Definisce l'estremo superiore e inferiore del tempo di questo set di misure
        int Inf = (60 * (k - 1));
        int Sup = (60 * k - 1);

        // Trova la misura corrispondente all'estremo inferiore
        int infIndex = 0;    // il punto nell'array corrispondente all'Inf
        for (int i = 0; i < nCleanMis; i++)
            if (misClean[i].t == Inf) {
                infIndex = i;
                break;
            }

        int supIndex = 0;   // il punto nell'array corrispondente al Sup
        for (int i = 0; i < nCleanMis; i++)
            if (misClean[i].t == Sup) {
                supIndex = i;
                break;
            }

        // Ricordati di catchare la flag

        // Se lo stato della misura inferiore e' + (e quindi quella di tutte le altre nel set)
        if (misClean[infIndex].stato == '+') {

            // Stampa le prime tre dell
            for (int j = infIndex; j < infIndex + 3; j++) {
                sout << "Misura #" << j + 1 << ": " << endl <<
                        "   Istante: " << misClean[j].t << endl <<
                        "   Valore: " << misClean[j].mis << endl <<
                        "   Temperatura: " << misClean[j].temp << endl <<
                        "   Stato: " << misClean[j].stato << endl << endl;
                print(sout);
            }

            for (int j = supIndex - 3; j < supIndex; j++) {
                sout << "Misura #" << j + 1 << ": " << endl <<
                        "   Istante: " << misClean[j].t << endl <<
                        "   Valore: " << misClean[j].mis << endl <<
                        "   Temperatura: " << misClean[j].temp << endl <<
                        "   Stato: " << misClean[j].stato << endl << endl;
                print(sout);
            }

            flagPrimoPiu = true; // Aggiorna la flag perche' e' gia' stato stampato una misura con + 
        }

        if (flagPrimoPiu) break;
    }

}