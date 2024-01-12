#include<iostream>
#include<string>

using namespace std;

// Struct di Arrays

// Stack
struct puntoArrStack {
    doule xcoord[2]; //  0 == x e 1 == y
};

// Heap
struct puntoArrHeap {
    double* xcoord;
}


// Array di Struct
struct punto {
    double x, y;
};


int main() {
    // Stack
    puntoArrStack pS;
    pS.xcoord[0] = 5;
    pS.xcoord[1] = 10;

    // Heap
    puntoArrHeap pH;
    pH.xcoord = new double[2];
    pH.xcoord[0] = 5;
    pH.xcoord[1] = -6;
    delete[] pH.xcoord;

    // Array di Struct
    punto p[10];
    // oppure
    punto *p = new punto[10];
    for (int i = 0; i < 10; i++) 
        cin >> p[i].x >> p[i].y;
    //  mi raccomando non p.x[i]!
    delete[] p;

    // posso scrivere:
    punto p;
    p.x = 7;
    p.y = 6; 
    // oppure 
    punto *p = new punto;
    p -> x = 7;
    p -> x = 6;


    return 0;
}