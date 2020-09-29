#include "Conjunto2.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    int n=40000;

    Conjunto<int> A(n), B(n);
    
    for(int i = 1; i<=n; i++){
        A.insere(i);
        B.insere(i);
    }

    Conjunto<int> C = A + B;

    cout << C.pertence(10) << endl;

    return 0;
}