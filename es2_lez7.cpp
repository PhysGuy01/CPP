#include <iostream>
#include <string>
using namespace std;

// printa il vettore
void print_array(int a[], int n){
    for(int i = 0; i < n; i++) {
        cout << "v[" << i << "] = " << a[i] << endl;
    }
}

// individua il massimo
int max_array(int a[], int n) {
    int r = a[0];
    for(int i = 0; i < n; i++) {
        if (a[i] > r)  
            r = a[i];
    }
    return r;
}

// indiviua il minimo
int min_array(int a[], int n) {
    int r = a[0];
    for(int i = 0; i < n; i++) {
        if (a[i] < r)  
            r = a[i];
    }
    return r;
}

// returna minimo e massimo
void min_max_array(int w[], int n, int &max, int &min) {
    max = max_array(w, n);
    min = min_array(w, n);
}

// sorteggio ottimizzato
void sort_array(int a[], int n) {
    int *p, *q;
    for(int i = 0; i < n; i++) {
        p = &a[i];
        for(int j = i; j < n; j++){
            q = &a[j];
            if (a[j] < a[i]) {
                double tmp = *p;
                *p = *q;
                *q = tmp;
            }
        }
        cout << "v[" << i << "] = " << a[i] << endl;
    }
}

int main(){
    int v[10] = {9,2,1,3,4,7,0,11,20,5};
    print_array(v, 10);
    cout << "\nmax = " << max_array(v, 10) << endl;
    cout << "min = " << min_array(v, 10) << endl;

    int min, max;
    min_max_array(v, 10, min, max);
    cout << "\nmin = " << min << "; max = " << max << endl;

    cout << "\nvettore sortato: " << endl;
    sort_array(v, 10);
    return 0;
}