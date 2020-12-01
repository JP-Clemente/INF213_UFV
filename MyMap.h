#ifndef MY_MAP_H
#define MY_MAP_H

#include <algorithm> //classe pair esta aqui...
using namespace std;

template <class K, class V>
class MyMapIterator;

template <class K, class V>
class Node
{
public: //classe auxiliar.. vamos utiliza-la apenas neste arquivo (nao e' muito necessario ter encapsulamento)
	Node(const K &key_, const V &value_) : keyValue(key_, value_), left(NULL), right(NULL) {}
	Node<K, V> *left, *right;
	pair<K, V> keyValue;
	Node<K, V> *parent; //agora cada nodo armazena seu pai
};

template <class K, class V>
class MyMap
{
public:
	typedef MyMapIterator<K, V> iterator;

	int size() const;
	MyMap() : size_(0), root(NULL) {}

	//note que o insert espera como argumento
	pair<iterator, bool> insert(const pair<K, V> &keyAndValue); //retorna um iterador para o elemento inserido (o valor booleano sera' true se o elemento nao existia no conjunto e falso caso ele ja exista (ou seja, o novo elemento nao foi inserido) ).
	iterator find(const K &key);								//por simplicidade, nao vamos implementar um find constante...
	int count(const K &key) const;								//quantos elementos com a chave key ha no map? (retornos validos sao apenas 0 ou 1)
	V &operator[](const K &key);								//retorna uma referencia para o valor associado a chave key. Se o valor ainda nao estiver no mapa --> cria um novo usando o construtor padrao.

	iterator end() { return iterator(NULL); };
	iterator begin();

	MyMap(const MyMap &other);
	MyMap &operator=(const MyMap &other);
	~MyMap();

private:
	Node<K, V> *root;
	int size_;

	//funcoes auxiliares...
	pair<iterator, bool> insert(const pair<K, V> &keyAndValue, Node<K, V> *&root, Node<K, V> *parent);
	iterator find(const K &key, Node<K, V> *root);

	int count(const K &key, const Node<K, V> *root) const;

	void deleteNodes(Node<K, V> *root);
	Node<K, V> *copyNodes(const Node<K, V> *root, Node<K, V> *parent) const;
};

//por enquanto vamos desconsiderar os operadores ++ e -- em conjuntos...
//tais operadores serao "escondidos"
template <class K, class V>
class MyMapIterator
{
	friend class MyMap<K, V>;

public:
	MyMapIterator(Node<K, V> *ptr_) : ptr(ptr_) {}
	pair<K, V> &operator*() { return ptr->keyValue; }

	bool operator==(const MyMapIterator &other) const { return ptr == other.ptr; }
	bool operator!=(const MyMapIterator &other) const { return ptr != other.ptr; }

	MyMapIterator operator++();
	MyMapIterator operator++(int);

	MyMapIterator operator--();
	MyMapIterator operator--(int);

private:
	Node<K, V> *ptr;
};

//operador de pre-incremento
template <class K, class V>
MyMapIterator<K, V> MyMapIterator<K, V>::operator++()
{
	if (ptr->right)
	{ //pegue o menor elemento da sub-arvore direita
		ptr = ptr->right;
		while (ptr->left)
			ptr = ptr->left;
	}
	else
	{ //mais dificil..temos que subir na arvore ate fazermos a primeira virada a direita
		while (ptr->parent && ptr->parent->right == ptr)
			ptr = ptr->parent; //enquanto vou a esquerda para chegar a meu pai, suba...
		ptr = ptr->parent;	   //vire a direita (subindo) uma vez

		//para que precisamos do "ptr->parent &&" no while?
		//O que acontece se incrementarmos um iterador para o ultimo elemento da arvore?
	}
	return *this;
}

//operador de pre-decremento
template <class K, class V>
MyMapIterator<K, V> MyMapIterator<K, V>::operator--()
{
	//faca tudo que fez no operador ++, mas no sentido contrario (left --> right e vice-versa)!
	if (ptr->left)
	{
		ptr = ptr->left;
		while (ptr->right)
			ptr = ptr->right;
	}
	else
	{
		while (ptr->parent && ptr->parent->left == ptr)
			ptr = ptr->parent;
		ptr = ptr->parent;

		//para que precisamos do "ptr->parent &&" no while?
		//O que acontece se decrementarmos um iterador para o primeiro elemento?
		//O que acontece se decrementarmos um apontador para end()?
	}
	return *this;
}

//operador de pos-incremento
template <class K, class V>
MyMapIterator<K, V> MyMapIterator<K, V>::operator++(int)
{
	MyMapIterator<K, V> old(*this);
	++(*this);
	return old;
}

//operador de pos-decremento
template <class K, class V>
MyMapIterator<K, V> MyMapIterator<K, V>::operator--(int)
{
	MyMapIterator<K, V> old(*this);
	--(*this);
	return old;
}

template <class K, class V>
typename MyMap<K, V>::iterator MyMap<K, V>::begin()
{
	if (!root)
		return end();
	Node<K, V> *ptr = root;
	while (ptr->left)
		ptr = ptr->left;
	return iterator(ptr);
}

template <class K, class V>
MyMap<K, V>::MyMap(const MyMap &other)
{
	size_ = 0;
	root = NULL;
	*this = other; //vamos usar o operador de atribuicao..
}

template <class K, class V>
void MyMap<K, V>::deleteNodes(Node<K, V> *root)
{
	if (!root)
		return;
	deleteNodes(root->left);
	deleteNodes(root->right);
	delete root;
}

template <class K, class V>
MyMap<K, V>::~MyMap()
{
	deleteNodes(root);
}

template <class K, class V>
Node<K, V> *MyMap<K, V>::copyNodes(const Node<K, V> *root, Node<K, V> *parent) const
{
	if (root == NULL)
	{ //caso base
		return NULL;
	}
	Node<K, V> *ans = new Node<K, V>(root->keyValue);
	ans->parent = parent;
	ans->left = copyNodes(root->left, ans);
	ans->right = copyNodes(root->right, ans);

	return ans;
}

template <class K, class V>
MyMap<K, V> &MyMap<K, V>::operator=(const MyMap &other)
{
	if (this == &other)
		return *this; //testa auto-atribuicao...
	deleteNodes(root);
	root = copyNodes(other.root, NULL);
	size_ = other.size_;
	return *this;
}

template <class K, class V>
int MyMap<K, V>::size() const
{
	return size_; //exercicio: como calcular o tamanho de forma dinamica? (i.e., sem armazenar o inteiro "size" na classe)
}

//funcao auxiliar...
//exercicio: por que a raiz precisa ser passada por referencia?
template <class K, class V>
pair<typename MyMap<K, V>::iterator, bool> MyMap<K, V>::insert(const pair<K, V> &keyAndValue, Node<K, V> *&root, Node<K, V> *parent)
{ //retorna um iterador para o elemento inserido (o valor booleano sera' true se o elemento nao existia no conjunto e falso caso ele ja exista (ou seja, o novo elemento nao foi inserido) ).
	if (!root)
	{
		root = new Node<K, V>(keyAndValue.first, keyAndValue.second);
		root->parent = parent;
		size_++;
		return make_pair(iterator(root), true);
	}
	else
	{
		if (root->keyValue.first > keyAndValue.first)
			return insert(keyAndValue, root->left, root); //note que todas comparacoes sao realizadas usando a chave!
		else if (root->keyValue.first < keyAndValue.first)
			return insert(keyAndValue, root->right, root);
		else
			return make_pair(iterator(root), false); //igual..
	}
}

template <class K, class V>
pair<typename MyMap<K, V>::iterator, bool> MyMap<K, V>::insert(const pair<K, V> &keyAndValue)
{ //retorna um iterador para o elemento inserido (o valor booleano sera' true se o elemento nao existia no conjunto e falso caso ele ja exista (ou seja, o novo elemento nao foi inserido) ).
	return insert(keyAndValue, root, NULL);
}

//funcao auxiliar...
template <class K, class V>
typename MyMap<K, V>::iterator MyMap<K, V>::find(const K &key, Node<K, V> *root)
{ //retorna um iterador para o elemento inserido (o valor booleano sera' true se o elemento nao existia no conjunto e falso caso ele ja exista (ou seja, o novo elemento nao foi inserido) ).
	if (!root)
	{
		return iterator(NULL);
	}
	else
	{
		if (root->keyValue.first > key)
			return find(key, root->left);
		else if (root->keyValue.first < key)
			return find(key, root->right);
		else
			return iterator(root); //igual..
	}
}

template <class K, class V>
typename MyMap<K, V>::iterator MyMap<K, V>::find(const K &key)
{
	return find(key, root);
}

template <class K, class V>
int MyMap<K, V>::count(const K &key, const Node<K, V> *root) const
{
	if (!root)
	{
		return 0;
	}
	else
	{
		if (root->keyValue.first > key)
			return count(key, root->left);
		else if (root->keyValue.first < key)
			return count(key, root->right);
		else
			return 1; //igual..
	}
}

template <class K, class V>
int MyMap<K, V>::count(const K &key) const
{ //retorna 1 se a chave estiver no mapa, 0 caso contrario...
	return count(key, root);
}

template <class K, class V>
V &MyMap<K, V>::operator[](const K &key)
{ //retorna uma referencia para o valor associado a chave key. Se o valor ainda nao estiver no mapa --> cria um novo usando o construtor padrao.
	typename MyMap<K, V>::iterator it = find(key);
	if (it == end())
	{
		it = insert(make_pair(key, V())).first; //se chave nao esta no mapa --> a insira associando-a a um valor (Gerado com o construtor padrao de V)
	}
	return (*it).second; //retorna uma referencia para o valor associado a chave
}

#endif
