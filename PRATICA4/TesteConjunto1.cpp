/*----------------- File: TestConjunto1.cpp  --------------+
| Programa para testar a primeira versao da implementacao  |
| da classe gen�rica Conjunto - sem lancamento de excecao  |
| Implementado por Marcus V. A. Andrade em 04/06/2013      |
| Atualizado por Marcus V. A. Andrade em 28/03/2017        |
+----------------------------------------------------------+ */

#include "Conjunto1.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
   int tam = 3;
   Conjunto<double> d(tam);

   cout << "\n--- Criando um conjunto de double (maximo " << tam << " elementos) --- \n" << endl;

   if (!d.insere(1.34))
       cout << "Erro na insercao de " << 1.34 << endl;
   if (!d.insere(3.1417))
       cout << "Erro na insercao de " << 3.1417 << endl;
   if (!d.insere(1.6666))
       cout << "Erro na insercao de " << 1.6666 << endl;

   if (d.pertence(3.1417))
      cout << "O valor de Pi esta no conjunto\n";
   else
      cout << "O valor de Pi nao esta no conjunto\n";

   if (d.pertence(0.3010))
      cout << "O valor de log 2 esta no conjunto \n";
   else
      cout << "O valor de log 2 nao esta no conjunto \n";

   if (!d.insere(0.9999))
        cout << "Erro na insercao de " << 0.9999 << endl;

   Conjunto<double> c = d;  // testa operador de atribuicao

   double r;
   bool ok;
   cout << "--- Inserindo elementos --- \n";
   for (int i=0; i < tam; i++) {
       cout << "Digite um numero = ";
       cin >> r;
       ok = d.insere(r);
       if (!ok) {
          cout << "A insercao nao pode ser realizada -- ";
          cout << d.numelementos() << endl;
          if (d.numelementos() == tam) {
              cout << "Capacidade maxima atingida\n";
              break;
          }
          else
              cout << "Elemento ja existe\n";
       }
   }

   cout << "\n--- CONJUNTO DE DOUBLE CRIADO ---\n";
   cout << "d  = " << d << endl;

   Conjunto<char> c1;
   cout <<  "\n--- Criando um conjunto de caracteres (maximo 10 elementos) --- \n" << endl;
   cin >> c1;

   Conjunto<char> c2(c1);         // testa construtor de copia
   cout << "c1 = " << c1 << endl;
   cout << "c2 = " << c2 << endl;

   if (c1 == c2)
      cout << "Os conjuntos c1 e c2 sao iguais \n";
   else
      cout << "Os conjunto c1 e c2 sao diferentes \n";

   if (c2.insere('x')) {
       cout << "c1 = " << c1 << endl;
       cout << "c2 = " << c2 << endl;
       if (c1 == c2)
          cout << "Os conjuntos c1 e c2 sao iguais \n";
       else
          cout << "Os conjunto c1 e c2 sao diferentes \n";
   }
   else
        cout << "Nao foi possivel inserir x no conjunto c2 \n";
   return 0;
}

/* -----------------------------------------------------
              Resultado esperado

OBS: Para obter o resultado esperado listado abaixo
� NECESS�RIO digitar os mesmos valores em cada item
solicitado. Apos digitar a letra u (no final dos testes)
pressione Ctrl+D (isso representa o final da entrada)
--------------------------------------------------------
 
--- Criando um conjunto de double (maximo 3 elementos) --- 

O valor de Pi esta no conjunto
O valor de log 2 nao esta no conjunto 
Erro na insercao de 0.9999
--- Inserindo elementos --- 
Digite um numero = 1
A insercao nao pode ser realizada -- 3
Capacidade maxima atingida

--- CONJUNTO DE DOUBLE CRIADO ---
d  = {1.34,3.1417,1.6666}

--- Criando um conjunto de caracteres (maximo 10 elementos) --- 

a 
e
i
e
o
u
c1 = {a,e,i,o,u}
c2 = {a,e,i,o,u}
Os conjuntos c1 e c2 sao iguais 
c1 = {a,e,i,o,u}
c2 = {a,e,i,o,u,x}
Os conjunto c1 e c2 sao diferentes 

*/
