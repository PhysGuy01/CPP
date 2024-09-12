#include<iostream>
#include<string>

using namespace std;

struct punto {
    double x;
    double y;
};


//        per copia   vv    o per riferimento: punto &a || punto *a
void printStruct(punto a){ 
    cout << a.x << " " << a.y << endl;
}

void setStruct(punto &a) {
    a.x = 10;
    a.y = 20; // modifica i valori per riferimento quindi non printa 5, 10 ma 10, 20
}

int main(){
    punto p;
    p.x = 5;
    p.y = 10;
    printStruct(p);
    
    return 0;
}