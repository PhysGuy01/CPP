#include <iostream>
#include <string>
using namespace std;

int main() {
    const int n = 5;
    double* a = new double[n]{2, 5, 10, 20, 50};
    double* b = new double[n]{10, -5, 3, 1, 100};

    double sum = 0;
    for (int i = 0; i < n; i++) {
        cout << a[i] << endl << b[i];
        sum += a[i] * b[i];
    }
    
    cout << "Prodotto Scalare: " << sum << endl;
    
    // TODO: normalizzazione

    delete[] a;
    delete[] b;

    return 0;
}