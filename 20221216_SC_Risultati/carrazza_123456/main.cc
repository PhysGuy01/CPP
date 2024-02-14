#include <iostream>
#include <sstream>
#include <cmath>
#include "funzioni.h"
using namespace std;

int main()
{
    stringstream sout; // my custom printer
    int ntot = 0;
    misure *m = load_misure("data.dat", ntot);

    sout << endl;
    sout << "Punto 1" << endl;
    sout << "#######" << endl;
    sout << "i)   Total points   = " << ntot << endl;
    sout << "ii)  Descrizione dei punti (t, vx, vy, vz, k): " << endl;
    print_misure(m, ntot, sout);

    sout << endl;
    sout << "Punto 2" << endl;
    sout << "#######" << endl;
    sout << "i) Sorting by time:" << endl;
    sort_by_time(m, ntot);
    sout << "ii) Printing to video:" << endl;
    print_misure(m, ntot, sout);

    sout << endl;
    sout << "Punto 3" << endl;
    sout << "#######" << endl;
    sout << "(x,y,z) @ t=5 = " << x(m[5]) << " " << y(m[5]) << " " << z(m[5]) << endl;
    sout << "(x,y,z) @ t=10 = " << x(m[10]) << " " << y(m[10]) << " " << z(m[10]) << endl;
    sout << "(x,y,z) @ t=15 = " << x(m[15]) << " " << y(m[15]) << " " << z(m[15]) << endl;


    // Punto 4
    sout << endl;
    sout << "Punto 4" << endl;
    sout << "#######" << endl;
    sout << "i & ii) computing masses..." << endl;
    fill_mass(m, ntot);
    sout << "iii) printing description" << endl;
    print_misure(m, ntot, sout);
    double mean_mass = 0, std_mass = 0;
    for (int i = 0; i < ntot; i ++)
    {
        sout << m[i].t << " "
             << m[i].vx << " "
             << m[i].vy << " "
             << m[i].vz << " "
             << m[i].K << " "
             << m[i].massa << endl;
        mean_mass += m[i].massa;
    }
    mean_mass /= ntot;
    for (int i = 0; i < ntot; i++)
    {
        std_mass += pow(m[i].massa - mean_mass, 2);
    }
    std_mass = sqrt(std_mass / ntot);

    sout << "iv) mean/std of masses = " << mean_mass << " " << std_mass << endl;

    // Punto 5
    store_masses(m, ntot);

    // print to terminal and file
    print_and_clear_buffer(sout);

    // clear memory
    delete[] m;

    return 0;
}
