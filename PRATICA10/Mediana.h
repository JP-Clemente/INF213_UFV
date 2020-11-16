#ifndef Mediana_H
#define Mediana_H

#include "MyVecNewIterator.h"
#include "MyPriorityQueue.h"

class Mediana
{
public:
    void insere(int);
    int getMediana();

private:
    MyPriorityQueue<int> fila;
    MyPriorityQueue<int> fila2;
};

#endif