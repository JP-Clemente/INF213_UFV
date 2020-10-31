#include <iostream>
#include "MyList2NewIterator.h"
#include <cstdlib>
using namespace std;

//implemente aqui a funcao nao-membro reverse (etapa 3):
template <class T>
void reverse(MyList2<T> &lista)
{
    typename MyList2<T>::iterator itToFirst = lista.begin();
    typename MyList2<T>::iterator itToLast = lista.begin();
    typename MyList2<T>::iterator itAux = lista.begin();
    if (itToFirst == lista.end())
    {
        return;
    }
    int cont = 0;
    while (itToFirst != lista.end())
    {
        cont++;
        itToLast = itToFirst;
        ++itToFirst;
    }
    itToFirst = itAux;
    for (int i = 0; i <= (cont / 2); i++)
    {
        if (cont % 2 == 0 && i == cont / 2)
        {
            itToFirst++;
            itToLast--;
        }
        else
        {
            swap(*itToFirst, *itToLast);
            itToFirst++;
            itToLast--;
        }
    }
}

void testesSizeEmpty()
{
    MyList2<int> v;
    for (int i = 0; i < 3; i++)
    {
        cout << v.size() << " " << v.empty() << endl;
        v.push_back(i);
    }
}

void testaIteradores()
{
    MyList2<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    for (MyList2<int>::iterator it = v.begin(); it != v.end(); it++)
        cout << *it << " ";
    cout << endl;
    for (MyList2<int>::iterator it = v.begin(); it != v.end();)
        cout << (*(it++)) << " ";
    cout << endl;

    for (MyList2<int>::iterator it = v.begin(); it != v.end(); ++it)
        cout << *it << " ";
    cout << endl;

    MyList2<int>::iterator it = v.begin();
    cout << *(it++) << endl;
    cout << *(++it) << endl;
    it++;
    cout << *(it--) << endl;
    cout << *(--it) << endl;
}

void testaConstrutoresEtc()
{
    MyList2<char> v;
    cout << v << endl;
    v.push_back('a');
    cout << v << endl;
    for (int i = 1; i < 10; i++)
    {
        v.push_back('a' + i);
        cout << v << endl;
    }

    { //testando criacao e destrucao de vetor vazio..
        MyList2<char> v2;
    }

    {
        //copias de vetor vazio
        MyList2<char> v2;
        MyList2<char> v3 = v2; //construtor de copia
        v3 = v2;

        v2 = v;
        v2 = v;
        v3 = v;

        MyList2<char> v4 = v2;
    }

    v.insert('0', v.begin());
    cout << v << endl;

    MyList2<char>::iterator it = v.begin();
    it++;
    it++;
    it++;
    v.insert('w', it);

    cout << v << endl;

    while (it != v.end())
        it++; //obviamente poderiamos fazer apenas it = v.end();, mas quero iterar para testar melhor o iterador...
    v.insert('z', it);

    cout << v << endl;
}

template <class T>
typename MyList2<T>::iterator find(const T &elem, const MyList2<T> &list)
{ //funcao auxiliar para os testes
    typename MyList2<T>::iterator it = list.begin();
    while (it != list.end() && list.derref(it) != elem)
    {
        it = list.next(it);
    }
    return it;
}

void testaReverse()
{
    cout << "Testando a funcao reverse..." << endl;
    MyList2<int> l1;

    for (int i = 0; i < 6; i++)
    {
        MyList2<int> l2 = l1;
        reverse(l2);
        cout << "Lista: " << endl
             << l1 << " Reverse: " << endl
             << l2 << endl
             << "--------------" << endl;
        l1.push_back(i);
    }
}

void printReverse(MyList2<int> &l1)
{
    //nao passamos por referencia constante porque nao nos preocupamos com iteradores constantes
    //na implementacao da classe MyList2 (sem esses iteradores nao podemos iterar em listas constantes,
    //visto que um iterador pode modificar a lista com a operacao de derreferencia)
    MyList2<int>::iterator it = l1.end();
    if (it != l1.begin())
    { //lista nao vazia...
        do
        {
            it--;
            cout << *it << " ";
        } while (it != l1.begin());
    }
    cout << endl;
}

void testaDecrementoEnd()
{
    cout << "Testando o decremento do iterador end()" << endl;
    MyList2<int> l1;

    for (int i = 0; i < 6; i++)
    {
        printReverse(l1);
        l1.push_back(i);
    }

    //e se criarmos um iterador para end() e inserirmos algo antes do end(), o decremento
    //vai acessar o novo valor corretamente?
    MyList2<int>::iterator it = l1.end();
    l1.insert(6, l1.end());
    it--;
    cout << "Isso deve imprimir o numero 6...: " << *it << endl;
    it--;
    cout << "Isso deve imprimir o numero 5...: " << *it << endl;
}

/*
O arquivo de entrada contem um tipo de teste 
A primeira linha do arquivo contem um caractere. 
Se o caractere for 'S', entao o arquivo representa testes com a funcao size e empty. 
Se for 'D' significa testes com o decremento do iterador apontando para end(). 
Se for 'N' significa testes com a funcao nao-membro reverse.
Se nao for nenhum dos anteriores, entao representa testes com iteradores
*/

int main()
{
    MyList2<string> v; //Realiza testes com strings...
    char tipoTeste;
    cin >> tipoTeste;

    if (tipoTeste == 'N')
    { //testes com funcao reverse
        cout << "Testes com reverse (nao-membro)" << endl;
        testaReverse();
    }
    else if (tipoTeste == 'D')
    { //testes com decremento do end()s
        cout << "Testes com decremento do iterador end" << endl;
        testaDecrementoEnd();
    }
    else if (tipoTeste == 'S')
    { //testes com size(), empty()
        testesSizeEmpty();
    }
    else
    {
        cout << "Testes com iteradores" << endl;
        testaIteradores();
    }
}