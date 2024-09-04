
#include <iostream>
#include <cstring>

using namespace std;


int main() {
    char a[100];
    cout << "Enter a string: ";
    cin>>a;
    cout << "String: ";
    for (int i = 0; i < strlen(a); i++)
        cout << a[i] << "";

    cout << "\nThe length of the string is " << strlen(a) << endl;
    for (int i = 0;i < strlen(a) / 2; i++){
        char tmp = a[i];
        a[i] = a[strlen(a) - i - 1];
        a[strlen(a) - i - 1] = tmp;
    }

    cout << "Rev: ";
    for (int i = 0; i < strlen(a); i++)
        cout << a[i] << "";

    return 0;
}
