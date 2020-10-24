#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <iostream>

using namespace std; 

template <class T>
class MyMatrix{ 
    public:
        //protótipos de todas funções que serão implementadas abaixo da declaração da classe:
        //construtores e destrutor da classe:
        MyMatrix(int n, const int[], bool); 
        MyMatrix(const MyMatrix &); //construtor de cópia
        ~MyMatrix(); //destrutor

        //operador de atribuição:
        MyMatrix & operator=(const MyMatrix &);

        //funções get e set:
        const T& get(const int, const int) const;
        void set(const int, const int, const T &);

        //funções que retornam número de linhas, elementos e colunas respectivamente:
        int getNumRows() const;
        int getNumElems() const;
        int getNumCols(const int) const;

        //funções para redimencionar quantidade de colunas e linhas respectivamente:
        void resizeRow(const int, const int);
        void resizeNumRows(const int);

        //função para checar se a matriz está no formato tradicional ou ragged:
        bool isRagged() const;

        //funções de conversão de matriz para ragged e tradicional respectivamente:
        void convertToRagged();
        void convertToTraditional();

        //função para mostrar a matriz:
        void print() const;

    protected:
        //variável de número de linhas (rows) e variável size que conta os elementos (inicializada com 0):
        int rows = 0, size = 0; 

        //variáveis correspondentes a matriz no formato tradicional (todas inicializadas com NULL, podendo ser modificadas ou não dependendo da função main):
        int *tam = NULL; //array que armazena quantos elementos existem em cada coluna da matriz no formato tradicional.
        T **matriz = NULL; //variável do tipo T que armazena a matriz tradicional.

        //variáveis correspondentes a matriz no formato ragged (também inicializadas com NULL podendo ou não serem modificadas caso a matriz esteja neste formato):
        int *start = NULL; //array que armazena as posições do array principal "ragged" em que se encontra o primeiro elemento de cada linha.
        T *ragged = NULL; //array principal que armazena a matriz no formato ragged.
        
        void destroy(); //função protegida auxiliar para destruir o objeto.
};

//a implementação de todas funções da classe se encontra em ordem semelhante a de declaração:

//implementação do construtor:
//complexidade para matriz tradicional: O(R*C); complexidade para matriz ragged: O(T).
template <class T>
MyMatrix<T>::MyMatrix(int rowNumber, const int colNumbers[], bool matrixType){
    rows = rowNumber; //iguala a variável que armazena a quantidade de linhas a variável recebida.
    if(!matrixType){ //situação em que o booleano recebido é falso, indicando que o formato da matriz é tradicional.
        if(rows>0){ //caso o número de linhas seja maior que zero, a matriz é criada. Caso seja zero ou menos, continua apontando para NULL.
            //alocação do vetor que armazena a quantidade de colunas por linha e da primeira parte da matriz principal respectivamente:
            this -> tam = new int [rows];
            this -> matriz = new T *[rows];
            for(int i=0; i<rowNumber; i++){//repetição para alocação dinâmica das colunas;
                tam[i] = colNumbers[i]; //o vetor que armazena o número de colunas por linha recebe os valores correspondentes aos do vetor passado como parâmetro.
                size += tam[i]; //incrementa a variável size de acordo com o número de colunas em cada linha, armazenados no vetor "tam".
                if(tam[i] > 0){
                    this -> matriz[i] = new T[tam[i]]; //para cada linha da matriz, aloca um vetor dinâmico de um tamanho correspondente ao número de colunas da linha (armazenados no vetor "tam").
                }
                else{matriz[i] = NULL;} //caso a linha não possua colunas, ela aponta para NULL.
            } 
        }
    }         
    else{ //implementação do construtor para construir a matriz para o caso do tipo ragged:
        this -> start = new int [rows + 1]; start[0] = 0; /*aloca o vetor start dinamicamente (mesmo com número de linhas igual a zero, visto que o seu valor inicial sempre será o mesmo e para
        diferenciar as matrizes na função isRAgged).*/
        if(rows>0){
            for(int i=0; i<rows; i++){
                size += colNumbers[i];
                start[i+1] = colNumbers[i] + start[i]; //o vetor start recebe os valores de onde se encontram os primeiros elementos de cada linha a partir do vetor recebido como parâmetro.
            }
            start[rows] = size;
            this -> ragged = new T[size]; //aloca o vetor (matriz ragged) dinamicamente,
        }
    }
}

//implementação do construtor de cópia:
//complexidade para matriz tradicional: O(R*C); complexidade para matriz ragged: O(T).
template<class T>
MyMatrix<T>::MyMatrix(const MyMatrix &other) {
        //não é necessário apontar para NULL pois a função 'destroy' já realiza esta operação.
        *this = other; //aproveita sobrecarga do operador de atribuição.
}

//implementação do destrutor:
//complexidade para matriz tradicional: O(R*C); complexidade para matriz ragged: O(T).
template <class T>
MyMatrix<T>::~MyMatrix(){
    destroy(); //apenas chama a função protected destroy (implementada logo abaixo).
}

//função destroy auxiliar (protegida) que desaloca todos membros de dados alocados:
//complexidade para matriz tradicional: O(R*C); complexidade para matriz ragged: O(T).
template<class T>
void MyMatrix<T>::destroy() {
	if(isRagged()==false){ //checa se o formato da matriz é tradicional:
        for(int i = 0; i < rows; i++){
            delete [] matriz[i]; //para cada linha da matriz, desaloca o array correspondente a esta linha.
        }
        delete [] matriz; //desaloca o array principal que aponta para as linhas (desalocadas acima).
        delete [] tam; //desaloca o vetor que armazena o número de colunas em cada linha da matriz.    
        //torna a apontar os objetos desalocados para NULL em todos os casos:
        matriz = NULL;
        tam = NULL;   
    }
    else{ //caso destrutor para o caso da matriz estar no tipo ragged:
        delete [] ragged; //desaloca o vetor "ragged" que armazena a matriz.
        delete [] start; //desaloca o vetor start que armazena os primeiros elementos de cada linha.
        ragged = NULL;
        start = NULL;
    }
    size = 0; //caso um objeto seja destruído, seu número de colunas é igualado a zero.
}

//implementação do operador de atribuição:
//complexidade para matriz tradicional: O(R*C); complexidade para matriz ragged: O(T).
template<class T>
MyMatrix<T> & MyMatrix<T>::operator=(const MyMatrix &other) {
	if(this==&other) return *this; //evitar atribuição entre objetos iguais.
	if(!other.isRagged()){ //situação em que a matriz é do tipo tradicional:
        destroy(); //primeiramente destrói o objeto para desalocar a memória que estava sendo usada por este.
        //iguala o número de linhas e colunas do objeto em questão para o que será recebido para a cópia:
        rows = other.rows;
        size = other.size;
        if(rows>0){ //realiza atribuição apenas caso a matriz possua um número de linhas maior que zero.
            //aloca o vetor que armazena a quantidade de colunas de cada linha da matriz e o vetor de linhas da matriz:
            this -> tam = new int [rows];
            this -> matriz = new T *[rows];
            for(int i=0; i<rows; i++){
                tam[i] = other.tam[i];
                if(tam[i] > 0){
                    this -> matriz[i] = new T[tam[i]]; //para cada linha da matriz, aloca um vetor dinâmico de um tamanho correspondente ao número de colunas da linha (armazenados no vetor "tam").
                }
                else{matriz[i] = NULL;} //caso aquela linha não possua colunas, ela aponta para NULL.
            }
            //iguala os elementos do objeto aos que devem ser copiados (do outro objeto).
            for(int i=0; i<rows; i++){
                for(int j=0; j<tam[i]; j++){
                    matriz[i][j] = other.matriz[i][j];
                }
            }
        }
    }  
    else{
        destroy(); 
        rows = other.rows;
        size = other.size;
        this -> start = new int [rows + 1]; start[0] = 0; //aloca o vetor start dinamicamente, e atribui 0 ao primeiro valor.
        for(int i=1; i<=rows; i++){start[i] = other.start[i];} //iguala os valores de start dos dois objetos.
        this -> ragged = new T[size]; //aloca o vetor (matriz ragged) dinamicamente,
        for(int i=0; i<size; i++){ragged[i] = other.ragged[i];} //atribui ao vetor que receberá a atribuição os valores de ragged.
     }
	return *this;
}

//implementação das funções get e set respectivamente:
//Complexidade em ambos casos: O(1).
template <class T>
const T& MyMatrix<T>::get(const int row, const int column) const{
    if(!isRagged()){return matriz[row][column];} //implementação caso a função esteja no formato tradicional (apenas retorna a posição na matriz).
    else{return ragged[start[row]+column];} /*caso a matriz esteja no formato ragged basta retornar o valor do vetor ragged na posição do vetor start na linha especificada somado a coluna do elemento que deve ser imprimido.*/
}

//Complexidade em ambos casos: O(1).
template <class T>
void MyMatrix<T>::set(const int row, const int column, const T &element){ 
    if(!isRagged()){matriz[row][column] = element;} //implementação da função set para matriz no formato tradicional.
    else{ragged[start[row]+column] = element;} //implementação da função set para matriz no formato ragged.
}

//implementação das funções que retornam número de linhas, elementos e colunas na linha selecionada:
//Complexidade em ambos casos: O(1).
template <class T>
int MyMatrix<T>::getNumRows() const{return rows;} 

//Complexidade em ambos casos: O(1).
template <class T>
int MyMatrix<T>::getNumElems() const{return size;}

//Complexidade em ambos casos: O(1).
template <class T> 
int MyMatrix<T>::getNumCols(const int line) const{ //exige uma implementação diferente para cada possível formato da matriz (tradicional ou ragged):
    if(isRagged()==false){ //implementação em que a matriz está no formato tradicional:
        return tam[line]; //simplesmente retorna o valor correspondente a linha passada como parâmetro que está armazenado no vetor "tam".
    }
    else {return (start[line+1] - start[line]);} //caso a matriz seja ragged basta retornar a diferença da posição do elemento da linha desejada para o da próxima linha,
}

//implementação da função que redimensiona o número de colunas de uma linha:
//complexidade para matriz tradicional: O(C); complexidade para matriz ragged: O(T).
template <class T> 
void MyMatrix<T>::resizeRow(const int line, const int newColNumber){
    if(!isRagged()){//checa o formato da matriz.
        if(newColNumber!=tam[line]){ //caso o número de colunas recebido como parâmetro seja igual ao já existente, nada acontece.
        
            size += (newColNumber-tam[line]); //atualiza o tamanho de size visto que o número de colunas da linha será alterado.

            //condicionais para evitar o acesso a posição inválida da memória e alocação desnecessária para o vetor auxiliar caso o novo número de colunas seja menor:
            if(newColNumber>tam[line]){ //condicional caso o novo número de colunas seja maior que o antigo:

                //aloca dinamicamente um vetor auxiliar para armazenar os elementos daquela linha e os copia para este vetor:
                T *auxLine = new T[tam[line]];
                for(int i = 0; i < tam[line]; i++){auxLine[i] = matriz[line][i];}

                //deleta a linha que será modificada e a aloca novamente: 
                delete[] matriz[line];
                matriz[line] = new T[newColNumber]();//aloca e preenche toda linha alocada com o valor padrão do tipo T.

                for(int i = 0; i < tam[line]; i++){matriz[line][i] = auxLine[i];} //copia os elementos do array auxiliar para a linha que foi realocada. 
                delete [] auxLine; //desaloca o vetor auxiliar que foi alocado.      
            }
            //caso o novo número de colunas seja menor que o antigo:
            else{
                T *auxLine = new T[newColNumber]; //aloca um vetor auxiliar que armazena apenas o novo número de colunas (não há necessidade de armazenar mais visto que os elementos sobressalentes não serão copiados).
                for(int i = 0; i < newColNumber; i++){auxLine[i] = matriz[line][i];} //copia newColNumber elementos da linha escolhida da matriz para o vetor auxiliar.

                //deleta a linha que será modificada e a aloca novamente: 
                delete[] matriz[line];

                if(newColNumber > 0){matriz[line] = new T[newColNumber];} //caso o novo número de colunas seja maior que zero, aloca um espaço igual a newColNumber.
                else{matriz[line] = NULL;} //caso newColNumber seja zero ou menos, a linha da matriz aponta para NULL.

                for(int i = 0; i < newColNumber; i++){matriz[line][i] = auxLine[i];} //copia os elementos do array auxiliar para a linha que foi realocada.
                tam[line] = newColNumber; 
                delete[] auxLine; //desaloca o vetor auxiliar que foi alocado.   
            }

            tam[line] = newColNumber; //atualiza o número de colunas daquela linha no vetor "tam".     
        }
    }
    //situação em que a matriz está no formato ragged:
    else{
        if(newColNumber!=getNumCols(line)){ //caso o novo número de colunas seja o mesmo, nada acontece.

            int oldColNumber = getNumCols(line); //variável que armazena o antigo número de colunas.
            int difference = newColNumber - oldColNumber; //variável que armazena a diferença do antigo número de colunas para o novo.
            int newSize = size + difference; //variável que armazena o novo tamanho da matriz.
            int *auxStart = new int [rows+1]; //criação de um vetor start auxiliar para armazenar os novos valores para criar o novo vetor ragged.

            for(int i=0; i<=rows; i++){ //preenche o vetor start auxiliar com seus novos valores (já atualizados para o novo número de colunas da linha selecionada).
                if(i<=line){auxStart[i] = start[i];}
                else{auxStart[i] = start[i] + difference;}
            }

            T *auxRagged = new T[newSize]; //alocação de um vetor ragged auxiliar.

            if(newColNumber>oldColNumber){
            int colInserted = 0; //variável que conta inserções de elementos no vetor na linha que será alterada, para saber se elementos devem ser copiados do vetor original ou deve-se preencher com o valor padrão do tipo T naquela posição.
                for(int i=0; i<auxStart[line+1]; i++){ //loop que funciona até o fim da linha que será alterada
                    if((i>=auxStart[line])&&(i<auxStart[line+1])){ //caso o iterador esteja na linha que será alterada, checa se deve copiar elementos ou preencher com o valor padrão:
                        if(colInserted<(start[line+1]-start[line])){ //caso ainda hajam elementos para copiar do vetor original, os copia (essa checagem é necessária para evitar acesso a posição inválida no vetor original, tentando copiar elementos que não existem).
                            auxRagged[i] = ragged[i];
                            colInserted++; //aumenta inserções caso copie um valor.
                        }
                        else{ //caso não existam mais elementos para copiar, preenche com valor auxiliar.
                            auxRagged[i] = T();
                        }
                    }
                    else{auxRagged[i] = ragged[i];} //caso esteja antes da linha que será modificada, apenas copia elementos.
                }
                for(int i=auxStart[line+1]; i<newSize; i++){auxRagged[i] = ragged[i-difference];} //loop que termina de copiar elementos após redimensionamento da linha.
            }
            else{ //caso o antigo número de colunas seja maior, basta copiar os elementos e desprezar os elementos excedentes daquela linha:
                for(int i=0; i<newSize; i++){
                    if(i<auxStart[line+1]){auxRagged[i] = ragged[i];}
                    else{auxRagged[i] = ragged[i-difference];}
                }
            }
            //desaloca e realoca o vetor ragged para copiar os elementos do auxiliar para ele. Essa operação não é necessária com start, visto que seu tamanho não se altera após redimensionar o número de colunas em uma linha.
            delete[] ragged;
            ragged = new T[newSize];

            //copia os elementos dos vetores auxiliares de start e ragged:
            for(int i=0; i<=rows; i++){start[i] = auxStart[i];}
            for(int i=0; i<newSize; i++){ragged[i] = auxRagged[i];} 

            //desaloca os vetores auxiliares:
            delete[] auxStart;
            delete[] auxRagged;

            size = newSize; //atualiza o tamanho da matriz.
        }
    }
}

//implementação da função que altera o número de linhas da matriz:
//complexidade para matriz tradicional: O(R*C); complexidade para matriz ragged: O(T).
template <class T> 
void MyMatrix<T>::resizeNumRows(const int newRowNumber){
    if(newRowNumber!=rows){ //primeiro checa se o novo número de colunas é diferente ao original. Caso sejam iguais, nada acontece.
        if(!isRagged()){ //caso a função esteja no formato tradicional:
            int *auxTam = new int[newRowNumber]; //aloca um vetor auxiliar "auxTam" para armazenar os valores de "tam".

            for(int i = 0; i<newRowNumber; i++){ //copia os valores para o vetor auxiliar:
                if(i<rows){auxTam[i] = tam[i];}
                else{auxTam[i] = 0;} //caso não existam valores para copiar (novas linhas), o tamanho dessas linhas é preenchido com zero.
            }
            
            //desaloca o vetor tam original para realocá-lo após o aumento do número de linhas e preenche com os valores do auxiliar.
            delete[] tam;
            tam = new int[newRowNumber];
            for(int i=0; i<newRowNumber; i++){tam[i] = auxTam[i];}

            delete[] auxTam; //desaloca o vetor auxiliar.

            //cria uma matriz auxiliar e copia para ela os elementos da matriz original.
            T **auxMatrix = new T *[newRowNumber]; //aloca linhas da matriz auxiliar.
            for(int i=0; i<newRowNumber; i++){
                auxMatrix[i] = new T[tam[i]]; //aloca as colunas da matriz auxiliar.
                for(int j=0; j<tam[i]; j++){auxMatrix[i][j] = matriz[i][j];} //copia elementos.
            }
            
            //desaloca a matriz original:
            for(int i=0; i<rows; i++){delete[] matriz[i];}
            delete[] matriz;

            //realoca a matriz original e copia os elementos de volta para ela:
            matriz = new T *[newRowNumber];
            for(int i=0; i<newRowNumber; i++){
                matriz[i] = new T[tam[i]];
                for(int j=0; j<tam[i]; j++){matriz[i][j] = auxMatrix[i][j];}
            }

            //desaloca colunas e linhas da matriz auxiliar respectivamente:
            for(int i=0; i<newRowNumber; i++){delete[] auxMatrix[i];}
            delete[] auxMatrix;

            //caso o novo número de linhas seja menor, atualiza-se o valor de size pois as linhas removidas poderiam conter elementos:
            if(newRowNumber<rows){
                size = 0;
                for(int i=0; i<newRowNumber; i++){size += tam[i];}
            }
            rows = newRowNumber; //atualiza o número de linhas.
        }
        else{ //caso a matriz esteja no formato ragged:
            if(newRowNumber<rows){ //situação em que o novo número de linhas é menor:
                int *auxStart = new int[newRowNumber+1]; //aloca um vetor start auxiliar.
                for(int i=0; i<=newRowNumber; i++){auxStart[i] = start[i];} //copia os elementos do vetor start original para o auxiliar.

                //desaloca o vetor start original e o realoca após redimensioná-lo:
                delete[] start;
                start = new int[newRowNumber+1];

                //copia os elementos do vetor auxiliar de volta para o vetor original start e desaloca o vetor auxiliar:
                for(int i=0; i<=newRowNumber; i++){start[i] = auxStart[i];}
                delete[] auxStart;

                //aloca um vetor ragged auxiliar e copia para eles os elementos do vetor original:  
                T *auxRagged = new T[start[newRowNumber]];
                for(int i=0; i<start[newRowNumber]; i++){auxRagged[i] = ragged[i];}

                //desaloca o vetor original e o realoca de forma redimensionada:
                delete[] ragged;
                ragged = new T[start[newRowNumber]];

                for(int i=0; i<start[newRowNumber]; i++){ragged[i] = auxRagged[i];} //copia os elementos de volta do auxiliar para o vetor ragged original redimensionado.

                delete[] auxRagged; //desaloca o vetor ragged auxiliar.
                rows = newRowNumber; //atualiza o número de linhas.
                size = start[rows]; //atualiza o tamanho do vetor.
            }
            else{ //situação em que o novo número de linhas é maior que o antigo:
                int *auxStart = new int[newRowNumber+1]; //aloca um vetor start auxiliar.
                for(int i=0; i<=rows; i++){auxStart[i] = start[i];} //copia os elementos do vetor start original para o auxiliar.
                for(int i=rows+1; i<=newRowNumber; i++){auxStart[i] = auxStart[rows];} //preenche os elementos de start correspondentes as novas linhas com o mesmo valor do último valor que foi preenchido a partir do original, pois novas linhas não possuem elementos.

                delete[] start; //desaloca o vetor start original para redimensioná-lo abaixo:
                start = new int[newRowNumber+1];
                for(int i=0; i<=newRowNumber; i++){start[i] = auxStart[i];} //copia os elementos de volta do auxiliar para o start original.

                delete[] auxStart; //desaloca o vetor start auxiliar.
                rows = newRowNumber; //atualiza o número de linhas da matriz.
            }
        }
    }
}
//implementação da função que checa o tipo da matriz criada (tradicional ou "ragged"):
//Complexidade em ambos casos: O(1).
template <class T>
bool MyMatrix<T>::isRagged() const{
    if(start!=NULL){ //como matrizes no formato tradicional possuem o membro de dados "start" nulo, basta apenas checar isto para verificar o tipo da matriz que foi criada.
        return true; //retorna falso no caso em que a matriz está no formato tradicional.
    }
    return false; //retorna true no formato em que a matriz está no formato ragged.
}

//implementação da função que converte a matriz para ragged:
//ordem de complexidade para matriz tradicional: O(R*C). Ordem de complexidade para matriz ragged: O(1).
template <class T>
void MyMatrix<T>::convertToRagged(){
    if(!isRagged()){ //primeiro checa se a matriz que passará pela conversão já está no formato ragged, e caso não esteja, executa, assim, a função.
        this -> start = new int [rows + 1]; start[0] = 0; //aloca o vetor start da mesma forma como no construtor.
        for(int i=0; i<rows; i++){start[i+1] = tam[i] + start[i];} //o vetor start recebe os valores de onde se encontram os primeiros elementos de cada linha a partir do vetor "tam" recebido como parâmetro.
        this -> ragged = new T[size]; //aloca o vetor (matriz ragged) dinamicamente.
        int aux = 0; //variável auxiliar que é um iterador para andar pelo vetor ragged.
        for(int i = 0; i<rows; i++){
            for(int j=0; j<tam[i]; j++){
                ragged[aux] = matriz[i][j]; //copia os elementos da matriz tradicional para o vetor ragged.
                aux++; 
            }
        }
        //desaloca a matriz tradicional anterior e faz os vetores "matriz" e "tam" aṕontarem para NULL.
        for(int i = 0; i < rows; i++){
            delete [] matriz[i]; //para cada linha da matriz, desaloca o array correspondente a esta linha.
        }
        delete [] matriz; //desaloca o array principal que aponta para as linhas (desalocadas acima).
        delete [] tam; //desaloca o vetor que armazena o número de colunas em cada linha da matriz.    
        //torna a apontar os objetos desalocados para NULL em todos os casos:
        matriz = NULL;
        tam = NULL;   
    }
}

//implementação da função que converte a matriz para o formato ragged:
//ordem de complexidade para matriz tradicional: O(1), pois não converte. Para ragged: O(R*C).
template <class T>
void MyMatrix<T>::convertToTraditional(){
    if(isRagged()){ //primeiro checa se a matriz está no formato ragged para ser convertida ou não.
        this -> tam = new int [rows];
        this -> matriz = new T *[rows];
        for(int i=0; i<rows; i++){tam[i] = (start[i+1] - start[i]);} //atribui os valores ao vetor "tam" a partir do vetor "start";
        for(int i=0; i<rows; i++){
            if(tam[i] > 0){
                this -> matriz[i] = new T[tam[i]]; //para cada linha da matriz, aloca um vetor dinâmico de um tamanho correspondente ao número de colunas da linha (armazenados no vetor "tam").
            }
            else{matriz[i] = NULL;} //caso aquela linha não possua colunas, ela aponta para NULL.
        }
        int aux = 0; //variável auxiliar que é um iterador para ragged.
        for(int i=0; i<rows; i++){ //loop para andar pela matriz e copiar os elementos.
            for(int j=0; j<tam[i]; j++){
                matriz[i][j] = ragged[aux];
                aux++;
            }
        }
        //desaloca os vetores antigos do formato ragged que estavam em uso e os faz apontar para NULL.
        delete[] start; 
        delete[] ragged; 
        ragged = NULL;
        start = NULL;
    }
}

//implementação da função que imprime a matriz:
//complexidade para matriz tradicional: O(R*C); complexidade para matriz ragged: O(T).
template <class T>
void MyMatrix<T>::print() const{ 
    //imprime número de linhas e elementos na matriz:
    cout << "Rows: " << rows << endl;
    cout << "Elems: " << size << endl;
    //faz-se necessária a checagem do tipo da matriz para verificar qual algoritmo usar para imprimí-la:
    if(isRagged()==false){ //situação em que o tipo da matriz é tradicional:
        for(int i = 0; i < rows; i++){ //loop que controla as linhas (i).
            cout << tam[i] << ":"; //imprime quantos elementos existem na linha.
            for(int j=0; j<tam[i]; j++){//loop que controla as colunas (j).
                cout << " " << matriz[i][j];
            }
            cout << endl;
        }
    }
    else{//situação para o tipo da matriz ragged: 
        if(rows>0){//se a matriz não possuir linhas, simplesmente não imprime elementos.
            int line = 1;//variável que conta a próxima linha da matriz para controle de saída e formatação.
            cout <<(start[line] - start[line-1])<< ":";
            for(int i = 0; i <= size; i++){//loop para imprimir a matriz.
                if(line<rows){//enquanto a linha for menor que número de colunas, realiza-se o processo abaixo:
                    if(i == start[line]){//caso a posição do iterador que acompanha ragged seja o primeiro da linha, existe uma quebra de linha anterior a este.
                        cout << endl << (start[line+1] - start[line])<< ":";
                        line ++;//incrementa-se o contador de linhas quando se chega no primeiro elemento de uma nova linha.
                        while((start[line]==start[line-1])&&(line<rows)){//pode ser que a nova linha não possua elementos, por isso checa-se os elementos de start:
                            cout << endl << (start[line+1] - start[line]) << ":"; //apenas quebra-se a linha no caso de não existirem elementos.
                            line ++; //incrementa-se a linha mesmo possuindo zero elementos.
                        }
                    } 
                }
                if(i == size){ break; } //quebra o loop caso i seja igual ao número total de elementos para não acessar posição inválida (ragged[size]).
                if(i!=start[line]){
                    cout << " "; //caso não seja o último elemento da linha, salta um espaço.
                cout << ragged[i]; //imprime os elementos sem quebrar linha.    
                }
            }
            cout << endl; //quebra linha ao final da impressão da matriz.     
        } 
    }
}     

#endif