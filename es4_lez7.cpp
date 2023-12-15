#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const double xC = 1, yC = 1, r = 1;

double distanza(double xP, double yP){
    return sqrt(pow(xP - xC, 2) + pow(yP - yC, 2));
}

void check_circle(double xP, double yP, bool &status){
    double z = distanza(xP, yP);
    if (z < r) status = true;
    else status = false;
}

int main(){
    bool status;
    double xP, yP;
    cout << "\nInserire x: ";
    cin >> xP;
    cout << "Inserire y: ";
    cin >> yP;
    cout << "Distanza dal centro: " << distanza(xP, yP) << endl;
    check_circle(xP, yP, status);
    if (status) 
        cout << "Il punto sta nel cerchio" << endl;
    else cout << "Il punto non sta nel cerchio" << endl << endl;
}