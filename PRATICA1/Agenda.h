#ifndef AGENDA_H
#define AGENDA_H

#include <iostream>
#include <string>
#include "Data.h"
#include "Horario.h"
using namespace std; 


class ItemAgenda{
    private:
    string descricao;
    Data d;
    Horario h;

    public:
    ItemAgenda();
    ItemAgenda(const string&, const Data &, const Horario &);
    ItemAgenda(const ItemAgenda &);
    
    void setDesc(const string &);
    void setData(const Data&);
    void setHorario(const Horario &);

    string getDesc()const;
    Data getData()const;
    Horario getHorario()const;
    
};

class Agenda{
    private: 
        int contador;
        ItemAgenda list[1000];
    
    public:
        Agenda();
        void inserirItem(const ItemAgenda &);
        void compromissosData(const Data &)const;
};

#endif