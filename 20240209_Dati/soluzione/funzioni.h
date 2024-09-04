#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct voto {
    int cod; // codice esame
    int cre; // crediti esame
    int matr; // matricola studente
    int val; // voto conseguito
};

struct studente {
    int matr; // matricola
    int cre ; // numero crediti
    float wm; // media pesata
    int nfails; // esami falliti
    bool is_out; // espulso o no
};

int nrighe(string filename);
int nSuff(voto *v, int &n);
bool Bocciato(studente s);
int nEspulsi(studente *s, int &n);
void stampaEspulsi(studente *s, int &n);
studente *scremaEspulsi(studente *s, int size);
studente *sortStudenti(studente *s, int &size);
void stampaPrimiUltimiTre(studente *s, int &NewSize);
studente *nuoviDatiStudGF(voto *v, studente *sNew, int &nvoti, int &numPromossi);
void stampaPromossiGF(studente *s, int &numNuoviPromossi);