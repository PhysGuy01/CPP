#include "funzioni.h"

int contaRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);

    string line;
    int count = 0;
    while(getline(f, line))
        count++;
    
    return count;
}

void print(stringstream &ss) {
    fstream f;
    f.open("results.out", ios::app);

    cout << ss.str();
    f << ss.str();

    ss.str("");
    ss.clear();
}

bersaglio* loadBers(bersaglio* bers, int nBers, int &nDistr) {
    fstream f;
    f.open("bersagli.dat", ios::in);
    
    for (int i = 0; i < nBers; i++) {
        f >> bers[i].x >> bers[i].y >> bers[i].c;
        bers[i].distr = ((bers[i].c < 0) ? true : false);
        nDistr += ((bers[i].distr) ? 1 : 0);
    }

    return bers;
}

void stampaPrimiTreBers(bersaglio* bers, int nBers) {
    stringstream sout;
    int contaBers = 0;
    for (int i = 0; i < nBers; i++) {
        if (!bers[i].distr) {
            sout << "Bersaglio #" << i + 1 << ": " << endl <<
                    "   Coordinate (x, y): " << "(" << bers[i].x << ", " << bers[i].y << ")" << endl << 
                    "   Capacita': " << bers[i].c << ", " << ((bers[i].distr) ? "Distrutto" : "Intatto") << endl << endl;
            print(sout);
            contaBers++;
        }
        if (contaBers == 3) break;
    }

    contaBers = 0;
    for (int i = 0; i < nBers; i++) {
        if (bers[i].distr) {
            sout << "Bersaglio #" << i + 1 << ": " << endl <<
                    "   Coordinate (x, y): " << "(" << bers[i].x << ", " << bers[i].y << ")" << endl << 
                    "   Capacita': " << bers[i].c << ", " << ((bers[i].distr) ? "Distrutto" : "Intatto") << endl << endl;
            print(sout);
            contaBers++;
        }
        if (contaBers == 3) break;
    }
}

float calcXf(colpo colpi) {
    return pow(100,2)* sin(2*(colpi.theta)) * cos(colpi.phi) / 9.81;
}

float calcYf(colpo colpi) {
    return pow(100,2)*sin(2*(colpi.theta)) * sin(colpi.phi) / 9.81;
}

colpo* loadColpi(colpo *colpi, int nCol) {
    fstream f;
    f.open("alzo_angolo.dat", ios::in);

    for (int i = 0; i < nCol; i++) {
        f >> colpi[i].theta >> colpi[i].phi;
        colpi[i].hit = false;
        colpi[i].xf = calcXf(colpi[i]);
        colpi[i].yf = calcYf(colpi[i]);
        cout << colpi[i].xf;
    }

    return colpi;
}

// Stampa i primi e gli ultimi tre colpi caricati 🥳
void stampaPrimiUltimiTreColpi(colpo* colpi, int nCol) {
    stringstream sout;
    for (int i = 0; i < 3; i++) {
        sout << "Colpo #" << i + 1 << endl << 
                "   Alzo e angolo (θ, φ): " << "(" << colpi[i].theta << ", " << colpi[i].phi << ")" << endl << endl;
    }

    for (int i = nCol - 3; i < nCol; i++) {
        sout << "Colpo #" << i + 1 << endl << 
                "   Alzo e angolo (θ, φ): " << "(" << colpi[i].theta << ", " << colpi[i].phi << ")" << endl << endl;
    }
}

float calcDist(bersaglio bers, colpo colpi) {
    return sqrt(pow(bers.x - colpi.xf, 2) + pow(bers.y - colpi.yf, 2));
}

float calcH(bersaglio bers, colpo colpi) {
    return 2 * (1 - calcDist(bers, colpi) / 10);
}

bersaglio* updateBers(bersaglio* bers, int nBers, colpo* colpi, int nCol, int &colpiti, int &distrutti, float &dannoTOT) {
    for (int j = 0; j < nCol; j++) {
        for (int i = 0; i < nBers; i++){
                if (!bers[i].distr) {
                    colpi[j].hit = (calcDist(bers[i], colpi[j]) < 10) ? true : false;
                    cout << calcDist(bers[i],colpi[j]) << endl;
                    if (colpi[j].hit) {
                        colpiti++;
                        double danno = calcH(bers[i], colpi[j]);
                        bers[i].c -= danno;
                        dannoTOT += danno;
                        
                        if (bers[i].c < 0) {
                            bers[i].distr = true;
                            distrutti++;
                        }
                    }
                }
        }
    }
    return bers;
} 

colpo colpoMaxDist(colpo* colpi, int nCol) {
    colpo max;

    bersaglio origine;
    origine.x= 0;
    origine.y = 0;

    double distMax = calcDist(origine, max);

    for (int i = 1; i < nCol; i++) 
        if (calcDist(origine, colpi[i]) > distMax) 
            max = colpi[i];
    
    return max;
}


colpo colpoMinDist(colpo* colpi, int nCol) {
    colpo min;

    bersaglio origine;
    origine.x = 0;
    origine.y = 0;

    double distMin = calcDist(origine, min);

    for (int i = 1; i < nCol; i++) 
        if (calcDist(origine, colpi[i]) > distMin) 
            min = colpi[i];
    
    return min;
}