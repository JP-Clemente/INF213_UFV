#include "Screen.h"

using namespace std;

//construtores da classe:
Screen::Screen(const int height_parameter, const int width_parameter){
    //inicializa os valores de altura e largura do jogo com os parâmetros recebidos:
    width = width_parameter;
    height = height_parameter;
    //inicializa o vetor que irá apontar para as colunas do jogo:
    this->data = new int *[width];
    this->dataHeight = new int[width](); //inicializa todos valores do dataHeight com 0 já na alocação (visto que a matriz não possui elementos).

    for(int i=0; i<width; i++){ //repetição que faz com que cada coluna da matriz aponte para NULL inicialmente.
        this ->data[i] = new int[0];
    }
}
//construtor de cópia:
Screen::Screen(const Screen &other){
    *this = other;
}
//destrutor da classe:
Screen::~Screen(){ 
    destroy();
}

void Screen::destroy(){
    //desaloca as colunas do jogo: 
    if(data!=NULL){
        for(int i=0; i<width; i++){
            delete[] data[i];
        } 
    }
    //desaloca o vetor inicial de data que armazenava as colunas e o vetor que armazena o tamanho de cada coluna:
    delete[] data;
    delete[] dataHeight;
    
    data = NULL;
    dataHeight = NULL;
}

//operador de atribuição:
Screen & Screen::operator=(const Screen &other){
    if(this == &other){return *this;}
    destroy();
    
    //copia a largura e altura da tela e aloca o vetor dataHeight para armazenar a altura das colunas:
    width = other.width;
    height = other.height;
    dataHeight = new int[width]();
       
    for(int i=0; i<width; i++){dataHeight[i] = other.dataHeight[i];} //copia elementos de dataHeight.
    
    //aloca a matriz data:
    data = new int *[width];
    for(int i=0; i<width; i++){ 
        data[i] = new int[dataHeight[i]];
    }
    
    //copia os elementos para a matriz data:
    for(int i=0; i<width; i++){dataHeight[i] = other.dataHeight[i];}
    for(int i=0; i<width; i++){
        for(int j=0; j<dataHeight[i]; j++){
            data[i][j] = other.data[i][j];
        }
    }
    return *this;
}

//implementação das funções que retornam o valor referente a largura e a altura do jogo respectivamente:
const int Screen::getWidth()const{return width;}
const int Screen::getHeight()const{return height;}

//função que retorna o estado de um determinado pixel no jogo (EMPTY, WALL, SNAKE ou FOOD):
const int Screen::get(const int row, const int column) const{
    if(row<0||column<0){return WALL;} //caso os parâmetros sejam negativos, o que seriam posições fora da tela, a função retorna WALL.
    if((row<height)&&(column<width)){ //caso o pixel esteja dentro das dimensões do mapa:
        if(row>=dataHeight[column]){
            return EMPTY; //retorna valor equivalente a EMPTY se for uma região não alocada porém nas dimensões do jogo (posição na coluna maior que dataHeight[column]).
        }
        else{
            return data[column][row]; //retorna a posição diretamente caso seja uma posição alocada.
        }
    }
    else{
        return WALL; //retorna o valor equivalente a WALL caso seja uma posição inválida (além das dimensões do mapa).
    }
}

void Screen::set(const int row, const int column, const int val){
    if(row<0 || column<0){return;}
    if((val==SNAKE)||(val==FOOD)){ //caso as variáveis sejam algum valor visível na tela (cobra ou comida):
        if(row>=dataHeight[column]){ //esta situação existe caso seja necessário redimensionar a coluna:
            int *auxColumn = new int[dataHeight[column]]; //vetor auxiliar para armazenar os elementos antes do redimensionamento da coluna.
            int oldColNumber = dataHeight[column]; //variável auxiliar para saber o antigo tamanho da coluna para copiar de volta os elementos do vetor auxiliar.
            for(int i=0; i<dataHeight[column]; i++){ //iteração que copia os valores da coluna que será redimensionada para o vetor auxiliar.
                auxColumn[i] = data[column][i];
            }
            dataHeight[column] = row+1; //incrementa o tamanho da coluna no vetor que os armazena.
            //descaloca e realoca a coluna que será redimensionada:
            delete[] data[column];
            data[column] = new int[dataHeight[column]]();
            //copia os elementos de volta do vetor auxiliar para a coluna da matriz, desaloca o vetor auxiliar e coloca o valor "val" na matriz:
            for(int i=0; i<oldColNumber; i++){
                data[column][i] = auxColumn[i];
            }
            delete[] auxColumn;
            data[column][row] = val;
        }
        else{
            data[column][row] = val; //caso a coluna não precisa ser redimensionada (posição na coluna abaixo de dataHeight[row]).
        }
    }
    if(val==EMPTY){ //caso o valor a ser inserido seja o de vazio (EMPTY):
        if(row<dataHeight[column]){ //o valor só é modificado caso esteja dentro das dimensões já alocadas para a coluna, visto que é um valor vazio, seria desnecessário redimensioná-la.
            if(row==(dataHeight[column]-1)){ //esta situação existe caso o valor EMPTY a ser inserido sobrescreva o ponto mais alto da coluna que representa uma cobra ou uma comida.
                data[column][row] = 0; //coloca o valor EMPTY na matriz, sobrescrevendo uma comida ou cobra.
                int countHighestPos = 0; //esta variável serve para localizar o novo valor mais alto na matriz que será o novo valor de dataHeight[column].
                for(int i=0; i<dataHeight[column]; i++){ //iteração para descobrir o valor do novo valor de dataHeight[column].
                    if((data[column][i]==2)||(data[column][i] == 3)){
                        countHighestPos = i;
                    }
                }
                dataHeight[column] = countHighestPos+1; //atualiza o valor de dataHeight[column].
                int *auxVector = new int[dataHeight[column]]; //vetor auxiliar para copiar os elementos da matriz após redimensionamento.
                for(int i=0; i<dataHeight[column]; i++){
                    auxVector[i] = data[column][i]; //copia elementos da coluna para o vetor auxiliar.
                }
                //desaloca a coluna, redimensiona a mesma, copia os valores do vetor auxiliar para ela, e desaloca o vetor auxiliar:
                delete[] data[column];
                data[column] = new int[dataHeight[column]];
                for(int i=0; i<dataHeight[column]; i++){
                    data[column][i] = auxVector[i];
                }
                delete[] auxVector;
            }
            else{
                data[column][row] = 0; //caso a posição a se inserir EMPTY não seja o ponto mais alto naquela coluna, basta modificar o valor na matriz.
            }
        }
    }
}
