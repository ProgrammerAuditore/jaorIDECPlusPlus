// --------------------------------------------------------------------------------------------------
// IDE_C++
// Editor para Lenguaje C++
// Autor y Derechos Reservados:JAOR
// IDE_GLOBALES.hpp
// Archivo de Definición de Variables Globales
// --------------------------------------------------------------------------------------------------

// Incluye las variables para el Menu Archivo
#include "IDE_GBL_MENUARCHIVO.hpp"

// Incluye las variables para el Menu Edición
#include "IDE_GBL_MENUEDICION.hpp"

// Incluye las variables para el Menu Buscar
#include "IDE_GBL_MENUBUSCAR.hpp"

// Incluye las variables para el Menu Crear
#include "IDE_GBL_MENUCREAR.hpp"

// Cambiar a constantes
const string          gstrAplicacion="IDE C++";           // Para el Nombre de la Aplicación
const string          gstrVersion="save.me";  // Para la Versión a desplegar

// Dejaremos Globales las Variables Principales
GtkWidget *window;         // La ventana principal
GtkWidget *vbox;           // El Contenedor

// Menu Principal
GtkWidget *menuBarra;      // El Contenedor del Menu

// Barra de Estado
GtkWidget     *eventstatusbox;
GtkWidget     *statusbar;
gint           statusbarId;

// Barra de Herramientas
GtkWidget     *toolbarBox;
GtkWidget     *toolbar;

// Editor de Texto con su Scroll
GtkWidget            *scrollEditor,               // El Scroll para el Editor de Texto
                     *textviewEditor;             // El Editor
GtkTextBuffer        *bufferEditor;               // Variable para el Buffer de Texto
PangoFontDescription *fontEditor;                 // Para controlar la Fuente
string                gstrFont="Monospace 12";    // El Nombre de la Fuente

// Variable Global de Error
bool                  gbError=false;              // Variable para Control de Errores

// AVANCE
// Ventana de Compilación
GtkWidget            *scrollCompilacion,          // El Scroll para Ventana de Compilación
                     *textviewCompilacion;        // El Editor para Ventana de Compilación
GtkTextBuffer        *bufferCompilacion;          // Variable para el Buffer de Compilación
