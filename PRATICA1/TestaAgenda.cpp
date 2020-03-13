/* 
Programa para ler um arquivo contendo casos de teste e testar algumas
funcionalidades das classes agenda, horario e data.

Autor: Salles Magalhaes

Os arquivos de entrada (lidos a partir da entrada padrao) devem estar no formato:
NC NQ
C1
D1 M1 A1 H1 Min1 S1
....
D_NC M_NC A_NC H_NC Min_NC S_NC
<Linha em branco>
D1 M_1 A_1
...
D_NQ M_NQ A_NQ

Onde NC e' o numero de compromissos a serem incluidos na agenda

A seguir, ha 2*NC linhas representando os compromissos a serem inseridos.

Cada par de linhas contem:
C_i (na primeira linha do par), que e' uma string representando o i-esimo compromisso
D_i M_i A_i H_i Min_i S_i (na segunda linha do par), que representam, respectivamente, o dia, mes, ano, hora, minuto e segundo do i-esimo compromisso

Apos a insercao dos NC compromissos ha NQ linhas representando as consultas.
Cada consulta contem o dia, mes e ano a ser consultado.

Para cada consulta e' impresso (em ordem) os compromissos na referida data (observe que datas invalidas
devem ser instanciadas utilizando os valores padrao descritos nas instrucoes do laboratorio). Apos imprimir
todos os compromissos da data, deve-se imprimir uma linha em branco para facilitar a leitura dos resultados.

O formato da impressao das consultas e' o seguinte:
Data: linha contendo a data da consulta
Horario_1 Compr_1
....
Horario_n Compr_n

I.e., deve ser impressa uma linha com a data da consulta e n linhas para cada um dos n compromissos
encontrados nessa data. Cada compromisso e' representado por um horario (ex: 2:5:57 (2 horas, 5 minutos e 
57 segundos)) seguido pela string descrevendo o titulo do compromisso.
*/

#include <iostream>
#include <string>

using namespace std;

#include "Agenda.h"
#include "Horario.h"

using namespace std;



int main()
{
  int numCompromissos, numConsultas;
  cin >> numCompromissos >> numConsultas;
  Agenda ag;
  //cerr << numCompromissos << numConsultas << endl;
  //Le os compromissos
  for(int i=0;i<numCompromissos;i++) {
    string compr;
    cin.ignore();
    getline(cin,compr);
    Data d;
    Horario h;
    cin >> d >> h;
    
    //abaixo declaramos versoes constantes dos objetos data/horario e item agenda
    //com o objetivo de testar se os metodos que nao deveriam modificar tais dados 
    //realmente estao funcionando com objetos constantes
    const Data d2 = d;
    const Horario h2 = h;
    const ItemAgenda ia = ItemAgenda(compr,d2,h2);
    //cerr << dia << mes << ano << hora << min << sec << compr << endl;
    ag.inserirItem(ia);
  }

  //Como as consultas nao modificam o objeto da classe agenda, o codigo abaixo
  //deve compilar e executar sem erros
  const Agenda ag2 = ag;
  
  for(int i=0;i<numConsultas;i++) {
    Data d;
    cin >> d;

    const Data d2 = d;
    cout << d2 << endl;
    ag2.compromissosData(d2);
    cout << endl;
  }

  return 0;

}

