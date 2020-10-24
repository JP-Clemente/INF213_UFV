#include <iostream>
#include "MyMatrix.h"
using namespace std;




int main() {
	int tams[] = {1,3,0,2};

	//Cria uma matriz de inteiros com numero de colunas em cada linha: 1,3,0,2
	//O primeiro argumento do construtor é o número de linhas da matriz
	//O segundo argumento é um apontador para um array (com tamanho igual ao número de linhas) indicando o número de colunas em cada linha
	//O terceiro argumento deve ser true se a matriz for criada no modo ragged ou false se for criada no modo tradicional
	MyMatrix<int> m(4, tams, false);	

	//Inicializa a matriz com os elementos: [ [1], [2,3,4], [], [5,6] ]
	//getNumRows retorna o número de linhas da matriz (4 nesse caso)
	//getNumCols retorna quantas colunas tem na linha passada como argumento
	//a função "set" armazena, na linha passada como primeiro argumento e coluna passada como segundo, o terceiro argumento da função
	//Neste trabalho, funcoes do tipo "get" e "set" devem ter complexidade maxima O(1). Alem disso, elas nao devem fazer tratamento de erros (ou seja, voce pode supor que o usuario ira sempre se referir a uma posicao valida)
	for(int i=0,ct=1;i<m.getNumRows();i++) {
		for(int j=0;j<m.getNumCols(i);j++,ct++) {
			m.set(i,j,ct); 
		}
	}
	cout << m.get(1,2) << "\n"; //retorna o elemento da linha 1, coluna 2 da matriz (deve ser o numero 4 nesse exemplo...)
	cout << m.getNumElems() << "\n"; //retorna quantos elementos (mesmo se nao inicializados) há na matriz... nesse caso, há 6. Deve ter complexidade máxima O(1)

	//imprime "Rows: rows", onde rows é o numero de linhas da matriz. 
	//Na proxima linha, imprime "Elems: elems", onde elems é o número total de elementos na matriz.
	//A seguir, imprime o conteúdo de cada linha (separado por um espaco em branco os elementos e criando uma nova linha para cada linha). 
	//Antes de cada linha essa funcao tambem deve imprimir o numero de elementos nela, seguido por um ":"
	//Para o exemplo acima, a saída seria: 
	/*
	Rows: 4
	Elems: 6
	1: 1
	3: 2 3 4
	0:
	2: 5 6
	*/
	cout << "Imprimindo a matriz original..." << "\n";
	m.print();
	cout << "IsRagged? " << m.isRagged() << "\n"; //retorna true (1) se a matriz estiver no formato ragged e false (0) caso contrario...
	cout << "\n";

	cout << "Imprimindo a matriz apos converter para ragged..." << "\n";
	m.convertToRagged(); //converte a representacao interna da matriz para o modo "ragged" (caso a matriz esteja no formato tradicional)
	m.print(); //o resultado deve ser o mesmo do print anterior...
	cout << "IsRagged? " << m.isRagged() << "\n"; //retorna true (1) se a matriz estiver no formato ragged e false (0) caso contrario...
	cout << "\n";

	cout << "Imprimindo a matriz apos voltar para o formato tradicional..." << "\n";
	m.convertToTraditional(); //converte a representacao interna da matriz para o modo "tradicional" (caso a matriz esteja no formato ragged)
	m.print(); //o resultado deve ser o mesmo do print anterior...
	cout << "IsRagged? " << m.isRagged() << "\n"; //retorna true (1) se a matriz estiver no formato ragged e false (0) caso contrario...
	cout << "\n";

	m.resizeRow(1,5); //altera o numero de colunas na linha (primeiro argumento) para o valor do segundo argumento. Caso o número de colunas aumente, os novos elementos sao 
					  //preenchidos com o valor padrao do tipo (Ex: 0 para int, "\0" para char, ""  para string, etc)
					  //Assim como as outras, essa funcao deve funcionar nos dois modos (na sua implementacao voce nao deve mudar o modo para fazer resize...)
	
	cout << "Imprimindo a matriz apos mudar o tamanho da linha 1 para 5 colunas..." << "\n";
	m.print();
	cout << "\n";
	m.set(1,4,9); //altera o valor do elemento na linha 1, coluna 4 para 9

	cout << "Imprimindo a matriz apos mudaro valor do elemento (1,4) para 9..." << "\n";
	m.print();
	cout << "\n";

	m.resizeNumRows(7); //altera o numero de linhas da matriz para 7 (as novas linhas sao criadas inicialmente com 0 elementos)

	cout << "Imprimindo a matriz apos mudar o numero de linhas para 7" << "\n";
	m.print();
	cout << "\n";

	cout << "Imprimindo a matriz apos mudar o numero de linhas para 2" << "\n";
	m.resizeNumRows(2); //altera o numero de linhas para 2 (5 linhas serão apagadas)
	m.print();

}