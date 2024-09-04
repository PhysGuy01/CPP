#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define N 10000 

int main() {
    fstream data;
    data.open("data_higgs.dat", ios::in);
    if (!data.good()) {
        cout << "Errore" << endl; 
        return 1;
    }

    double mass[N];
    for (int k = 0; k < N; k++) {
        data >> mass[k];
    }

    for (int i = 0; i < N - 1; i++)
        for (int j = i + 1; j < N; j++) 
            if (mass[i] > mass[j]) {
                double tmp = mass[i];
                mass[i] = mass[j];
                mass[j] = tmp;
            }

    double massmax = mass[sizeof(mass) / sizeof(*mass) - 1];
    double massmin = mass[0];
    cout << "Massa Massima:" << mass[sizeof(mass) / sizeof(*mass) - 1] << endl;
    cout << "Massa Minima:" << mass[0] << endl;
    
    int nbins = int((massmax - massmin) / 5) + 1;
    double *bins = new double[nbins];
    int *freq = new int[nbins];
    for(int i = 0; i < nbins; i++) {
        bins[i] = mass[0] +1 * 5;
        freq[i] = 0;
    }

    //histogram
    for (int i = 0; i < N; i++) {
        for (int b=0; b< nbins -1; b++) {
            if (mass[i] <= bins[b+1]) // prendiamo upper edge del bin come soglia altrimenti stkovfl
            {
                freq[b]++;
                break;
            }
        }
    }
    cout << "\nIstogr: " << endl;
    for (int b = 0; b< nbins; b++)
        cout << "M = " << bins[b] <<  " GeV -->" << freq[b] << endl;
    int famx = 0;
    int freqmax = freq[0];
    for (int i = 1; i < nbins; i++) {
        if (freq[i] > freqmax) {
            freqmax = freq[i];
            
        }
    }

}