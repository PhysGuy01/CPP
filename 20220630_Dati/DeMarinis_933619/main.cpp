#include "lib.h"

int main() {
    
    int dimD = contaDATI();
    double *D = new double[dimD];
    caricaDATI(D, dimD);

    int dimP = contaPARAMS();
    neuralnet *P = new neuralnet[dimP];
    caricaPARAMS(P, dimP);

    ofstream out;
    out.open("risultati.dat");

    cout << endl;
    out << endl;

    cout << "Numero elementi caricati: " << dimD << endl;
    out << "Numero elementi caricati: " << dimD << endl;
    int p = 0, n = 0;
    for (int i=0; i<dimD; i++) {
        if ( D[i] >= 0 )
            p++;
        else 
            n++;
    }
    cout << "Numeri di elementi positivi: " << p << endl;
    out << "Numeri di elementi positivi: " << p << endl;
    cout << "Numeri di elementi negativi: " << n << endl;
    out << "Numeri di elementi negativi: " << n << endl;

    cout << endl;
    out << endl;

    cout << "Numero di parametri caricati: " << dimP << endl;
    out << "Numero di parametri caricati: " << dimP << endl;
    cout << endl;
    out << endl;
    cout << "Primi 5 set di parametri" << endl;
    out << "Primi 5 set di parametri" << endl;
    cout <<"-----------------------------------------------" << endl;
    out <<"-----------------------------------------------" << endl;
    for (int i=0; i<5; i++){
        cout << "w1=" << P[i].w1 << "\t" << "w2=" << P[i].w2 << "\t" << "w3=" << P[i].w3 << endl;
        out << "w1=" << P[i].w1 << "\t" << "w2=" << P[i].w2 << "\t" << "w3=" << P[i].w3 << endl;
    }
    cout << endl;
    out << endl;
    cout << "Ultimi 5 set di parametri" << endl;
    out << "Ultimi 5 set di parametri" << endl;
    cout <<"-----------------------------------------------" << endl;
    out <<"-----------------------------------------------" << endl;
    for (int i=dimP-5; i<dimP; i++){
        cout << "w1=" << P[i].w1 << "\t" << "w2=" << P[i].w2 << "\t" << "w3=" << P[i].w3 << endl;
        out << "w1=" << P[i].w1 << "\t" << "w2=" << P[i].w2 << "\t" << "w3=" << P[i].w3 << endl;
    }
    
    cout << endl;
    out << endl;

    cout << "Percentuale di elementi predetti correttamente per ciascun set di parametri" << endl;
    out << "Percentuale di elementi predetti correttamente per ciascun set di parametri" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    out << "-----------------------------------------------------------------------------" << endl;
    int r[dimP] = {};
    for (int i=0; i<dimP; i++) {
        r[i] = 0;
        for (int j=0; j<dimD; j++) {
            if ( NN( neural( D[j], P[i] ), P[i] ) == true && D[j] > 0 )
                r[i] = r[i] + 1;
            else 
                if ( NN( neural( D[j], P[i] ), P[i] ) == false && D[j] < 0 )
                    r[i] = r[i] + 1;
        }
        cout << i + 1 << ": " << (double) ( r[i] * 100 ) / dimD << "%" << endl;
        out << i + 1 << ": " << (double) ( r[i] * 100 ) / dimD << "%" << endl;
    }

    cout << endl;
    out << endl;
    
    double best = 0;
    int flag = 0;
    for (int i=0; i<dimP; i++)
        if ( r[i] / dimD > best ) {
            best = r[i] / dimD;
            flag = i;
        }
    cout << "Il set di parametri migliore e' il seguente:" << endl;
    cout << "w1=" << P[flag].w1 << "\t" << "w2=" << P[flag].w2 << "\t" << "w3=" << P[flag].w3 << endl;
    out << "Il set di parametri migliore e' il seguente:" << endl;
    out << "w1=" << P[flag].w1 << "\t" << "w2=" << P[flag].w2 << "\t" << "w3=" << P[flag].w3 << endl;

    cout << endl;
    out << endl;

    out.close();

    return 0;
}