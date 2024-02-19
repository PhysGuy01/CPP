#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int main() {
    vector<int> vec = {0, 1};
    cout << "Enter n: ";
    int n;
    cin >> n;

    while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "errore, reinserire: ";
        cin >> n;
    }

    vector<int> fib = {0, 1};
    for (int i = 1; fib.size() < n; i++) 
        fib.push_back(fib[i] + fib[i - 1]);
    
    for (int i = 0; i < n; i++) 
        cout << fib[i] << ", ";

    cout << endl;
    return 0;
}