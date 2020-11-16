#include <iostream>
#include <vector>
#include <cstdlib>
#include "MyQueue.h"
using namespace std;

#define USAR_COR

class Point
{
public:
    Point() : x(0), y(0) {}
    Point(int y_, int x_) : x(x_), y(y_) {}
    int getX() const { return x; }
    int getY() const { return y; }

private:
    int x, y;
};

class Maze
{
public:
    //w = largura, h = altura do labirinto...
    Maze(int w_, int h_) : w(w_), h(h_)
    {
        map = MyVec<MyVec<char>>(h, MyVec<char>(w, ' '));
    }
    void setPoint(const Point &p, char val) { map[p.getY()][p.getX()] = val; }
    int getW() const { return w; }
    int getH() const { return h; }
    void draw() const;

    bool canVisit(const Point &p) const;
    void visit(const Point &p);
    bool isEnd(const Point &p) const { return map[p.getY()][p.getX()] == '$'; }
    bool isStart(const Point &p) const { return map[p.getY()][p.getX()] == '@'; }
    bool contains(const Point &p) const { return p.getX() >= 0 && p.getX() < getW() && p.getY() >= 0 && p.getY() < h; } //o labirinto contem o ponto? (i.e., o ponto esta dentro dos limites do labirinto?)
private:
    MyVec<MyVec<char>> map;

    int w, h;
};

void Maze::draw() const
{
    const string original = "\033[0m";
    const string vermelho = "\033[7;31m";
    const string verde = "\033[7;32m";
    const string preto = "\033[7;31m";
    const string azul = "\033[7;34m";

    system("clear");
    for (int i = 0; i < getH(); i++)
    {
        for (int j = 0; j < getW(); j++)
        {
            char c = map[i][j];
#ifdef USAR_COR
            if (c == '#')
                cout << azul;
            else if (c == 'X')
                cout << vermelho;
            else
                cout << original;
#endif
            cout << c;
        }
        cout << endl;
    }
    system("sleep 0.05");
    cout << original << endl;
}

void Maze::visit(const Point &p)
{
    map[p.getY()][p.getX()] = '#';
}

bool Maze::canVisit(const Point &p) const
{
    int x = p.getX();
    int y = p.getY();
    return map[y][x] == '.' || map[y][x] == '$' || map[y][x] == '@';
}

//percorre o labirinto (modificando-o) ate encontrar o final dele (ou ate nao haver mais movimentos possiveis)
//retorna true <-> for possivel encontrar a saida do labirinto
bool solve(Maze &m)
{
    MyQueue<Point> s;
    int w = m.getW();
    int h = m.getH();

    Point start(0, 0);
    for (int i = 0; i < h; i++) //acha o inicio do labirinto...
        for (int j = 0; j < w; j++)
            if (m.isStart(Point(i, j)))
                start = Point(i, j);

    m.draw();
    s.push(start);
    while (!s.empty())
    {
        Point p = s.front();
        s.pop();
        if (m.canVisit(p))
        {
            bool encontreiFinal = m.isEnd(p);
            m.visit(p);
            m.draw();

            if (encontreiFinal)
                return true; //encontrei o final do labirinto!
            for (int i = -1; i <= 1; i++)
                for (int j = -1; j <= 1; j++)
                { //adiciona os vizinhos de p a pilha...
                    if (i * j != 0)
                        continue; //ignora as diagonais
                    Point p2(i + p.getY(), j + p.getX());
                    if (m.contains(p2) && m.canVisit(p2))
                    {               //o ponto eh valido (esta dentro dos limites) e ainda nao foi visitado?
                        s.push(p2); //adicione o ponto a pilha...
                    }
                }
        }
    }
    return false; //percorri o labirinto todo e nao encontrei o final...
}

int main()
{
    int w, h;
    cin >> h >> w;
    Maze m(w, h); //cria um labirinto com altura h e largura w...
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
        { //le os caracteres representando o labirinto...
            char c;
            cin >> c;
            m.setPoint(Point(i, j), c);
        }
    bool temSolucao = solve(m);
    if (temSolucao)
        cout << "Eh possivel atingir a saida do labirinto" << endl;
    else
        cout << "Nao eh possivel atingir a saida do labirinto" << endl;
}
