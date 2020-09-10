#include "Circulo.h"
#include "FigBase.h"
using std::cin;
using std::cout;

const float PI = 3.141592653589;

void Circulo::Le(){
    double x, y, raio;
    int espessura, cor, tipo;

    cin >> x >> y >> raio;
    cin >> espessura >> cor >> tipo;

    FigBase::Le(x, y, espessura, cor, tipo);
    setRaio(raio);
}

Circulo::Circulo(double x, double y, double raio, int espessura, int cor, int tipo) 
                : FigBase(x,y,espessura,cor,tipo){
    setRaio(raio);
}



void Circulo::setRaio(double raio){
    this->raio = raio;
}

double Circulo::getRaio() const {
    return raio;
}



float Circulo::area() const {
    return PI * raio * raio;    
}      
          
float Circulo::perimetro() const {
    return 2 * PI * raio;      
}


void Circulo::imprime() const {
    cout << "--- [Circulo] ---" << endl;
    FigBase::imprime();
    cout << "raio = " << getRaio() << endl;
    cout << "area = " << area() << " perimetro = " << perimetro() << endl;
    cout << endl; 
}


istream& operator>>(istream &, Circulo &c){
    c.Le();
    return cin;
}
ostream& operator<<(ostream &, const Circulo &c){
    c.imprime();
    return cout;
}
