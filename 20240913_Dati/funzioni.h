#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

struct posizione {
    int x, y;   // coordinate intere iniziali di un drone
};
struct traiettoria {
    int t;      // lunghezza della traiettoria
    char* T;    // array di t comandi di movimento
};

int contaRighe(string filename);
void print(stringstream &ss);
posizione* loadPos(posizione* pos, int nPos);
void stampaPrimeUltimeTrePos(posizione* pos, int nPos);
traiettoria* loadTraj(traiettoria* traj, int nTraj);
void minMaxTraj(traiettoria* traj, int nTraj, int &max, int &min);
traiettoria* sortTraj(traiettoria* traj, int nTraj);
posizione follow(posizione start, traiettoria C);
double calcDist(posizione pos);
traiettoria trajDronePiuLontano(traiettoria* traj, int nTraj, posizione* pos, int nPos);