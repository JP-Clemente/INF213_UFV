#include <iostream>

using namespace std;

#include "MyStack.h"
#include "MyQueue.h"

void etapa1() {

	int n = 6;
	MyQueue<int> fila;
	MyStack<int> pilha;
	
	for(int i=0;i<n;i++){
		int value; 
		cin >> value;
		fila.push(value);
		pilha.push(value);
	}

	while(!pilha.empty()){
		cout << pilha.top() << " ";
		pilha.pop();
	}
	cout << '\n';

	while(!fila.empty()){
		cout << fila.front() << " ";
		fila.pop();
	}
	cout << '\n';
}

//---------------------------------------

// Insira aqui o codigo para a etapa 2....

void etapa2() {
	char symbol;
	MyStack <char> pilha;
	
	while(cin>>symbol){

		if(pilha.empty() && (symbol==')' || symbol==']' || symbol=='}')){
			cout << "Inconsistente\n"; return;
		}
		
		if(symbol=='(' || symbol=='[' || symbol=='{'){
			pilha.push(symbol);
		}
			
		if(symbol==')' && pilha.top()=='(') pilha.pop();
		else if(symbol==']' && pilha.top()=='[') pilha.pop();
		else if(symbol=='}' && pilha.top()=='{') pilha.pop();	
	}

	if(pilha.empty()) cout << "Consistente\n";
	else cout << "Inconsistente\n";
	
}

//---------------------------------------
// Na etapa 3 voce deve implementar MyQueue2.h e descomentar os codigos de teste abaixo...


#include "MyQueue2.h"
void etapa3(){

	char operacao;
	MyQueue2<string> q;

	//le um arquivo contendo "comandos" para a fila e aplica-os a fila criada com sua classe...
	while(cin>> operacao){
		if(operacao=='p'){
			string st;
			cin >> st;
			q.push(st); //insere um novo elemento na sua fila...
		} 
		else if(operacao=='f'){ cout << q.front() << "\n";} 
		else if(operacao=='P'){ q.pop();} 
		else if(operacao=='e'){cout << ((q.empty())?"vazia":"cheia") << "\n";}
		else cout << q.size() << "\n";
	}	
}

//---------------------------------------

// Insira aqui o codigo para a etapa 4....


void etapa4() {
	int n, elm, cont = 1;
	MyStack<int> stack;

	cin >> n;

	for(int i = 0; i < n; i++){
		cin >> elm;
		if(stack.empty() || elm > stack.top()){
			for(int j = cont; j <= elm; j++){
				stack.push(j);
				cont++;
			}
			stack.pop();	
		} 
		else if(elm == stack.top()){ stack.pop();} 
		else break;
	}
	if(stack.empty()){cout<< "SIM" << endl;}
	else cout << "NAO" << endl; 
}
//---------------------------------------

int main() {
	int etapa;
	cin >> etapa;
	switch(etapa) {
		case 1:
			cout << "Etapa 1" << endl;
			etapa1();
			break;
		case 2:
			cout << "Etapa 2" << endl;
			etapa2();
			break;
		case 3:
			cout << "Etapa 3" << endl;
			etapa3();
			break;
		case 4:
			cout << "Etapa 4" << endl;
			etapa4();
			break;
	}
}