#include <iostream>
#include "Mediana.h"

using namespace std;

void Mediana::insere(int x)
{
    if (fila.size() == 0)
        fila.push(x);
    else
    {
        if (x > fila.top())
            fila2.push((-1) * (x));
        else
            fila.push(x);

        if ((fila.size() - fila2.size()) >= 2)
        {
            fila2.push((-1) * (fila.top()));
            fila.pop();
        }
        else if ((fila2.size() - fila.size()) >= 2)
        {
            fila.push((-1) * (fila2.top()));
            fila2.pop();
        }
    }
}

int Mediana::getMediana()
{
    if (fila.size() == fila2.size())
        return (fila.top() + (fila2.top()) * (-1)) / 2;
    else if ((fila.size() + fila2.size()) % 2 == 0)
    {
        return (fila.top() + (fila2.top()) * (-1)) / 2;
    }
    else
    {
        if (fila.size() > fila2.size())
            return fila.top();
        else
            return (-1) * fila2.top();
    }
}