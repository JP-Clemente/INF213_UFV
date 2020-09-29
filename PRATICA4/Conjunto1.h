#ifndef CONJUNTO1_H
#define CONJUNTO1_H

#include <iostream>
#include <ostream>
#include <istream>

using namespace std;

//devido a necessidade de declaração prévia das funções friend, também é necessário a declaração prévia da classe
template <class T>
class Conjunto;

//funções friend necessitam de declaração prévia
template <class T>
ostream &operator<<(ostream &, const Conjunto<T> &);
template <class T>
istream &operator>>(istream &, Conjunto<T> &);

template <class T>
class Conjunto
{

    friend ostream &operator<<<T>(ostream &, const Conjunto<T> &);
    friend istream &operator>><T>(istream &, Conjunto<T> &);

public:
    Conjunto(const Conjunto<T> &);                  //construtor de cópia
    Conjunto(int N);                                //construtor com argumento
    Conjunto();                                     //construtor vazio
    ~Conjunto();                                    //destrutor
    const Conjunto &operator=(const Conjunto<T> &); //operador de atribuição
    bool operator==(const Conjunto<T> &) const;
    bool pertence(const T &) const;
    bool insere(const T &);
    int numelementos() const { return num_elementos; } //devido a simplicidade da função, já foi implementada no corpo da classe
    //void le(Conjunto<T>);
    void imprime() const;

private:
    T *elementos;
    int num_elementos;
    int tam_array;
};

//destrutor que será utilizado na implementação do operator =
template <class T>
Conjunto<T>::~Conjunto()
{
    delete[] elementos;
}

//operator = que será reutilizado no construtor de cópia
template <class T>
const Conjunto<T> &Conjunto<T>::operator=(const Conjunto<T> &other)
{

    if (this == &other)
        return *this; //checagem de auto atribuição
    delete[] elementos;

    num_elementos = other.num_elementos;
    tam_array = other.tam_array;
    elementos = new T[tam_array]; //cria novo vetor

    for (int i = 0; i < num_elementos; i++)
        elementos[i] = other.elementos[i];
    return *this;
}

//construtor de cópia
template <class T>
Conjunto<T>::Conjunto(const Conjunto<T> &other)
{
    elementos = NULL;
    *this = other; //aproveita a sobrecarga do operator =
}

//construtor que recebe argumento
template <class T>
Conjunto<T>::Conjunto(int N)
{
    elementos = new T[N];
    num_elementos = 0;
    tam_array = N;
}

//construtor que não recebe argumentos
template <class T>
Conjunto<T>::Conjunto()
{
    num_elementos = 0;
    tam_array = 10;
    elementos = new T[tam_array];
}

//função pertence
template <class T>
bool Conjunto<T>::pertence(const T &elem) const
{
    for (int i = 0; i < num_elementos; i++)
        if (elementos[i] == elem)
            return true;
    return false;
}

//função insere, retorna false caso não seja possível inserir o elemento
template <class T>
bool Conjunto<T>::insere(const T &elem)
{
    if ((num_elementos >= tam_array) || (pertence(elem)))
        return false;
    elementos[num_elementos] = elem;
    num_elementos++;
    return true;
}

template <class T>
bool Conjunto<T>::operator==(const Conjunto<T> &other) const
{
    if (num_elementos != other.num_elementos)
    { //retorna false caso tamanhos sejam diferentes
        return false;
    }
    for (int i = 0; i < num_elementos; i++)
    {
        if (!pertence(other.elementos[i]))
            return false;
    }
    return true;
}
/*
template <class T>
void Conjunto<T>::le(Conjunto<T> vector)
{
    for (int i = 0; i < tam_array; i++)
    {
        cin >> vector.elementos[i];
        insere(vector.elementos[i]);
    }
}*/

template <class T>
void Conjunto<T>::imprime() const {
    cout << "{";  
    for(int i=0; i<num_elementos-1; i++) cout << elementos[i] << ",";
    if(num_elementos > 0){
        cout << elementos[num_elementos-1]<< "}";
    }else
    {
        cout << "}";
    }
    
}

template <class T>
ostream &operator<<(ostream &os, const Conjunto<T> &vector)
{
    vector.imprime();
    return os;
}

template <class T>
std::istream & operator>>(std::istream & in, Conjunto<T>& vector){
    T aux;
    while(in >> aux){
        vector.insere(aux);
    }
    return in;
}


#endif