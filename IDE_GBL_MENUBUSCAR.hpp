// --------------------------------------------------------------------------------------------------
// IDE_C++
// Editor para Lenguaje C++
// Autor y Derechos Reservados:JAOR
// IDE_GBL_MENUBUSCAR.hpp
// Variables Globales para Menu Buscar
// --------------------------------------------------------------------------------------------------

// Menú Edición
GtkWidget *menuBuscar;      // El Menu Buscar
GtkWidget *opcBuscar;

GtkWidget *opcBuscarEncontrar;
GtkWidget *boxBuscarEncontrar;
GtkWidget *icoBuscarEncontrar;
GtkWidget *lblBuscarEncontrar;

GtkWidget *opcBuscarReemplazar;
GtkWidget *boxBuscarReemplazar;
GtkWidget *icoBuscarReemplazar;
GtkWidget *lblBuscarReemplazar;


// Barra de Herramientas Edicion
GtkToolItem   *itemBuscarEncontrar,
              *itemBuscarReemplazar,
              *itemSeparador5;


// Se pasan a globales
GtkWidget  *iconBuscarEncontrar,
           *iconBuscarReemplazar;

// Se agregan para imagenes gray
GtkWidget  *iconBuscarEncontrarGray,
           *iconBuscarReemplazarGray;


// Acelerador
GtkAccelGroup *accel_group_buscar = NULL;

// Variables
GtkWidget *wndEncontrar;   // El Objeto para la Nueva Ventana
GtkWidget *chkTextCase;    // Para indicar que diferencíe en Mayúsculas y Minúsculas
GtkWidget *chkTextSelect;  // Para indicar búsqueda en texto seleccionado

// AVANCE
GtkWidget *chkTextReplace; // Texto que remplaza al texto buscado
GtkWidget *txtReplace;     // Texto de Replace
