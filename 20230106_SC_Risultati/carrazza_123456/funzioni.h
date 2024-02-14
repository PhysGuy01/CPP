#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>
using namespace std;

// Interface for events
struct evento
{
    bool segnale;
    double p1[4], p2[4], massainv;
};

// load events from file
evento *load_events(string const &filename,
                    int &ntotal, int &nsignal, int &nbackground);

// compute invariant mass
void compute_invmass(evento &evt);

// print to screen and file
void print_and_clear_buffer(stringstream &ss);

// sort by invmass
void sort(evento *evts, int ntot);

// print
string print_event(evento const &evt);

// Statistical estimators
enum event_type
{
    ALL_EVENTS,
    SIGNAL_EVENTS,
    BACKGROUND_EVENTS
};

// sum events
double sum(const evento *evts, int dim, const event_type etype);

// sum square events
double ssum2(const evento *evts, int dim, double mean, const event_type etype);

// minimum events
double min(const evento *evts, int dim, const event_type etype);

// maximum events
double max(const evento *evts, int dim, const event_type etype);
