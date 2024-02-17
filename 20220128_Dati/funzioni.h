#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct netpacket{
    int time; // timestamp del pacchetto
    double db; // qualita' del pacchetto
    char data; // carattere del messaggio
};


int contaRighe(string filename);
netpacket *loadData(netpacket *pack, int &nPacks);
void print(stringstream &v, string filename);
netpacket* goodPack(netpacket *pack, int &nPacks, int &nGood);
netpacket *sortPacks(netpacket *pack, int &nPacks);
void stampaPacchetti(netpacket *pack, int &nPacks);
void stampaMess(netpacket *pack, int &nPacks);