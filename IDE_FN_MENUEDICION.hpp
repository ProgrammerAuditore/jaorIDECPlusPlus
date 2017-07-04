// --------------------------------------------------------------------------------------------------
// IDE C++
// Editor para Lenguaje C++
// Autor y Derechos Reservados:JAOR
// IDE_FN_MENUEDICION.hpp
// Archivo Header de Funciones del Menu Edicion
// --------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------
// Funciones y Variables Externas
// --------------------------------------------------------------------------------------------------

// Función para desactivar o activar una opción del Menu
extern void FnMenuOpcionOnOff(GtkWidget *xOpcion,bool OnOff);

// Función para crear Items de Menu
extern void FnCreaItemDeMenu(GtkWidget  **xOpcion,
                      GtkWidget  **bOpcion,
                      GtkWidget  **iOpcion,
                      GtkWidget  **lOpcion,
                      const char *iconName,
                      const char *opcName);


// --------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------
// Prototipo de Funciones
// --------------------------------------------------------------------------------------------------

// Menu
void FnAppMenuEdicion();       // Construye el Menu

// Función para crear las opciones correspondiente a Edicion
void FnBarraMenuEdicion();

// Corta el Texto y lo envia al ClipBoard
void FnEdicionCortar(GtkWidget *cortar);

// Copia el Texto al Clipboard
void FnEdicionCopiar(GtkWidget *copiar);

// Inserta el texto desde el ClipBoard
void FnEdicionPegar(GtkWidget *pegar);

// Funcion para las Señales
void FnSenalesMenuEdicion();

// Función para controlar la tecla presionada
static gboolean FnTextViewKeyPress(GtkWidget *xWidget, GdkEventKey *event);

// Función para grabar en el Undo-Redo
void FnBufferUndoRedo();

// Función para realizar Undo
void FnEdicionUndo(GtkWidget *undo);

// Función para relizar Redo
void FnEdicionRedo(GtkWidget *redo);

// Función para realizar el Clear del Undo-Credo
void FnEdicionClearUndoRedo(GtkWidget *clear_undo_redo);

// Está función obtiene el indent en espacios de la Línea Actual; gIntRow
int FnIntIndentLineaActual();

// --------------------------------------------------------------------------------------------------
// Fin de Prototipo de Funciones
// --------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------
// Funciones
// --------------------------------------------------------------------------------------------------

// Función para Crear el Menu Principal
void FnAppMenuEdicion()
{

  // Creamos el Menu Edición
  menuEdicion   = gtk_menu_new();

  // Creamos las Opciones de Edicion
  opcEdicion            = gtk_menu_item_new_with_mnemonic("_Edicion");


  // Crea el Item de Edicion Cortar
  FnCreaItemDeMenu(&opcEdicionCortar,&boxEdicionCortar,&icoEdicionCortar,
                   &lblEdicionCortar,"edit-cut","Cortar");


  // Crea el Item de Edicion Copiar
  FnCreaItemDeMenu(&opcEdicionCopiar,&boxEdicionCopiar,&icoEdicionCopiar,
                   &lblEdicionCopiar,"edit-copy","Copiar");


  // Crea el Item de Edicion Pegar
  FnCreaItemDeMenu(&opcEdicionPegar,&boxEdicionPegar,&icoEdicionPegar,
                   &lblEdicionPegar,"edit-paste","Pegar");


  // El Separador de Opciones
  separador5            = gtk_separator_menu_item_new();

  // Crea el Item de Edicion Undo
  FnCreaItemDeMenu(&opcEdicionUndo,&boxEdicionUndo,&icoEdicionUndo,
                   &lblEdicionUndo,"edit-undo","Deshacer");


  // Crea el Item de Edicion Redo
  FnCreaItemDeMenu(&opcEdicionRedo,&boxEdicionRedo,&icoEdicionRedo,
                   &lblEdicionRedo,"edit-redo","Rehacer");


  // Crea el Item de Edicion Undo Clear
  FnCreaItemDeMenu(&opcEdicionUndoClear,&boxEdicionUndoClear,&icoEdicionUndoClear,
                   &lblEdicionUndoClear,"edit-clear","Limpiar Deshacer");



  // Establecemos el Item File como una opción de la Barra de Menu
  gtk_menu_shell_append(GTK_MENU_SHELL(menuBarra), opcEdicion);


  // Agregamos la opcion del Menu Edición
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(opcEdicion), menuEdicion);


  // Establecemos las opciones del Menu
  gtk_menu_shell_append(GTK_MENU_SHELL(menuEdicion), opcEdicionCortar);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuEdicion), opcEdicionCopiar);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuEdicion), opcEdicionPegar);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuEdicion), separador5);

  gtk_menu_shell_append(GTK_MENU_SHELL(menuEdicion), opcEdicionUndo);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuEdicion), opcEdicionRedo);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuEdicion), opcEdicionUndoClear);


  // Crea el Acelerador
  accel_group_edicion = gtk_accel_group_new();
  gtk_window_add_accel_group(GTK_WINDOW(window), accel_group_edicion);


  // Agregamos un Acelerador a las Opciones
  gtk_widget_add_accelerator(opcEdicionCortar,"activate",accel_group_edicion,
                             GDK_KEY_X,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator(opcEdicionCopiar,"activate",accel_group_edicion,
                             GDK_KEY_C,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator(opcEdicionPegar,"activate",accel_group_edicion,
                             GDK_KEY_V,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);

  gtk_widget_add_accelerator(opcEdicionUndo,"activate",accel_group_edicion,
                             GDK_KEY_Z,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator(opcEdicionRedo,"activate",accel_group_edicion,
                             GDK_KEY_Y,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);

  // Desactivamos las opciones de Guardar, Guardar Como y Cerrar del Menu Archivo
  FnMenuOpcionOnOff(opcEdicionCortar,FALSE);
  FnMenuOpcionOnOff(opcEdicionCopiar,FALSE);
  FnMenuOpcionOnOff(opcEdicionPegar,FALSE);

  FnMenuOpcionOnOff(opcEdicionUndo,FALSE);
  FnMenuOpcionOnOff(opcEdicionRedo,FALSE);
  FnMenuOpcionOnOff(opcEdicionUndoClear,FALSE);

}

// Función para crear la Barra de Herramientas
void FnBarraMenuEdicion()
{

  // Cargamos la imagen que deseamos
  iconEdicionCortar       = gtk_image_new_from_file ("edit-cut.png");
  iconEdicionCopiar       = gtk_image_new_from_file ("edit-copy.png");
  iconEdicionPegar        = gtk_image_new_from_file ("edit-paste.png");

  // Se agregan imagenes gray
  iconEdicionCortarGray   = gtk_image_new_from_file ("edit-cut-gray.png");
  iconEdicionCopiarGray   = gtk_image_new_from_file ("edit-copy-gray.png");
  iconEdicionPegarGray    = gtk_image_new_from_file ("edit-paste-gray.png");

  // Cargamos la imagen que deseamos
  iconEdicionUndo       = gtk_image_new_from_file ("edit-undo.png");
  iconEdicionRedo       = gtk_image_new_from_file ("edit-redo.png");

  // Se agregan imagenes gray
  iconEdicionUndoGray   = gtk_image_new_from_file ("edit-undo-gray.png");
  iconEdicionRedoGray   = gtk_image_new_from_file ("edit-redo-gray.png");

  // Hace a los iconos permanentes
  g_object_ref_sink(G_OBJECT(iconEdicionCortar));
  g_object_ref_sink(G_OBJECT(iconEdicionCortarGray));
  g_object_ref_sink(G_OBJECT(iconEdicionCopiar));
  g_object_ref_sink(G_OBJECT(iconEdicionCopiarGray));
  g_object_ref_sink(G_OBJECT(iconEdicionPegar));
  g_object_ref_sink(G_OBJECT(iconEdicionPegarGray));

  g_object_ref_sink(G_OBJECT(iconEdicionUndo));
  g_object_ref_sink(G_OBJECT(iconEdicionUndoGray));
  g_object_ref_sink(G_OBJECT(iconEdicionRedo));
  g_object_ref_sink(G_OBJECT(iconEdicionRedoGray));

  // Creamos los Item
  itemEdicionCortar = gtk_tool_button_new(iconEdicionCortar,NULL);
  gtk_tool_item_set_tooltip_text (itemEdicionCortar,"Cortar Texto");

  itemEdicionCopiar = gtk_tool_button_new(iconEdicionCopiar,NULL);
  gtk_tool_item_set_tooltip_text (itemEdicionCopiar,"Copiar Texto");

  itemEdicionPegar  = gtk_tool_button_new(iconEdicionPegar,NULL);
  gtk_tool_item_set_tooltip_text (itemEdicionPegar,"Pegar Texto");

  // Separador
  itemSeparador3  = gtk_separator_tool_item_new ();

  // Creamos los Item
  itemEdicionUndo = gtk_tool_button_new(iconEdicionUndo,NULL);
  gtk_tool_item_set_tooltip_text (itemEdicionUndo,"Deshacer");

  itemEdicionRedo = gtk_tool_button_new(iconEdicionRedo,NULL);
  gtk_tool_item_set_tooltip_text (itemEdicionRedo,"Rehacer");

  // Separador
  itemSeparador4  = gtk_separator_tool_item_new ();


  // Agrega los Item de Cortar, Copiar y Pegar
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemSeparador3, 6);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemEdicionCortar, 7);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemEdicionCopiar, 8);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemEdicionPegar, 9);

  // Agrega los items de Undo y Redo
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemSeparador4, 10);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemEdicionUndo, 11);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemEdicionRedo, 12);

  // Activa-Desactiva las opciones e item's correspondientes
  FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionCortar),FALSE);
  FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionCopiar),FALSE);
  FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionPegar),FALSE);
  gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionCortar),iconEdicionCortarGray);
  gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionCopiar),iconEdicionCopiarGray);
  gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionPegar),iconEdicionPegarGray);
  FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionUndo),FALSE);
  FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionRedo),FALSE);
  gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionUndo),iconEdicionUndoGray);
  gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionRedo),iconEdicionRedoGray);

  // Se actualiza la barra de herramientas
  gtk_widget_show_all(GTK_WIDGET(toolbar));

}

// Corta el Texto y lo envía al Clipboard
void FnEdicionCortar(GtkWidget *cortar)
{
    // Guarda en el buffer antes de cortar
    FnBufferUndoRedo();

    GtkClipboard *clipboard = gtk_clipboard_get (GDK_SELECTION_CLIPBOARD);
    gtk_text_buffer_cut_clipboard (bufferEditor, clipboard, TRUE);

    // Activa Undo
    FnMenuOpcionOnOff(opcEdicionUndo,TRUE);
    FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionUndo),TRUE);

    // Cambia la imagen
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionUndo),iconEdicionUndo);

    // Se actualiza la barra de herramientas
    gtk_widget_show_all(GTK_WIDGET(toolbar));

}

// Copia el Texto al ClipBoard
void FnEdicionCopiar(GtkWidget *copiar)
{
    GtkClipboard *clipboard = gtk_clipboard_get (GDK_SELECTION_CLIPBOARD);
    gtk_text_buffer_copy_clipboard (bufferEditor, clipboard);
}

// Inserta el Texto desde el Clipoard
void FnEdicionPegar(GtkWidget *pegar)
{

    // Guarda en el buffer antes de pegar
    FnBufferUndoRedo();

    GtkClipboard *clipboard = gtk_clipboard_get (GDK_SELECTION_CLIPBOARD);
    gtk_text_buffer_paste_clipboard (bufferEditor, clipboard, NULL, TRUE);

    // Activa bandera de que sea realizado un pegado
    gIntRowPegadoTexto=gIntRow;

    // Activa Undo
    FnMenuOpcionOnOff(opcEdicionUndo,TRUE);
    FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionUndo),TRUE);

    // Cambia la imagen
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionUndo),iconEdicionUndo);

    // Se actualiza la barra de herramientas
    gtk_widget_show_all(GTK_WIDGET(toolbar));

}

// Señales del Menu Edición
void FnSenalesMenuEdicion()
{

    // Controla las Señales del Menu y Barra de Edicion
    // Cortar, Copiar y Pegar
    g_signal_connect (G_OBJECT (opcEdicionCortar), "activate",G_CALLBACK (FnEdicionCortar), NULL);
    g_signal_connect (G_OBJECT (itemEdicionCortar), "clicked",G_CALLBACK (FnEdicionCortar), NULL);
    g_signal_connect (G_OBJECT (opcEdicionCopiar), "activate",G_CALLBACK (FnEdicionCopiar), NULL);
    g_signal_connect (G_OBJECT (itemEdicionCopiar), "clicked",G_CALLBACK (FnEdicionCopiar), NULL);
    g_signal_connect (G_OBJECT (opcEdicionPegar),  "activate",G_CALLBACK (FnEdicionPegar) , NULL);
    g_signal_connect (G_OBJECT (itemEdicionPegar),  "clicked",G_CALLBACK (FnEdicionPegar) , NULL);

    // Undo y Redo
    g_signal_connect (G_OBJECT (textviewEditor), "key-press-event",G_CALLBACK(FnTextViewKeyPress), NULL);
    g_signal_connect (G_OBJECT (opcEdicionUndo),  "activate",G_CALLBACK (FnEdicionUndo) , NULL);
    g_signal_connect (G_OBJECT (itemEdicionUndo),  "clicked",G_CALLBACK (FnEdicionUndo) , NULL);
    g_signal_connect (G_OBJECT (opcEdicionRedo),  "activate",G_CALLBACK (FnEdicionRedo) , NULL);
    g_signal_connect (G_OBJECT (itemEdicionRedo),  "clicked",G_CALLBACK (FnEdicionRedo) , NULL);

    // Clear Undo-Redo
    g_signal_connect (G_OBJECT (opcEdicionUndoClear),"activate",G_CALLBACK (FnEdicionClearUndoRedo), NULL);

}

// Función para controlar la tecla presionada y guardar el buffer cuando hay Enter
static gboolean FnTextViewKeyPress(GtkWidget *xWidget, GdkEventKey *event)
{

   // Declaración de Variables para busqueda de Texto
   GtkTextIter start_sel, end_sel;       // Para el inicio y final de Selección
   GtkTextIter start_find, end_find;     // Para inicio y final de palabra encontrada
   GtkTextIter start_match, end_match;   // Para inicio y final de Match
   gboolean selected;                    // Seleccionado
   gchar *text;                          // Para el texto


    //g_print ("Type:%d State:%d Keyval:%d \n",event->type,event->state,event->keyval);
    // Verifica que el Evento sea KeyPress                     ojojojojo
    if (event->type == GDK_KEY_PRESS && event->state!=33554436 && event->state!=33554452)
    {

        // Verifica que sea enter y caracteres validos
        if (event->keyval == GDK_KEY_Return || event->keyval == GDK_KEY_Delete || event->keyval == GDK_KEY_BackSpace || event->keyval < 125)
        {

            // Activa bandera de Texto Insertado
            gbTextoInsertado=true;

            // Verifica que se haya presionado Return para obtener el INDENT
            if (event->keyval == GDK_KEY_Return)
            {
               // Obtiene el Indent de Espacios
               gIntIndent= FnIntIndentLineaActual();

            }

            // Verifica
            if (event->keyval == GDK_KEY_Return || event->keyval == GDK_KEY_BackSpace
                                                || event->keyval == GDK_KEY_Delete)

               // Llama a la función de Buffer
               FnBufferUndoRedo();

            // Desactiva Redo al entrar cualquier tecla
            FnMenuOpcionOnOff(opcEdicionRedo,FALSE);
            FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionRedo),FALSE);

            // Activa Undo al entrar cualquier tecla
            FnMenuOpcionOnOff(opcEdicionUndo,TRUE);
            FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionUndo),TRUE);
            FnMenuOpcionOnOff(opcEdicionUndoClear,TRUE);


            // Cambia la imagen
            gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionUndo),iconEdicionUndo);
            gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionRedo),iconEdicionRedoGray);

            // Verifica si está vació el buffer del Undo para agregar empty
            if (gintUndoRedoIndice==-1)
            {

               // Incrementa el Indice
               gintUndoRedoIndice++;

               // Agrega el Empty
               gvecUndoRedo.push_back(gstrEmpty);
               gvecCursorCol.push_back(0);
               gvecCursorRow.push_back(0);

            }
        }
    }


    // Incluyo el código para Buscar Texto en el
    // Verifica si se ha presionado una tecla
    if ((event->type == GDK_KEY_PRESS) &&
       (event->state & GDK_CONTROL_MASK))
    {

       // Verifica cual tecla se ha presionado
       switch (event->keyval)
       {

         case GDK_KEY_e :
         case GDK_KEY_E :

           // Obtiene el Texto Seleccionado
           selected = gtk_text_buffer_get_selection_bounds(bufferEditor,&start_sel, &end_sel);

           // Verifica si hay texto seleccionado
           if (selected)
           {
              // Obtiene los iter al inicio y fin del Texto en el buffer
              gtk_text_buffer_get_start_iter(bufferEditor, &start_find);
              gtk_text_buffer_get_end_iter(bufferEditor, &end_find);

              // Remueve el Tag si existe en el texto
              gtk_text_buffer_remove_tag_by_name(bufferEditor, "green_bg",&start_find, &end_find);

              // Obtiene el texto Seleccionado
              text = (gchar *) gtk_text_buffer_get_text(bufferEditor, &start_sel,&end_sel, FALSE);

              // Ciclo para ir seleccionando el texto en todo el contenido del buffer
              // Busca text desde start_find, y obtiene su inicio y final en start_match y end_match
              while (gtk_text_iter_forward_search(&start_find, text,
                                                   GtkTextSearchFlags(GTK_TEXT_SEARCH_TEXT_ONLY |
                                                                      GTK_TEXT_SEARCH_VISIBLE_ONLY |
                                                                      GTK_TEXT_SEARCH_CASE_INSENSITIVE),
                                                  &start_match, &end_match, NULL))
              {
                  // Aplica el Tag al buffer, en donde encotré el texto; start_match y end_match
                  gtk_text_buffer_apply_tag_by_name(bufferEditor, "green_bg",&start_match, &end_match);

                  // Obtiene el desplazamiento alel final del match
                  gint offset = gtk_text_iter_get_offset(&end_match);

                  // Obtiene el nuevo start_find, a partir del offset
                  gtk_text_buffer_get_iter_at_offset(bufferEditor,&start_find, offset);
              }

              // Libera la variable del texto
              g_free(text);
           }
           break;

         case GDK_KEY_l:
         case GDK_KEY_L:

           // Obtiene el Inicio y Final del Buffer
           gtk_text_buffer_get_start_iter(bufferEditor, &start_find);
           gtk_text_buffer_get_end_iter(bufferEditor, &end_find);

           // Remueve el Tag del Buffer
           gtk_text_buffer_remove_tag_by_name(bufferEditor, "green_bg",&start_find, &end_find);
           break;
       }
    }


    // Para que no se pierda la tecla presionada debe ser FALSE
    return FALSE;
}

// Función para grabar en el Undo-Redo
void FnBufferUndoRedo()
{
   // Variable para mandar a Undo
   string strUndo;

   // Definición de Variables
   GtkTextIter iterInicio,iterFinal;  // Ubicación
   gchar      *strTexto;              // Obtener el Texto
   GtkTextIter iter;                  // Para obtener columna y renglon
   gint row, col;                     // Renglon y Columna

    // Obtiene el Inicio y Final del Buffer
   gtk_text_buffer_get_start_iter (bufferEditor, &iterInicio);
   gtk_text_buffer_get_end_iter   (bufferEditor, &iterFinal);

   // Obtiene el Texto del Buffer
   strTexto = gtk_text_buffer_get_text (bufferEditor, &iterInicio, &iterFinal, FALSE);

   // Desplegando el Texto
   strUndo = strTexto;

   // Agregando al vector de Undo
   gvecUndoRedo.push_back(strUndo);
   gintUndoRedoIndice=gvecUndoRedo.size()-1;

   // Obtiene la Información de donde está el cursor
   gtk_text_buffer_get_iter_at_mark(bufferEditor,&iter, gtk_text_buffer_get_insert(bufferEditor));

   // Obtiene el Row y la Col y lo almacenamos en el vector
   row = gtk_text_iter_get_line(&iter);
   col = gtk_text_iter_get_line_offset(&iter);
   gvecCursorCol.push_back(col);
   gvecCursorRow.push_back(row);

}

// Función para realizar Undo
void FnEdicionUndo(GtkWidget *undo)
{
   // Variables
   GtkTextIter iter;  // Ubicación

   // Verifica si hubo un texto insertado para agregarlo al final
   if (gbTextoInsertado)
   {

      // Primero guardo lo que hay
      FnBufferUndoRedo();

   }

   // Decremento el Indice
   gintUndoRedoIndice--;

   // Restablece el Buffer Previo
   gtk_text_buffer_set_text (bufferEditor, gvecUndoRedo[gintUndoRedoIndice].c_str(), -1);

   // AVANCE
   // Procesa las lineas pegadas
   for (int iCtaLineas=0; iCtaLineas<gIntRow; iCtaLineas++)
   {
         // Llama a la función
         FnProcesaLinea(iCtaLineas);

   }

   // Obtiene la Posición Inicial del Buffer
   gtk_text_buffer_get_start_iter (bufferEditor, &iter);

   // Establece la posición del cursor
   gtk_text_iter_set_line(&iter,gvecCursorRow[gintUndoRedoIndice]);
   gtk_text_iter_set_line_offset(&iter,gvecCursorCol[gintUndoRedoIndice]);

   // Coloca el Cursor en la posición correspondiente
   gtk_text_buffer_place_cursor (bufferEditor,&iter);


   // Verifica que si llego a -1 entonces desactiva Undo ya que no hay
   if (gintUndoRedoIndice==0)
   {

      // Desactiva la opción de Undo
      FnMenuOpcionOnOff(opcEdicionUndo,FALSE);
      FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionUndo),FALSE);

      // Cambia la imagen
      gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionUndo),iconEdicionUndoGray);

   }

   // Activa la opción de Redo
   FnMenuOpcionOnOff(opcEdicionRedo,TRUE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionRedo),TRUE);
   FnMenuOpcionOnOff(opcEdicionUndoClear,TRUE);

   // Cambia la imagen
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionRedo),iconEdicionRedo);

   // Se actualiza la barra de herramientas
   gtk_widget_show_all(GTK_WIDGET(toolbar));

   // Variable que indica que no se ha introducido un caracter
   gbTextoInsertado=false;
}

// Función para relizar Redo
void FnEdicionRedo(GtkWidget *redo)
{
   // Variables
   GtkTextIter iter;  // Ubicación

   // Me muevo a la siguiente posición en el buffer
   gintUndoRedoIndice++;


   // Restablece el Buffer Siguiente
   gtk_text_buffer_set_text (bufferEditor, gvecUndoRedo[gintUndoRedoIndice].c_str(), -1);

   // AVANCE
   // Procesa las lineas pegadas
   for (int iCtaLineas=0; iCtaLineas<gIntRow; iCtaLineas++)
   {
         // Llama a la función
         FnProcesaLinea(iCtaLineas);

   }

   // Obtiene la Posición Inicial del Buffer
   gtk_text_buffer_get_start_iter (bufferEditor, &iter);

   // Establece la posición del cursor
   gtk_text_iter_set_line(&iter,gvecCursorRow[gintUndoRedoIndice]);
   gtk_text_iter_set_line_offset(&iter,gvecCursorCol[gintUndoRedoIndice]);

   // Coloca el Cursor en la posición correspondiente
   gtk_text_buffer_place_cursor (bufferEditor,&iter);

   // Verifica que si llego al tope del Buffer Undo-Redo
   if (gintUndoRedoIndice==(signed)gvecUndoRedo.size()-1)
   {
      // Desactiva la opción de Redo
      FnMenuOpcionOnOff(opcEdicionRedo,FALSE);
      FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionRedo),FALSE);

      // Cambia la imagen
      gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionRedo),iconEdicionRedoGray);

   }

   // Activa la opción de Undo
   FnMenuOpcionOnOff(opcEdicionUndo,TRUE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionUndo),TRUE);
   FnMenuOpcionOnOff(opcEdicionUndoClear,TRUE);

   // Cambia la imagen
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionUndo),iconEdicionUndo);


   // Se actualiza la barra de herramientas
   gtk_widget_show_all(GTK_WIDGET(toolbar));

   // La variable para indicar que no se ha tecleado nada
   gbTextoInsertado=false;

}

// Función para realizar el Clear del Undo-Credo
void FnEdicionClearUndoRedo(GtkWidget *clear_undo_redo)
{
   // Desactivo ClearUndoRedo
   FnMenuOpcionOnOff(opcEdicionUndoClear,FALSE);

   // Se inicializa los Controles del Undo-Redo
   gvecUndoRedo.clear();
   gvecCursorCol.clear();
   gvecCursorRow.clear();

   // Llamo a función que guarda lo que haya en este momento
   FnBufferUndoRedo();
   gbTextoInsertado=false;

   // Desactiva la opción de Undo
   FnMenuOpcionOnOff(opcEdicionUndo,FALSE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionUndo),FALSE);

   // Cambia la imagen
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionUndo),iconEdicionUndoGray);

   // Desactiva la opción de Redo
   FnMenuOpcionOnOff(opcEdicionRedo,FALSE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionRedo),FALSE);

   // Cambia la imagen
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionRedo),iconEdicionRedoGray);

}

// Obtiene el Indent de la Linea Actual
int FnIntIndentLineaActual()
{
    // Definición de Variables
    GtkTextIter iterLineaIni;    // Para el Inicio de la Linea
    GtkTextIter iterLineaFin;    // Para el Final de la Línea
    int  iLineasTotales;         // Obtener las Lineas Totales del Buffer
    int  iCtaSpaces;             // Para contar los Espacios

    // Obtengo el iter al Inicio de la Línea
    gtk_text_buffer_get_iter_at_line (bufferEditor,&iterLineaIni,gIntRow);

    // Obtengo las Lineas Totales
    iLineasTotales = gtk_text_buffer_get_line_count (bufferEditor);

    // Verifico las lineas
    if ( gIntRow+1 < iLineasTotales)

       // Obtengo el iter de la Linea Siguiente que es el fin de la presente
       gtk_text_buffer_get_iter_at_line (bufferEditor,&iterLineaFin,gIntRow+1);

    else

       // Obtengo el Iter Final del Texto
       gtk_text_buffer_get_end_iter(bufferEditor,&iterLineaFin);


    // Obtengo el texto de la Linea
    gchar *strLinea = gtk_text_buffer_get_text (bufferEditor,&iterLineaIni,&iterLineaFin,false);

    // Ciclo para buscar los Espacios
    for (iCtaSpaces=0; iCtaSpaces < (int)strlen(strLinea);iCtaSpaces++)

        // Verifica que no sea espacio
        if (strLinea[iCtaSpaces]!=32)
           break;

    // Retorna el valor del Spaces
    //g_print("Indent de Linea:%d \n",iCtaSpaces);
    return iCtaSpaces;

}


// --------------------------------------------------------------------------------------------------
// Fin de Funciones
// --------------------------------------------------------------------------------------------------
