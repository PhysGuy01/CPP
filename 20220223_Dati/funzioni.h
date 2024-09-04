#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct walker {
    int x, y, n; // Coord iniziali e numero n di passi
    char *moves; // array delle n mosse (n caratteri)
    bool s; // true: dispositivo messaggero, false: altrimenti
};

void print(stringstream &v);
walker *loadWalker(walker *w, int &K, int &n);
int contaMess(walker *w, int &K);
walker *loadMess(walker *w, int &K, int &nMess);
double calcDist(walker w1, walker w2);
double calcMaxDist(walker *w, int &K);
walker *aggPos(walker *w, int &K, int &n);
walker *aggMess(walker *w, int &K, float &dist);