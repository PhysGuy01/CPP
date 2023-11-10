#include <iostream>
using namespace std;

int main(){
    cout << "Fibonacci! Inserisci n numero di termini della sequenza che vuoi calcolare: ";
    int n;
    cin >> n;
    int a = 0, b = 1;
    cout << a << "\n" << b << endl;
    for (int i = 0; i <= n-3; i++) {
        int c = b + a;
        a = b;
        b = c;
        cout << c << endl;
    }
}