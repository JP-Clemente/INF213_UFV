#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Snake.h"
#include "Screen.h"

using namespace std;

//struct utilizado para armazenar dados relativos as comidas que existem no jogo:
struct Food{
    int time; //tempo até que as comidas desapareçam.
    pair<int, int> position; //variável pair que armazena as coordenadas da comida na tela do jogo.
};

class Game{
    public:
        //construtor e destrutor da classe Game:
        Game(const int height, const int width, const int snake_size);
        ~Game();

        bool step(int dr, int dc); //os parâmetros dessa função não foram declarados como constantes pois no caso do movimento inverso ao anterior, estes parâmetros serão modificados.
        void addFood(const int dr, const int dc, const int ttl);
        const Screen getScreen() const;
        const int getNumFood();

    private:
        void destroy();
        pair<int, int> lastMovement; //variável auxiliar que armazena os valores do último step passado para o jogo.
        Snake *Serpent = NULL;
        Screen *S = NULL;
        Food F[10];
};

#endif