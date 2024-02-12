#include "funzioni.h"

int main(){

    // -----------------------
    //   1. Analisi dei voti
    // -----------------------

    fstream voti;
    voti.open("votiGF.dat", ios::in);

    int nvoti = nrighe("votiGF.dat");

    // Array di voti
    voto *v = new voto[nvoti];

    // Caricamento dei voti sull'array
    for (int i = 0; i < nvoti; i++) {
        voti >> v[i].cod >> v[i].cre >> v[i].matr >> v[i].val;
    }

    voti.close();

    // Stampa dati generali sui voti (voti totali, sufficienti e insufficienti)
    int votiSuff = nSuff(v, nvoti);
    cout << "Numero di voti caricati: " << nvoti << 
            "\n% Sufficienti: " << votiSuff * 100 / nvoti << "%" << 
            "\n% Insufficienti: " << (nvoti - votiSuff)*100 / nvoti << "%" << endl;
    
    // Stampa primi tre voti
    for (int i = 0; i < 3; i++) {
        cout << "\nVoto #" << i + 1
                << "\n\tCodice esame: " << v[i].cod
                << "\n\tNumero crediti: " << v[i].cre
                << "\n\tVoto conseguito: " << v[i].val << endl;
    }

    // Stampa ultimi tre voti
    for (int i = nvoti - 3; i < nvoti; i++) {
        cout << "\nVoto #" << i + 1
                << "\n\tCodice esame: " << v[i].cod
                << "\n\tNumero crediti: " << v[i].cre
                << "\n\tVoto conseguito: " << v[i].val << endl;
    }


    // -----------------------
    //   2. Analisi studenti 
    // -----------------------

    fstream studenti;
    studenti.open("studenti.dat", ios::in);

    int nstud = nrighe("studenti.dat");

    // Array di studenti
    studente *s = new studente[nstud];

    // Carica i dati dagli studenti da studenti.dat e determina se sono boociati
    for (int i = 0; i < nstud; i++) {
        studenti >> s[i].matr >> s[i].cre >> s[i].wm >> s[i].nfails;
        s[i].is_out = Bocciato(s[i]);
    }

    // Stampa il numero di studenti totali e quelli espulsi e promossi
    int numEspulsi = nEspulsi(s, nstud);
    int numPromossi = nstud - numEspulsi;
    cout << "\nNumero studenti totali: " << nstud <<
            "\nStudenti espulsi: " << numEspulsi <<
            "\nStudenti non espulsi: " << numPromossi << endl;

    cout << "\nLista di studenti espulsi: ";
    stampaEspulsi(s, nstud);
    

    // Nuovo array di studenti senza i bocciati
    studente *sNew = scremaEspulsi(s, nstud);

    cout << "\nPrimi tre e ultimi tre studenti promossi in ordine di matricola: ";
    stampaPrimiUltimiTre(sNew, numPromossi);


    // ------------------------------------------------------------------
    //   4&5. Aggiornamento dati dopo la sessione di gennaio e febbraio
    // ------------------------------------------------------------------

    // Aggiorna l'array con i dati nuovi 
    studente *sNewNew = nuoviDatiStudGF(v, sNew, nvoti, numPromossi);

    // Localizza gli espulsi dopo questa sessione e li stampa a video
    // calcolando anche il numero di promossi e di bocciati
    int numNuoviEspulsi = nEspulsi(sNewNew, numPromossi);
    int numNuoviPromossi = numPromossi - numNuoviEspulsi;

    cout << "\nStudenti promossi dopo questa sessione: " << numNuoviPromossi << endl;
    cout << "\nStudenti bocciati dopo questa sessione: ";
    stampaEspulsi(sNewNew, numPromossi);

    // Screma gli studenti dopo l'aggiornamento e li stampa su studenti_GF.dat
    studente *studGF = scremaEspulsi(sNewNew, numPromossi);
    
    stampaPromossiGF(studGF, numNuoviPromossi);


    delete[] v;
    delete[] s;
    delete[] sNew;
    delete[] studGF;

    return 0;
}