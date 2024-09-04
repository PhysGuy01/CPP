#include "funzioni.h"

// load events from file
evento *load_events(string const &filename,
                    int &ntotal, int &nsignal, int &nbackground)
{
    ifstream infile;
    infile.open(filename.c_str());
    if (!infile)
        throw runtime_error("Cound not open file.");

    ntotal = nsignal = nbackground = 0;
    string tmp;
    for (;;)
    {
        getline(infile, tmp);
        if (infile.eof())
            break;
        ntotal++;
    }
    infile.clear();
    infile.seekg(0);

    evento *out = new evento[ntotal];
    for (int i = 0; i < ntotal; i++)
    {
        for (int j = 0; j < 4; j++)
            infile >> out[i].p1[j];
        for (int j = 0; j < 4; j++)
            infile >> out[i].p2[j];
        infile >> out[i].segnale;
        if (out[i].segnale == true)
            nsignal++;
        else
            nbackground++;
    }
    return out;
}

// compute invariant mass
void compute_invmass(evento &evt)
{
    const double etot2 = pow(evt.p1[0] + evt.p2[0], 2);
    double ptot = 0;
    for (int i = 1; i < 4; i++)
        ptot += pow(evt.p1[i] + evt.p2[i], 2);
    evt.massainv = sqrt(etot2 - ptot);
}

// print to screen and file
void print_and_clear_buffer(stringstream &ss)
{
    cout << ss.str();
    ofstream outfile("risultati.dat", ios::app);
    outfile << ss.str();
    ss.str("");
    ss.clear();
}

// sort by invmass
void sort(evento *evts, int ntot)
{
    for (int i = 0; i < ntot - 1; i++)
        for (int j = i + 1; j < ntot; j++)
            if (evts[i].massainv > evts[j].massainv)
            {
                evento tmp = evts[i];
                evts[i] = evts[j];
                evts[j] = tmp;
            }
}

// print
string print_event(evento const &evt)
{
    stringstream res;
    res << "p1=(" << evt.p1[0] << "," << evt.p1[1] << "," << evt.p1[2] << "," << evt.p1[3] << ")" << endl;
    res << "p2=(" << evt.p2[0] << "," << evt.p2[1] << "," << evt.p2[2] << "," << evt.p2[3] << ")" << endl;
    res << "IsSignal = " << evt.segnale << endl;
    return res.str();
}

double sum(const evento *evts, int dim, const event_type etype)
{
    double sum = 0;
    for (int i = 0; i < dim; i++)
        if (etype == ALL_EVENTS)
            sum += evts[i].massainv;
        else if (etype == SIGNAL_EVENTS && evts[i].segnale == true)
            sum += evts[i].massainv;
        else if (etype == BACKGROUND_EVENTS && evts[i].segnale == false)
            sum += evts[i].massainv;
    return sum;
}

// somma scarto al quadrato
double ssum2(const evento *evts, int dim, double mean, const event_type etype)
{
    double sum = 0;
    for (int i = 0; i < dim; i++)
        if (etype == ALL_EVENTS)
            sum += pow(evts[i].massainv - mean, 2);
        else if (etype == SIGNAL_EVENTS && evts[i].segnale == true)
            sum += pow(evts[i].massainv - mean, 2);
        else if (etype == BACKGROUND_EVENTS && evts[i].segnale == false)
            sum += pow(evts[i].massainv - mean, 2);
    return sum;
}

// minimo
double min(const evento *evts, int dim, const event_type etype)
{
    double r = 1e5;
    for (int i = 0; i < dim; i++)
        if (etype == ALL_EVENTS)
        {
            if (evts[i].massainv < r)
                r = evts[i].massainv;
        }
        else if (etype == SIGNAL_EVENTS && evts[i].segnale == true)
        {
            if (evts[i].massainv < r)
                r = evts[i].massainv;
        }
        else if (etype == BACKGROUND_EVENTS && evts[i].segnale == false)
        {
            if (evts[i].massainv < r)
                r = evts[i].massainv;
        }
    return r;
}

// massimo
double max(const evento *evts, int dim, const event_type etype)
{
    double r = 0;
    for (int i = 0; i < dim; i++)
        if (etype == ALL_EVENTS)
        {
            if (evts[i].massainv > r)
                r = evts[i].massainv;
        }
        else if (etype == SIGNAL_EVENTS && evts[i].segnale == true)
        {
            if (evts[i].massainv > r)
                r = evts[i].massainv;
        }
        else if (etype == BACKGROUND_EVENTS && evts[i].segnale == false)
        {
            if (evts[i].massainv > r)
                r = evts[i].massainv;
        }
    return r;
}
