#include<iostream>
#include<string>

using namespace std;

struct vettore {
    double x;
    double y;
    double z;
};

double scalar(vettore v, vettore w) {
    return v.x * w.x + v.y * w.y + v.z * w.z;
}

vettore somma(vettore v, vettore w) {

    vettore somma;
    somma.x = v.x + w.x;
    somma.y = v.y + w.y;
    somma.z = v.z + w.z; 

    return somma;
    
}

int main(){
    vettore a,b;
    a.x = -1;
    a.y = 2;
    a.z = -3;
    
    b = a;

    cout << "\nProdotto scalare tra a e b: " << scalar(a,b) << endl;

    cout << "\nComponenti vettore somma a + b: "<< endl;
    vettore s = somma(a,b);

    cout << "x = " << s.x << endl;
    cout << "y = " << s.y << endl;
    cout << "z = " << s.z << endl;

    return 0; 
}