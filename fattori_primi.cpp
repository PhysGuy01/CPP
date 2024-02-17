#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int> primi;
    cout << "Enter n: ";
    int n;
    cin >> n;
    cout << "fattori primi di " << n << ": ";

    for (int i = 2; i <= n; i++){
        while (n % i == 0) {
            primi.push_back(i);
            n /= i;
        }
    }

    for (int i = 0; i < primi.size(); i++) {
        int count = 1;
        while (i + 1 < primi.size() && primi[i] == primi[i + 1]) {
            count ++;
            i++;
        }
        cout << primi[i] << "^" << count << " ";
    }

    cout << endl;
    
    return 0;
}