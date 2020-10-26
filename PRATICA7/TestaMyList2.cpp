#include <iostream>
#include "MyList2.h"
using namespace std;


void testaPushFront() {
  MyList2<char> v;
  cout << v << endl;
  v.push_front('a');
  cout << v << endl;  
  for(int i=1;i<10;i++) {
    v.push_front('a'+i);
    cout << v << endl;
  }
}

void testaConstrutoresEtc() {
  MyList2<char> v;
  cout << v << endl;
  v.push_back('a');
  cout << v << endl;  
  for(int i=1;i<10;i++) {
    v.push_back('a'+i);
    cout << v << endl;
  }



  { //testando criacao e destrucao de vetor vazio..
    MyList2<char> v2;
  }

  {
    //copias de vetor vazio
    MyList2<char> v2;
    MyList2<char> v3 = v2; //construtor de copia
    v3 = v2;

    v2 = v;
    v2 = v;
    v3 = v;

    MyList2<char> v4 = v2;
  }

  v.insert('0',v.begin());
  cout << v << endl;

  MyList2<char>::iterator it = v.begin();
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
  MyList2<string> v; //Realiza testes com strings...
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
  MyList2<string> v; //Realiza testes com strings...
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


template<class T>
typename MyList2<T>::iterator find(const T&elem, const MyList2<T> &list) { //funcao auxiliar para os testes
  typename MyList2<T>::iterator it = list.begin();
  while(it!=list.end() && list.derref(it)!=elem) {
    it = list.next(it);
  }
  return it;
}

void testaInsert() {
  int n,numInserts;
  cin >> n >> numInserts;
  MyList2<string> v; //Realiza testes com strings...
  string st;
  for(int i=0;i<n;i++) {
    cin >> st;
    v.push_back(st);
  }

  cout << "V antes das insercoes: " << endl;
  cout << v << endl;

  //agora vamos fazer os inserts..
  //cada insert e' composto de uma posicao (inteira) e de uma string
  for(int i=0;i<numInserts;i++) {
    int posInsert;
    cin >> posInsert >> st;
    MyList2<string>::iterator it = v.begin();
    for(int i=0;i<posInsert;i++, it = v.next(it)); //faca it apontar para a posicao "posInsert"
    v.insert(st,it);
    cout << "V apos a insercao de " << st << " na posicao " << posInsert << endl;
    cout << v << endl;
  }
}

void testaCompare() {
int n,numCompares;
  cin >> n >> numCompares;
  MyList2<string> v; //Realiza testes com strings...
  string st;
  for(int i=0;i<n;i++) {
    cin >> st;
    v.push_back(st);
  }

  cout << "V antes das comparacoes: " << endl;
  cout << v << endl;

  //agora vamos fazer os inserts..
  //cada insert e' composto de uma posicao (inteira) e de uma string
  for(int i=0;i<numCompares;i++) {
    int a,b;
    cin >> a >> b;
    MyList2<string>::iterator it1 = v.begin();
    for(int i=0;i<a;i++, it1 = v.next(it1)); //faca it1 apontar para a posicao "a"

    MyList2<string>::iterator it2 = v.begin();
    for(int i=0;i<b;i++, it2 = v.next(it2)); //faca it2 apontar para a posicao "b"

    cout << "Comparando posicoes: " << a << " " << b << " : " << ((v.compare(it1,it2))?"true":"false") << endl;
  }
}

/*
O arquivo de entrada contem um tipo de teste (ou testes com a funcao eraseMatchingElements ou testes com a funcao reverse ou testes mais gerais com a criacao/destruicao de listas)
As listas utilizadas nos testes contem apenas strings. Cada string e' formada apenas por letras e numeros.
A primeira linha do arquivo contem um caractere. Se o caractere for 'E', entao o arquivo representa
testes com a funcao eraseMatchingElements. Se for 'R' significa testes com a funcao reverse. Se for 'C',
entao representa testes com a funcao compare. Se for 'I', representa testes com a funcao insert. Se nao for nenhum
dos anteriores, entao representa testes gerais com push_front, construtores, etc
-----------------
Arquivos de testes gerais:
Sem dados de entrada
-----------------
Arquivos de teste da funcao eraseMatchingElements:
A segunda linha contem dois inteiros o tamanho do vetor inicial e o numero N de chamadas a funcao eraseMatchingElements que serao realizadas
Na terceria linha teremos os elementos do vetor utilizado nos testes
Cada uma das proximas N linhas contem uma string representando o elemento que desejamos remover do vetor
-----------------
Arquivos de teste da funcao reverse:  
A segunda linha contem um numero N representando o numero de elementos a serem inseridos na lista
Na terceira linha ha N strings a serem inseridas na lista (sempre comecamos com uma lista vazia)
-----------------
Arquivos de teste da funcao insert: 
A segunda linha contem dois numeros N e M.
N representa o numero de elementos a serem inseridos na lista inicial
M representa o numero de insercoes posteriores na lista.
A terceira linha contem N strings a serem inseridas na lista inicial
As proximas M linhas contem pares com um inteiro P e uma string S
: P representa a posicao da lista onde S sera inserida (note que a cada nova insercao a lista cresce)
-----------------
Arquivos de teste da funcao compare: 
A segunda linha contem dois numeros N e M.
N representa o numero de elementos a serem inseridos na lista inicial.
M representa o numero de comparacoes a serem feitas.
A terceira linha contem N strings a serem inseridas na lista inicial.
As proximas M linhas contem pares com dois inteiros A e B. O programa devera comparar
um iterador apontando para a posicao A com um iterador apontando para a posicao B (obviamente a saida devera ser
"true" sse A<B)
*/



int main() {
  MyList2<string> v; //Realiza testes com strings...
  char tipoTeste;
  cin >> tipoTeste; 

  if(tipoTeste=='E') { //testes com funcao eraseMatchingElements...
    cout << "Testes com eraseMatchingElements" << endl;
    testaEraseMatchingElements();
  } else if(tipoTeste=='R') { //testes com funcao reverse
    cout << "Testes com reverse" << endl;
    testaReverse();
  } else if(tipoTeste=='I') {
    cout << "Testes com insert" << endl;
    testaInsert();
  } else if(tipoTeste=='C') {
    cout << "Testes com compare" << endl;
    testaCompare();
  } else {
    cout << "Testes gerais" << endl;
    testaPushFront();
    testaConstrutoresEtc();
  }
}

