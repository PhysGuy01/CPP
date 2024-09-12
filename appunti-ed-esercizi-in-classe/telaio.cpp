/*

    Esercizio 3 - Scelta Telaio 
    Author: Francesco Specchia (@PhysGuy01) - 2023

*/
#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main() {
    cout << "Programma per scegliere il telaio perfetto per la vostra bicicletta." << endl;

    cout << "Inserire la vostra età: ";
    int age;
    cin >> age;

    while(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Valore inserito non corretto. Inserire un numero intero: ";
        cin >> age;
    }

    if (age < 10) {
        cout << "Il telaio ideale è l'XS" << endl;
    } else if (age >= 10 && age <= 18) {

        cout << "Per favore, inserire la vostra altezza in m (eg: 1.58): ";
        float height;
        cin >> height;

        while(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Valore non corretto, reinserire il numero: ";
            cin >> height;
        }
        
        if (height <= 1.10) {
            cout << "Il telaio ideale è l'XS" << endl;

        } else if (height > 1.10 && height <= 1.30) {
            cout << "Per favore, inserire il vostro peso in kg come numero intero (eg: 69): ";
            int weight;
            cin >> weight;

            while(cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Valore non corretto, riprovare: ";
                cin >> weight;
            }

            if (weight <= 40) {
                cout << "Il telaio ideale è l'S" << endl;
            } else /* w>40 */ {
                cout << "Il telaio ideale è l'S" << endl;
            }

        } else if (height > 1.30 && height <= 1.60) {
            cout << "Il telaio ideale è l'M" << endl;
        } else if (height > 1.60) {
            cout << "Il telaio ideale è l'L" << endl;
        }

    } else {

        cout << "Per favore, inserire la vostra altezza in m (eg: 1.58): ";
        float height;
        cin >> height;

        while(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Valore non corretto, reinserire il numero: ";
            cin >> height;
        }

        cout << "Per favore, inserire il vostro peso in kg come numero intero (eg: 69): ";
        int weight;
        cin >> weight;

        while(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Valore non corretto, riprovare: ";
            cin >> weight;
        }

        if (height <= 1.40 || weight <= 40) {
            cout << "Il telaio ideale è l'XS" << endl;
        } else if (height > 1.40 && height <= 1.60) {
            cout << "Il telaio ideale è l'S" << endl;
        } else if (height > 1.60 && height <= 1.70) {
            cout << "Il telaio ideale è l'M" << endl;
        } else if (height > 1.70 && height <= 1.90) {
            cout << "Il telaio ideale è l'L" << endl;
        } else {
            cout << "Il telaio ideale è l'XL" << endl;
        }
    }

    return 0;
}