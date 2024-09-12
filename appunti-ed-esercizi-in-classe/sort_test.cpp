#include <iostream>
#include <string>
#include <time.h>
using namespace std;

// sorteggio ottimizzato
void sort_array(int a[], int n) {
    int *p, *q;
    for(int i = 0; i < n; i++) {
        p = &a[i];
        for(int j = i; j < n; j++){
            q = &a[j];
            if (*p < *q) {
                double tmp = *p;
                *p = *q;
                *q = tmp;
            }
        }
    }
}
void sorteggio_std(int a[], int n) {
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++){
            if (a[i] < a[j]) {
                double tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

int main(){
    int v[100000];
    for (int i = 0; i < 100000; i++){
        v[i] = i * abs(-1)^i + i;
    }
    clock_t tStart = clock();
    sort_array(v, 100000);
    cout << "Time taken: "<< (double)(clock() - tStart)/CLOCKS_PER_SEC << "s" << endl;
    return 0;
}