/*********************************************************************

  Filename:  dyncast.cpp
  Compiler:  Borland C++     Version 5.1      Summer 1997
  Ira Pohl  Copyright May 1997
 
   Normally a safe cast that is portable
   A supplemental example showing the use of dynamic_cast
   See p 347 section 10.9 of Object-Oriented Programming Using C++, 2nd Edition
   See p 95 section 12.5 of C++ Distilled
   See p 341 section 9.9 of C++ for Fortran Programmers
***************************************************************/

#include <iostream>

using namespace std;

class A {
public:
    virtual void print()const {cout << " A\n";}
};

class B {
public:
    virtual void print()const {cout << " B\n";}
};

class C: public A, public B {
public:
    void print()const {cout << " C\n";}
};


int main()
{

    A* a = new A;
    B* b = new B;
    C* c = new C;

    a -> print(); b -> print(); c -> print();
    b = dynamic_cast< B*>(a);  //fails
    if (b)  
       b -> print();  
    else 
       cout << "no B\n";
    a = c;
    a -> print(); //C prints
    b = dynamic_cast< B*>(a);  //succeeds
    if (b)
       b -> print();  
    else 
       cout << "no B\n";
}
