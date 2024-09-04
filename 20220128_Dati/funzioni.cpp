#include "funzioni.h"

// Conta le righe in un file
int contaRighe(string filename){
    fstream f;
    f.open(filename, ios::in);

    if (!f.good()) 
        throw runtime_error("Could not open file.");
    
    string riga;
    int count = 0;
    while(getline(f, riga)) 
        count++;
    
    return count;
}

// Carica i dati su un array di netpacket
netpacket *loadData(netpacket *pack, int &nPacks) {
    fstream f;
    f.open("data.dat", ios::in);

    if (!f.good()) 
        throw runtime_error("Could not open file.");

    for(int i = 0; i < nPacks; i++) 
        f >> pack[i].time >> pack[i].db >> pack[i].data;

    return pack;   
}

// Stampa a video e su file
void print(stringstream &v, string filename) {
    fstream f;
    f.open(filename, ios::app);

    cout << v.str();
    f << v.str();

    v.str("");
    v.clear();
}

// Returna un array di tipo netpacket con i pacchetti di buona qualità
netpacket* goodPack(netpacket *pack, int &nPacks, int &nGood) {
    nGood = 0;
    for (int i = 0; i < nPacks; i++)
        if (pack[i].db >= 90)
            nGood++;

    stringstream sout;
    netpacket *gPack = new netpacket[nGood];
    int jG = 0, jB = 0;
    for (int i = 0; i < nPacks; i++)
        if (pack[i].db >= 90){
            gPack[jG] = pack[i];
            jG++;
        } else {
            jB++;
            sout << "Pacchetto corrotto #" << jB << ": " << endl <<
                    "\tTimestamp: " << pack[i].time << endl <<
                    "\tData: " << pack[i].data << endl << endl; 
            print(sout, "corrotti.out");
        }
    
    return gPack;
}

// Riordina i pacchetti in ordine crescente di tempo
netpacket *sortPacks(netpacket *pack, int &nPacks) {
    for (int i = 0; i < nPacks; i++)
        for (int j = 0; j < nPacks; j++)
            if (pack[i].time < pack[j].time) {
                netpacket tmp = pack[i];
                pack[i] = pack[j];
                pack[j] = tmp;
            }
    return pack;
}

// Stampa i primi e gli ultimi cinque pacchetti 
void stampaPacchetti(netpacket *pack, int &nPacks) {
    stringstream sout;
    for (int i = 0; i < 5; i++) {
        sout << "\nPacchetto #" << i + 1 << endl <<
                "\tTimestamp: " << pack[i].time << endl <<
                "\tData: " <<pack[i].data << endl;
        print(sout, "risultati.dat");
    }

    for (int i = nPacks - 5; i < nPacks; i++) {
        sout << "\nPacchetto #" << i + 1 << endl <<
                "\tTimestamp: " << pack[i].time << endl <<
                "\tData: " <<pack[i].data << endl;
        print(sout, "risultati.dat");
    }
}

// Stampa il messaggio con i pacchetti rimasti
void stampaMess(netpacket *pack, int &nPacks) {
    stringstream sout; 
    sout << "\n------------------------------------------" << endl << endl <<
            "Messaggio ricevuto: " << endl;
    print(sout, "risultati.dat");

    for (int i = 0; i < nPacks; i++) {
        char dat = pack[i].data;
        switch (dat) {
            case '#':
                sout << ' ';
                break;
            
            case '?':
                sout << endl;
                break;

            default:
                sout << pack[i].data;
                break;
        }
        print(sout, "risultati.dat");
    }
}
