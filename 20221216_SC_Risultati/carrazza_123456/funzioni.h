
#include <string>
#include <sstream>

// Interface for gruppo
struct misure
{
    int t;
    double vx, vy, vz, K, massa;
};

// load events from file
misure *load_misure(std::string const &filename, int &ntotal);

// print measures
void print_misure(misure *m, int ntot, std::stringstream &ss);

// sort by invmass
void sort_by_time(misure *m, int ntot);

// funzioni
double x(misure const& m);
double y(misure const& m);
double z(misure const& m);

// fill massa
void fill_mass(misure *m, int ntot);

// print masses to file
void store_masses(misure *m, int ntot);

// print to screen and file
void print_and_clear_buffer(std::stringstream &ss);
