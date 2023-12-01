#include <iostream>
using namespace std;

// due tipi di array -1 stack = dimensione fissa usa memoria cpu (piu' veloce)
//                   -2 heap  = dimensione variabile, usa RAM (piu' lenta)
// DataType (int, double...) name[lenght = const/int/macro] 
// EX: int v[3]; ==> v[0]... , v[1]...
// EX2: 
// const n = 3
// int w[n]
//
// Nota: si potrebbe usare una lunghezza storata in una var non const con compiler g++ ma non e' pratica generale perche' compresa solo da un sottinsieme di compilers
// N.B. una MACRO e':
// #define N 3 --> N = 3 constant

int main() {
    // EX: numero ignoto di elementi
    const int N = 10000 // = dimensione max
    double v[N], x;
    for (;;) {
        if (cin.eof() || n > N - 1) break;
        v[n] = x;                               // OK ma non ottimale perche' spreca memoria soprattutto n << N
        n++;
    }    
    for (int i = 0; i < n; i++) {   
        sum += v[i]                             // secondo motivo per cui non e' ottimale: conveniva salvare i valori in una variabile sum
    }
    cout << sum / n;

    // possso definire gli array in linea cosi':
    double p[3] = {2.0, 2.5, 3.7}; // oppure ometto 3
    int l[10] = {0}; // associa 0 ad ogni posizione

    // posso anche definire degli array in due dimensioni cosi':
    int A[3][4]; // tre righe e quattro colonne

    // DINAMIC ARRAYS:
    // dataType* aname = new dataType [n. di unita'] --> n di unita' puo' anche essere 
    // EX:
    double* v = new double [10];
    delete[] v;


    // max value in array:
    double v[n];
    double max = v[0];
    for (int i = 1; i < n; i++) {
        if (v[i] > max) max = v[i]; // min: if (v[i] < min) min = v[i]
    }

    // sorting alg per v[n] in ordine crescente (O(n^2))
    for (int i = 0; i < n-1; i++)       // per ogni elemento della lista
        for (int j = i+1; j < n; j++)   // per ogni elemento dopo l'iesimo
            if (v[i] > v[j]) {          // controlla se il valore i-esimo e' maggiore     
                double tmp = v[i];      // quando lo e': lo storiamo temporaneamente in tmp perche' vogliamo scambiare i valori
                v[i] = v[j];            // valore i-esimo diventa il j-esimo
                v[j] = tmp;             // il j-esimo diventa quello che prima era l'i-esimo
            }


    return 0;
}