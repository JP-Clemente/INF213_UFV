#include "Data.h"

Data::Data(int d, int m, int a){
    setDia(d);
    setMes(m);
    setAno(a);
}
Data::Data(const Data &dt){
    setDia(dt.getDia());
    setMes(dt.getMes());
    setAno(dt.getAno());
}


void Data::setDia(int d){
	if(d<1 || d>30){
		if(d<1){
			d = 1;
        }
		if(d>30){
			d = 30;
        }
	}
	dia = d;	
}

void Data::setMes(int m){
	if(m<1 || m>12){
		if(m<1){
			m = 1;
        }
		if(m>12){
			m = 12;
        }
	}
	mes = m;
}

void Data::setAno(int a){
	if(a<2018 || a>2020){
		if(a<2018){
			a = 2018;
        }
		if(a>2020){
			a = 2020;
        }
	}	
	ano = a;
}

int Data::getDia()const{
    return dia;
}

int Data::getMes()const{
    return mes;
}

int Data::getAno()const{
    return ano;
}

int Data::difDias(const Data &dma)const{
	return (ano*360 +  mes*30 + dia) - (dma.ano*360 +  dma.mes*30 + dma.dia);
}

int Data::compData(const Data &dma)const{
	int dif = difDias(dma);

	if (dif < 0){
        return -1;
    }
	else if (dif==0){
        return 0;
    } 
	else {
        return 1;
    }
}

void Data::imprime()const{
    cout << *this;
}

istream& operator>>(istream &in, Data &data) {
	int d,m,a;
	in >> d >> m >> a;
	data.setDia(d);
	data.setMes(m);
	data.setAno(a);
	return in;
}

ostream& operator<<(ostream &out, const Data &data) {
	out << data.getDia() << " " << data.getMes() << " " << data.getAno();
	return out;
}