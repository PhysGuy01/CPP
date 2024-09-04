/**
 * Soluzione prova di laboratorio
 **/
#include "funzioni.h"
using namespace std;

int main(int argc, char **argv)
{
    // my custom printer
    stringstream sout;

    // Punto 1
    int ntot = 0, nsgl = 0, nbkg = 0;
    evento *evts = load_events("eventi.dat", ntot, nsgl, nbkg);

    sout << "Punto 1" << endl;
    sout << "#######\n"
         << endl;
    sout << "Total events = " << ntot << endl;
    sout << "Total signal = " << nsgl << ", frac = " << static_cast<double>(nsgl) / ntot << endl;
    sout << "Total bkg    = " << nbkg << ", frac = " << static_cast<double>(nbkg) / ntot << endl;

    // Punto 2
    sout << endl;
    sout << "Punto 2" << endl;
    sout << "#######\n"
         << endl;
    sout << "First 10 invariant masses:" << endl;
    for (int i = 0; i < ntot; i++)
    {
        compute_invmass(evts[i]);
        if (i < 10)
            sout << i + 1 << " invmass = " << evts[i].massainv << endl;
    }

    // Punto 3
    sout << endl;
    sout << "Punto 3" << endl;
    sout << "#######\n"
         << endl;
    sort(evts, ntot);
    for (int i = 0; i < 4; i++)
        sout << "Top " << i + 1 << ": " << endl
             << print_event(evts[i]) << endl;
    for (int i = ntot - 1; i >= ntot - 4; i--)
        sout << "Bottom " << i + 1 << ": " << endl
             << print_event(evts[i]) << endl;

    // Punto 4
    sout << endl;
    sout << "Punto 4" << endl;
    sout << "#######\n"
         << endl;
    sout << "(i) all events:" << endl;

    const double media_all = sum(evts, ntot, ALL_EVENTS) / ntot;
    const double stddev_all = sqrt(ssum2(evts, ntot, media_all, ALL_EVENTS) / ntot);
    const double min_mass = min(evts, ntot, ALL_EVENTS);
    const double max_mass = max(evts, ntot, ALL_EVENTS);

    sout << "media = " << media_all << endl;
    sout << "stdev = " << stddev_all << endl;
    sout << "min   = " << min_mass << endl;
    sout << "max   = " << max_mass << endl;

    sout << "\n(ii) signal events:" << endl;

    const double media_sgl = sum(evts, ntot, SIGNAL_EVENTS) / nsgl;
    const double stddev_sgl = sqrt(ssum2(evts, ntot, media_sgl, SIGNAL_EVENTS) / nsgl);
    const double min_mass_sgl = min(evts, ntot, SIGNAL_EVENTS);
    const double max_mass_sgl = max(evts, ntot, SIGNAL_EVENTS);

    sout << "media = " << media_sgl << endl;
    sout << "stdev = " << stddev_sgl << endl;
    sout << "min   = " << min_mass_sgl << endl;
    sout << "max   = " << max_mass_sgl << endl;

    sout << "\n(iii) background events:" << endl;

    const double media_bkg = sum(evts, ntot, BACKGROUND_EVENTS) / nbkg;
    const double stddev_bkg = sqrt(ssum2(evts, ntot, media_bkg, BACKGROUND_EVENTS) / nbkg);
    const double min_mass_bkg = min(evts, ntot, BACKGROUND_EVENTS);
    const double max_mass_bkg = max(evts, ntot, BACKGROUND_EVENTS);

    sout << "media = " << media_bkg << endl;
    sout << "stdev = " << stddev_bkg << endl;
    sout << "min   = " << min_mass_bkg << endl;
    sout << "max   = " << max_mass_bkg << endl;

    print_and_clear_buffer(sout);

    // Punto 5
    fstream out;
    out.open("massainv.dat", ios::out);

    for (int i = 0; i < ntot; i++)
        out << evts[i].massainv << endl;
    out.close();

    // clear memory
    delete[] evts;

    return 0;
}
