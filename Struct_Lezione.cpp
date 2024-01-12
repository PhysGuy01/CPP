#include<iostream>
#include<string>

using namespace std;

struct structname {
    // dataType nomeVar1;
    // dataType nomeVar2;
    //       ...
    // Ex.
    int prezzo;         // <--
    double colore;      // <--    membri della struct
};

// Ex.2
struct punto {
    double x;
    double y;
};

// Ex.3
struct constants {
    double pi = 3.141592653589
    double hbar = 1.05e-34
} myconst; // --> variabile globale


int main(){
    punto p;
    p.x = 2.5;
    p.y = 5;
    cin >> p.x;

    // Oppure inline
    punto p = {2.5, 5};
    //         p.x  p.y

    punto a,b;
    a.x = 5;    // generalmente a.x != b.x
    a.y = 10;   

    // ma posso fare:
    b = a   // ==> {b.x = a.x e b.y = a.y} copia tutti gli elementi di a in b
    return 0;
}