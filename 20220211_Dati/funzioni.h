#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct val{
    char r; // risposta corretta
    int p; // punti domanda
};


struct elaborato{
    int matr; // matricola dello studente
    int nd; /* numero di domande del test
    (cioe’ il valore N sopra descritto)*/
    char risp[10]; // per vettore delle risposte
    int voto; // valutazione finale del test
};

val* loadVal(int &nd);
elaborato *loadElaborati(elaborato *elabs, int &nElab, int &N);
int contaElab();
elaborato *aggPuntElabs(elaborato* elabs, int &nElabs, val *schema, int &N);
void stampaPrimiUltimiCinque(elaborato *elabs, int &nElab, int& N);
elaborato *ordinaMatrElab(elaborato * elabs, int &nElab);
void stampaEsiti(elaborato *elabs, int &nElab);
void stampaStatistiche(elaborato* elabs, int &nElab);