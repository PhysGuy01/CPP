#include "funzioni.h"

using namespace std;

int main() {

    fstream iscritti, punteggi;


    // ---------------------
    //   Analisi giocatori
    // ---------------------

    iscritti.open("iscritti.dat", ios::in);

    string riga;
    int n = 0;
    while (getline(iscritti, riga)){
        n++;
    }

    iscritti.clear(); // clear the EOF flag
    iscritti.seekg(0, ios::beg); 

    // Nuovo array di giocatore 
    giocatore *g = new giocatore[n];
    
    // Carica su un array di giocatore i dati da iscritti.dat
    for (int i = 0; i < n; i++){
    
        // codice
        iscritti >> g[i].cod;

        // is pro?
        if (g[i].cod <= 1000) g[i].is_pro = true; 
        else g[i].is_pro = false;

        // tot punti e numero mani
        g[i].tot_punt = 0;
        g[i].nmani = 0;
        
    } // n è il numero di iterazioni compiute ==> numero di giocatoriù


    // Stringhe del numero di iscritti, professionisti ed amatori 
    // e del codice dei primi tre e ultimi tre giocatori e se sono pro o amatori
    stringstream NumIscritti, CodProAma;

    int numPro = numeroPro(g, n);
    NumIscritti << "Numero di Iscritti: " << n << endl <<
        "Numero di professionisti: " << numPro << endl <<
        "Numero di amatori: " << n - numPro << endl << endl;
    
    // stampa a video e su risultati.dat
    print(NumIscritti);

    
    // Stampiamo a video e sul file i primi tre e gli ultimi tre iscritti con codice e sigla 'pro' o 'ama' 

    // Primi tre iscritti
    for (int i = 0; i < 3; i++) {
        CodProAma.str("");
        CodProAma.clear();
        CodProAma << "Iscritto #" << i + 1 << " "<< g[i].cod << " " << isProAma(g[i]) << endl;
        print(CodProAma);
    }

    // Ultimi tre iscritti
    for (int i = n - 3; i < n; i++) {
        CodProAma.str("");
        CodProAma.clear();
        CodProAma << "Iscritto #" << i + 1 << " "<< g[i].cod << " " << isProAma(g[i]) << endl;
        print(CodProAma);
    }


    // ------------------
    //  Analisi punteggi
    // ------------------

    punteggi.open("punteggi.dat", ios::in);
    
    int k = 0;
    while (getline(punteggi, riga)){
        k++;
    }

    punteggi.clear(); // clear the EOF flag
    punteggi.seekg(0, ios::beg);

    mano *m = new mano[k];

    // carica dati da punteggi.dat su un array di mano
    for (int i = 0; i < k; i++) {
        punteggi >> m[i].cod >> m[i].punti;
    }

    // k è il numero complessivo di mani giocate e lo stampiamo
    stringstream numeroMani, stringaMani;

    numeroMani << "\nNumero mani giocate: " << k << endl << endl;
    print(numeroMani);


    // Analizziamo le prime tre e le ultime tre mani

    // Prime tre mani
    for (int i = 0; i < 3; i++) {
        stringaMani.str("");
        stringaMani.clear();
        stringaMani << "Mano #" << i + 1 << ", Codice giocatore: "<< m[i].cod 
                    << ", Punteggio: " << m[i].punti << endl;

        print(stringaMani);
    }

    // Ultime tre mani
    for (int i = k - 3; i < k; i++) {
        stringaMani.str("");
        stringaMani.clear();
        stringaMani << "Mano #" << i + 1 << ", Codice giocatore: "<< m[i].cod 
                    << ", Punteggio: " << m[i].punti << endl;

        print(stringaMani);
    }

    // Aggiornamento punteggio e numero di mani per ogni giocatore
    for (int i = 0; i < k; i++) {
        int numG = codiceAGiocatore(g, m[i].cod, n);
        g[numG].tot_punt += m[i].punti;
        g[numG].nmani += 1;
    }

    // Ordiniamo i giocatori e stampiamo i loro dati ordinati secondo la classifica
    ordinaGiocatori(g, n);
    stampaGiocatori(g, n);

    iscritti.close();
    punteggi.close();

    
    // ---------------------------------------
    //   Aggiornamento classifica nazionale
    // ---------------------------------------
    
    fstream tabellaClassifica;
    tabellaClassifica.open("classifica.dat", ios::in);
    
    int p = 0;
    while (getline(tabellaClassifica, riga)){
        p++;
    }
    tabellaClassifica.clear(); // clear the EOF flag
    tabellaClassifica.seekg(0, ios::beg);

    mano *classificati = new mano[p];

    for (int i = 0; i < p; i++) {
        tabellaClassifica >> classificati[i].cod >> classificati[i].punti;
    } 
    tabellaClassifica.clear(); // clear the EOF flag
    tabellaClassifica.seekg(0, ios::beg);

    // Aggiorna il punteggio della classifica nazionale
    for (int i = 0; i < p; i++) {
        int numG = codiceAGiocatore(g, classificati[i].cod, n);
        if (g[numG].nmani < 5) continue;
        else classificati[i].punti += g[numG].tot_punt; 
    }

    ordinaClassificati(classificati, p);
    stampaClassifica(classificati, p);

    delete[] g;
    delete[] m;
    delete[] classificati;

    return 0;
    
}