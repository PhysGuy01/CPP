#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define N 1000

int main() {
    fstream data_moto;
    data_moto.open("data_moto.dat", ios::in);
    if (!data_moto.good()) {
        cout << "Errore" << endl; 
        return 1;
    }
    double v[N];
    for (int k = 0; k < N; k++) {
        data_moto >> x >> y;
        if (data_moto.eof()) break;
        v[k] = x / y;
    }
    data_moto.close();

    double sum0 = 0;
    for (int i = 0; i < N; i++) 
        sum += v[i];
    
    double avg = sum / N;
    cout << "Media: " << avg << endl;

    // dev std
    double sum1 = 0;
    for( int i = 0; i < N; i++) 
        sum1 =+ pow(v[i] - avg, 2);
    
    double sigma = sqrt(sum1 / (N - 1));
    cout << "Dev. Std: " << sigma << endl;

    // v max
    double vmax = v[0];
    for (int n = 0; n < N; n++)
        if (v[n] > vmax) vmax = v[n];
    
    // TODO: vmin e finisci vmax
        


    return 0;
}   