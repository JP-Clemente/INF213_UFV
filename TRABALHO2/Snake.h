#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include "Screen.h"
#include <utility>

using namespace std;

//classe para representar os nodos da lista duplamente encadeada (tipo escolhido) que será usada na classe Snake:
class Node{
    public:
        Node(const int row, const int column) : data(row, column), prev(NULL), next(NULL) {} //inicialização dos valores.
        pair <int, int> data; //par de inteiros que armazena a posição do nodo na matriz screen.
        Node *prev, *next; //ponteiros para o próximo nodo e o nodo anterior.
};

class Snake{
    public:
        //construtores e destrutor da classe Snake:
        Snake(const int); 
        Snake(const Snake &);
        ~Snake();
       
        //operador de atribuição:
        Snake & operator=(const Snake &);

        //funções auxiliares:
        void draw(Screen &s, const int state);
        void move(const int dr, const int dc, const bool eating);
        const int getLength() const;
        const pair<int, int> getLastPos() const; //função auxiliar que retorna um par que representa a posição da cabeça da cobra na matriz.
        void push_back(const int dr, const int dc); 

    private:
        void destroy(); //função privada que será chamada no destrutor.
        Node *dataFirst = NULL, *dataLast = NULL; //ponteiros para primeiro e último nodo da cobra (cauda e cabeça, respectivamente).
};

#endif