#include <iostream>
#include <fstream>
#include <cmath>
#include "funzioni.h"
using namespace std;

#define NMAX 50000

// load events from file
misure *load_misure(string const &filename, int &ntotal)
{
    ifstream infile;
    infile.open(filename.c_str());
    if (!infile.good())
        throw runtime_error("Cound not open file.");

    misure *read = new misure[NMAX];
    for (;;)
    {
        infile >> read[ntotal].t >> read[ntotal].vx >> read[ntotal].vy >> read[ntotal].vz >> read[ntotal].K;
        read[ntotal].massa = 0;
        if (infile.eof())
            break;
        ntotal++;
    }

    // resize array for delivery
    misure *out = new misure[ntotal];
    for (int i = 0; i < ntotal; i++)
        out[i] = read[i];
    delete[] read;

    return out;
}

void print_misure(misure *m, int ntot, stringstream &sout)
{
    for (int i = 0; i < ntot; i++)
    {
        sout << m[i].t << " "
             << m[i].vx << " "
             << m[i].vy << " "
             << m[i].vz << " "
             << m[i].K << " "
             << m[i].massa << endl;
        ;
    }
}

double x(misure const& m)
{
    return m.vx * m.t;
}

double y(misure const& m)
{
    return m.vy * m.t + 0.5*m.t*m.t;
}

double z(misure const& m)
{
    return m.t*sqrt(m.vz);
}

void fill_mass(misure *m, int ntot)
{
    for (int i = 0; i < ntot; i++)
    {
        const double v = m[i].vx * m[i].vx + m[i].vy * m[i].vy + m[i].vz * m[i].vz;
        m[i].massa = 2 * m[i].K / v;
    }
}

void store_masses(misure *m, int ntot)
{
    fstream out;
    out.open("masses.dat", ios::out);
    if (!out.good())
        throw runtime_error("Cound not open file.");

    for (int i = 0; i < ntot; i++)
        out << m[i].massa << endl;
    out.close();
}

void print_and_clear_buffer(stringstream &ss)
{
    cout << ss.str();
    ofstream outfile("risultati.dat", ios::out);
    outfile << ss.str();
    ss.str("");
    ss.clear();
}

void sort_by_time(misure *m, int ntot)
{
    for (int i = 0; i < ntot - 1; i++)
        for (int j = i + 1; j < ntot; j++)
        {
            if (m[i].t > m[j].t)
            {
                misure tmp = m[i];
                m[i] = m[j];
                m[j] = tmp;
            }
        }
}
