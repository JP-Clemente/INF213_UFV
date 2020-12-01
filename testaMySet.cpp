#include <iostream>
#include "MySet.h"

using namespace std;

void procura(MySet<int> &s, int elem)
{
	cout << "Procurando " << elem << " : " << (s.find(elem) != s.end()) << endl;
}

void insere(MySet<int> &s, int elem)
{
	cout << "Inserindo " << elem << " : " << (s.insert(elem).second) << endl;
}

int main()
{
	MySet<int> s;
	insere(s, 1);
	insere(s, 2);
	insere(s, 10);
	insere(s, 10); //repetidos..
	insere(s, 10); //repetidos..
	insere(s, 1);

	s.imprimeBFS();
	cout << endl;

	procura(s, 10);
	procura(s, 2);
	procura(s, -1);
	procura(s, 0);
	procura(s, 15);

	MySet<int> s2 = s;
	procura(s2, 10);
	procura(s2, 2);
	procura(s2, -1);
	procura(s2, 0);
	procura(s2, 15);
}

/*
Saida esperada:
Inserindo 1 : 1
Inserindo 2 : 1
Inserindo 10 : 1
Inserindo 10 : 0
Inserindo 10 : 0
Inserindo 1 : 0
1 2 10
Procurando 10 : 1
Procurando 2 : 1
Procurando -1 : 0
Procurando 0 : 0
Procurando 15 : 0
Procurando 10 : 1
Procurando 2 : 1
Procurando -1 : 0
Procurando 0 : 0
Procurando 15 : 0
*/