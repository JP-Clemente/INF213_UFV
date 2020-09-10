#ifndef RETANGULO_H
#define RETANGULO_H
#include "FigBase.h"
#include <iostream>
using namespace std;


class Retangulo : public FigBase {
    public:
        Retangulo(double =1, double =1, double =1, double =1, int =1, int =1, int =1);
        void Le();

        double getLargura() const;
        double getAltura() const;

        void setLargura(double);
        void setAltura(double);

        float area() const;
        float perimetro() const;
        void imprime() const;

        friend istream& operator>>(istream &, Retangulo &);
        friend ostream& operator<<(ostream &, const Retangulo &);

    private:
        double largura, altura;
};

#endif
