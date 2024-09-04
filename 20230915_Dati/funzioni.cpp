#include "funzioni.h"

// Calcola il numero di righe in un file
int nRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);
    
    int count = 0;
    string riga;
    while(getline(f, riga)) {
        count++;
    }

    return count;
}

// Calcola il numero di bersagli distrutti in un 
// array di n bersagli 
int nDistrutti(bersaglio *b, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) 
        if (b[i].distr) count++;
    
    return count;
}

// Stampa a video e su file results.out
void print(stringstream &v) {
    cout << v.str();
    fstream f;
    f.open("results.out", ios::app);
    f << v.str();
}

// Stampa i primi bersagli non distrutti e i primi tre bersagli distrutti in un array di n bersagli
void stampaPrimiTreBers(bersaglio *b, int n){
    // Calcola il numero di bersagli distrutti e crea un array con essi
    int ndistr = nDistrutti(b, n);
    bersaglio *bDistr = new bersaglio[ndistr];

    int j = 0;
    for(int i = 0; i < n; i++) {
        if (b[i].distr){
            bDistr[j] = b[i];
            j++;
        }
    }

    // Calcola il numero di bersagli non distrutti e ne crea un array
    int nNonDistr = n - ndistr;
    bersaglio *bNnDistr = new bersaglio[nNonDistr];

    int p = 0;
    for(int i = 0; i < n; i++) {
        if (!b[i].distr){
            bNnDistr[p] = b[i];
            p++;
        }
    }

    stringstream bdis, nndis;
    bdis << "\n\nPrimi tre bersagli non distrutti: " << endl;
    print(bdis);

    // Stampa i dettagli dei primi tre non distrutti
    for (int i = 0; i < 3; i++) {
        bdis.str("");
        bdis.clear();
        bdis << "\nBersaglio #" << i + 1 << 
                "\n\tx: " << bNnDistr[i].x <<
                "\n\ty: " << bNnDistr[i].y << 
                "\n\tcor: " << bNnDistr[i].c << endl;
        print(bdis);
    }

    nndis << "\n\nPrimi tre bersagli distrutti: " << endl;
    print(nndis);

    // Stampa i dettagli dei primi tre distrutti
    for (int i = 0; i < 3; i++) {
        nndis.str("");
        nndis.clear();
        nndis << "\nBersaglio #" << i + 1 << 
                "\n\tx: " << bDistr[i].x <<
                "\n\ty: " << bDistr[i].y << 
                "\n\tcor: " << bDistr[i].c << endl;
        print(nndis);
    }
}

// Calcola le x del punto di impatto
double xImpatto(double theta, double phi) {
    double G = pow(100, 2) * sin(2*theta) / 9.81;
    double xf = G * cos(phi);
    return xf; 
}

// Calcola le y del punto di impatto
double yImpatto(double theta, double phi) {
    double G = pow(100, 2) * sin(2*theta) / 9.81;
    double yf = G * sin(phi);
    return yf; 
}

// Stampa i primi e gli ultimi tre colpi caricati
void stampaPrimiUltTreColpi(colpo *c, int &n) {
    stringstream colpi;
    colpi << "\n\nPrimi tre colpi sparati: " << endl;
    print(colpi);

    // Stampa i primi tre colpi
    for (int i = 0; i < 3; i++) {
        colpi.str("");
        colpi.clear();
        colpi << "\nColpo #" << i + 1 
            << "\n\tTheta = " << c[i].theta
            << "\n\tPhi = " << c[i].phi
            << "\n\t(xf, yf) = " << "(" << c[i].xf << ", " << c[i].yf << ")" 
            << "\n\tcolpito: " << c[i].hit << endl;
        print(colpi);
    }

    colpi << "\n\nUltimi tre colpi sparati: " << endl;
    print(colpi);
    // Stampa gli ultimi tre colpi
    for (int i = n - 3; i < n; i++) {
        colpi.str("");
        colpi.clear();
        colpi << "Colpo #" << i + 1 
            << "\n\tTheta = " << c[i].theta
            << "\n\tPhi = " << c[i].phi
            << "\n\t(xf, yf) = " << "(" << c[i].xf << ", " << c[i].yf << ")" 
            << "\n\tcolpito: " << c[i].hit << endl;
        print(colpi);
    }
}

// Calcola la distanza
double calcDist(double xi, double yi, double xf, double yf) {
    return sqrt(pow((xi - xf), 2) + pow((yi - yf), 2));
}

// Returna true se il colpo è andato a segno, false altrimenti
bool aSegno(double d) {
    if (d < delta) 
        return true;
    else
        return false; 
}

// Aggiorna stato dei bersagli
void aggStatoBers(bersaglio *b, int &nbersagli, colpo *c, int &ncolpi, double &colpiti, double &distrutti, double &dannoTOT) {
    for (int i = 0; i < nbersagli; i++) 
        for (int j = 0; j < ncolpi; j++) {

            double d = calcDist(b[i].x, b[i].y, c[j].xf, c[j].yf);
            
            if (aSegno(d)){
                c[j].hit = true;
                colpiti++;

                double danno = 2 * (1 - d / delta);
                dannoTOT += danno;

                // aggiorna la corazza e controlla se il bersaglio è stato distrutto
                b[i].c -= danno;
                if (b[i].c <= 0) {
                    b[i].distr = true;
                    distrutti++;
                }
            } 
        }   
}


double *distArray(colpo *c, double *dist, int &ncolpi){
    for (int i = 0; i < ncolpi; i++)
        dist[i] = calcDist(0, 0, c[i].xf, c[i].yf);
    return dist;
}

// Returna il massimo valore in un array di distanze
double maxD(double *dist, int &ndist) {
    double max = dist[0];
    for (int i = 0; i < ndist; i++) 
        if (max < dist[i])
            max = dist[i];
    return max;
}

// Returna il minimo valore in un array di distanze
double minD(double *dist, int &ndist) {
    double min = dist[0];
    for (int i = 0; i < ndist; i++) 
        if (min > dist[i])
            min = dist[i];
    return min;
} 

// Stampa la descrizione del colpo più lontano e più vicino
void stampaLontVic(double *dist, int &ncolpi, colpo *c) {
    stringstream colpi;
    for (int i = 0; i < ncolpi; i++) {
        colpi.str("");
        colpi.clear();
        double d = calcDist(0, 0, c[i].xf, c[i].yf);
        if (d == maxD(dist, ncolpi)){
            colpi << "\nIl colpo più lontano è il #" << i + 1 
                    << "\n\tTheta = " << c[i].theta
                    << "\n\tPhi = " << c[i].phi
                    << "\n\t(xf, yf) = " << "(" << c[i].xf << ", " << c[i].yf << ")" 
                    << "\n\tcolpito: " << c[i].hit << endl;
            print(colpi);
        } else if (d == minD(dist, ncolpi)) {
            colpi << "\nIl colpo più vicino è il #" << i + 1 
                    << "\n\tTheta = " << c[i].theta
                    << "\n\tPhi = " << c[i].phi
                    << "\n\t(xf, yf) = " << "(" << c[i].xf << ", " << c[i].yf << ")" 
                    << "\n\tcolpito: " << c[i].hit << endl;
            print(colpi);
        }
    }
}
