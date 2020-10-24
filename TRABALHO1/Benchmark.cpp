#include <iostream>
#include <chrono>
#include <iomanip>
#include "MyMatrix.h"
using namespace std;



template<class T>
T somaElems(const MyMatrix<T> &m) {
	T ans = T();
	int nr = m.getNumRows();
	for(int i=0;i<nr;i++) {
		int nc = m.getNumCols(i);
		for(int j=0;j<nc;j++) ans += m.get(i,j);
	}
	return ans;
}


void realizaExperimentosMatriz(int nrows,int *tams, bool ragged) {
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	int soma;
	std::chrono::duration<double> tempo;

	{
		start = std::chrono::high_resolution_clock::now();
		MyMatrix<int> m(nrows, tams,ragged);
		end = std::chrono::high_resolution_clock::now();
		tempo = end-start;
		cout << "Tempo para criar matriz      : " << std::fixed << setprecision(6) << tempo.count() << endl;

		start = std::chrono::high_resolution_clock::now();
		int nr = m.getNumRows();
		for(int i=0;i<nr;i++) {
			int nc = m.getNumCols(i);
			for(int j=0;j<nc;j++) {
				m.set(i,j,1); //vamos inicializar a matriz apenas com 1...
			}
		}
		end = std::chrono::high_resolution_clock::now();
		tempo = end-start;
		cout << "Tempo para inicializar matriz: " <<  std::fixed << setprecision(6) << tempo.count() << endl;

		
		start = std::chrono::high_resolution_clock::now();
		soma = somaElems(m);
		end = std::chrono::high_resolution_clock::now();
		tempo = end-start;
		cout << "Tempo para somar matriz      : " <<  std::fixed << setprecision(6) << tempo.count() << endl;


		start = std::chrono::high_resolution_clock::now();
		m.resizeRow(0,m.getNumCols(0)*2);
		end = std::chrono::high_resolution_clock::now();
		tempo = end-start;
		cout << "Tempo para dobrar o numero de colunas na primeira linha      : " <<  std::fixed << setprecision(6) << tempo.count() << endl;				

		start = std::chrono::high_resolution_clock::now();
	} //como estamos terminando um bloco, a matriz (automatica) sera deletada automaticamente aqui...
	end = std::chrono::high_resolution_clock::now();
	tempo = end-start;
	cout << "Tempo para deletar matriz    : " <<  std::fixed << setprecision(6) << tempo.count() << endl;

	cout << "Soma: " << soma <<  endl; //imprime as somas (lixo) -- e' bom fazer isso, caso contrario o compilador pode achar a chamada da funcao soma inutil e remove-la do codigo!
}

int main(int argc, char **argv) {
	if(argc!=3) {
		cerr << "Erro... os argumentos deste programa sao: o numero de linhas da matriz e o maximo de colunas por linha" << endl;
		return 1;
	}
	int nrows = atoi(argv[1]);
	int mxColsPerRow = atoi(argv[2]);

	int *tams = new int[nrows];
	for(int i=0;i<nrows;i++) tams[i] = rand()%(mxColsPerRow+1);//sorteia um numero entre 0 e mxColsPerRow (a semente do rand eh sempre a mesma) para o numero de colunas nas linhas da matriz

	cout << "Experimentos com matriz tradicional: " << endl;
	realizaExperimentosMatriz(nrows, tams,false);
	cout << "\nExperimentos com matriz no formato ragged: " << endl;
	realizaExperimentosMatriz(nrows, tams,true);
	delete []tams;
}

 