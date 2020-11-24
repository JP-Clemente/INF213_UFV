#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
using namespace std;

class Screen{
    public:
        //construtores e destrutor da classe:
        Screen(const int height_parameter, const int width_parameter);
        Screen(const Screen &);
        ~Screen();
        

        //operador de atribuição:
        Screen & operator=(const Screen &);

        //métodos públicos:
        const int getWidth() const;
        const int getHeight() const;
        const int get(const int row, const int column) const;
        void set(const int row, const int column, const int val);

        //membros de dado públicos para representar o estado dos "pixels" do jogo:
        static const int EMPTY = 0;
        static const int WALL = 1;
        static const int SNAKE = 2;
        static const int FOOD = 3;

    private:  
        void destroy();
        int width, height;
        int **data = NULL;
        int *dataHeight = NULL;
};

#endif
