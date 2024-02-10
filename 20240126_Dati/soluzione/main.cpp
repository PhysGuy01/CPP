#include "funzioni.h"

using namespace std;

int main() {
    fstream iscritti, punteggi;

    iscritti.open("iscritti.dat", ios::in);

    // array di giocatore 
    giocatore *g = new giocatore;

    int n = 0;
    while (iscritti.peek() != EOF){
        // codice
        iscritti >> g[n].cod;

        // is pro?
        if (g[n].cod <= 1000) g[n].is_pro = true; 
        else g[n].is_pro = false;

        // tot punti e numero mani
        g[n].tot_punt = 0;
        g[n].nmani = 0;

        n++;
    }
    // numero di iscritti = n
    for (int i = 0; i < n; i++) 
            cout << "Numero di Iscritti" << endl;

    // TODO: output on outout.txt (print())
    
    // analisi punteggi
    punteggi.open("punteggi.dat", ios::in);
    mano *m = new mano;

    int k = 0;
    while (punteggi.peek() != EOF) {
        punteggi >> m[k].cod >> m[k].punti;
        k++;
    }


    
}