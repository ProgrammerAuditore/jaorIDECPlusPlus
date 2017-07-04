// ---------------------------------------------------------------------------------------------------
// IDE_C++.cpp
// Editor para Lenguaje C++
// Autor y Derechos Reservados:JAOR
// ---------------------------------------------------------------------------------------------------

// Incluimos la Librería
#include <gtk/gtk.h>
#include <string>

// Estableciendo el Nombre de Espacio
using namespace std;

// Incluimos las Variables Globales
#include "IDE_GLOBALES.hpp"

// Incluimos las Funciones
#include "IDE_FUNCIONES.hpp"

// Función Principal
int main(int argc, char *argv[])
{

  // Iniciamos la Librería
  gtk_init(&argc, &argv);

  // Inicializamos la Aplicacion
  FnAppInicializa();

  // Establece el Control de Señales
  FnAppSenales();

  // Ejecutamos el Loop Principal
  gtk_main();

  // Retornamos 0
  return 0;

}
// Agregar este comentario