#include <iostream>
#include <fstream>
using namespace std;
int main(){
    fstream data;
    data.open("data.dat", ios::in);
    float sum=0.0, i=0, n=0;
    while(1) {
        data >> n;
        if (data.eof()) break;
        sum += n;
        i++;
    }
    cout << sum << endl;
    cout << i << endl;
    float avg = sum / i;
    cout << "media: " << avg << endl;
    return 0;
} 