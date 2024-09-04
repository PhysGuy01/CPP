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

    // Stampano i primi e gli ultimi tre voti 
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

    int nAmmessi = 0;

    // Stampa tutti gli studenti registrati
    for (int i = 0; i < nStud; i++) {
        sout << "Studente #" << i + 1 << endl <<
                "   Matricola: " << stud[i].matr << endl <<
                "   Crediti: " << stud[i].cre << endl <<
                "   Media: " << stud[i].wm << endl <<
                "   Numero di esami falliti: " << stud[i].nfails << endl <<
                "   È fuori: " << ((stud[i].is_out) ? "fuori" : "dentro") << endl << endl; 
        print(sout);
        
        // Calcola il numero degli ammessi
        if (!stud[i].is_out) nAmmessi++;
    }


    // ----------------------------
    //     3. Scrematura espulsi
    // ----------------------------

    studente* newStud = new studente[nAmmessi];

    newStud = scremaStud(stud, nStud, newStud, nAmmessi);
    
    sout << endl << "------------------------" << endl <<
        "Primi e ultimi studenti passati in ordine di matricola crescente: " << endl << endl;
    print(sout);

    // Stampa i primi e gli utlimi tre studenti ammessi
    for (int i = 0; i < 3; i++) {
        sout << "Studente ammesso #" << i + 1 << endl <<
                "   Matricola: " << newStud[i].matr << endl <<
                "   Crediti: " << newStud[i].cre << endl <<
                "   Media: " << newStud[i].wm << endl <<
                "   Numero di esami falliti: " << newStud[i].nfails << endl << endl;
        print(sout);
    }

    for (int i = nAmmessi - 3; i < nAmmessi; i++) {
        sout << "Studente ammesso #" << i + 1 << endl <<
                "   Matricola: " << newStud[i].matr << endl <<
                "   Crediti: " << newStud[i].cre << endl <<
                "   Media: " << newStud[i].wm << endl <<
                "   Numero di esami falliti: " << newStud[i].nfails << endl << endl;
        print(sout);
    }


    // -----------------------------------
    //  4&5. Aggiornamento nuova sessione
    // -----------------------------------
    
    int nEspulsi = 0;

    newStud = updateStud(newStud, nAmmessi, vot, nVoti, nEspulsi);

    sout << endl << "------------------------" << endl <<
        "Numero di studenti espulsi in questa sessione: " << nEspulsi << endl << endl;
    print(sout);

    // Stampa tutti gli studenti espulsi
    int count = 1;
    for (int i = 0; i < nAmmessi; i++) 
        if (newStud[i].is_out) {
            sout << "Studente #" << count << endl <<
                    "   Matricola: " << newStud[i].matr << endl <<
                    "   Crediti: " << newStud[i].cre << endl <<
                    "   Media: " << newStud[i].wm << endl <<
                    "   Numero di esami falliti: " << newStud[i].nfails << endl <<
                    "   È fuori: fuori" << endl << endl; 
            print(sout);
            count++;
        }
    

    // ---------------------------------
    //   6. Aggiornamento file studenti
    // ----------------------------------

    savePassedStuds(newStud, nAmmessi);


    delete[] vot;
    delete[] stud;
    delete[] newStud;

    vot = nullptr;
    stud = nullptr;
    newStud = nullptr;

    return 0;
}