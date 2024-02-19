#include <iostream>

using namespace std;

int main() {
    int size = 10, count = 0;
    int *dat = new int[size]{1,2,2,3,4,5,6,7,7,8};
    for (int i = 0; i <size; i++)   
        for (int j = i + 1; j < size; j++)
            if (dat[i] == dat[j])
                count++;


    cout <<"conta " << count << endl;
}