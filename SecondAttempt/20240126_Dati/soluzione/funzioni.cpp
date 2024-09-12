#include "funzioni.h" 

// Stampa su schermo e su un file .dat separato
void print(stringstream &v) {
    cout << v.str();
    fstream res;
    res.open("risultati.dat", ios::app);
    res << v.str();
} 

// Calcola il numero di pro
int numeroPro(giocatore *g, int &n) {
    int pro = 0;
    for (int i = 0; i < n; i++) 
        if (g[i].is_pro) pro++;
    return pro;
} 

// Controlla se il giocatore è professionista o amatore e returna
// 'pro' o 'ama' di conseguenza
string isProAma(giocatore g) {
    if (g.is_pro) return "pro"; else return "ama";
}

// Stampa i dati di ogni giocatore
void stampaGiocatori(giocatore *g, int &n){
    stringstream datiGiocatore;

    for (int i = 0; i < n; i++) {
        datiGiocatore.str("");
        datiGiocatore.clear();
        datiGiocatore << "\nGiocatore #" << i + 1 << endl
                            << "\tCodice giocatore: " << g[i].cod << endl
                            << "\tProfessionista o amatore: " << isProAma(g[i]) << endl
                            << "\tNumero di mani giocate: " << g[i].nmani << endl
                            << "\tPunteggio totale: " << g[i].tot_punt << endl;

        print(datiGiocatore);
    }
}

// Ordina i giocatori in base al loro punteggio
void ordinaGiocatori(giocatore *g, int &n) {
    for (int i = 0; i < n; i++) 
        for (int j = i; j < n; j++) 
            if (g[i].tot_punt < g[j].tot_punt) {
                giocatore tmp = g[i];
                g[i] = g[j];
                g[j] = tmp;
            }
}

// Cerca il numero del giocatore in base al codice
int codiceAGiocatore(giocatore *g, int codice, int &n) {
    for (int i = 0; i < n; i++) {
        if (g[i].cod == codice) {
            return i; 
            break;
        } 
    }  
    return -1;
}

// Printa classifica nazionale
void stampaClassifica(mano *classificati, int &p){
    stringstream datiClassificato;

    for (int i = 0; i < p; i++) {
        datiClassificato.str("");
        datiClassificato.clear();
        datiClassificato << "\nClassificato #" << i + 1 << endl
                            << "\tCodice giocatore: " << classificati[i].cod << endl
                            << "\tPunteggio totale: " << classificati[i].punti << endl;

        print(datiClassificato);
    }
}

void ordinaClassificati(mano *classificati, int &p) {
    for (int i = 0; i < p; i++) 
        for (int j = i; j < p; j++) 
            if (classificati[i].punti < classificati[j].punti) {
                mano tmp = classificati[i];
                classificati[i] = classificati[j];
                classificati[j] = tmp;
            }
}
