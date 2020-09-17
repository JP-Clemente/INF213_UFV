#ifndef __SEGMENTO_H
#define __SEGMENTO_H

#include "FigBase.h"
#include <iostream>
using std::istream;
using std::ostream;

class Segmento : public FigBase {

friend ostream& operator<< (ostream &, const Segmento &);
friend istream& operator>> (istream &, Segmento &);

private:
    double x2, y2;

public:
    Segmento(double=0.0, double=0.0, double=0.0, double=0.0, int=1, int=1, int=1);
    double getX2() const;
    void setX2(double);
    double getY2() const;
    void setY2(double);
    virtual float area() const;
    virtual float perimetro() const;
    virtual void imprime() const;
    virtual void ler();
};

#endif
