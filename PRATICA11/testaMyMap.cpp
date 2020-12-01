#include <iostream> //classe pair esta aqui...
#include "MyMap.h"
using namespace std;

int main()
{
	MyMap<string, int> m;

	m["abc"] = 8;
	m["salles"] = 52700;
	cout << "Tamanho do map: " << m.size() << endl;
	cout << m["abc"] << endl;
	cout << m["salles"] << endl;

	m["abc"] = 0;
	cout << "Tamanho do map: " << m.size() << endl;
	cout << m["abc"] << endl;
	cout << m["salles"] << endl;

	//mapas podem ser usados ate para mapear inteiros em algum outro tipo.
	//exemplo: um mapa de inteiro para strings
	//Note que isso funciona de forma basicamente similar a um array de strings!
	//Quais as vantagens e desvantagens de usar um mapa como um array?
	//Vantagem: armazena apenas o que e' necessario. Por exemplo, em um sistema de matricula teriamos apenas uma entrada para cada matricula
	//se tivessemos usado um array ou vetor dinamico de strings para o exemplo abaixo --> precisariamos de um array com tamanho pelo menos 100001
	//Outra vantegem: e' dinamico (--> facilidade de implementacao). Toda alocacao e' feita de forma simples e transparente
	//Desvantagens:
	//- Se nao fossem essas desvatanges, arrays nao seriam necessarios (seria melhor usar mapas sempre!)
	//- Desvantagem 1: ha overhead no armazenamento (cada elemento e' armazenado em um nodo que precisa de pelo menos 3 ponteiros extras...)
	//- Desvantagem 2: ha um custo de O(log n) (supondo que a arvore esteja balanceada -- o que pode ser resolvido usando uma ABP balanceada, algo que sera estudado em breve) enquanto
	//um array teria tempo de acesso O(1)
	//Logo, mapas sao melhores quando os dados estao "esparsos" ou quando a chave e' algum tipo diferente do tipo int
	MyMap<int, string> nomeAluno;

	nomeAluno[52700] = "Salles";
	nomeAluno[100000] = "Ligia";

	cout << "Aluno com matricula 52700: " << nomeAluno[52700] << endl;
}