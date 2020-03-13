#include <iostream>
#include "Agenda.h"

ItemAgenda::ItemAgenda(){
    setDesc("make");
    Data d;
    setData(d);
    Horario h;
    setHorario(h);
}

ItemAgenda::ItemAgenda(const string& desc, const Data &dt, const Horario &hr){
    setDesc(desc);
    setData(dt);
    setHorario(hr);
}

ItemAgenda::ItemAgenda(const ItemAgenda &it){
    setDesc(it.getDesc());
    setData(it.getData());
    setHorario(it.getHorario());
}

void ItemAgenda::setDesc(const string &desc){
    descricao = desc;
}

void ItemAgenda::setData(const Data &dt){
    d = dt;
}

void ItemAgenda::setHorario(const Horario &hr){
    h = hr;
}

string ItemAgenda::getDesc()const{
    return descricao;
}
Data ItemAgenda::getData()const{
    return d;
}
Horario ItemAgenda::getHorario()const{
    return h;
}

Agenda::Agenda(){
    contador = 0;
}


void Agenda::inserirItem(const ItemAgenda &it){
    list[contador] = it;
    contador ++;
}

void Agenda::compromissosData(const Data &d)const{
    for(int i = 0; i<contador; i++){
        if((list[i].getData()).getAno() == d.getAno()){
            if((list[i].getData()).getMes() == d.getMes()){
                if((list[i].getData()).getDia()==d.getDia()){
                    cout << list[i].getHorario() << " " << list[i].getDesc() << endl;
                }
            }

        }
    }
}