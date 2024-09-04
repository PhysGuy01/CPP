//
//                -- Author: @PhysGuy01 --
//        Programma per calcolare il prodotto scalare
//       la norma di una matrice e la matrice trasposta
//

#include <iostream>
#include <string>
#include <math.h>
using namespace std;

double scalar(int n, double* a, double* b) {
    double sum = 0;
    for (int i = 0; i < n; i++) 
        sum += a[i] * b[i];
    return sum;
}

double norm(int n, double* a) {
    return sqrt(scalar(n, a, a));
}

double scambia(double* x, double* y) {
    double tmp = *x;
    *x = *y;
    *y = tmp;
    return *x, *y;
}
int main(){
    const int n = 5;
    double v[n] = {1,2,3,4,5}, w[n] = {10,2,4,3,2};
    double M[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};

    cout << "v * w = " << scalar(n, v, w) << endl;
    cout << "||v|| = " << norm(n, v) << endl;
    
    for (int i = 0; i < 3; i++) 
        for (int j = 0; j < 3; j++) {
            scambia(&M[i][j], &M[j][i]); 
            cout << "M[" << i << "][" << j << "] = " << M[i][j] << endl;
        }

    return 0;
}
/*

| 1 2 3 |     | 1 4 7 |
| 4 5 6 | ==> | 2 5 8 |
| 7 8 9 |     | 3 6 9 |

{{1,2,3}, {4,5,6}, {7,8,9}} ==> {{1,4,7}, {2,5,8}, {3,6,9}}
*/