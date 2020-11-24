#include "Screen.h"
#include <iostream>

using namespace std;

void print(const Screen &s) {
    for (int j=0; j<s.getWidth()+2; j++) cout << "-";
    cout << endl;
    for (int i=0; i<s.getHeight(); i++) {
        cout << "|";
        for (int j=0;j<s.getWidth();j++) {
            if (s.get(s.getHeight()-1-i,j) == Screen::EMPTY) cout << " ";
            else if (s.get(s.getHeight()-1-i,j) == Screen::SNAKE) cout << "#";
            else cout << "$";
        }
        cout << "|" << "\n";
    }
    for (int j=0; j<s.getWidth()+2; j++) cout << "-";
    cout << "\n\n";
}

int main() {
    int height = 6, width = 10;
    Screen s(height, width);

    // Coloca tudo como Comida
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            s.set(i, j, Screen::FOOD);

    print(s);
    
    // Volta tudo para Empty
    for (int i = (height-1); i >= 0; i--)
        for (int j = (width-1); j >=0; j--)
            s.set(i, j, Screen::EMPTY);
    print(s);
    
    for (int i = (width-1); i >=0; i--)
        s.set(3, i, Screen::SNAKE);

    s.set(0, 0, Screen::FOOD);
    s.set(0, 1, Screen::FOOD);
    print(s);
    
    return 0;
}