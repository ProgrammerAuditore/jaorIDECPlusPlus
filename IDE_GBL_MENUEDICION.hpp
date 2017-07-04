// --------------------------------------------------------------------------------------------------
// IDE_C++
// Editor para Lenguaje C++
// Autor y Derechos Reservados:JAOR
// IDE_GBL_MENUEDICION.hpp
// Variables Globales para Menu Edución
// --------------------------------------------------------------------------------------------------

// Menú Edición
GtkWidget *menuEdicion;      // El Menu Edición
GtkWidget *opcEdicion;

GtkWidget *opcEdicionCortar;
GtkWidget *boxEdicionCortar;
GtkWidget *icoEdicionCortar;
GtkWidget *lblEdicionCortar;

GtkWidget *opcEdicionCopiar;
GtkWidget *boxEdicionCopiar;
GtkWidget *icoEdicionCopiar;
GtkWidget *lblEdicionCopiar;

GtkWidget *opcEdicionPegar;
GtkWidget *boxEdicionPegar;
GtkWidget *icoEdicionPegar;
GtkWidget *lblEdicionPegar;
GtkWidget *separador5;

GtkWidget *opcEdicionUndo;
GtkWidget *boxEdicionUndo;
GtkWidget *icoEdicionUndo;
GtkWidget *lblEdicionUndo;

GtkWidget *opcEdicionRedo;
GtkWidget *boxEdicionRedo;
GtkWidget *icoEdicionRedo;
GtkWidget *lblEdicionRedo;

GtkWidget *opcEdicionUndoClear;
GtkWidget *boxEdicionUndoClear;
GtkWidget *icoEdicionUndoClear;
GtkWidget *lblEdicionUndoClear;
GtkWidget *separador6;


// Barra de Herramientas Edicion
GtkToolItem   *itemEdicionCortar,
              *itemEdicionCopiar,
              *itemEdicionPegar,
              *itemSeparador3;

GtkToolItem   *itemEdicionUndo,
              *itemEdicionRedo,
              *itemSeparador4;


// Se pasan a globales
GtkWidget  *iconEdicionCortar,
           *iconEdicionCopiar,
           *iconEdicionPegar;

// Se agregan para imagenes gray
GtkWidget  *iconEdicionCortarGray,
           *iconEdicionCopiarGray,
           *iconEdicionPegarGray;

GtkWidget  *iconEdicionUndo,
           *iconEdicionRedo,
           *iconEdicionUndoGray,
           *iconEdicionRedoGray;


// Acelerador
GtkAccelGroup *accel_group_edicion = NULL;

// Variable para el control del Buffer del Undo y el Redo
vector<string> gvecUndoRedo;               // Vector del Undo-Redo
vector<int>    gvecCursorCol;
vector<int>    gvecCursorRow;
int            gintUndoRedoIndice=-1;      // Indice del Undo-Redo
string         gstrEmpty;
bool           gbTextoInsertado=false;
