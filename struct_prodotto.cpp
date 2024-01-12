#include<iostream>
#include<string>

using namespace std;

struct prodotto {
    string nome;
    int peso;
    double prezzo;
};

void stampaProdotto(prodotto p) {
    cout << endl << "Prodotto:" << endl;
    cout << "   - nome: " << p.nome << endl;
    cout << "   - peso: " << p.peso << endl;
    cout << "   - prezzo: " << p.prezzo << endl << endl;
}

void fattura(prodotto *p, int size){
    double tot = 0;

    cout << endl << "Fattura" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << " Nome\t\tPeso(g)\t\tPrezzo(euro)" << endl;
    for (int i = 0; i < size; i++){
        cout << " " << p[i].nome << "\t\t" << p[i].peso << "\t\t" << p[i].prezzo << endl;
        tot += p[i].prezzo;
    }
    cout << "-------------------------------------------------" << endl;
    cout << "Totale (euro): " << tot << endl;
    cout << "-------------------------------------------------\n" << endl;
}


int main(){
    /*
    prodotto banana;
    banana.nome = "banana";
    banana.peso = 200;
    banana.prezzo = 2.5;
    stampaProdotto(banana);
    */

    prodotto *p = new prodotto[4];

    cout << "Inserire nome del prodotto, peso e prezzo o 'q' per terminare la lista" << endl;

    int size = 0;
    for (int i = 0; i < 4; i++) {
        cout << "\nProdotto " << i + 1 << ": " << endl;
        cout << " - nome: ";
        cin >> p[i].nome;

        if (p[i].nome == "q") break;  

        cout << " - peso(g): ";
        cin >> p[i].peso;

        cout << " - prezzo(euro): ";
        cin >> p[i].prezzo;
        size++;      
    }

    fattura(p, size);

    
    delete[] p;

    return 0;
}