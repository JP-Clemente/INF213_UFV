#include "FigBase.h"
#include <iostream>

using namespace std;

void FigBase::Le(double x, double y, int espessura, int cor, int tipo){

    setX(x);
    setY(y);
    setEspessura(espessura);
    setCor(cor);
    setTipo(tipo);
}

FigBase::FigBase(double x, double y, int espessura, int cor, int tipo){
    setX(x); setY(y); setEspessura(espessura);
    setCor(cor); setTipo(tipo);
}


void FigBase::imprime() const{
    cout << "Atributos da linha: \n" << "Espessura = " << getEspessura() << "\n" <<
    "Cor = " << getCor() << "\n" << "Tipo = " << getTipo() << endl;
    cout << "x = " << getX() << " y = " << getY() << endl;
}

void FigBase::setX(double x){
    this->x = x;
}

void FigBase::setY(double y){
    this->y  = y;
}

void FigBase::setEspessura(int espessura){
    if(espessura > 5 ){
        espessura = 5;   
    }
    else if(espessura < 1){ 
        espessura =1;
    }

    this->espessura = espessura;
}

void FigBase::setCor(int cor){
    if(cor > 5){
        cor = 5;
    }
    else if(cor < 1){ 
        cor = 1;
    }

    this->cor = cor;
}

void FigBase::setTipo(int tipo){
    if(tipo > 3){
        tipo = 3;
    }
    else if(tipo < 1){
        tipo = 1;
    }

    this->tipo = tipo;
}

double FigBase::getX() const{
    return x;
}

double FigBase::getY() const{
    return y;
}

int FigBase::getEspessura() const{
    return espessura;
}

int FigBase::getCor() const{
    return cor;
}

int FigBase::getTipo() const{
    return tipo;
}
