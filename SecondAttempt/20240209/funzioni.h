#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct voto {
    int cod, cre, matr, val;
};

struct studente {
    int matr, cre, nfails;
    float wm;
    bool is_out;
};

int contaRighe(string filename);
voto* loadVoti(voto* vot, int nVoti);
void print(stringstream &ss);
studente* loadStud(studente* stud, int nStud);