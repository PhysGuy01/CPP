#include "funzioni.h"

int main() {

    // ----------------------------
    //   1. Caricamento posizioni
    // ----------------------------

    int nPos = contaRighe("posizioni.dat");
    posizione* pos = new posizione[nPos];

    pos = loadPos(pos, nPos);

    stringstream sout;
    sout << endl << "Numero di posizioni caricate: " << nPos << endl << endl <<
            "Prime e ultime tre posizioni caricate:" << endl << endl;
    print(sout);

    stampaPrimeUltimeTrePos(pos, nPos);

    
    // Conta le posizioni in ciascun quadrante
    int nPosPrimo = 0, nPosSec = 0, nPosTer = 0, nPosQuar = 0;
    for (int i = 0; i < nPos; i++) {
        if (pos[i].x > 0 && pos[i].y > 0) // primo quadrante, x e y positive
            nPosPrimo++;
        else if (pos[i].x < 0 && pos[i].y > 0) // secondo quad, x neg y pos
            nPosSec++;
        else if (pos[i].x < 0 && pos[i].y < 0) // terzo quad, x neg y neg
            nPosTer++;
        else if (pos[i].x > 0 && pos[i].y < 0) // quarto quad, x pos y neg
            nPosQuar++;
    }

    sout << endl << "Numero di droni nel primo quadrante: " << nPosPrimo << endl <<
            "Numero di droni nel secondo quadrante: " << nPosSec << endl <<
            "Numero di droni nel terzo quadrante: " << nPosTer << endl <<
            "Numero di droni nel quarto quadrante: " << nPosQuar << endl << endl <<
            "------------------------------------------------------" << endl << endl;
    print(sout);


    // ------------------------------
    //   2. Caricamento traiettorie
    // ------------------------------

    int nTraj = contaRighe("traiettorie.dat");
    traiettoria* traj = new traiettoria[nTraj];

    traj = loadTraj(traj, nTraj);

    int min, max;
    minMaxTraj(traj, nTraj, max, min);

    sout << "Numero di traiettorie caricate: " << nTraj << endl <<
            "Lunghezza minima delle traiettorie: " << min << endl <<
            "Lunghezza massima delle traiettorie: " << max << endl << endl <<
            "Traiettorie in ordine crescente di lunghezza:" << endl;
    print(sout);

    traj = sortTraj(traj, nTraj);

    // Stampa la descrizione di tutte le traiettorie caricate 
    for (int i = 0; i < nTraj; i++) {

        sout << "Traiettoria #" << i + 1 << ":" << endl <<
                "   Lunghezza: " << traj[i].t << endl <<
                "   Comandi: ";

        // Stampa tutti i comandi
        for (int j = 0; j < traj[i].t; j++) 
           sout << traj[i].T[j] << " ";
    
        sout << endl << endl;
    
        print(sout);
    }


    // ------------------------------
    //   3. Aggiornamento posizioni
    // ------------------------------

    sout << "-------------------------------------" << endl <<
            "Posizioni dei droni aggiornate seguendo la traiettoria piu' corta:" << endl;
    print(sout);

    // Carica le posizioni iniziali dei droni in un array 
    posizione* posTrajCorta = new posizione[nPos];
    posTrajCorta = pos;

    // e calcola la posizione dei droni dopo aver seguito la traiettoria corta
    for (int i = 0; i < nPos; i++) {
        posTrajCorta[i] = follow(posTrajCorta[i], traj[0]);  // Le traiettorie sono in ordine crescente (la prima e' la piu corta)
        sout << "Posizione del drone #" << i + 1 << ": (" << posTrajCorta[i].x << ", " << posTrajCorta[i].y << ")" << endl;
        print(sout);
    }

    // -------------------------------------------------------
    //   4. Traiettoria che ha portato un drone piu' lontano
    // -------------------------------------------------------

    traiettoria trajLont = trajDronePiuLontano(traj, nTraj, pos, nPos);

    sout << endl << "----------------------------------------" << endl << endl <<
            "Traiettoria che ha portato un drone piu' lontano: " << endl <<
                "   Lunghezza: " << trajLont.t << endl <<
                "   Comandi: ";

    // Stampa tutti i comandi
    for (int j = 0; j < trajLont.t; j++) 
        sout << trajLont.T[j] << " ";
        
    sout << endl << endl;

    print(sout);


    delete[] pos;
    delete[] posTrajCorta;
    
    for (int i = 0; i < nTraj; i++) {
        delete[] traj[i].T;
        traj[i].T = nullptr;
    }

    delete[] traj;

    pos = nullptr;
    posTrajCorta = nullptr;
    traj = nullptr;

    return 0;
}