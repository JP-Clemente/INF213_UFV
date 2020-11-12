#include <iostream>
#include "MyStack.h"

using namespace std;


int main() {
	MyStack<int> s;
	
	int ct = 1;
	int n;
	cin >> n;

	cout << n;
	for(int i=0;i<2*n;i++) { //le os 2n comandos...
		char c;
		cin >> c;
		if(c=='I') {
			s.push(ct);
			ct++;
		} else if(c=='R') {
			if(s.empty()) {
				cerr << "Entrada invalida! Removendo mais elementos do que o contido na pilha" << endl;
				exit(1);
			}
			cout << " " << s.top(); 
			s.pop();
		}
		cout << endl;
	}

}