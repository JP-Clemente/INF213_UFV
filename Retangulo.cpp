#include "Retangulo.h"
#include "FigBase.h"
using std::cin;
using std::cout;

void Retangulo::Le(){
    double x, y, largura, altura;
    int espessura, cor, tipo;

    cin >> x >> y >> largura >> altura;
    cin >> espessura >> cor >> tipo;

    FigBase::Le(x, y, espessura, cor, tipo);
    setLargura(largura);
    setAltura(altura);
}

Retangulo::Retangulo(double x, double y, double largura, double altura, int espessura, int cor, int tipo) 
            : FigBase(x, y, espessura, cor, tipo){
    setLargura(largura);
    setAltura(altura);
}

double Retangulo::getLargura() const{
    return largura;
}

double Retangulo::getAltura() const{
    return altura;
}

void Retangulo::setLargura(double largura){
    this->largura = largura;
}
void Retangulo::setAltura(double altura){
    this->altura = altura;
}

float Retangulo::area()const{
    return largura*altura;
}
float Retangulo::perimetro()const{
    return ((2*largura) + (2*altura));
}

void Retangulo::imprime() const{
    cout << "--- [Retangulo] ---" << endl;
    FigBase::imprime();
    cout << "largura = " << getLargura() << " altura = " << getAltura() << endl;
    cout << "area = " << area() << " perimetro = " << perimetro() << endl;
    cout << endl;
}


istream& operator>>(istream &, Retangulo &r){
    r.Le();
    return cin;
}
ostream& operator<<(ostream &, const Retangulo &r){
    r.imprime();
    return cout;
}
