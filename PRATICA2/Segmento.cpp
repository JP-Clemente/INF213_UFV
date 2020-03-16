#include <cmath>
#include "Segmento.h"
#include "FigBase.h"
using std::cin;
using std::cout;


void Segmento::Le(){
    double x, y, x2, y2;
    int espessura, cor, tipo;

    cin >> x >> y >> x2 >> y2;
    cin >> espessura >> cor >> tipo;

    FigBase::Le(x, y, espessura, cor, tipo);
    setX2(x2);
    setY2(y2);
}
Segmento::Segmento(double x, double y, double x2, double y2, int espessura, int cor, int tipo)
        : FigBase(x, y, espessura, cor, tipo){
    setX2(x2); setY2(y2);
}

void Segmento::imprime() const{
    cout << "--- [Segmento] ---" << endl;
    FigBase::imprime();
    cout << "x2 = " << getX2() << " y2 = " << getY2() << endl;
    cout << "area = " << area() << " perimetro = " << perimetro() << endl;
    cout << endl; 
}

void Segmento::setX2(double x2) {
    this->x2 = x2;
}

void Segmento::setY2(double y2) {
    this->y2 = y2;
}

double Segmento::getX2() const {
    return x2;
}

double Segmento::getY2() const {
    return y2;
}

float Segmento::area() const {
    return 0;
}

float Segmento::perimetro() const {
    return (sqrt(pow((x2-FigBase::getX()),2)+pow((y2-FigBase::getY()),2)));
}

istream& operator>>(istream &, Segmento &s){
    s.Le();
}
ostream& operator<<(ostream &, const Segmento &s){
    s.imprime();
}