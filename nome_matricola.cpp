/*

    Esercizio 4 - Switch nome matricola
    Author: Francesco Specchia (@PhysGuy01) - 2023

*/
#include <iostream>
#include <limits>

int main() {   

    // dichiaro una variabile indicativa per il while loop 
    int i = 0;
    // variabile del numero di matricola
    int num;
    std::cout << "Inserire il numero di matricola: ";

    // finché non verrà aggiornata la variabile (= finché non trova la matricola) ripete il programma in loop
    while (i == 0){

        std::cin >> num;
        // se num non è un numero intero afferra l'errore e chiede di re-inserire il valore
        while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Valore inserito non corretto. Inserire un numero: ";
            std::cin >> num;
        }

        // switch per cercare il caso del numero di matricola
        switch (num) {
            case 33171:
                std::cout << "Nome della matricola n°" << num << ": Francesco Specchia." << std::endl;
                // aggiorno variabile indicativa per bloccare il loop
                i = 1;
                break;
            default:
                std::cout << "Matricola n°" << num << " non trovata." << std::endl;
                std::cout << "Inserire un altro numero: ";
                // i è ancora uguale a 0 ==> ripete il loop 
                break;
        }
    }

    return 0;
}