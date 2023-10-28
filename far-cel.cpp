/*

    Esercizio - Convertitore Farheneit-Celsius 
    Author: Francesco Specchia (@PhysGuy01) - 2023

*/
#include <iostream>
#include <string>
#include <limits>
using namespace std;

float FC(float F){
    float C;
    return C = (F - 32) / 1.8;
}

float CF(float C){
    float F;
    return F = C * 1.8 + 32;
}

int main() {
    string FC_CF;
    float F;
    float C;

    while(true) {
        cout << "\nInserisci FC per convertire Fahrenheit a Celsius o CF per il contrario. Scrivi q per uscire: ";
        cin >> FC_CF;

        if (FC_CF == "FC") {

            cout << "Valore in Farhenheit: ";
            cin >> F;

            while(cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Valore errato, inserisci un NUMERO: ";
                cin >> F;
            }
            cout << F << "F = " << FC(F) << "C! \n";
            continue;

        } else if (FC_CF == "CF") {

            cout << "Valore in Celsius: ";
            cin >> C;

            while(cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Valore errato, inserisci un NUMERO: ";
                cin >> C;
            }
            cout << C << "C = " << CF(C) << "F! \n";
            continue;

        } else if (FC_CF == "q") {
            break;

        } else {
            cout << "Mi spiace, non ho capito...\n \n";
            continue;
        }
    }
    return 0;
}
