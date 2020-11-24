#include "Snake.h"
#include "Screen.h"

using namespace std;

Snake::Snake(const int snake_size){
	dataFirst = dataLast = new Node(0, 0); //inicializa separadamente o primeiro nodo da cobra e iguala dataFirst e dataLast visto que só existe um nodo.
	for(int i=1; i<snake_size; i++){ //loop que cria os próximos nodos da cobra na posição especificada:
		dataLast->next = new Node(0, i); //acrescenta os nodos e faz as operações necessárias para organizar o novo dataLast (último nodo da lista).
		dataLast->next->prev = dataLast;
		dataLast = dataLast->next;
	}
}

Snake::Snake(const Snake &other){
    *this = other;
}

Snake::~Snake(){
    destroy();
}

void Snake::destroy(){  
    while(dataFirst!=NULL){
        Node *aux = dataFirst; //variável auxiliar para apagar a lista.
        dataFirst = dataFirst->next;
        delete aux;  
    }
    //aponta dataFirst e dataLast para NULL ao deletar a cobra:
    dataFirst = NULL;
    dataLast = NULL;
}

Snake & Snake::operator=(const Snake &other){
    if(this == &other){return *this;} //evita atribuir uma cobra a si mesma.
    destroy();
    dataFirst = dataLast = new Node(((other.dataFirst)->data.first),((other.dataFirst)->data.second)); //primeiro nodo da cobra.
    Node *curr = dataFirst; //nodo auxiliar da cobra que receberá a atribuição.
    Node *other_curr = other.dataFirst; //nodo auxiliar para a cobra other.

    //iguala os nodos de uma cobra a outra:
	for(int i=1; i<other.getLength(); i++){
		curr->next = new Node((other_curr->next)->data.first,(other_curr->next)->data.second);
        curr->next->prev = curr;
        curr = curr->next;
        other_curr = other_curr->next;
	}
    dataLast = curr; //atualiza o valor de dataLast.
    return *this;
}

void Snake::draw(Screen &s, const int state){
    Node *curr = dataFirst; //ponteiro auxiliar para andar pela lista.
    while(curr!=NULL){
        s.set(curr->data.first, curr->data.second, state); //muda os valores da tela relativos a cobra de acordo com state (usado para apagar a cobra se state for igual a EMPTY ou desenhar esta se for igual a SNAKE).
        curr = curr->next; 
    }
}

void Snake::move(const int dr, const int dc, const bool eating){
    if(eating == true){push_back(dr, dc); return;} //caso a cobra esteja comendo, não é necessário movê-la, apenas adicionar um nodo no local da comida.
    else{ //situação em que a cobra não esteja se alimentando:
        Node *curr = dataFirst; //nodo auxiliar para andar pela cobra:
        while(curr->next!=NULL){ //faz com que cada nodo da lista desde o primeiro aponte para o próximo:
            curr->data.first = (curr->next)->data.first;
            curr->data.second = (curr->next)->data.second;
            curr = curr->next;
        }
    }
    //acresce as posições do último nodo da lista aos valores do movimento para obter as novas coordenadas:
    dataLast->data.first += dr;
    dataLast->data.second += dc;
}

//função com retorno do tipo pair responsável por retornar as posições relativas a cabeça da cobra:
const pair<int, int> Snake::getLastPos() const{
    pair <int, int> coordinates;

    coordinates.first = dataLast->data.first;
    coordinates.second = dataLast->data.second;

    return coordinates;
}

const int Snake::getLength() const{
    Node *curr = dataFirst;
    int snake_length = 0; //armazena a quantidade de nodos.
    while(curr!=NULL){ //anda pela lista duplamente encadeada até chegar no último ponteiro (nulo). Para cada iteração a variável relativa ao tamanho da cobra é acrescida.
        curr = curr->next;
        snake_length++;
    }
    return snake_length;
}

//esta função cria um novo nodo para a cobra quando ela se alimenta (eating == true).
void Snake::push_back(const int dr, const int dc){
    dataLast->next = new Node(dr+dataLast->data.first, dc+dataLast->data.second); //cria um novo nodo na posição do último nodo somado das posições relativas ao movimento (pares possíveis de dr e dc).
	//atualiza valores relativos ao último nodo após aumentar a cobra:
    dataLast->next->prev = dataLast;
	dataLast = dataLast->next;
}