// ---------------------------------------------------------------------------------------------------
// IDE_C++.cpp
// Editor para Lenguaje C++
// Autor y Derechos Reservados:JAOR
// ---------------------------------------------------------------------------------------------------

// Incluimos Librerías
#include <gtk/gtk.h>             // La librería Gtk
#include <string>                // Manejo de Cadenas
#include <gdk/gdkkeysyms.h>      // Constantes para el control del Teclado
#include <vector>                // Clase Vector

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

  // Ejecutamos el Loop Principal
  gtk_main();

  // Retornamos 0
  return 0;

}
