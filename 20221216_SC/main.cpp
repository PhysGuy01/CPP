#include "funzioni.h"

int main() {

    // -------------------
    //   1. Loading dati
    // -------------------

    int nMis = contaRighe("data.dat");
    misure *m = new misure[nMis];

    fstream data;
    data.open("data.dat", ios::in);

    // Carica i dati sull'array di misure
    for (int i = 0; i < nMis; i++) {
        data >> m[i].t >> m[i].vx >> m[i].vy >> m[i].vz >> m[i].K;
        m[i].massa = 0;
    }    
    
    data.close();

    cout << "tempo " << m[2].t << endl;

    // Stampa il numero di misure e la descrizione di tutte 
    stringstream sout;

    sout << "Numero di misure: " << nMis << endl;
    print(sout);

   stampaMisure(m, nMis); // ----------------------


    // -------------------------
    //   2. Ordinamento misure
    // -------------------------

    // Ordina le misure
    m = sortMisure(m, nMis);
    // Stampa le misure ordinate
    stampaMisure(m, nMis);


    // ----------------------------------
    //   3. Calcolo coordinate spaziali
    // ----------------------------------

    // Stampa le coord delle misure che hanno tempo t = 5, 10, 15
    double x, y, z;
    for (int i = 0; i < nMis; i++)
        if (m[i].t == 5 || m[i].t == 10 || m[i].t == 15){
            calcolaPosizione(m[i], x, y, z);
            sout << "\nCoordinate posizione della misura #" << i + 1 << ": " << "(" 
                                                                            << x << ", " 
                                                                            << y << ", " 
                                                                            << z << ")";
            print (sout);
        }
    

    // ---------------------------------
    //   4. Calcolo massa delle misure
    // ---------------------------------

    for (int i = 0; i < nMis; i++) 
        m[i].massa = calcolaMassa(m[i]);

    stampaMisure(m, nMis);

    sout << "\n\nMedia delle massa: " << meanM(m, nMis) << endl
        << "Dev Std: " << calcDevStdM(m, nMis) << endl;
    print(sout);


    // ----------------------------------
    //   5. Preparazione per pyplotting 
    // ----------------------------------

    fstream datamasse;
    datamasse.open("datamasse.dat", ios::app);

    for (int i = 0; i < nMis; i++) 
        datamasse << m[i].massa << endl;
    
    datamasse.close();

    delete[] m;

    return 0;
}