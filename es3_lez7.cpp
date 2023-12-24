#include <iostream>
#include <string>
#include <cmath>
#define pi 3.141592653589793

using namespace std;

double gauss(double x){
    return 1/(sqrt(2*pi)) * exp(-x*x/2);
}

double integrate_gaussian(double a, double b, int n) {
    double d = (b-a)/n;
    double integrale = 0;
    for (int i = 0; i < n; i++) 
        integrale += (gauss(a + i * d) + gauss(a + (i + 1) * d))/2;
    
    return d * integrale;
}
int main() {
    double a,b,n;
    cout << "Enter a: ";
    cin >> a;

    cout << "Enter b: ";
    cin >> b;

    cout << "Enter number of steps: ";
    cin >> n;

    cout << "\nIntegrale della Gaussiana tra " << a << " e " << b << " e': " << integrate_gaussian(a,b,n) << endl;
    return 0; 
}