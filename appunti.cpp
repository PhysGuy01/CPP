
#include <iostream>

using namespace std;
/*iostream
    -> std
        ->cout
        ->cin
        ->endl
        ...
 mylib
    -> mymod
        ->cout
        ->cin
        ...
==> per evitare malintesi e collisioni nel compiler, per includere entrambe posso usare per ex:
 using std::cout; --> ogni volta che uso cout faccio riferimento a quello nel namespace std di iostream
*/

int main(){
    cout << "hello \u2655" << endl;
    return 0;
}
