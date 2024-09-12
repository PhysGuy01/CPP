#include "funzioni.h"

void scambia1(double &a, double &b){
    double tmp = a;
    a = b;
    b = tmp;
}

void scambia2(double *a, double *b){
    double tmp = *a;
    *a = *b;
    *b = tmp;
}