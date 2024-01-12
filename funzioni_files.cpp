/*
 
HEADERS "*.h"

SORGENTI
    |
    L >  main.cc
    |
    L > *.cc ...?
_____________________________________
Header |  functions.h
void setValue(double &x, double &y);

_____________________________________
//functions.cc
#include "functions.h"

void setValue(double &x, double &y) {
    x = y;
}

_____________________________________
//main.cc

#include "functions.h"

int main(){
    double v;
    setValue(v,5);
    return 0;
}
_____________________________________

==> per compilare:
g++ -o prog main.cc functions.cc

oppure (piu conveniente per molti files)

g++ -c functions.cc
...
g++ -o prog functions.o main.o (??? .o?)

*/

// stringstream per salvare i log dell'out

#include<sstring>
#include<iostream>

using namespace std;


// stampa su schermo e su un file txt separato
void print(stringstream &v) {
    cout << v.str();
    fstream f;
    f.open("files.txt");
    f << v.str();
}
int main(){
    stringstream ss;
    ss << "Hello" << "hi" <</*etc*/ endl;
    cout << ss.str();
    string a = ss.str();
    print(ss);
    
    return 0;
}