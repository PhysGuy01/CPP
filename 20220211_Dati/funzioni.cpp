#include "funzioni.h"

// Carica i dati delle risposte
val* loadVal(int &nd) {    
    fstream f;
    f.open("schema.dat", ios::in);

    if (!f.good())
        throw runtime_error("Could not open file.");
    
    f >> nd; // numero di domande
    val *schema = new val[nd];

    for (int i = 0; i < nd; i++) 
        f >> schema[i].r >> schema[i].p;
    
    return schema;
}

// conta il numero di elaborati
int contaElab() {
    
    fstream f;
    f.open("letture.dat", ios::in);

    if (!f.good())
        throw runtime_error("Errore nell'apertura del file");

    // Conta le righe del file
    string riga;
    int nElab = 0;
    while (getline(f, riga)) 
        nElab++;

    return nElab;
}
// Carica elaborati su un array dinamico
elaborato *loadElaborati(elaborato *elabs, int &nElab, int &N) {
    fstream f;
    f.open("letture.dat", ios::in);

    if (!f.good())
        throw runtime_error("Errore nell'apertura del file");

    // Carica i dati da letture.dat su un array di elaborati
    for (int i = 0; i < nElab; i++) {
        f >> elabs[i].matr;

        elabs[i].nd = N;
        for (int j = 0; j < N; j++)
            f >> elabs[i].risp[j];
        
        elabs[i].voto = 0;
    }

    return elabs;
}

// Stampa i primi e gli ultimi cinque elaborati
void stampaPrimiUltimiCinque(elaborato *elabs, int &nElab, int& N) {
    cout << "\n-------------------------------------------\n\n" <<
            "Numero di elaborati caricati: " << nElab << endl;
    
    // Stampa i primi cinque elaborati
    for (int i = 0; i < 5; i++) {
        cout << "\nElaborato #" << i + 1 << endl << 
                "\tMatricola: " << elabs[i].matr << endl <<
                "\tNumero di domande: " << elabs[i].nd << endl <<
                "\tVoto: " << elabs[i].voto << endl <<
                "\tRisposte:";

        for (int j = 0; j < N; j++) 
            cout << " " << elabs[i].risp[j];
    }

    // Stampa gli ultimi cinque elaborati
    for (int i = nElab - 5; i < nElab; i++) {
        cout << "\nElaborato #" << i + 1 << endl << 
                "\tMatricola: " << elabs[i].matr << endl <<
                "\tNumero di domande: " << elabs[i].nd << endl <<
                "\tVoto: " << elabs[i].voto << endl <<
                "\tRisposte:";

        for (int j = 0; j < N; j++) 
            cout << " " << elabs[i].risp[j];
    }    

    cout << "\n-------------------------------------------\n\n";
}

// Aggiorna i voti degli elaborati
elaborato *aggPuntElabs(elaborato* elabs, int &nElabs, val *schema, int &N) {
    for (int i = 0; i < nElabs; i++) 
        for (int j = 0; j < N; j++) 
            if (elabs[i].risp[j] == schema[j].r)
                elabs[i].voto += schema[j].p;
    return elabs;
}

// Ordina le matricole in ordine crescente
elaborato *ordinaMatrElab(elaborato * elabs, int &nElab) {
    for (int i = 0; i < nElab; i++)
        for (int j = i; j < nElab; j++)
            if (elabs[i].matr > elabs[j].matr) {
                elaborato tmp = elabs[i];
                elabs[i] = elabs[j];
                elabs[j] = tmp;
            }
    return elabs;
}

// Stampa gli esiti
void stampaEsiti(elaborato *elabs, int &nElab) {
    fstream f;
    f.open("esiti.out", ios::app);

    for (int i = 0; i < nElab; i++)
        f << elabs[i].matr << " " << elabs[i].voto << endl;
    
    f.close();
}

// Stampa le statistiche dell'esame su statistiche.out
void stampaStatistiche(elaborato* elabs, int &nElab){
    fstream f;
    f.open("statistiche.out", ios::app);

    int promossi = 0, sum = 0;
    for (int i = 0; i < nElab; i++) 
        if (elabs[i].voto >= 18){
            sum += elabs[i].voto;
            promossi++;
        }

    f << "Numero di test totali: " << nElab << endl <<
         "Numero di studenti promossi: " << promossi << endl <<
         "Numero di studenti bocciati: " << nElab - promossi << endl <<
         "Media aritmetica dei voti sufficienti: " << static_cast<double>(sum) / promossi;
}