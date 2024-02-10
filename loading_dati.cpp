// abbiamo un data.dat
#include<iostream>
#include <fstream>
using namespace std;

int main(){
    fstream f;
    f.open("data.dat", ios::in);
    int count = 0;
    string tmp;
    for(;;){
        getline(f,tmp);
        if(f.eof()) break;
        count++;
    } //conteggio linee di un file
    //oppure
    while(f.peek() != EOF){
        getline(f,tmp);
        count++;
    }
    // per tornare all'inizio del file:
    f.clear(); // ??
    f.seekg(0);
    // ...
}