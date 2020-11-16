/*
TAD MyList2
- Representa uma lista implementada por encadeamento simples
- Criado por Salles Magalhaes em 19/02/2018

*/

#ifndef MyList2_H__
#define MyList2_H__

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
	Node(const T &elem) : data(elem), next(NULL), prev(NULL) {}
	T data;
	Node<T> *next;
	Node<T> *prev;
};

template <class T>
class MyList2Iterator; //precisamos declarar essa classe antes da MyList2 para que o typedef abaixo nao de erro
					   //por outro lado, so podemos implementar o iterador apos a classe MyList2 (visto que precisaremos acessar
					   //dados da classe)

template <class T>
class MyList2
{
public:
	//decidimos utilizar o typedef com o objetivo de "abstrair" o conceito de iterador (a utilidade disso sera vista posteriormente)
	typedef MyList2Iterator<T> iterator; //define um iterador, um tipo utilizado para percorrer uma estrutura de dados e "apontar" para os items armazenados nela

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

	iterator begin() { return iterator(dataFirst); } //Exercicio: e se tivermos uma lista constante, como itera-la para, por exemplo, imprimir os elementos?
	iterator end() { return iterator(NULL); }		 //retorna um apontador para um nodo que estaria APOS o final da lista

	//por simplicidade, nao vamos criar iteradores constantes...

	void clear();

	//Exercicio: implementar as duas funcoes abaixo supondo que nao ha um membro de dados dataSize (o calculo do tamanho da lista seria dinamico)
	void empty() const { return size() == 0; };
	int size() const { return dataSize; }; // na STL List, a funcao size() calcula o tamanho da lista dinamicamente (exercicio: qual a ordem de complexidade?)

private:
	Node<T> *dataFirst, *dataLast;
	int dataSize; //quantos elementos ha na lista?

	void create();
	void destroy();
	void destroy(Node<T> *it);
};

template <class T>
class MyList2Iterator
{
	friend class MyList2<T>;

public:
	MyList2Iterator(Node<T> *ptr_) : ptr(ptr_) {}
	T &operator*() { return ptr->data; }
	const T &operator*() const { return ptr->data; } //versao constante do operador de derreferencia

	bool operator==(const MyList2Iterator &other) const { return ptr == other.ptr; }
	bool operator!=(const MyList2Iterator &other) const { return ptr != other.ptr; }

	//exercicio: faz sentido ter operatores <, > , <=, etc?
	//           faz sentido termos operadores +, =+ (para "pularmos" n elementos em vez de
	//                                                avancarmos de um em um) , etc?

	//exercicio: armazenamos um ponteiro nesta classe. Deveriamos ter destrutor, constr. de copia, etc?

	//pre incremento/decremento
	MyList2Iterator<T> operator++();
	MyList2Iterator<T> operator--();

	//pos incremento/decremento
	//o argumento (int) eh uma convencao do C++ usada para diferenciar a implementacao
	// do operador de pos e pre incremento
	MyList2Iterator<T> operator++(int);
	MyList2Iterator<T> operator--(int);

private:
	Node<T> *ptr;
};

//pre incremento/decremento
template <class T>
MyList2Iterator<T> MyList2Iterator<T>::operator++()
{
	ptr = ptr->next;
	return *this;
}

template <class T>
MyList2Iterator<T> MyList2Iterator<T>::operator--()
{
	ptr = ptr->prev;

	return *this;
}

//pos incremento/decremento
//o argumento (int) eh uma convencao do C++ usada para diferenciar a implementacao
// do operador de pos e pre incremento
template <class T>
MyList2Iterator<T> MyList2Iterator<T>::operator++(int)
{
	MyList2Iterator<T> oldIt = *this;
	ptr = ptr->next;
	return oldIt;
}

template <class T>
MyList2Iterator<T> MyList2Iterator<T>::operator--(int)
{
	MyList2Iterator<T> oldIt = *this;
	ptr = ptr->prev;

	return oldIt;
}

//funcao auxiliar (nao membro)
//Dado um apontador first para o primeiro nodo de uma lista encadeada, deleta todos os nodos apos
//first (incluindo first)
template <class T>
void MyList2<T>::destroy(Node<T> *first)
{
	if (first == NULL)
		return;
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

	if (other.dataFirst == NULL)
	{
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
	if (dataFirst == NULL)
	{ //caso especial: lista inicialmente vazia
		dataFirst = dataLast = new Node<T>(elem);
	}
	else
	{
		iterator newNode = new Node<T>(elem);
		newNode->next = dataFirst;
		dataFirst->prev = newNode;
		dataFirst = newNode;
	}
	dataSize++;
}

//insere o elemento na posicao NA posicao nodeBefore
//diferentemente da lista simplesmente encadeada, isso pode ser feito de forma
//eficiente na lista duplamente encadeada
template <class T>
void MyList2<T>::insert(const T &elem, iterator whereIt)
{
	Node<T> *where = whereIt.ptr;
	if (whereIt == end())
	{ //caso especial: insercao no final da lista...
		push_back(elem);
	}
	else if (whereIt == begin())
	{ //caso especial: insercao no inicio da lista
		Node<T> *newNode = new Node<T>(elem);
		newNode->next = dataFirst;
		dataFirst->prev = newNode;
		dataFirst = newNode;
		dataSize++;
	}
	else
	{ //insercao no meio da lista...
		Node<T> *newNode = new Node<T>(elem);
		where->prev->next = newNode;
		newNode->prev = where->prev;
		newNode->next = where;
		where->prev = newNode;
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
typename MyList2<T>::iterator MyList2<T>::erase(iterator elemIt)
{	//remove o elemento apontado por Elem
	//retorna o (apontador) para o elemento apos o removido
	Node<T> *elem = elemIt.ptr;
	dataSize--;
	if (elem == dataFirst && elem == dataLast)
	{ //exercicio: por que precisamos desse caso especial?
		//so ha um elemento na lista
		delete elem;
		dataFirst = dataLast = NULL;
		return begin();
	}
	else if (elem == dataFirst)
	{
		dataFirst = dataFirst->next;
		dataFirst->prev = NULL;
		delete elem;
		return begin();
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

		return iterator(beforeElem->next);
	}
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

	return out;
}

#endif