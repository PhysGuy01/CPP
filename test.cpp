#include <iostream>
#include <vector>

using namespace std;


int main(){
    int a;
    cout << "Inserisci un numero: ";
    cin >> a;
    cout << "first even fib numbers smaller than " << a << ": ";
    vector<int> fibs = {0, 1};

    for (int i = 1; i < a; i++)
        fibs.push_back(fibs[i] + fibs[i - 1]);
    for (int i = 0; i < a && fibs[i] < a; i++){
        if (fibs[i] % 2 == 0)
            cout << " " << fibs[i];
    }
            

    return 0;
}