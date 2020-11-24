#include "Game.h"

using namespace std;

//construtor da classe:
Game::Game(const int height, const int width, const int snake_size){
    //cria a cobra e a tela do jogo de acordo com os parâmetros recebidos pelo construtor:
    Serpent = new Snake(snake_size);
    S = new Screen(height, width);

    //inicia os valores relativos a comida: 
    for(int i=0; i<10; i++){
        F[i].time = 0; //comidas são todas inicializadas com tempo 0.
        F[i].position.first = -1; //posições inicialmente recebem -1.
        F[i].position.second = -1;
    }

    //o par de dados que armazena o último movimento recebe a direção em que a cobra é criada:
    lastMovement.first = 0;
    lastMovement.second = 1;

    //desenha a cobra no jogo após o jogo ser criado:
    Serpent->draw(*S, Screen::SNAKE);
}

//destrutor da classe e função auxiliar privada destroy:
Game::~Game(){
    destroy();
}

void Game::destroy(){
    //desaloca a cobra e a tela e os aponta para NULL.
    delete Serpent;
    delete S;
    Serpent = NULL;
    S = NULL;
}

//função step responsável pelos movimentos no jogo:
bool Game::step(int dr, int dc){
    pair <int, int> lastNodePosition = Serpent->getLastPos(); //variável pair criada para armazenar os dados relativos a cabeça da cobra utilizando a função auxiliar criada na classe Snake.
    bool eating = false; //variável para armazenar se a cobra está comendo ou não.

    //trecho de código criado para decidir se a cobra está indo para sentido invertido e assim atribuir a última direção para qual estava indo para a nova:
    if((lastMovement.first+dr==0)&&(lastMovement.second+dc==0)){
        dr = lastMovement.first;
        dc = lastMovement.second;
    }

    //trecho de código responsável por deletar as comidas com o tempo 0, e após isso decrementar o tempo das comidas restantes:
    for(int i=0; i<10; i++){
        if(F[i].time == 0){
            if(S->get(F[i].position.first, F[i].position.second) == Screen::FOOD){
                S->set(F[i].position.first, F[i].position.second, Screen::EMPTY);
                F[i].time == 0;
            }
        }
        if(F[i].time>0){
            F[i].time--;
        }
    }

    //caso a cobra vá se mover para uma posição com comida, o booleano "eating" torna-se true:
    if(S->get(lastNodePosition.first+dr, lastNodePosition.second+dc) == Screen::FOOD){eating = true;}
    //checa se a próxima posição seria uma parede, o que se configura como um movimento não sucedido:
    else if(S->get(lastNodePosition.first+dr, lastNodePosition.second+dc) == Screen::WALL){return false;}
    //também checa se a cobra iria chocar-se contra si mesma, o que também configura-se como um movimento não sucedido:
    else if(S->get(lastNodePosition.first+dr, lastNodePosition.second+dc) == Screen::SNAKE){return false;}

    //apaga a cobra, move a mesma e desenha ela no mapa com as posições e tamanho (caso ela tenha se alimentado) atualizados:
    Serpent->draw(*S, Screen::EMPTY);
    Serpent->move(dr, dc, eating);
    Serpent->draw(*S, Screen::SNAKE);

    //esse trecho de código zera o tempo da comida de que a cobra se alimentou para depois apagá-la no próximo step, no trecho da linha 50.
    if(eating == true){
        for(int i=0; i<10; i++){
            if(F[i].position.first == lastNodePosition.first+dr){
                if(F[i].position.second == lastNodePosition.second+dc){
                    F[i].time = 0;
                }
            }
        }
    }
    //atualiza os valores relativos ao último movimento recebido:
    lastMovement.first = dr;
    lastMovement.second = dc;
    return true;//caso a função tenha chegado até aqui, retorna true pois o movimento foi bem sucedido.
}

//função responsável por adicionar comidas ao mapa:
void Game::addFood(const int dr, const int dc, const int ttl){
    if(S->get(dr, dc) != Screen::EMPTY){return;} //caso a comida fosse ser adicionada em uma posição não vazia, a função retorna e nada acontece.
    for(int array_pos=0; array_pos<10; array_pos++){
        if(F[array_pos].time == 0){ //ao encontrar uma food no array com valor de tempo igual a zero, isto significa que uma nova comida pode ser colocada naquele local.
            if(S->get(F[array_pos].position.first, F[array_pos].position.second) == Screen::FOOD){ //primeiro checa se a comida que será substituída já foi apagada. Caso não tenha sido, procura a próxima posição válida no vetor de comida.
                continue;
            }
            //atualiza os valores relativos a posição da nova comida:
            F[array_pos].position.first = dr;
            F[array_pos].position.second = dc;
            F[array_pos].time = ttl;
            //atualiza aquele local da tela para receber o valor de uma comida:
            S->set(dr, dc, Screen::FOOD);
            return;
        }
    }
}

//métodos responsáveis por retornar a quantidade de comidas no jogo e a tela respectivamente:
const int Game::getNumFood(){
    int active = 0;
    for(int i=0; i<10; i++){ //conta pelo array de comidas, todas aquelas em que o tempo é maior que 0 (comidas ativas).
        if(F[i].time>0){active++;}
    }
    return active;
}

const Screen Game::getScreen() const{
    return *S;
}