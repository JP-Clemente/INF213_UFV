#include <iostream>
#include <cassert>
#include "MyVec.h"
using namespace std;

//Realiza alguns testes na classe MyVec (a saida esperada se encontra no final deste arquivo)

int main() {
  MyVec<char> v;
  cout << v << endl;
  v.push_back('a');
  cout << v << endl;  
  for(int i=1;i<10;i++) {
    v.push_back('a'+i);
    cout << v << endl;
  }


  {
    cout << "Testando construtor de copia" << endl;
    MyVec<char> outroVetor(v);

    assert(outroVetor.size()==10);
    for(int i=0;i<10;i++) {
      assert(outroVetor[i] = 'a'+i);
    }

    outroVetor[2] = ' ';
    outroVetor[9] = 'z';
  }

  cout << "Verificando a consistencia do vetor original (apos a copia)" << endl;
  assert(v.size()==10);
  for(int i=0;i<10;i++) {
    assert(v[i] = 'a'+i);
  }

  cout << "Criando um vetor com 100 inteiros e testando resultado" << endl;
  MyVec<int> vetorInt;
  for(int i=0;i<100;i++) vetorInt.push_back(i);
  for(int i=0;i<100;i++) assert(vetorInt[i]==i);

  cout << "Utilizando outro construtor para criar um vetor com 10000 elementos" << endl;
  MyVec<int> vetorInt2(10000,99);
  for(int i=0;i<10000;i++) assert(vetorInt2[i]==99);
  assert(vetorInt2.size()==10000);


  { //testando criacao e destrucao de vetor vazio..
    MyVec<char> v2;
  }

  {
    //copias de vetor vazio
    MyVec<char> v2;
    MyVec<char> v3 = v2; //construtor de copia
    v3 = v2;

    v2 = v;
    v2 = v;
    v3 = v;

    MyVec<char> v4 = v2;
  }

  v.insert('0',0);
  cout << v << endl;
  v.insert('z',v.size());
  cout << v << endl;

  cout << "Testando insercao em posicao invalida do vetor" << endl;
  try {
    v.insert('-', -1);
  } catch (const MyVecException & e) {
    cout << e.what() << endl << endl;
  }


  cout << "Testando insercao em posicao invalida do vetor" << endl;
  try {
    v.insert('-', 1000);
  } catch (const MyVecException & e) {
    cout << e.what() << endl << endl;
  }

  v.insert('+',3);
  cout << v << endl;

  MyVec<char> v2;
  v2 = v;

  v.push_back('z');
  cout << v << endl;
  cout << v2 << endl;

  v2.push_back('w');
  cout << v << endl;
  cout << v2 << endl;

  v.resize(1);
  cout << v << endl;

  v.resize(0);
  cout << v << endl;

  v.push_back('q');
  cout << v << endl;


  v.resize(5);
  cout << v << endl;

  for(int i=0;i<5;i++)
    v[i] = 'x';

  cout << v << endl;

  v.resize(6);
  v[5] = 'y';
  cout << v << endl;

  v.resize(3);
  cout << v << endl;

  return 0;
  
}


/* Saida esperada:
Size: 0
Capacity: 0


Size: 1
Capacity: 1
a 

Size: 2
Capacity: 2
a b 

Size: 3
Capacity: 4
a b c 

Size: 4
Capacity: 4
a b c d 

Size: 5
Capacity: 8
a b c d e 

Size: 6
Capacity: 8
a b c d e f 

Size: 7
Capacity: 8
a b c d e f g 

Size: 8
Capacity: 8
a b c d e f g h 

Size: 9
Capacity: 16
a b c d e f g h i 

Size: 10
Capacity: 16
a b c d e f g h i j 

Testando construtor de copia
Verificando a consistencia do vetor original (apos a copia)
Criando um vetor com 100 inteiros e testando resultado
Utilizando outro construtor para criar um vetor com 10000 elementos
Size: 11
Capacity: 16
0 a b c d e f g h i j 

Size: 12
Capacity: 16
0 a b c d e f g h i j z 

Testando insercao em posicao invalida do vetor
Erro na funcao insert: posicao invalida

Testando insercao em posicao invalida do vetor
Erro na funcao insert: posicao invalida

Size: 13
Capacity: 16
0 a b + c d e f g h i j z 

Size: 14
Capacity: 16
0 a b + c d e f g h i j z z 

Size: 13
Capacity: 16
0 a b + c d e f g h i j z 

Size: 14
Capacity: 16
0 a b + c d e f g h i j z z 

Size: 14
Capacity: 16
0 a b + c d e f g h i j z w 

Size: 1
Capacity: 16
0 

Size: 0
Capacity: 16


Size: 1
Capacity: 16
q 

Size: 5
Capacity: 16
q     

Size: 5
Capacity: 16
x x x x x 

Size: 6
Capacity: 16
x x x x x y 

Size: 3
Capacity: 16
x x x 


*/