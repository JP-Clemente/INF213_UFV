
#ifndef __FIG_BASE_H
#define __FIG_BASE_H

#include <iostream>
using std::istream;
using std::ostream;

class FigBase {

friend ostream& operator<< (ostream &, const FigBase &);
friend istream& operator>> (istream &, FigBase &);

private:
    double x, y;

    // atributos da linha
    int espessura; // inteiro de 1 a 5
    int cor;       // inteiro de 1 a 5
    int tipo;      // inteiro de 1 a 3

public:
    FigBase(double=0.0, double=0.0, int=1, int=1, int=1);

    double getX() const;
    void setX(double);

    double getY() const;
    void setY(double);

    int getEspessura() const;
    void setEspessura(int);

    int getCor() const;
    void setCor(int);

    int getTipo() const;
    void setTipo(int);

    virtual float area() const = 0;
    virtual float perimetro() const = 0;
    virtual void imprime() const;
    virtual void ler();   // funcao adicional (nao especificada no UML)

};

#endif
