#include "lib.h"

int contaDATI(){
    ifstream in;
    in.open("data.dat");
    if ( !in ) {
        cout << "File inesistente" << endl;
        return -1;
    }
    int k = 0;
    string s;
    getline(in, s);
    while ( !in.eof() ) {
        k++;
        getline(in, s);
    }
    in.close();
    return k;
}

void caricaDATI(double *X, int dim){
    ifstream in;
    in.open("data.dat");
    if ( !in ) {
        cout << "File inesistente" << endl;
    }
    for (int i=0; i<dim; i++) {
        in >> X[i];
    }
    in.close();
}

double sigmoide(double x){
    return 1 / ( 1 + exp( - x ) );
}

double neural(double x, neuralnet W){
    return sigmoide( W.w3 * sigmoide( W.w2 * sigmoide( W.w1 * x ) ) );
}

int contaPARAMS(){
    ifstream in;
    in.open("params.dat");
    if ( !in ) {
        cout << "File inesistente" << endl;
        return -1;
    }
    int k = 0;
    string s;
    getline(in, s);
    while ( !in.eof() ) {
        k++;
        getline(in, s);
    }
    in.close();
    return k;
}

void caricaPARAMS(neuralnet *X, int dim){
    ifstream in;
    in.open("params.dat");
    if ( !in ) {
        cout << "File inesistente" << endl;
    }
    for (int i=0; i<dim; i++) {
        in >> X[i].w1 >> X[i].w2 >> X[i].w3;
    }
    in.close();
}

bool NN(double v, neuralnet pars){
    return neural( v, pars) >= 0.5;
}
