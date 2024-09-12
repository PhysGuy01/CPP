#include "funzioni.h"
#include <iostream>

using namespace std;

int main(){
    double a = 5;
    double b = 10;

    scambia1(a, b);
    cout << a << " " << b << endl;

    scambia2(&a, &b);
    cout << a << " " << b << endl;

    return 0;
}