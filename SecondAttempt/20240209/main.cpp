#include "funzioni.h"

int main() {

    // ----------------------------
    //     1. Caricamento voti
    // ----------------------------

    int nVoti = contaRighe("votiGF.dat");
    
    voto* vot = new voto[nVoti];

    vot = loadVoti(vot, nVoti);

    stringstream sout;
    sout << endl << "Primi e ultimi tre voti caricati: " << endl << endl;
    print(sout);

    for (int i = 0; i < 3; i++) {
        sout << "Voto #" << i + 1 << endl << 
                "   Codice: " << vot[i].cod << endl <<
                "   Crediti: " << vot[i].cre << endl <<
                "   Matricola: " << vot[i].matr << endl <<
                "   Voto conseguito: " << vot[i].val << endl << endl;
        print(sout);
    }

    for (int i = nVoti - 3; i < nVoti; i++) {
        sout << "Voto #" << i + 1 << endl << 
                "   Codice: " << vot[i].cod << endl <<
                "   Crediti: " << vot[i].cre << endl <<
                "   Matricola: " << vot[i].matr << endl <<
                "   Voto conseguito: " << vot[i].val << endl << endl;
        print(sout);
    }

    // ----------------------------
    //    2. Caricamento studenti
    // ----------------------------

    int nStud = contaRighe("studenti.dat");

    studente* stud = new studente[nStud];

    stud = loadStud(stud, nStud);

    sout << endl << "------------------------" << endl <<
        "Studenti caricati: " << endl << endl;
    print(sout);

    for (int i = 0; i < nStud; i++) {
        sout << "Studente espulso: " << endl <<
                "   Matricola: " << stud[i].matr << endl <<
                "   Crediti: " << stud[i].cre << endl <<
                "   Media: " << stud[i].wm << endl <<
                "   Numero di esami falliti: " << stud[i].nfails << endl <<
                "   È fuori: " << ((stud[i].is_out) ? "fuori" : "dentro"); 
        print(sout);
    }

    

    delete[] vot;
    delete[] stud;

    vot = nullptr;
    stud = nullptr;

    return 0;
}