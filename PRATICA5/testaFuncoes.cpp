#include <iostream>

#include "MyVec.h"

using namespace std;

/*
O arquivo de entrada contem um tipo de teste (ou testes com a funcao eraseMatchingElements ou testes com a funcao sortedInsert)

Os vetores utilizados nos testes contem apenas strings. Cada string e' formada apenas por letras e numeros.

A primeira linha do arquivo contem um caractere. Se o caractere for 'E', entao o arquivo representa
testes com a funcao eraseMatchingElements, caso contrario testes com a funcao sortedInsert

-----------------
Arquivos de teste da funcao eraseMatchingElements:
A segunda linha contem dois inteiros o tamanho do vetor inicial e o numero N de chamadas a funcao eraseMatchingElements que serao realizadas
Na terceria linha teremos os elementos do vetor utilizado nos testes
Cada uma das proximas N linhas contem uma string representando o elemento que desejamos remover do vetor
-----------------
Arquivos de teste da funcao sortedInsert:	
A segunda linha contem um numero N representando o numero de insercoes a serem realizadas
Cada uma das proximas N linhas contem uma string a ser inserida no vetor (sempre comecamos com um vetor vazio)

*/

void printVector(MyVec<string> &v) {
	cout << "(Size: " << v.size() << ") : ";
	for(int i=0;i<v.size();i++) cout << v[i] << " ";
	cout << endl;
}

int main() {
	MyVec<string> v; //Realiza testes com strings...
	char tipoTeste;
	cin >> tipoTeste; 

	if(tipoTeste=='E') { //testes com funcao eraseMatchingElements...
		int size, calls;
		cin >> size >> calls;
		v.resize(size);
		for(int i=0;i<size;i++) cin >> v[i]; // le os "size" elementos do vetor...

		printVector(v);	
		for(int i=0;i<calls;i++) {
			string elemRemover;
			cin >> elemRemover;
			cout << "Removendo: " << elemRemover << endl;
			int numRemoved = v.eraseMatchingElements(elemRemover);
			cout << "Numero de elementos removidos: " << numRemoved << endl;
			cout << "Novo vetor: ";
			printVector(v);
			cout << endl;
		}
	} else { //testes com funcao sortedInsert
		int size;
		cin >> size;
		for(int i=0;i<size;i++) {
			string st;
			cin >> st;
			v.sortedInsert(st);
			cout << "Inserindo: " << st << endl;
			cout << "Novo vetor: ";
			printVector(v);
		}
	}
}