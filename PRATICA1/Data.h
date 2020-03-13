#ifndef DATA_H
#define DATA_H

#include <fstream>
#include <iostream>
using namespace std;

class Data{
    private: 
        int dia;
        int mes;
        int ano;

    public:
        Data(int d=1,int m = 1,int a = 2018);
        Data(const Data &);

        void setDia(int d);
        void setMes(int m);
        void setAno(int a);

        int getDia() const;
        int getMes() const;
        int getAno() const;

        int difDias(const Data &dma) const;
        int compData(const Data &dma) const;

        void imprime()const;
        
        friend ostream& operator<<(ostream &out, const Data &data);
};

istream& operator>>(istream &in, Data &data);


#endif