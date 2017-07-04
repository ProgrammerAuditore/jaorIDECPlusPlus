// --------------------------------------------------------------------------------------------------
// IDE_C++
// Editor para Lenguaje C++
// Autor y Derechos Reservados:JAOR
// IDE_GBL_MENUARCHIVO.hpp
// Variables Globales para Menu Archivo
// --------------------------------------------------------------------------------------------------

// Menu Archivo
GtkWidget *menuArchivo;    // El Menu Archivo
GtkWidget *opcArchivo;

GtkWidget *opcArchivoNuevo;
GtkWidget *boxArchivoNuevo;
GtkWidget *icoArchivoNuevo;
GtkWidget *lblArchivoNuevo;
GtkWidget *separador1;

GtkWidget *opcArchivoAbrir;
GtkWidget *boxArchivoAbrir;
GtkWidget *icoArchivoAbrir;
GtkWidget *lblArchivoAbrir;
GtkWidget *separador2;

GtkWidget *opcArchivoGuardar;
GtkWidget *boxArchivoGuardar;
GtkWidget *icoArchivoGuardar;
GtkWidget *lblArchivoGuardar;
GtkWidget *opcArchivoGuardarComo;
GtkWidget *boxArchivoGuardarComo;
GtkWidget *icoArchivoGuardarComo;
GtkWidget *lblArchivoGuardarComo;
GtkWidget *separador3;

GtkWidget *opcArchivoCerrar;
GtkWidget *boxArchivoCerrar;
GtkWidget *icoArchivoCerrar;
GtkWidget *lblArchivoCerrar;
GtkWidget *separador4;

GtkWidget *opcArchivoSalir;
GtkWidget *boxArchivoSalir;
GtkWidget *icoArchivoSalir;
GtkWidget *lblArchivoSalir;

// Barra de Herramientas Archivo
GtkToolItem   *itemNuevo,
              *itemAbrir,
              *itemGuardar,
              *itemGuardarComo,
              *itemSeparador1,
              *itemSeparador2;

// Se pasan a globales
GtkWidget  *iconNuevo,
           *iconAbrir,
           *iconGuardar,
           *iconGuardarComo;
// Se agregan para las imagenes gray
GtkWidget  *iconNuevoGray,
           *iconAbrirGray,
           *iconGuardarGray,
           *iconGuardarComoGray;

// Acelerador
GtkAccelGroup *accel_group_archivo = NULL;

// Variables para el Archivo Editado
string                gstrArchivo="";              // Para el Nombre del Archivo
// AVANCE
string                gstrExecutable="";           // Para el archivo que se genera al Compilar
string                gstrRuta="";                 // Para la Ruta del Archivo
bool                  gbArchivoGuardado=false;     // Para saber si el archivo ya fue guardado
int                   gintArchivoModificado=0;     // Para saber cuando un archivo se modifico
gint           gIntRow, gIntCol;                   // Renglon y Columna Desplegadas en el Editor
vector<string> gvecReservadas;                     // Vector con palabras reservadas
vector<string> gvecEspeciales;                     // Vector con caracteres especiales
string         gstrReservadasColor="green";        // Color de las palabras reservadas
string         gstrEspecialesColor="red";          // Color de los Números
string         gstrComentariosColor="blue";        // Color de los Comentarios
gint           gIntRowPegadoTexto=-1;              // Para controlar el pegado de texto
gint           gIntIndent=0;                       // Los Espacios de Indent
bool           gBoolProcesando=false;              // Evitar el Ciclo Infinito
char           gStrSpaces[80];                     // El Vector para Insertar los Espacios
