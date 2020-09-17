#ifndef __RETANGULO_H
#define __RETANGULO_H

#include "FigBase.h"
#include <iostream>
using std::istream;
using std::ostream;

class Retangulo : public FigBase {

friend ostream& operator<< (ostream &, const Retangulo &);
friend istream& operator>> (istream &, Retangulo &);

private:
    double largura, altura;

public:
    Retangulo(double=0.0, double=0.0, double=0.0, double=0.0, int=1, int=1, int=1);
    double getLargura() const;
    void setLargura(double);
    double getAltura() const;
    void setAltura(double);
    virtual float area() const;
    virtual float perimetro() const;
    virtual void imprime() const;
    virtual void ler();
};

#endif
