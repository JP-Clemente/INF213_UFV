#ifndef SEGMENTO_H
#define SEGMENTO_H
#include "FigBase.h"
#include <iostream>
using namespace std;

class Segmento : public FigBase{
    public:
        Segmento(double =1, double =1, double =1, double =1, int =1, int =1, int =1);
        void Le();

        double getX2() const;
        double getY2() const;

        void setX2(double);
        void setY2(double);

        float area() const;
        float perimetro() const;
        void imprime() const;

        friend istream& operator>>(istream &, Segmento &);
        friend ostream& operator<<(ostream &, const Segmento &);

    private:
        double x2, y2;
};


#endif