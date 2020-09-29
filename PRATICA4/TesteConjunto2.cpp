/*----------------- File: TestConjunto2.cpp  --------------+
| Programa para testar a segunda versao da implementacao   |
| da classe genérica Conjunto com sobrecarga dos           |
| operadores + (uniao, * (intersecao) e - (diferenca)      |
| Implementado por Marcus V. A. Andrade em 04/06/2013      |
| Atualizado por Marcus V. A. Andrade em 28/03/2016        |
+----------------------------------------------------------+ */

#include "Conjunto2.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{  Conjunto<double> dc1(5), dc2(7), dc(12);
   double r;
   cout << "Conjunto 1 (de double): \n";
   double x;
   for(int i=0;i<5;i++) {
    cin >> x;
    dc1.insere(x);
   }
   cout << "\n\nConjunto 2 (de double): \n";
   for(int i=0;i<4;i++) {
    cin >> x;
    dc2.insere(x);
   }
   cout << endl;

   cout << "dc1 + dc2 = " << dc1 + dc2 << endl;
   cout << "dc1 * dc2 = " << dc1 * dc2 << endl;
   cout << "dc1 - dc2 = " << dc1 - dc2 << endl << endl;

   Conjunto<int> ci;
   {
        cout << "\n\nConjunto ci (de inteiros): \n";
        int xi;
        for(int i=0;i<4;i++) {
          cin >> xi;
          ci.insere(xi);
         }
        Conjunto<int> ci2(ci);   // construtor de copia
        cout << "Apos construtor de  copia ci2(ci) \n";
        cout << "ci  = " << ci << endl;
        cout << "ci2 = " << ci2  << endl;

   } // para chamar o destrutor do objeto ci2

   cout << "Apos chamada do destrutor de ci2 \n";
   cout << "ci  = " << ci << endl << endl;

   // verifica se existe um numero entre 1 e 10 no conjunto ci
   for (int i=1; i <= 10; i++)
      if (ci.pertence(i)) {
         cout << "O elemento " << i << " pertence ao conjunto \n";
         break;
      }

   return 0;
}

/* -----------------------------------------------------
              Resultado esperado

OBS: Para obter o resultado esperado listado abaixo
É NECESSÁRIO digitar os mesmos valores em cada item
solicitado
--------------------------------------------------------

Conjunto 1 (de double): 
1.33
4.59
5.39
7.89
8.88


Conjunto 2 (de double): 
4.59
7.89
9.99
11.30

dc1 + dc2 = {1.33,4.59,5.39,7.89,8.88,9.99,11.3}
dc1 * dc2 = {4.59,7.89}
dc1 - dc2 = {1.33,5.39,8.88}



Conjunto ci (de inteiros): 
2
4
6
8
Apos construtor de  copia ci2(ci) 
ci  = {2,4,6,8}
ci2 = {2,4,6,8}
Apos chamada do destrutor de ci2 
ci  = {2,4,6,8}

O elemento 2 pertence ao conjunto




*/

