#include "funzioni.h"

void print(stringstream &v) {
    fstream f;
    f.open("risultati.dat", ios::app);

    cout << v.str();
    f << v.str();

    v.str("");
    v.clear();
}

// Conta le righe di un file
int contaRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);

    string riga;
    int count = 0;
    while(getline(f, riga))
        count++;

    return count;
}

// Carica i dati da linfociti.dat su un array 
linfocita *loadLinf(linfocita* linf, int nLinf) {
    fstream f;
    f.open("linfociti.dat", ios::in);

    if (!f.good()) 
        throw runtime_error("Could not load file");
    
    for (int i = 0; i < nLinf; i++){
        f >> linf[i].x >> linf[i].y >> linf[i].cap >> linf[i].r >> linf[i].id;
        linf[i].n_bact = 0;
    }

    return linf;
}

// Stampa i dati di tutti i linfociti
void stampaLinf(linfocita* linf, int nLinf) {
    stringstream sout;
    for (int i = 0; i < nLinf; i++) {
        sout << "Linfocita #" << i + 1 << endl << 
                "\tCoordinate: " << "(" << linf[i].x << ", " << linf[i].y << ")" << endl <<
                "\tN° di batteri fagocitabili: " << linf[i].cap << endl << 
                "\tRaggio: " << linf[i].r << endl << 
                "\tID: " << linf[i].id << endl <<
                "\tN° di batteri fagocitati: " << linf[i].n_bact << endl << endl;
        print(sout);
    }
}

// Carica i batteri da batteri.dat
batterio *loadBatt(batterio *batt, int nBatt) {
    fstream f;
    f.open("batteri.dat", ios::in);

    if (!f.good())
        throw runtime_error("Could not open file.");

    for (int i = 0; i< nBatt; i++){
        f >> batt[i].x >> batt[i].y;
        batt[i].killed_by = 'n';
    }

    return batt;
}


// Calcola la distanza tra un batterio e un linfocita
double calcDist(linfocita linf, batterio batt) {
    double dx = pow(batt.x - linf.x, 2);
    double dy = pow(batt.y - linf.y, 2);

    return sqrt(dx + dy);
}

// Ordina i linfociti per capacità decrescente
linfocita* sortLinf(linfocita* linf, int nLinf) {
    for (int i = 0; i < nLinf; i++)
        for (int j = i; j < nLinf; j++)
            if (linf[i].cap < linf[j].cap) {
                linfocita tmp = linf[i];
                linf[i] = linf[j];
                linf[j] = tmp;
            }
    return linf;
}

// Stampa tutti e soli i batteri uccisi 
void stampaBattAgg(batterio* batt, int nBatt) {
    stringstream sout;
    int jB = 1;
    for (int i = 0; i < nBatt; i++)
        if (batt[i].killed_by != 'n') {
            sout << "Batterio ucciso #" << jB << ": " << endl <<
                    "\tCoordinate: " << "(" << batt[i].x << ", " << batt[i].y << ")" << endl <<
                    "\tUcciso da: " << batt[i].killed_by << endl << endl;
            print(sout);
            jB++;
        }
}

// Salva su file ascisse.dat le ascisse dei batteri vivi  
// calcolando la minima e massima globale
void ascBattVivi(batterio *batt, int nBatt, int &minx, int &maxx) {
    fstream f;
    f.open("ascisse.dat", ios::app);

    minx = batt[0].x;
    maxx = batt[0].x;

    for (int i = 0; i < nBatt; i++)
        if (batt[i].killed_by == 'n'){
            
            f << batt[i].x << endl;

            if (batt[i].x < minx)   
                minx = batt[i].x;
            else if (batt[i].x > maxx)
                maxx = batt[i].x; 
        }
}