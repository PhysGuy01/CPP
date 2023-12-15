#include <iostream>
using namespace std;

/*

FUNZIONI:
    a) return un valore
    b) return void 


a) return value
dataType; 
 ||  nome funz ed eventuali argomenti   
 ||    |    |
 vv    v    v                        */
double y(double x) {
    return 3*x + 5;  // <-- return value double
}

/* 

b) return void
void  nome funz e args
 vv   vv      vv      vv            */
void prod(double a, double b) {
    cout << a * b << endl;
}

// Modalita' per riferimento:
void fun(double &a) {
    a = 5;
}


// C-Style:
void fun2(double *a) {
    *a = 5;
}


// EX: (scambio valori)
//      per rif
void scambioR(double &a, double &b) {
    double tmp = a;
    a = b;
    b = tmp;
}

// C-Style
void scambiaC(double *a, double *b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}


/* Funzioni per Array:
    due modalia' equivalenti:
-i              */
void print1(int *v, int n) {
    for(int i = 0; i < n; i++)
        cout << v[i] << endl;
}
/*
-ii             */
void print2(int v[], int n) {
    for(int i = 0: i < n; i++) 
        cout << v[i] << endl;
}

int main() {

    // a)
    cout << y(9.6) << endl;
    double t = -3.5;
    double z = y(t);
    cout << z << endl;


    // b)
    prod(3,5);


    // riferimento
    double w = 3;
    cout << w << endl; // --> 9
    fun(w);
    cout << w << endl; // --> 3


    // C-Style
    double v = 3
    y(&v);
    cout << v << endl; // --> 5


    // scambio rif
    double k = 5, h = 3;
    scambioR(k, h);
    cout << k << " " << h << endl;


    // scamio C-Style
    double p = 2, q = 7;
    scambioR(p, q);
    cout << p << " " << q << endl;

    // funzioni x array
    int *f = new int[10];

    print1(f, 10);
    print2(f, 10);

    delete[] f;


    return 0;  
}