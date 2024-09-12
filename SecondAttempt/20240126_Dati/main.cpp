#include "funzioni.h"

int main() {

    // -------------------
    //   1. Classificati
    // -------------------

    int nIscr = contaRighe("iscritti.dat");

    giocatore* gioc = new giocatore[nIscr];

    gioc = loadGioc(gioc, nIscr);

    stringstream sout;
    
    sout << endl << "Numero di Iscritti: " << nIscr << endl << endl << 
        "Primi e ultimi tre iscritti:" << endl << endl;
    
    for (int i = 0; i < 3; i++) {
        sout << "Iscritto: " << gioc[i].cod << " " << ((gioc[i].is_pro) ? "pro" : "ama") << endl << endl;
        print(sout);
    }

    for (int i = nIscr - 3; i < nIscr; i++) {
        sout << "Iscritto: " << gioc[i].cod << " " << ((gioc[i].is_pro) ? "pro" : "ama") << endl << endl;
        print(sout);
    }


    // -------------------
    //     2. Punteggi
    // -------------------

    int nMan = contaRighe("punteggi.dat");

    mano* man = new mano[nMan];

    man = loadPunteggi(man, nMan);

    sout <<  endl << endl << "-------------------------------" << endl << endl <<
            "Numero di mani: " << nMan << endl <<
            "Prime e ultime tre mani: " << endl << endl;
    print(sout);

    for (int i = 0; i < 3; i++) {
        sout << "Mano #" << i + 1 << ": " << endl <<
                "   Codice: " << man[i].cod << endl <<
                "   Punti: " << man[i].punti << endl << endl;
        print(sout);
    }

    for (int i = nMan - 3; i < nMan; i++) {
        sout << "Mano #" << i + 1 << ": " << endl <<
                "   Codice: " << man[i].cod << endl <<
                "   Punti: " << man[i].punti << endl << endl;
        print(sout);
    }


    // ----------------------------
    //  3. Aggiornamento giocatori
    // ----------------------------

    gioc = updateGioc(gioc, man, nMan, nIscr);
    sout <<  endl << endl << "-------------------------------" << endl << endl <<
            "Primi e ultimi tre iscritti al torneo:" << endl << endl;
    print(sout);

    for (int i = 0; i < 3; i++) {
        sout << "Iscritto #" << i + 1 << ": " << endl << 
                "   Codice: " << gioc[i].cod << " " << ((gioc[i].is_pro) ? "pro" : "ama") << endl << 
                "   Punti: " << gioc[i].tot_punt << endl <<
                "   Mani: " << gioc[i].nmani << endl << endl;
        print(sout);
    }

    for (int i = nIscr - 3; i < nIscr; i++) {
        sout << "Iscritto #" << i + 1 << ": " << endl << 
                "   Codice: " << gioc[i].cod << " " << ((gioc[i].is_pro) ? "pro" : "ama") << endl << 
                "   Punti: " << gioc[i].tot_punt << endl <<
                "   Mani: " << gioc[i].nmani << endl << endl;        
        print(sout);
    }


    // ----------------------------
    //  4. Aggiornamento classfica
    // ----------------------------

    gioc = updateClassifTempor(gioc, nIscr);

    int nClassificati = contaRighe("classifica.dat");
    mano *classif = new mano[nClassificati];

    classif = loadClassif(classif, nClassificati);

    classif = updateClassTot(classif, nClassificati, gioc, nIscr);

    // Stampa la classifica generale
    sout << endl << endl << "-------------------------------" << endl << endl <<
        "Classifica generale aggiornata dal torneo di Masnago:" << endl << endl;
    print(sout);

    for (int i = 0; i < nClassificati; i++) {
        sout << "Classificato #" << i + 1 << ": " << endl <<
                "   Codice: " << classif[i].cod << endl << 
                "   Punteggio: " << classif[i].punti << endl << endl;
        print(sout);
    }

    delete[] gioc;
    delete[] man;
    delete[] classif;

    gioc = nullptr;
    man = nullptr;
    classif = nullptr;

    return 0;
}