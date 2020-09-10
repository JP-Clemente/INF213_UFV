#ifndef CIRCULO_H
#define CIRCULO_H
#include "FigBase.h"
#include <iostream>
using namespace std;

class Circulo : public FigBase {
    public:
        void Le();
        Circulo(double=1, double=1, double=1, int=1, int=1, int=1);

        double getRaio() const;

        void setRaio(double);

        float area() const;
        float perimetro() const;
        void imprime() const;
        friend istream& operator>>(istream &, Circulo &);
        friend ostream& operator<<(ostream &, const Circulo &);

    private:
        double raio;
};

#endif
