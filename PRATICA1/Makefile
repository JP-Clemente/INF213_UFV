all: snap

snap: TestaAgenda.o Horario.o Data.o Agenda.o
	g++ TestaAgenda.o Horario.o Data.o Agenda.o

TestaAgenda.o: TestaAgenda.cpp
	g++ -c TestaAgenda.cpp

Horario.o: Horario.cpp
	g++ -c Horario.cpp

Data.o: Data.cpp
	g++ -c Data.cpp

Agenda.o: Agenda.cpp
	g++ -c Agenda.cpp

clean:
	rm -rf *o snap