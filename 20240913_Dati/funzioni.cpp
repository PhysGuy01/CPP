#include "funzioni.h"

// Calcola il numero di righe in un file 
int contaRighe(string filename) {
    fstream f;
    f.open(filename, ios::in);
    if (!f) throw runtime_error("File non trovato");

    string line;
    int count = 0;
    while (getline(f, line)) 
        count++;
    
    f.close();
    return count;
}

// Stampa a video e su risultati.dat
void print(stringstream &ss) {
    fstream f;
    f.open("risultati.dat", ios::app);

    f << ss.str();
    cout << ss.str();

    ss.str("");
    ss.clear();
    f.close();
}

// Carica i dati dal file posizioni.dat in un array di posizioni
posizione* loadPos(posizione* pos, int nPos) {
    fstream f;
    f.open("posizioni.dat", ios::in);

    for (int i = 0; i < nPos; i++) 
        f >> pos[i].x >> pos[i].y;
    
    return pos;
}

// Stampa le prime e le ultime tre posizioni dall'array
void stampaPrimeUltimeTrePos(posizione* pos, int nPos) {
    stringstream sout;
    for (int i = 0; i < 3; i++) {
        sout << "Posizione #" << i + 1 << ": (" << pos[i].x << ", " << pos[i].y << ")" << endl;
        print(sout);
    }
    for (int i = nPos - 3; i < nPos; i++) {
        sout << "Posizione #" << i + 1 << ": (" << pos[i].x << ", " << pos[i].y << ")" << endl;
        print(sout);
    }
}

// Carica tutte le traiettorie dal file "traiettorie.dat" in un array di traiettoria
traiettoria* loadTraj(traiettoria* traj, int nTraj) {
    fstream f; 
    f.open("traiettorie.dat", ios::in);

    for (int i = 0; i < nTraj; i++) {
        f >> traj[i].t; // trova la lunghezza della traiettoria

        // Crea un array di char di lunghezza t
        traj[i].T = new char[traj[i].t]; 
        
        // cicla nella traiettoria secondo la sua lunghezza
        for (int j = 0; j < traj[i].t; j++) 
            f >> traj[i].T[j];
        
    }

    return traj;
}

// Calcola la traiettoria minima e massima tra quelle caricate su traj
void minMaxTraj(traiettoria* traj, int nTraj, int &max, int &min) {
    max = traj[0].t;
    min = traj[0].t;

    for (int i = 1; i < nTraj; i++) {
        if (traj[i].t > max)
            max = traj[0].t;
        else if (traj[i].t < min)
            min = traj[0].t;
    }
}

// Sorteggia le traiettorie in ordine di lunghezza crescente 
traiettoria* sortTraj(traiettoria* traj, int nTraj) {
    for (int i = 0; i < nTraj; i++)
        for (int j = i + 1; j < nTraj; j++)
            if (traj[j].t < traj[i].t) {
                traiettoria tmp = traj[i];
                traj[i] = traj[j];
                traj[j] = tmp;
            }
    return traj;
}

// Restituisce una posizione da una di partenza seguendo una traiettoria C
posizione follow(posizione start, traiettoria C) {
    for (int j = 0; j < C.t; j++) {
        switch (C.T[j]) {
            case 'N':
                start.y++;
                break;

            case 'E':
                start.x++;
                break;

            case 'W':
                start.x--;
                break;

            case 'S':
                start.y--;
                break;

            default:
                break;
        }
    }

    return start;
}

// Calcola la distanza dall'origine degli assi
double calcDist(posizione pos) {
    return sqrt(pow(pos.x, 2) + pow(pos.y, 2));
}


traiettoria trajDronePiuLontano(traiettoria* traj, int nTraj, posizione* pos, int nPos) {
    traiettoria maxTraj = traj[0];
    posizione maxPos = pos[0];

    for (int j = 0; j < nTraj; j++) {

        // Nuovo array di posizioni che verranno aggiornate secondo una traiettoria
        posizione* newPos = new posizione[nPos];
        newPos = pos;
        
        for (int i = 0; i < nPos; i++){
            newPos[i] = follow(newPos[i], traj[j]);
            double d = calcDist(newPos[i]);
            if (d > calcDist(maxPos)) {
                maxPos = newPos[i];
                maxTraj = traj[j];
            }
        }

        delete[] newPos;
        newPos = nullptr;
    }

    return maxTraj;
}   

// Aggiorna la posizione di un drone in base a un solo comando (N E S W)
posizione passoDrone(posizione pos, char CarTraj) {
    switch (CarTraj) {
            case 'N':
                pos.y++;
                break;

            case 'E':
                pos.x++;
                break;

            case 'W':
                pos.x--;
                break;

            case 'S':
                pos.y--;
                break;

            default:
                break;
        }
    return pos;
}

// Ritrona la lunghezza maggiore tra le due traiettorie
int maxTraDueTraj(traiettoria Cp, traiettoria Cq) {
    return ((Cp.t > Cq.t) ? Cp.t : Cq.t);
}

/*
bool collision(posizione p, posizione q, traiettoria Cp, traiettoria Cq) {
    for (int j = 0; j < maxTraDueTraj(Cp, Cq); j++) {
        if (passoDrone(p,))

    }

}

finito il tempo
*/