#ifndef CONJUNTO2_H
#define CONJUNTO2_H

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
    //construtores e destrutores
    Conjunto(const Conjunto<T> &);
    Conjunto(int N);
    Conjunto();
    ~Conjunto();

    bool insere(const T &);
    bool pertence(const T &) const;
    //funções operator
    Conjunto operator+(const Conjunto<T> &) const;
    Conjunto operator*(const Conjunto<T> &) const;
    Conjunto operator-(const Conjunto<T> &) const;
    bool operator==(const Conjunto<T> &) const;
    const Conjunto &operator=(const Conjunto<T> &);

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

template <class T>
Conjunto<T> Conjunto<T>::operator+(const Conjunto<T> &other) const
{
    int tam = tam_array + other.tam_array;
    Conjunto<T> temp(tam);

    for (int i = 0; i < num_elementos; i++)
        temp.insere(elementos[i]);
    for (int i = 0; i < other.num_elementos; i++)
        temp.insere(other.elementos[i]);

    return temp;
}

template <class T>
Conjunto<T> Conjunto<T>::operator*(const Conjunto<T> &other) const
{
    int tam = (tam_array < other.tam_array) ? tam_array : other.tam_array;
    int total_elem = num_elementos + other.num_elementos;

    Conjunto<T> temp(tam);

    for (int i = 0; i < tam_array; i++)
        temp.insere(elementos[i]);
    for (int i = 0; i < other.tam_array; i++)
        temp.insere(other.elementos[i]);

    Conjunto<T> temp2(tam);

    for (int i = 0; i < total_elem; i++)
    {
        if (pertence(temp.elementos[i]) && other.pertence(temp.elementos[i]))
            temp2.insere(elementos[i]);
    }
    return temp2;
}

template <class T>
Conjunto<T> Conjunto<T>::operator-(const Conjunto<T> &other) const
{
    int tam = tam_array + other.tam_array;
    int total_elem = num_elementos + other.num_elementos;
    Conjunto<T> temp(tam);
    for (int i = 0; i < tam_array; i++)
        temp.insere(elementos[i]);
    for (int i = 0; i < other.tam_array; i++)
        temp.insere(other.elementos[i]);
    Conjunto<T> temp2(tam);

    for (int i = 0; i < total_elem; i++)
    {
        if (pertence(temp.elementos[i]) && other.pertence(temp.elementos[i]))
            temp2.insere(elementos[i]);
    }
    Conjunto<T> temp3(tam);
    for (int i = 0; i < total_elem; i++)
    {
        if (other.pertence(temp.elementos[i]) && temp2.pertence(temp.elementos[i]))
        {
            continue;
        }
        else if (pertence(temp.elementos[i]))
        {
            temp3.insere(elementos[i]);
        }
    }
    return temp3;
}

template <class T>
void Conjunto<T>::imprime() const
{
    cout << "{";
    for (int i = 0; i < num_elementos - 1; i++)
        cout << elementos[i] << ",";
    if (num_elementos > 0)
    {
        cout << elementos[num_elementos - 1] << "}";
    }
    else
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