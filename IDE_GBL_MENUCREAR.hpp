// --------------------------------------------------------------------------------------------------
// IDE_C++
// Editor para Lenguaje C++
// Autor y Derechos Reservados:JAOR
// IDE_GBL_MENUCREAR.hpp
// Variables Globales para Menu Build
// --------------------------------------------------------------------------------------------------

// Menú Crear
GtkWidget *menuCrear;           // El Menu Crear
GtkWidget *opcCrear;

GtkWidget *opcCrearCompilar;
GtkWidget *boxCrearCompilar;
GtkWidget *icoCrearCompilar;
GtkWidget *lblCrearCompilar;

GtkWidget *opcCrearEjecutar;
GtkWidget *boxCrearEjecutar;
GtkWidget *icoCrearEjecutar;
GtkWidget *lblCrearEjecutar;

GtkWidget *opcCrearCompilarEjecutar;
GtkWidget *boxCrearCompilarEjecutar;
GtkWidget *icoCrearCompilarEjecutar;
GtkWidget *lblCrearCompilarEjecutar;


// Barra de Herramientas Edicion
GtkToolItem   *itemCrearCompilar,
              *itemCrearEjecutar,
              *itemCrearCompilarEjecutar,
              *itemSeparador6;


// Variables para los iconos
GtkWidget  *iconCrearCompilar,
           *iconCrearEjecutar,
           *iconCrearCompilarEjecutar,
           *iconCrearCompilarGray,
           *iconCrearEjecutarGray,
           *iconCrearCompilarEjecutarGray;


// Acelerador
GtkAccelGroup *accel_group_crear = NULL;
