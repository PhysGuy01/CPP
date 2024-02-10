#include "funzioni.h" 

// stampa su schermo e su un file txt separato
void print(stringstream v) {
    cout << v.str();
    fstream out;
    out.open("output.txt");
    out << v.str();
} 