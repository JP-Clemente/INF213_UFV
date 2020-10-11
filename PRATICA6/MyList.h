/*
TAD MyList
- Representa uma lista implementada por encadeamento simples
- Criado por Salles Magalhaes em 19/02/2018
*/

#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <string>
#include <ostream>

//Excessao usada pela classe MyList
class MyListException
{
private:
	std::string msg;

public:
	MyListException(const std::string &msg0) : msg(msg0) {}
	const std::string &what() const { return msg; }
};

template <class T>
class Node;

template <class T>
class Node
{ //a classe Node sera "escondida" quando trabalharmos com iteradores
public:
	Node(const T &elem) : data(elem), next(NULL) {}
	T data;
	Node<T> *next;
};

template <class T>
class MyList
{
public:
	//decidimos utilizar o typedef com o objetivo de "abstrair" o conceito de iterador (a utilidade disso sera vista posteriormente)
	typedef Node<T> *iterator; //define um iterador, um tipo utilizado para percorrer uma estrutura de dados e "apontar" para os items armazenados nela

	template <class T2>
	friend std::ostream &operator<<(std::ostream &, const MyList<T2> &);

	//construtores/destrutures/etc
	MyList();
	MyList(int n, const T &init = T());

	//destrutor
	~MyList() { destroy(); };

	//Construtor de copia
	MyList(const MyList &);
	MyList &operator=(const MyList &);

	//funcoes de acesso
	void push_back(const T &);
	void push_front(const T &);
	void insert(const T &, iterator nodeBefore); //insere o primeiro argumento APOS o nodo apontado pelo segundo elemento
												 //isso sera melhorado no futuro (quando estudarmos iteradores)
	iterator erase(iterator elem);				 //remove o elemento apontado por Elem
												 //retorna o (apontador) para o elemento apos o removido

	iterator begin() { return dataFirst; } //Exercicio: e se tivermos uma lista constante, como itera-la para, por exemplo, imprimir os elementos?
	iterator end() { return NULL; }		   //retorna um apontador para um nodo que estaria APOS o final da lista
	iterator next(iterator curr);
	T &deref(iterator curr); //Retorna o elemento da lista apontado por curr (faz uma "derreferencia")

	//versoes constantes dos 4 metodos acima
	const iterator begin() const { return dataFirst; } //Exercicio: e se tivermos uma lista constante, como itera-la para, por exemplo, imprimir os elementos?
	const iterator end() const { return NULL; }		   //retorna um apontador para um nodo que estaria APOS o final da lista
	const iterator next(const Node<T> *curr) const;
	const T &deref(const iterator curr) const; //Retorna o elemento da lista apontado por curr

	void clear();

	//Exercicio: implementar as duas funcoes abaixo supondo que nao ha um membro de dados dataSize (o calculo do tamanho da lista seria dinamico)
	void empty() const { return size() == 0; };
	int size() const { return dataSize; }; // na STL List, a funcao size() calcula o tamanho da lista dinamicamente (exercicio: qual a ordem de complexidade?)

	int eraseMatchingElements(const T);
	void reverse();
	void reverse(Node<T> *, Node<T> *);

private:
	Node<T> *dataFirst, *dataLast;
	int dataSize; //quantos elementos ha na lista?

	void create();
	void destroy();
	//void recursiveDestroy(Node<T> *);
};

/*template<class T>
void MyList<T>::recursiveDestroy(Node<T> *ptr){
	if(ptr == NULL)	return;
	recursiveDestroy(ptr->next);
	delete ptr;
}*/

template <class T>
void MyList<T>::destroy()
{
	if (dataFirst == NULL)
		return;

	Node<T> *temp = dataFirst;
	dataFirst = dataFirst->next;
	delete temp;

	destroy();
}


template <class T>
void MyList<T>::create()
{
	dataSize = 0;
	dataFirst = dataLast = NULL;
}

template <class T>
MyList<T>::MyList()
{
	create();
}

template <class T>
MyList<T>::MyList(int n, const T &init)
{
	create();
	for (int i = 0; i < n; i++)
		push_back(init); //implementacao pode ser mais eficiente se evitar atualizar o apontador "dataLast" em cada iteracao
}

//Construtor de copia
template <class T>
MyList<T>::MyList(const MyList &other)
{
	create(); //Crie um vetor vazio
	*this = other;
}

template <class T>
MyList<T> &MyList<T>::operator=(const MyList &other)
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
void MyList<T>::push_back(const T &elem)
{
	if (dataFirst == NULL)
	{ //caso especial: lista inicialmente vazia
		dataFirst = dataLast = new Node<T>(elem);
	}
	else
	{
		dataLast->next = new Node<T>(elem);
		dataLast = dataLast->next;
	}
	dataSize++;
}

template <class T>
void MyList<T>::push_front(const T &elem)
{
	//Termine esta funcao
	if (dataFirst == NULL)
	{ //caso especial: lista inicialmente vazia
		dataFirst = dataLast = new Node<T>(elem);
	}
	else
	{
		Node<T> *temp = dataFirst;
		dataFirst = new Node<T>(elem);
		dataFirst->next = temp;
	}
	dataSize++;
}

//insere o elemento na posicao APOS a posicao nodeBefore
template <class T>
void MyList<T>::insert(const T &elem, iterator nodeBefore)
{
	if (nodeBefore == NULL)
	{
		throw MyListException("Erro, insercao em posicao invalida da lista");
	}

	iterator newNode = new Node<T>(elem);
	newNode->next = nodeBefore->next;
	nodeBefore->next = newNode;

	if (nodeBefore == dataLast)
	{ //caso especial
		dataLast = newNode;
	}
	dataSize++;
}

template <class T>
void MyList<T>::clear()
{
	destroy();
	create();
}

//assumimos que elem seja um ponteiro valido para um nodo da lista
template <class T>
typename MyList<T>::iterator MyList<T>::erase(iterator elem)
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
		delete elem;
		return dataFirst;
	}
	else
	{
		//o elemento a ser removido nao e' o primeiro.
		Node<T> *beforeElem = dataFirst;
		Node<T> *curr = dataFirst->next;

		while (curr != elem)
		{
			beforeElem = curr;
			curr = curr->next;
		}

		//agora curr aponta para elem e beforeElem aponta para um elemento antes de curr
		beforeElem->next = curr->next;
		delete curr;
		if (curr == dataLast)
		{
			dataLast = beforeElem;
		}
		return beforeElem->next;
	}
}

template <class T>
typename MyList<T>::iterator MyList<T>::next(iterator curr)
{
	return curr->next;
}

template <class T>
T &MyList<T>::deref(iterator curr)
{ //Retorna o elemento da lista apontado por curr (faz uma "derreferencia")
	return curr->data;
}

template <class T>
const typename MyList<T>::iterator MyList<T>::next(const Node<T> *curr) const
{
	return curr->next;
}

template <class T>
const T &MyList<T>::deref(const iterator curr) const
{ //Retorna o elemento da lista apontado por curr (faz uma "derreferencia")
	return curr->data;
}

template <class T2>
std::ostream &operator<<(std::ostream &out, const MyList<T2> &v)
{
	out << "Size: " << v.size() << "\n";
	/* //usando iteradores para abstrairem a iteracao
	MyList<T2>::iterator it = v.begin();
	while(it!=v.end()) {
		 out << v.deref(it) << " ";
		 it = v.next(it);
	}
	*/
	Node<T2> *curr = v.dataFirst; //versao utilizando ponteiros...
	while (curr != NULL)
	{ // equivalente a while(curr)
		out << curr->data << " ";
		curr = curr->next;
	}

	out << "\n";

	return out;
}

template <class T>
int MyList<T>::eraseMatchingElements(const T elem)
{
	int removed = 0;
	Node<T> *temp = dataFirst;
	while (temp != NULL)
	{
		if (temp->data == elem)
		{
			temp = erase(temp);
			removed++;
		}
		else
			temp = temp->next;
	}
	return removed;
}

template <class T>
void MyList<T>::reverse()
{
	reverse(dataFirst, NULL);

	Node<T> *temp = dataFirst;
	dataFirst = dataLast;
	dataLast = temp;
}
template <class T>
void MyList<T>::reverse(Node<T> *curr, Node<T> *before)
{
	if (curr->next != NULL)
		reverse(curr->next, curr);
	curr->next = before;
}

#endif