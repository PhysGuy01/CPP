#include "funzioni.h"
// 9:50
int main(){

    // ----------------------------
    //   1. Caricamento parametri
    // ----------------------------

    // Apre il file con i parametri
    fstream pars;
    pars.open("parametri.dat", ios::in);
    
    if (!pars.good())
        throw runtime_error("Could not open file.");
    
    // e li carica sulle rispettive variabili:
    // num di disposititivi, n di passi
    // e distanza massima di trasmissione
    int K, n;
    float dist;
    pars >> K >> n >> dist;

    pars.close();

    // Stampa i parametri caricati
    stringstream sout;
    sout << "\nNumero di dispositivi: " << K << endl <<
            "Numero di passi: " << n << endl << 
            "Distanza max di trasmissione: " << dist << endl << 
            "-----------------------------------------------------------" << endl;
    print(sout);

    
    // -----------------------
    //   2. Caricamento dati
    // -----------------------

    walker *w = new walker[K];

    w = loadWalker(w, K, n);

    int nMess;
    walker *wMess = loadMess(w, K, nMess);

    for (int i = 0; i < nMess; i++) {

        sout << "\nDispositivo messaggero #" << i + 1 << ": " << endl <<
                "\tCoord iniziali: " << "(" << wMess[i].x << ", " << wMess[i].y << ")";
        print(sout);

        for (int j = 0; j < n; j++) {
            sout << " " << w[i].moves[j];
            print(sout);
        }
    }

    double maxDist = calcMaxDist(wMess, nMess);
    sout << "\n\n-----------------------------------------------------------" << endl << endl <<
            "Massuna distanza tra due dispositivi messaggeri all'istante iniziale: " << maxDist << endl;
    print(sout);


    // ------------------------------------------
    //   3. Aggiornamento posizione dispositivi
    // ------------------------------------------

    sout << "\n-----------------------------------------------------------" << endl;
    print(sout);


    // Crea un array di al massimo K dispositivi che possono essere messaggeri
    int countMess = nMess;
    walker *newMess = new walker[K];
    newMess = wMess;
    for (int i = 0; i < n; i++) {
        w = aggPos(w, K, i);
        for (int j = 0; j < K; j++) 
            for (int k = 0; k < K; k++)
                if (calcDist(w[j], w[k]) < dist){
                    if (w[j].s == 1 && w[k].s == 0){
                        newMess[countMess] = w[j];
                        countMess++;
                    } else if (w[j].s == 0 && w[k].s == 1) {
                        newMess[countMess] = w[k];
                        countMess++;
                    }
                }
        
        sout << "\nNumero messaggeri al passo #" << i + 1 << ": " << countMess;
        print(sout);
    }

    

    // Conta i messaggeri dopo n passi e li carica su un array
    //int nNewMess = contaMess(w, K);
    sout << "\n-----------------------------------------------------------" << endl << 
            "Numero di dispositivi messaggeri finale: " << countMess << endl << endl <<
            "Posizione finale e sequenza delle n mosse dei dispositivi messaggeri:" << endl <<endl;
    print(sout);

    // Stampa la pos finale e la sequenza delle n mosse dei dispositivi messaggeri
    for (int i = 0; i < countMess; i++) {
        sout << "Posizione finale del dispositivo #" << i + 1 << ": " << "(" << wMess[i].x << ", " << wMess[i].y << ")" << endl <<
                "Sequenza delle mosse: ";
        print(sout);

        for (int j = 0; j < n; j++){
            sout << " " << wMess[i].moves[j];
            print(sout);
        }

        sout << endl << endl;
        print(sout);
    }

    sout << "Massima distanza tra due dispositivi messaggeri: " << calcMaxDist(newMess, countMess) << endl;
    print(sout);

    for (int i = 0; i < K; i++){
        delete[] w[i].moves;
        w[i].moves = nullptr;
    }    
    
    delete[] w;
    w = nullptr;
    delete[] wMess;
    wMess = nullptr;
    

    return 0;
}   