
// Demonstrando downcasting e o RTTI
// NOTA: Para esse exemplo executar em Visual C++ .NET,
// você precisa ativar o RTTI (Run-Time Type Info) para o projeto.
#include <iostream>
using namespace std;


#include <iomanip>
using std::setprecision;
  
#include <vector>
using std::vector;

#include <typeinfo>

// inclui definições de classes na hierarquia Employee
#include "Employee.h"
#include "SalariedEmployee.h" 
#include "HourlyEmployee.h"
#include "CommissionEmployee.h"  
#include "BasePlusCommissionEmployee.h" 

int main()
{
   // configura a formatação de saída de ponto flutuante
   cout << fixed << setprecision( 2 ); 
   
   // cria um vector a partir dos quatro ponteiros da classe básica
   vector < Employee * > employees( 4 );

   // inicializa vector com vários tipos de Employees
   employees[ 0 ] = new SalariedEmployee(            
      "John", "Smith", "111-11-1111", 800 );         
   employees[ 1 ] = new HourlyEmployee(              
      "Karen", "Price", "222-22-2222", 16.75, 40 );  
   employees[ 2 ] = new CommissionEmployee(          
      "Sue", "Jones", "333-33-3333", 10000, .06 );   
   employees[ 3 ] = new BasePlusCommissionEmployee(  
      "Bob", "Lewis", "444-44-4444", 5000, .04, 300 );

   const type_info& tipoEmpregado = typeid(Employee);
   const type_info& tipoEmpregadoAssalariado = typeid(*employees[0]);
   const type_info& tipoEmpregadoComissionado = typeid(CommissionEmployee);
   cout << tipoEmpregado.name() << endl;
   cout << tipoEmpregadoAssalariado.name() << endl;
   cout << tipoEmpregadoComissionado.name() << endl;
   
   // processa polimorficamente cada elemento no vector employees
   for ( size_t i = 0; i < employees.size(); i++ ) 
   {
        Employee * emp = employees[i];
        if (typeid(*emp) == tipoEmpregadoAssalariado) {
            SalariedEmployee * semp = dynamic_cast<SalariedEmployee *>(emp);
            semp->print(); cout << endl;
        } else if (typeid(*emp) == tipoEmpregadoComissionado) {
            CommissionEmployee * cemp = dynamic_cast<CommissionEmployee *>(emp);
            cemp->print(); cout << endl;
        }
    }  
      
      
   // libera objetos apontados pelos elementos do vector
   for ( size_t j = 0; j < employees.size(); j++ ) 
   {
      // gera saída do nome de classe                
      cout << "deleting object of "                  
         << typeid( *employees[ j ] ).name() << endl;

      delete employees[ j ];
   } // fim do for
   
   return 0;
} // fim de main

