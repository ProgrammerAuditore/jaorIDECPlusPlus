// Incluye las Librerías
#include <iostream>
#include <string>

// Declara el nombre de espacio
using namespace std;

// Función
int main ()
{

   // Variables de Cadena
   string str1 = "Hello";
   string str2 = "World";
   string str3;
   
   // Variable para la longitud
   int len ; 

   // Despliega el valor de las cadenas
   cout << "str1 :" << str1 << endl;
   cout << "str2 :" << str2 << endl;   
   
   // Copia str1 en str3
   str3 = str1;
   
   // Despliega 
   cout << "str3 :" << str3 << endl;

   // Concatena str1 con str2
   str3 = str1 + str2;

   // Despliega la concatenación
   cout << "str1 + str2 :" << str3 << endl;
   
   // Obtiene la longitud destr3 después de la concatenación
   len = str3.size();
   
   // Despliega
   cout << "str3.size() :" << len << endl;

   // Finaliza retornando 0
   return 0;

}