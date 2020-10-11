#include <iostream>
#include "MyList.h"
using namespace std;


void testaPushFront() {
  MyList<char> v;
  cout << v << endl;
  v.push_front('a');
  cout << v << endl;  
  for(int i=1;i<10;i++) {
    v.push_front('a'+i);
    cout << v << endl;
  }
}

void testaConstrutoresEtc() {
  MyList<char> v;
  cout << v << endl;
  v.push_back('a');
  cout << v << endl;  
  for(int i=1;i<10;i++) {
    v.push_back('a'+i);
    cout << v << endl;
  }



  { //testando criacao e destrucao de vetor vazio..
    MyList<char> v2;
  }

  {
    //copias de vetor vazio
    MyList<char> v2;
    MyList<char> v3 = v2; //construtor de copia
    v3 = v2;

    v2 = v;
    v2 = v;
    v3 = v;

    MyList<char> v4 = v2;
  }

  v.insert('0',v.begin());
  cout << v << endl;

  MyList<char>::iterator it = v.begin();
  it = v.next(it);
  it = v.next(it);
  it = v.next(it);
  v.insert('w',it);

  cout << v << endl;

  while(v.next(it)!=v.end()) it = v.next(it);
  v.insert('z',it);

  cout << v << endl; 


}

//descomente o codigo dessa funcao para apos terminar a etapa 3 da aula pratica
void testaEraseMatchingElements() {
  int n, numErase;
  cin >> n >> numErase;
  MyList<string> v; //Realiza testes com strings...
  string st;
  for(int i=0;i<n;i++) {
    cin >> st;
    v.push_back(st);
  }

  cout << "Lista: " << endl;
  cout << v << endl;
  for(int i=0;i<numErase;i++) {
      string elemRemover;
      cin >> elemRemover;
      cout << "Removendo: " << elemRemover << endl;
      int numRemoved = v.eraseMatchingElements(elemRemover);
      cout << "Numero de elementos removidos: " << numRemoved << endl;
      cout << "Nova lista: ";
      cout << v << endl;
    }
}

void testaReverse() {
  int n;
  cin >> n;
  MyList<string> v; //Realiza testes com strings...
  string st;
  for(int i=0;i<n;i++) {
    cin >> st;
    v.push_back(st);
  }
  cout << "Antes de reverse: " << endl;
  cout << v << endl;
  v.reverse();

  cout << "Apos reverse: " << endl;
  cout << v << endl;
}


/*
O arquivo de entrada contem um tipo de teste (ou testes com a funcao eraseMatchingElements ou testes com a funcao reverse ou testes mais gerais com a criacao/destruicao de listas)

As listas utilizadas nos testes contem apenas strings. Cada string e' formada apenas por letras e numeros.

A primeira linha do arquivo contem um caractere. Se o caractere for 'E', entao o arquivo representa
testes com a funcao eraseMatchingElements, caso contrario testes com a funcao reverse

-----------------
Arquivos de teste da funcao eraseMatchingElements:
A segunda linha contem dois inteiros o tamanho do vetor inicial e o numero N de chamadas a funcao eraseMatchingElements que serao realizadas
Na terceria linha teremos os elementos do vetor utilizado nos testes
Cada uma das proximas N linhas contem uma string representando o elemento que desejamos remover do vetor
-----------------
Arquivos de teste da funcao reverse:  
A segunda linha contem um numero N representando o numero de elementos a serem inseridos na lista
Na terceira linha ha N strings a serem inseridas na lista (sempre comecamos com uma lista vazia)

*/



int main() {
  MyList<string> v; //Realiza testes com strings...
  char tipoTeste;
  cin >> tipoTeste; 

  if(tipoTeste=='E') { //testes com funcao eraseMatchingElements...
    testaEraseMatchingElements();
  } else if(tipoTeste=='R') { //testes com funcao reverse
    testaReverse();
  } else {
    testaPushFront();
    testaConstrutoresEtc();
  }
}


