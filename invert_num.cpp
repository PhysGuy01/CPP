#include <iostream>
using namespace std;

int main() {
    int n, nInv;
    cin >> n;
    nInv = 0;
    int resto = 0;
    while (n != 0) {
        resto = n % 10;
        nInv = resto + nInv * 10;
        n /= 10;
    }

    cout << nInv;
    return 0;
}