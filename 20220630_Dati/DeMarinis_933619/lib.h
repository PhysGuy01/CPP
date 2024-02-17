#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

struct neuralnet{
    double w1, w2, w3;
};   

int contaDATI();
void caricaDATI(double *X, int dim);
double sigmoide(double x);
double neural(double x, neuralnet W);
int contaPARAMS();
void caricaPARAMS(neuralnet *X, int dim);
bool NN(double v, neuralnet pars);

