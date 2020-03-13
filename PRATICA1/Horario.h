#ifndef HORARIO_H
#define HORARIO_H

#include <fstream>
#include <iostream>
using namespace std;

class Horario{
    private: 
        int hora;
        int minuto;
        int segundo;

    public:
        Horario(int h = 0,int m = 0,int s = 0);
        Horario(const Horario &);

        void setHora(int h);
        void setMinuto(int m);
        void setSegundo(int s);

        int getHora() const;
        int getMinuto() const;
        int getSegundo() const;

        int difSegundos(const Horario &hms) const;
        int compHorario(const Horario &hms) const;

        void imprime()const;
        
        friend ostream& operator<<(ostream &out, const Horario &horario);
};

istream& operator>>(istream &in, Horario &horario);


#endif