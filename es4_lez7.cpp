//
//             -- Author: @PhysGuy01 --
//        Programma per controllare se un punto 
//    in coordinate cartesiane sta dentro un cerchio 
//            unitario centrato in (1,1)
//

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

double distanza(const double xP, const double yP, 
                const int &xC, const int &yC){
    return sqrt(pow(xP - xC, 2) + pow(yP - yC, 2));
}

void check_circle(double xP, double yP, 
                    int &xC, int &yC, 
                    int &r, bool &status){
    double z = distanza(xP, yP, xC, yC);
    if (z < r) status = true;
    else status = false;
}

int main(){
    int xC = 1, yC = 1, r = 1;
    bool status;
    double xP, yP;
    while (true) {
        cout << "\nInserire x e y: ";
        cin >> xP >> yP;
        if (cin.eof()) break;
        while(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Valore errato, inserisci due NUMERI: ";
            cin >> xP >> yP;
        } 
        cout << "\nDistanza dal centro: " << distanza(xP, yP, xC, yC) << endl;
        check_circle(xP, yP, xC, yC, r, status);
        if (status) 
            cout << "Il punto sta nel cerchio" << endl;
        else cout << "Il punto non sta nel cerchio" << endl << endl;
    }
}