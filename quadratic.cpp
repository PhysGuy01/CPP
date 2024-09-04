/*

    Esercizio - Risolutore equazioni quadratiche  
    Author: Francesco Specchia (@PhysGuy01) - 2023

*/
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main() {

    cout << "Programma per calcolare equazioni quadratiche del genere: ax^2 + bx + c." << endl;

    // chiediamo i parametri in input
    float a;
    cout << "Inserisci a: ";
    cin >> a;

    // se non viene inserito un float chiede di ri-inserire il valore
    while(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Valore errato, inserisci un NUMERO: ";
        cin >> a;
    }

    float b;
    cout << "Inserisci b: ";
    cin >> b;

    while(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Valore errato, inserisci un NUMERO: ";
        cin >> b;
    }
    
    float c;
    cout << "Inserisci c: ";
    cin >> c;

    while(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Valore errato, inserisci un NUMERO: ";
        cin >> c;
    }
    
    // calcolo Delta e definiamo i risultati
    float D = pow(b , 2) - 4 * a * c;
    float x1 , x2, x12;

    // se il delta è maggiore, minore o uguale a zero
    if (D>0) {
        x1 = (-b + sqrt(D))/2;
        cout << "x_1 = " << x1 << endl;
        x2 = (-b - sqrt(D))/2;
        cout << "x_2 = " << x2 << endl;

    } else if (D==0) {
        x12 = (-b + sqrt(D))/2;
        cout << "x_1 = x_2 = " << x12 << endl;

    } else if (D<0) {
        // definiamo parte reale e immaginaria
        float Re = -b/2;
        float Im = sqrt(-D)/2;

        // se la parte immaginaria è uguale a 1 la sottintendiamo per un risultato più pulito
        // eg: "-4 + 1i" ==> "-4 + i"
        if (Im != 1) {
            cout << "x_1 = " << Re << " + " << Im << "i" << endl;
            cout << "x_2 = " << Re << " - " << Im << "i" << endl;
        } else {
            cout << "x_1 = " << Re << " + " << "i" << endl;
            cout << "x_2 = " << Re << " - " << "i" << endl;
        }
    }
    return 0;
}