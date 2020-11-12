#ifndef MyQueue_H__
#define MyQueue_H__

#include "MyVecNewIterator.h"
#include <iostream>
using namespace std;

template<class T>
class MyQueue {
public:
	MyQueue() : first(-1), last(-1), vec(4) {} //vamos inicialmente criar uma fila de tamanho 4

	void push(const T&el);
	const T & front() const { return vec[ first ]; }
	void pop() ;

	bool empty() const { return first == -1; }
	int size() const;

	//para estudar o estado da fila...
	void print()  const ;
private:
	bool full() const { return first == (last+1)%vec.size(); }
	int first, last;
	MyVec<T> vec;
};




template<class T>
void MyQueue<T>::push(const T&el) {
	if(empty()) {
			first = last = 0;
			vec[last] = el;
	} else {
		if(full()) {
			int tamanhoAntigoLista = vec.size();
			vec.resize(vec.size()*2);
			if(first!=0) { //se first ==0 --> a fila comecava no inicio da lista e terminava no final --> nao precisamos fazer nada
													// apos redimensionar a lista..
				//a fila comeca apos o inicio da lista e termina no inicio (dando uma "volta")
				//temos que copiar os elementos do inicio para o final da nova lista
				//exercicio: ha risco de tentarmos colocar um elemento apos o final da lista (i.e.: temos que tratar
				//o final da lista seria preenchido e precisariamos passar a copiar alguns elementos para o inicio 
				//da lista circular?)
				for(int i=0;i<first;i++) vec[(tamanhoAntigoLista+i)] = vec[i]; 
				last = (tamanhoAntigoLista+first-1);				
			}
		}

		last = (last+1)%vec.size();
		vec[last] = el;
	}	
}


template<class T>
void MyQueue<T>::pop() { 
	if(first==last) { // ha apenas um elemento? temos que marcar first como sendo -1 para indicar fila vazia...
		first = last = -1;
	} else
		first = (first+1)%vec.size(); 
}

template<class T>
int MyQueue<T>::size() const {
	if(last>=first) return last-first+1;
	else return vec.size() - (first-last+1);
}

//para estudar o estado da fila...
template<class T>
void MyQueue<T>::print() const {
	cout << "First,last: " << first << " " << last << endl; 
	cout << "Size: " << size() << endl;
	for(int i=0;i<vec.size();i++) cout << vec[i] << " "; 
	cout << endl << endl;
}



#endif