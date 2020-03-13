#include "Horario.h"

Horario::Horario(int h, int m, int s){
    setHora(h);
    setMinuto(m);
    setSegundo(s);
}
Horario::Horario(const Horario &hr){
    setHora(hr.getHora());
    setMinuto(hr.getMinuto());
    setSegundo(hr.getSegundo());
}


void Horario::setHora(int h){
	if(h<0 || h>23){
		if(h<0){
			h = 0;
        }
		if(h>23){
			h = 23;
        }
	}
	hora = h;	
}

void Horario::setMinuto(int m){
	if(m<0 || m>59){
		if(m<0){
			m = 0;
        }
		if(m>59){
			m = 59;
        }
	}
	minuto = m;
}

void Horario::setSegundo(int s){
	if(s<0 || s>59){
		if(s<0){
			s = 0;
        }
		if(s>59){
			s = 59;
        }
	}	
	segundo = s;
}

int Horario::getHora()const{
    return hora;
}

int Horario::getMinuto()const{
    return minuto;
}

int Horario::getSegundo()const{
    return segundo;
}

int Horario::difSegundos(const Horario &hms)const{
	return (hora*3600 +  minuto*60 + segundo) - (hms.hora*3600 +  hms.minuto*60 + hms.segundo);
}

int Horario::compHorario(const Horario &hms)const{
	int dif = difSegundos(hms);

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

void Horario::imprime()const{
    cout << *this;
}

istream& operator>>(istream &in, Horario &horario) {
	int h,m,s;
	in >> h >> m >> s;
	horario.setHora(h);
	horario.setMinuto(m);
	horario.setSegundo(s);
	return in;
}

ostream& operator<<(ostream &out, const Horario &horario) {
	out << horario.getHora() << " " << horario.getMinuto() << " " << horario.getSegundo();
	return out;
}