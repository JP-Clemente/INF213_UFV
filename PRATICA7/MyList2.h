/*
TAD MyList2
- Representa uma lista implementada por encadeamento simples
- Criado por Salles Magalhaes em 19/02/2018
*/

#ifndef MYLIST2_H
#define MYLIST2_H

#include <iostream>
#include <string>
#include <ostream>

//Excessao usada pela classe MyList2
class MyList2Exception
{
private:
	std::string msg;

public:
	MyList2Exception(const std::string &msg0) : msg(msg0) {}
	const std::string &what() const { return msg; }
};

template <class T>
class Node;

template <class T>
class Node
{ //a classe Node sera "escondida" quando trabalharmos com iteradores
public:
	Node(const T &elem) : data(elem), next(NULL), prev(NULL) {} // forma de inicialização dos dados
	T data;
	Node<T> *next; //aponta para o próximo nodo
	Node<T> *prev; //aponta para o nodo anterior
};

template <class T>
class MyList2
{
public:
	//decidimos utilizar o typedef com o objetivo de "abstrair" o conceito de iterador (a utilidade disso sera vista posteriormente)
	typedef Node<T> *iterator; //define um iterador, um tipo utilizado para percorrer uma estrutura de dados e "apontar" para os items armazenados nela

	template <class T2>
	friend std::ostream &operator<<(std::ostream &, const MyList2<T2> &);

	//construtores/destrutures/etc
	MyList2();
	MyList2(int n, const T &init = T());

	//destrutor
	~MyList2() { destroy(); };

	//Construtor de copia
	MyList2(const MyList2 &);
	MyList2 &operator=(const MyList2 &);

	//funcoes de acesso
	void push_back(const T &);
	void push_front(const T &);
	void insert(const T &, iterator where); //insere o primeiro argumento NA POSICAO apontada pelo segundo elemento
											//os outros elementos sao deslocados
											//diferentemente da lista simplesmente encadeada, aqui podemos inserir um elemento na posicao
											// "where" de forma eficiente!
	iterator erase(iterator elem);			//remove o elemento apontado por Elem
											//retorna o (apontador) para o elemento apos o removido

	int eraseMatchingElements(const T &elem);

	iterator begin() { return dataFirst; } //Exercicio: e se tivermos uma lista constante, como itera-la para, por exemplo, imprimir os elementos?
	iterator end() { return NULL; }		   //retorna um apontador para um nodo que estaria APOS o final da lista
	iterator next(iterator curr);
	iterator prev(iterator curr);
	T &deref(iterator curr); //Retorna o elemento da lista apontado por curr (faz uma "derreferencia")

	//versoes constantes dos 4 metodos acima
	const iterator begin() const { return dataFirst; } //Exercicio: e se tivermos uma lista constante, como itera-la para, por exemplo, imprimir os elementos?
	const iterator end() const { return NULL; }		   //retorna um apontador para um nodo que estaria APOS o final da lista
	const iterator next(const iterator curr) const;
	const iterator prev(const iterator curr) const;
	const T &deref(const iterator curr) const; //Retorna o elemento da lista apontado por curr

	void clear();

	//Exercicio: implementar as duas funcoes abaixo supondo que nao ha um membro de dados dataSize (o calculo do tamanho da lista seria dinamico)
	void empty() const { return size() == 0; };
	//int size() const {return dataSize;}; // na STL List, a funcao size() calcula o tamanho da lista dinamicamente (exercicio: qual a ordem de complexidade?)
	int size() const;

	void reverse();
	bool compare(Node<T> *, Node<T> *);

private:
	Node<T> *dataFirst, *dataLast;
	int dataSize; //quantos elementos ha na lista?

	void create();
	void destroy();
	void destroy(iterator it);
	int size(iterator curr) const;
	void reverse(Node<T> *, Node<T> *);
};

//funcao auxiliar (nao membro)
//Dado um apontador first para o primeiro nodo de uma lista encadeada, deleta todos os nodos apos
//first (incluindo first)
template <class T>
void MyList2<T>::destroy(MyList2<T>::iterator first)
{
	if (first == NULL)
		return; //lista vazia
	destroy(first->next);
	delete first;
}

template <class T>
void MyList2<T>::destroy()
{ // Lab...
	dataSize = 0;
	destroy(dataFirst);
}

template <class T>
void MyList2<T>::create()
{
	dataFirst = dataLast = NULL;
	dataSize = 0;
}

template <class T>
MyList2<T>::MyList2()
{
	create();
}

template <class T>
MyList2<T>::MyList2(int n, const T &init)
{
	create();
	for (int i = 0; i < n; i++)
		push_back(init); //implementacao pode ser mais eficiente se evitar atualizar o apontador "dataLast" em cada iteracao
}

//Construtor de copia
template <class T>
MyList2<T>::MyList2(const MyList2 &other)
{
	create(); //Crie um vetor vazio
	*this = other;
}

template <class T>
MyList2<T> &MyList2<T>::operator=(const MyList2 &other)
{
	if (this == &other)
		return *this;
	clear(); //Exercicio: por que precisamos disso?
	// Para que os valores antigos da lista sejam removidos corretamente e assim preparar da forma certa a nova atribuição

	if (other.dataFirst == NULL)
	{ // caso especial
		dataFirst = dataLast = NULL;
	}
	else
	{
		Node<T> *curr = other.dataFirst;
		while (curr != NULL)
		{ //equivalente a "while(curr)"
			push_back(curr->data);
			curr = curr->next; //avance para o proximo nodo
		}
	}
	return *this;
}

// ---------- Função Size Recursiva ------------ //
template <class T>
int MyList2<T>::size() const
{
	iterator curr = dataLast;
	return size(curr);
}

template <class T>
int MyList2<T>::size(iterator curr) const
{
	if (curr == NULL)
		return 0;
	else
		return size(curr->prev) + 1;
}
// -------------- //

// ---------- Função Reverse Recursiva ------------ //

template <class T>
void MyList2<T>::reverse()
{
	int cont = 0;
	Node<T> *aux;
	Node<T> *ptr = dataFirst;
	reverse(dataFirst, aux);
	dataFirst = dataLast;
	dataLast = ptr;
}

template <class T>
void MyList2<T>::reverse(Node<T> *rev, Node<T> *aux)
{
	if (size() == 0)
	{
		return;
	}
	else if (rev->next == end())
	{
		aux = rev->prev;
		rev->prev = rev->next;
		rev->next = aux;
		return;
	}
	else
	{
		reverse(rev->next, aux);
		aux = rev->prev;
		rev->prev = rev->next;
		rev->next = aux;
	}
}
// -------------- //

// ---------- Função Compare ------------ //

template <class T>
bool MyList2<T>::compare(Node<T> *it1, Node<T> *it2)
{
	if (it1 == it2)
		return false;
	if (it1->next == it2)
		return true;
	if (it1->next == NULL)
		return false;
	return compare(it1->next, it2);
}

// -------------- //

//---------------------------------------------------------------------------------------
//Funcoes de acesso

template <class T>
void MyList2<T>::push_back(const T &elem)
{
	if (dataFirst == NULL)
	{ //caso especial: lista inicialmente vazia
		dataFirst = dataLast = new Node<T>(elem);
	}
	else
	{
		dataLast->next = new Node<T>(elem);
		dataLast->next->prev = dataLast;
		dataLast = dataLast->next;
	}
	dataSize++;
}

template <class T>
void MyList2<T>::push_front(const T &elem)
{
	//para inserir um novo elemento é preciso:
	//criar um novo nodo, saber para onde ele aponta(dataFirst->next), colocar o elem, renovar o dataFirst
	if (dataFirst == NULL)
	{ // caso especial: lista vazia
		dataLast = dataFirst = new Node<T>(elem);
	}
	else
	{
		dataFirst->prev = new Node<T>(elem);
		dataFirst->prev->next = dataFirst;
		dataFirst = dataFirst->prev;
	}
	dataSize++;
}

//insere o elemento na posicao NA posicao nodeBefore
//diferentemente da lista simplesmente encadeada, isso pode ser feito de forma
//eficiente na lista duplamente encadeada
template <class T>
void MyList2<T>::insert(const T &elem, iterator where)
{
	Node<T> *nodeBefore = where;
	if (nodeBefore == begin())
	{
		push_front(elem);
	}
	else if (nodeBefore == end())
	{
		push_back(elem);
	}
	else
	{
		Node<T> *newNode = new Node<T>(elem);
		nodeBefore->prev->next = newNode;
		newNode->prev = nodeBefore->prev;
		newNode->next = nodeBefore;
		nodeBefore->prev = newNode;
		dataSize++;
	}
}

template <class T>
void MyList2<T>::clear()
{
	destroy();
	create();
}

//assumimos que elem seja um ponteiro valido para um nodo da lista
template <class T>
typename MyList2<T>::iterator MyList2<T>::erase(iterator elem)
{	//remove o elemento apontado por Elem
	//retorna o (apontador) para o elemento apos o removido

	dataSize--;
	if (elem == dataFirst && elem == dataLast)
	{ //exercicio: por que precisamos desse caso especial?
		//so ha um elemento na lista
		delete elem;
		dataFirst = dataLast = NULL;
		return NULL;
	}
	else if (elem == dataFirst)
	{
		dataFirst = dataFirst->next;
		dataFirst->prev = NULL;
		delete elem;
		return dataFirst;
	}
	else
	{
		//o elemento a ser removido nao e' o primeiro.
		Node<T> *beforeElem = elem->prev;

		beforeElem->next = elem->next;
		if (elem == dataLast)
		{ //caso especial... eh o ultimo elemento
			dataLast = beforeElem;
		}
		else
			elem->next->prev = beforeElem;

		delete elem;

		return beforeElem->next;
	}
}

// --------------- Função EraseMatching Elements --------------- //

template <class T>
int MyList2<T>::eraseMatchingElements(const T &elem)
{
	iterator val = begin();
	int cont = 0;
	while (val != end())
	{
		if (elem == val->data)
		{
			val = erase(val);
			cont++;
		}
		else
			val = val->next;
	}
	delete val;
	return cont;
}

// ---------------- //

template <class T>
typename MyList2<T>::iterator MyList2<T>::next(iterator curr)
{
	return curr->next;
}

template <class T>
typename MyList2<T>::iterator MyList2<T>::prev(iterator curr)
{
	return curr->prev;
}

template <class T>
T &MyList2<T>::deref(iterator curr)
{ //Retorna o elemento da lista apontado por curr (faz uma "derreferencia")
	return curr->data;
}

template <class T>
const typename MyList2<T>::iterator MyList2<T>::next(const iterator curr) const
{
	return curr->next;
}

template <class T>
const typename MyList2<T>::iterator MyList2<T>::prev(const iterator curr) const
{
	return curr->prev;
}

template <class T>
const T &MyList2<T>::deref(const iterator curr) const
{ //Retorna o elemento da lista apontado por curr (faz uma "derreferencia")
	return curr->data;
}

template <class T2>
std::ostream &operator<<(std::ostream &out, const MyList2<T2> &v)
{
	out << "Size: " << v.size() << "\n";
	/* //usando iteradores para abstrairem a iteracao
	MyList2<T2>::iterator it = v.begin();
	while(it!=v.end()) {
		 out << v.deref(it) << " ";
		 it = v.next(it);
	}
	*/
	Node<T2> *curr = v.dataFirst;
	while (curr != NULL)
	{ // equivalente a while(curr)
		out << curr->data << " ";
		curr = curr->next;
	}

	out << "\n";

	out << "Ordem reversa (testando ponteiros prev...)"
		<< "\n";
	curr = v.dataLast;
	while (curr != NULL)
	{ // equivalente a while(curr)
		out << curr->data << " ";
		curr = curr->prev;
	}

	out << "\n";

	return out;
}

#endif