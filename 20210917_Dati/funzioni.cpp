#include "funzioni.h"


// Conta le righe di un file
int contaRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);

    if (!f.good())
        throw runtime_error("Could not open file");
    
    string riga;
    int count = 0;
    while(getline(f, riga))
        count++;
    
    return count;
}

// Carica un array di tipo double con i dati da xgrid.dat
// e li stampa a video e su file salvando il valore minimo e ilmassimo
double *loadXgrid(int &N, double &max, double &min) {
    N = contaRighe("xgrid.dat");

    fstream f;
    f.open("xgrid.dat", ios::in);

    if (!f.good())
        throw runtime_error("Could not open file");
    
    stringstream sout;
    max = 0;
    min = 1;
    double* xgrid = new double[N];
    
    for (int i = 0; i < N; i++){
        f >> xgrid[i];

        if (xgrid[i] > max) max = xgrid[i];
        if (xgrid[i] < min) min = xgrid[i];

        sout << "Frazione di impulso #" << i + 1 << ": " << xgrid[i] << endl;
        print(sout);
    }

    return xgrid;
}

// Stampa a video e su un file risultati.dat separato
void print(stringstream &v) {
    fstream f;
    f.open("risultati.dat", ios::app);

    cout << v.str();
    f << v.str();

    v.str("");
    v.clear();
}

// Carica le repliche
replica *loadData(int &N, int &M) {
    fstream f;
    f.open("gluone.dat", ios::in);

    if (!f.good())
        throw runtime_error("Could not open file");
    
    M = contaRighe("gluone.dat");
    replica *gl = new replica[M];

    for(int i = 0; i < M; i++) {
        gl[i].data = new double[N];
        for (int j = 0; j < N; j++){
            f >> gl[i].data[j];
        }

        gl[i].nome = "gluone"; 
        gl[i].negdata = 0;       
    }

    return gl;
}

// Stampa le priime e le ultime tre repliche caricate
void stampPrimeUltimeTre(replica *gl, int &N, int &M) {
    stringstream sout;
    for (int i = 0; i < 3; i++) {
        sout << "\nReplica #" << i + 1 << ": ";
        print(sout);
        for (int j = 0; j < N; j++) {
            sout << gl[i].data[j] << " ";
            print(sout);
        }
    }

    for (int i = M - 3; i < M; i++) {
        sout << "\nReplica #" << i + 1 << ": ";
        print(sout);
        for (int j = 0; j < N; j++) {
            sout << gl[i].data[j] << " ";
            print(sout);
        }
    }
}

// Aggiorna i dati negativi per ogni replica 
replica *aggNegData(replica *gl, int &N, int &M) {
    for (int i = 0; i < M; i++) 
        for (int j = 0; j < N; j++) 
            if (gl[i].data[j] < 0) 
                gl[i].negdata++;
    return gl;
}

// Calcola la lunghezza di una replica
double calcArcLen(replica gl, int &N, double *xgrid) {
    double sum = 0;
    for (int i = 1; i < N; i++)
        sum += sqrt(pow(xgrid[i] - xgrid[i - 1], 2) + pow(gl.data[i] - gl.data[i - 1], 2));
    
    return sum;
}

// Aggiorna la lunghezza
replica *aggArcLen(replica *gl, int &N, int &M, double* xgrid) {
    for (int i = 0; i < M; i++)
        gl[i].arclength = calcArcLen(gl[i], N, xgrid);
    
    return gl;
}

// Calcola la massima lunghezza tra tutte le repliche
double maxLen(replica *gl, int &M) {
    double max = gl[0].arclength;
    for (int i = 0; i < M; i++)
        if (gl[i].arclength > max) 
            max = gl[i].arclength;
    
    return max;
}

// Calcola la media 
double calcMediaLen(replica *gl, int &M) {
    double sum = 0;
    for (int i = 0; i < M; i++) 
        sum += gl[i].arclength;
    
    return sum / M;    
}

// Calcola la deviazione standard delle len
double calcDevStdLen(replica *gl, int& M, double &mean) {
    double sumDiffQuad = 0;
    
    for (int i = 0; i < M; i++)
        sumDiffQuad += pow(gl[i].arclength - mean, 2);
    
    return sqrt(sumDiffQuad / M);
}

replica *aggRepliche(replica *gl, int &M, int &nGlAgg,  double &mean,  double &sigma) {
    nGlAgg = 0;
    
    for(int i = 0; i < M; i++)
        if (gl[i].arclength < mean + sigma)
            nGlAgg++;
    
    replica *glAgg = new replica[nGlAgg];

    fstream data;
    data.open("lenghts.dat", ios::app);

    int jGl = 0;
    for (int i = 0; i < M; i++)
        if (gl[i].arclength < mean + sigma){
            glAgg[jGl] = gl[i];
            data << glAgg[jGl].arclength << endl;
            jGl++;
        }

    return glAgg;
}