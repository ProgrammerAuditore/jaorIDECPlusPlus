// --------------------------------------------------------------------------------------------------
// IDE C++
// Editor para Lenguaje C++
// Autor y Derechos Reservados:JAOR
// IDE_FN_MENUBUSCAR.hpp
// Archivo Header de Funciones del Menu Buscar
// --------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------
// Funciones Externas
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

extern void FnBufferUndoRedo();

// --------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------
// Prototipo de Funciones
// --------------------------------------------------------------------------------------------------

// Menu
void FnAppMenuBuscar();       // Construye el Menu

// Función para crear las opciones correspondiente a Edicion
void FnBarraMenuBuscar();

// Función para Encontrar
void FnBuscarEncontrar(GtkWidget *encontrar);

// Función para Reemplazar
void FnBuscarReemplazar(GtkWidget *reemplazar);

// Funcion para las Señales
void FnSenalesMenuBuscar();

// Función que muestra la Ventana para encontrar texto
void FnEncontrarTexto(GtkWidget *encontrar, GtkEntry *texto);

// Función que busca el texto en el buffer
void FnEncontrarTextoBuffer(const gchar *texto);


// Función que muestra la Ventana para encontrar texto y reemplazarlo
void FnReemplazaTexto(GtkWidget *encontrar, GtkEntry *texto);

// Función que busca el texto en el buffer y que lo reemplaza
void FnReemplazaTextoBuffer(const gchar *texto);

// Función que busca una cadena en otra para reemplazarla
string FnStrReplace(const char *source,
                    const char *fromStr,
                    const char *toStr,
                    int   offset,
                    bool  bExacto,
                    int   &iMatchs);

// --------------------------------------------------------------------------------------------------
// Fin de Prototipo de Funciones
// --------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------
// Funciones
// --------------------------------------------------------------------------------------------------

// Función para Crear el Menu Buscar
void FnAppMenuBuscar()
{

  // Creamos el Menu Buscar
  menuBuscar   = gtk_menu_new();

  // Creamos las Opciones de Buscar
  opcBuscar            = gtk_menu_item_new_with_mnemonic("Busca_r");

  // Crea el Item de Buscar-Encontrar
  FnCreaItemDeMenu(&opcBuscarEncontrar,&boxBuscarEncontrar,&icoBuscarEncontrar,
                   &lblBuscarEncontrar,"edit-find","Encontrar");


  // Crea el Item de Buscar-Reemplazar
  FnCreaItemDeMenu(&opcBuscarReemplazar,&boxBuscarReemplazar,&icoBuscarReemplazar,
                   &lblBuscarReemplazar,"edit-find-replace","Reemplazar");

  // Establecemos el Item File como una opción de la Barra de Menu
  gtk_menu_shell_append(GTK_MENU_SHELL(menuBarra), opcBuscar);


  // Agregamos la opcion del Menu Edición
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(opcBuscar), menuBuscar);

  // Establecemos las opciones del Menu
  gtk_menu_shell_append(GTK_MENU_SHELL(menuBuscar), opcBuscarEncontrar);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuBuscar), opcBuscarReemplazar);


  // Crea el Acelerador
  accel_group_buscar = gtk_accel_group_new();
  gtk_window_add_accel_group(GTK_WINDOW(window), accel_group_buscar);


  // Agregamos un Acelerador a las Opciones
  gtk_widget_add_accelerator(opcBuscarEncontrar,"activate",accel_group_buscar,
                             GDK_KEY_F,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator(opcBuscarReemplazar,"activate",accel_group_edicion,
                             GDK_KEY_G,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);

  // Desactivamos las opciones de Guardar, Guardar Como y Cerrar del Menu Archivo
  FnMenuOpcionOnOff(opcBuscarEncontrar,FALSE);
  FnMenuOpcionOnOff(opcBuscarReemplazar,FALSE);

}

// Función para crear la Barra de Herramientas
void FnBarraMenuBuscar()
{

  // Cargamos la imagen que deseamos
  iconBuscarEncontrar       = gtk_image_new_from_file ("search-find.png");
  iconBuscarReemplazar      = gtk_image_new_from_file ("search-replace.png");

  // Se agregan imagenes gray
  iconBuscarEncontrarGray   = gtk_image_new_from_file ("search-find-gray.png");
  iconBuscarReemplazarGray  = gtk_image_new_from_file ("search-replace-gray.png");


  // Hace a los iconos permanentes
  g_object_ref_sink(G_OBJECT(iconBuscarEncontrar));
  g_object_ref_sink(G_OBJECT(iconBuscarEncontrarGray));
  g_object_ref_sink(G_OBJECT(iconBuscarReemplazar));
  g_object_ref_sink(G_OBJECT(iconBuscarReemplazarGray));

  // Creamos los Item
  itemBuscarEncontrar  = gtk_tool_button_new(iconBuscarEncontrar,NULL);
  gtk_tool_item_set_tooltip_text (itemBuscarEncontrar,"Encontrar Texto");

  itemBuscarReemplazar = gtk_tool_button_new(iconBuscarEncontrar,NULL);
  gtk_tool_item_set_tooltip_text (itemBuscarReemplazar,"Reemplazar Texto");

  // Separador
  itemSeparador5  = gtk_separator_tool_item_new ();

  // Agrega el Separador y los Item de Encontrar y Reemplazar
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemSeparador5, 13);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemBuscarEncontrar, 14);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemBuscarReemplazar, 15);

  // Activa-Desactiva las opciones e item's correspondientes
  FnMenuOpcionOnOff(GTK_WIDGET(itemBuscarEncontrar),FALSE);
  FnMenuOpcionOnOff(GTK_WIDGET(itemBuscarReemplazar),FALSE);
  gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemBuscarEncontrar),iconBuscarEncontrarGray);
  gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemBuscarReemplazar),iconBuscarReemplazarGray);

  // Se actualiza la barra de herramientas
  gtk_widget_show_all(GTK_WIDGET(toolbar));

}

// Función para Mostrar la Ventana de Buscar Texto
void FnBuscarEncontrar(GtkWidget *encontrar)
{

   // Variables
   GtkWidget *boxBuscar;  // Contenedor
   GtkWidget *lblBuscar;  // La etiqueta
   GtkWidget *txtBuscar;  // Texto de Entrada
   GtkWidget *btnBuscar;  // Botón para Buscar
   GtkWidget *btnCancel;  // Botón para Cancelar


   // Crea la Ventana Nueva y la Configura
   wndEncontrar = gtk_window_new (GTK_WINDOW_TOPLEVEL);

   // Evitamos que sea redimensionable
   gtk_window_set_resizable(GTK_WINDOW(wndEncontrar),FALSE);

   // La hace aparecer como una ventana de dialogo (DESCENTRA LA VENTANA)
   gtk_window_set_type_hint(GTK_WINDOW(wndEncontrar),GDK_WINDOW_TYPE_HINT_MENU);

   // Ubicamos la Ventana
   gtk_window_set_position(GTK_WINDOW(wndEncontrar), GTK_WIN_POS_CENTER);

   // Coloca el Título
   gtk_window_set_title (GTK_WINDOW (wndEncontrar), "Encontrar");
   gtk_container_set_border_width (GTK_CONTAINER (wndEncontrar), 10);
   gtk_widget_set_size_request (wndEncontrar, 350, 200);


   // Establece que la ventana sea modal
   gtk_window_set_modal(GTK_WINDOW (wndEncontrar), TRUE);

   // Creamos los objetos de la Ventana
   lblBuscar     = gtk_label_new("Texto a Encontrar");        // La etiqueta
   txtBuscar     = gtk_entry_new();                        // El Texto de Entrada
   gtk_entry_set_width_chars(GTK_ENTRY(txtBuscar),40);     // El tamaño del Texto
   btnBuscar     = gtk_button_new_with_label("Encontrar"); // Crea el Botón de la Suma
   btnCancel     = gtk_button_new_with_label("Cancelar");  // Crea el Botón de la Suma

   // Check de Texto Exacto y Check de Texto Seleccionado
   chkTextCase   = gtk_check_button_new_with_label("Texto Exacto");
   chkTextSelect = gtk_check_button_new_with_label("En Texto Seleccionado");

   // Define el Contenedor
   boxBuscar     = gtk_fixed_new();

   // Agrega la etiqueta en una posición específica
   gtk_fixed_put(GTK_FIXED(boxBuscar), lblBuscar, 0, 10);
   gtk_fixed_put(GTK_FIXED(boxBuscar), txtBuscar, 0, 30);
   gtk_fixed_put(GTK_FIXED(boxBuscar), chkTextCase, 0, 70);
   gtk_fixed_put(GTK_FIXED(boxBuscar), chkTextSelect, 0, 100);
   gtk_fixed_put(GTK_FIXED(boxBuscar), btnBuscar, 0, 140);
   gtk_fixed_put(GTK_FIXED(boxBuscar), btnCancel, 263, 140);


   // Añade el Contenedor la Ventana
   gtk_container_add(GTK_CONTAINER(wndEncontrar), boxBuscar);

   // Muestra los objetos de la Ventana
   gtk_widget_show_all (wndEncontrar);

   // Señales
   // Botón de Cancelar Cierra Obligatoriamente la ventana
   g_signal_connect_swapped(G_OBJECT (btnCancel), "clicked",G_CALLBACK (gtk_widget_destroy),(gpointer) wndEncontrar);

   // Función para el botón Aceptar
   g_signal_connect(G_OBJECT (btnBuscar), "clicked",G_CALLBACK (FnEncontrarTexto),(gpointer) txtBuscar);


}

// Funcíón que busca texto en el buffer
void FnEncontrarTextoBuffer(const gchar *texto)
{
   // Variables
   gboolean selected=false;              // Para verificar si hay texto seleccionado
   GtkTextIter start_find, end_find;     // Para inicio y final de palabra encontrada
   GtkTextIter start_match, end_match;   // Para inicio y final de Match
   GtkTextSearchFlags xSearchFlag;       // Para Bandera de búsqueda

   // Verifica si la búsqueda será exacta o no
   if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(chkTextCase)))
      xSearchFlag = GtkTextSearchFlags(GTK_TEXT_SEARCH_TEXT_ONLY | GTK_TEXT_SEARCH_VISIBLE_ONLY);
   else
      xSearchFlag = GtkTextSearchFlags(GTK_TEXT_SEARCH_TEXT_ONLY |
                                       GTK_TEXT_SEARCH_VISIBLE_ONLY |
                                       GTK_TEXT_SEARCH_CASE_INSENSITIVE);

   // Verifica si hay que buscar en texto seleccionado
   if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(chkTextSelect)))
   {
      // Obtiene el Texto a Buscar
      selected = gtk_text_buffer_get_selection_bounds(bufferEditor,&start_find, &end_find);
   }
   else
   {
      // Obtiene los iter al inicio y fin del Texto en el buffer
      gtk_text_buffer_get_start_iter(bufferEditor, &start_find);
      gtk_text_buffer_get_end_iter(bufferEditor, &end_find);
   }

   // Remueve el Tag si existe en el texto
   gtk_text_buffer_remove_tag_by_name(bufferEditor, "green_bg",&start_find, &end_find);

   // Ciclo para ir seleccionando el texto en todo el contenido del buffer
   // Busca text desde start_find, y obtiene su inicio y final en start_match y end_match
   while (gtk_text_iter_forward_search(&start_find,       // Desde donde buscar
                                        texto,            // Texto a Encontrar
                                        xSearchFlag,      // Bandera de búsqueda
                                       &start_match,      // Marca inicial donde encontró
                                       &end_match,        // Marca final donde encontró
                                       &end_find))        // Hasta donde buscar
   {
      // Aplica el Tag al buffer, en donde encotré el texto; start_match y end_match
      gtk_text_buffer_apply_tag_by_name(bufferEditor, "green_bg",&start_match, &end_match);

      // Obtiene el desplazamiento alel final del match
      gint offset = gtk_text_iter_get_offset(&end_match);

      // Obtiene el nuevo start_find, a partir del offset
      gtk_text_buffer_get_iter_at_offset(bufferEditor,&start_find, offset);
   }

   // Verifica si hubo texto seleccionado
   if (selected)
      // DesSelecciona texto en el buffer
      gtk_text_buffer_select_range(bufferEditor,&start_find,&start_find);

}

// Función CallBack que despliega ventana de Buscar Texto
void FnEncontrarTexto(GtkWidget *encontrar, GtkEntry *texto)
{
    // Variable para obtener el texto
    const gchar *gstrTexto;

    // Variable para generar el MessageDialog
    GtkWidget *dialog;

    // Variable para la longitud del texto
    gint16 giLongitud;


    // Obtiene la Longitud del Texto a Buscar
    giLongitud = gtk_entry_get_text_length(texto);

    // Verifica que haya texto que buscar
    if (giLongitud == 0)
    {
       // Despliega Mensaje de que debe capturar algo a Encontrar
       // Crea el MessageDialog
       dialog = gtk_message_dialog_new(GTK_WINDOW(wndEncontrar),
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_ERROR,
                GTK_BUTTONS_OK,
                "Debe capturar el texto a Encontrar");

       // Establece el Título de la Ventana
       gtk_window_set_title(GTK_WINDOW(dialog), "Error");

       // Ejecuta el Diálogo y obtiene su respuesta
       gtk_dialog_run(GTK_DIALOG(dialog));

       // Destruye el Diálogo
       gtk_widget_destroy(dialog);


    }
    else
    {

      // Obtiene el Texto
      gstrTexto = gtk_entry_get_text (texto);

      //Llama a la Función que encuentra el texto
      FnEncontrarTextoBuffer(gstrTexto);

      //Llama a la Función que destruye la Ventana de Encontrar
      gtk_widget_destroy(wndEncontrar);

    }
}


// Función para Reemplazar Texto
void FnBuscarReemplazar(GtkWidget *copiar)
{
   // Variables
   GtkWidget *boxBuscar;    // Contenedor
   GtkWidget *lblBuscar;    // La etiqueta
   GtkWidget *txtBuscar;    // Texto de Entrada
   GtkWidget *lblReplace;   // La etiqueta de Replace
   GtkWidget *btnBuscar;    // Botón para Buscar
   GtkWidget *btnCancel;    // Botón para Cancelar


   // Crea la Ventana Nueva y la Configura
   wndEncontrar = gtk_window_new (GTK_WINDOW_TOPLEVEL);

   // Evitamos que sea redimensionable
   gtk_window_set_resizable(GTK_WINDOW(wndEncontrar),FALSE);

   // La hace aparecer como una ventana de dialogo (DESCENTRA LA VENTANA)
   gtk_window_set_type_hint(GTK_WINDOW(wndEncontrar),GDK_WINDOW_TYPE_HINT_MENU);

   // Ubicamos la Ventana
   gtk_window_set_position(GTK_WINDOW(wndEncontrar), GTK_WIN_POS_CENTER);

   // Coloca el Título
   gtk_window_set_title (GTK_WINDOW (wndEncontrar), "Reemplazar");
   gtk_container_set_border_width (GTK_CONTAINER (wndEncontrar), 10);
   gtk_widget_set_size_request (wndEncontrar, 300, 200);


   // Establece que la ventana sea modal
   gtk_window_set_modal(GTK_WINDOW (wndEncontrar), TRUE);

   // Creamos los objetos de la Ventana
   lblBuscar     = gtk_label_new("Texto a Encontrar");     // La etiqueta
   txtBuscar     = gtk_entry_new();                        // El Texto a Encontrar
   lblReplace    = gtk_label_new("Texto que Reemplaza");   // La etiqueta
   txtReplace    = gtk_entry_new();                        // El Texto que Reemplaza
   gtk_entry_set_width_chars(GTK_ENTRY(txtBuscar),40);     // El tamaño del Texto
   gtk_entry_set_width_chars(GTK_ENTRY(txtReplace),40);     // El tamaño del Texto
   btnBuscar     = gtk_button_new_with_label("Reemplazar"); // Crea el Botón de la Suma
   btnCancel     = gtk_button_new_with_label("Cancelar");  // Crea el Botón de la Suma

   // Check de Texto Exacto y Check de Texto Seleccionado
   chkTextCase   = gtk_check_button_new_with_label("Texto Exacto");
   chkTextSelect = gtk_check_button_new_with_label("En Texto Seleccionado");

   // Define el Contenedor
   boxBuscar     = gtk_fixed_new();

   // Agrega la etiqueta en una posición específica
   gtk_fixed_put(GTK_FIXED(boxBuscar), lblBuscar, 0, 10);
   gtk_fixed_put(GTK_FIXED(boxBuscar), txtBuscar, 0, 30);
   gtk_fixed_put(GTK_FIXED(boxBuscar), lblReplace, 0, 70);
   gtk_fixed_put(GTK_FIXED(boxBuscar), txtReplace, 0, 90);
   gtk_fixed_put(GTK_FIXED(boxBuscar), chkTextCase, 0, 130);
   gtk_fixed_put(GTK_FIXED(boxBuscar), chkTextSelect, 0, 160);
   gtk_fixed_put(GTK_FIXED(boxBuscar), btnBuscar, 0, 200);
   gtk_fixed_put(GTK_FIXED(boxBuscar), btnCancel, 263, 200);


   // Añade el Contenedor la Ventana
   gtk_container_add(GTK_CONTAINER(wndEncontrar), boxBuscar);

   // Muestra los objetos de la Ventana
   gtk_widget_show_all (wndEncontrar);

   // Señales
   // Botón de Cancelar Cierra Obligatoriamente la ventana
   g_signal_connect_swapped(G_OBJECT (btnCancel), "clicked",G_CALLBACK (gtk_widget_destroy),(gpointer) wndEncontrar);

   // Función para el botón Aceptar
   g_signal_connect(G_OBJECT (btnBuscar), "clicked",G_CALLBACK (FnReemplazaTexto),(gpointer) txtBuscar);

}

// Función CallBack que despliega ventana de Buscar Texto
void FnReemplazaTexto(GtkWidget *encontrar, GtkEntry *texto)
{
    // Variable para obtener el texto
    const gchar *gstrTexto;

    // Variable para generar el MessageDialog
    GtkWidget *dialog;

    // Variable para la longitud del texto
    gint16 giLongitud;


    // Obtiene la Longitud del Texto a Buscar
    giLongitud = gtk_entry_get_text_length(texto);

    // Verifica que haya texto que buscar
    if (giLongitud == 0)
    {
       // Despliega Mensaje de que debe capturar algo a Encontrar
       // Crea el MessageDialog
       dialog = gtk_message_dialog_new(GTK_WINDOW(wndEncontrar),
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_ERROR,
                GTK_BUTTONS_OK,
                "Debe capturar el texto a Reemplazar");

       // Establece el Título de la Ventana
       gtk_window_set_title(GTK_WINDOW(dialog), "Error");

       // Ejecuta el Diálogo y obtiene su respuesta
       gtk_dialog_run(GTK_DIALOG(dialog));

       // Destruye el Diálogo
       gtk_widget_destroy(dialog);


    }
    else
    {

      // Obtiene el Texto
      gstrTexto = gtk_entry_get_text (texto);


      //Llama a la Función que encuentra el texto
      FnReemplazaTextoBuffer(gstrTexto);

      //Llama a la Función que destruye la Ventana de Encontrar
      gtk_widget_destroy(wndEncontrar);

    }
}

// Funcíón que reemplaza texto en el buffer
void FnReemplazaTextoBuffer(const gchar *texto)
{
   // Variables
   gboolean selected=false;              // Para verificar si hay texto seleccionado
   GtkTextIter start_find, end_find;     // Para inicio y final de palabra encontrada
   GtkTextIter start_match, end_match;   // Para inicio y final de Match
   GtkTextSearchFlags xSearchFlag;       // Para Bandera de búsqueda
   gchar *gstrReplace;                   // Variable para obtener el texto
   bool bExacta;                         // Variable para búsqueda exacta
   gchar *strTextoSeleccionado;          // Para el Texto Seleccionado
   string strTextoReemplazado;           // Para el Texto Reemplazado
   GtkTextIter iterPosCursor;            // Para posición del Cursor
   gint row, col;                        // Renglon y Columna
   int iReemplazos;                      // Para saber cuantos reemplazos


   // Obtiene el texto que se utilizara para reemplazar
   gstrReplace = (gchar *)gtk_entry_get_text (GTK_ENTRY(txtReplace));

   // Obtiene busqueda exacta
   bExacta = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(chkTextCase));

   // Verifica si la búsqueda será exacta o no
   if (bExacta)
      xSearchFlag = GtkTextSearchFlags(GTK_TEXT_SEARCH_TEXT_ONLY | GTK_TEXT_SEARCH_VISIBLE_ONLY);
   else
      xSearchFlag = GtkTextSearchFlags(GTK_TEXT_SEARCH_TEXT_ONLY |
                                       GTK_TEXT_SEARCH_VISIBLE_ONLY |
                                       GTK_TEXT_SEARCH_CASE_INSENSITIVE);

   // Verifica si hay que buscar en texto seleccionado
   if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(chkTextSelect)))
   {

      // Obtiene el Texto Seleccionado
      selected = gtk_text_buffer_get_selection_bounds(bufferEditor,&start_find, &end_find);

      // Verifica si hubo texto seleccionado
      if (selected)
      {
         // Obtiene la Información de donde está el cursor
         gtk_text_buffer_get_iter_at_mark(bufferEditor,&iterPosCursor, gtk_text_buffer_get_insert(bufferEditor));

         // Obtiene el Row y la Col
         row = gtk_text_iter_get_line(&iterPosCursor);
         col = gtk_text_iter_get_line_offset(&iterPosCursor);


         // Obtiene el texto Seleccionado
         strTextoSeleccionado = (gchar *) gtk_text_buffer_get_text(bufferEditor,
                                                                    &start_find,
                                                                    &end_find,
                                                                    FALSE);

         // Obtiene el texto con el Reemplazo
         strTextoReemplazado = FnStrReplace(strTextoSeleccionado,texto,gstrReplace,0,bExacta,iReemplazos);

         // Verifica si hubo reemplazos
         if (iReemplazos>0)
         {
             // Guarda en el Buffer antes de reemplazar
             FnBufferUndoRedo();

             // Activa Undo
             FnMenuOpcionOnOff(opcEdicionUndo,TRUE);
             FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionUndo),TRUE);

             // Cambia la imagen
             gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionUndo),iconEdicionUndo);

             // Se actualiza la barra de herramientas
             gtk_widget_show_all(GTK_WIDGET(toolbar));

             // Borra el Texto Seleccionado
             gtk_text_buffer_delete(bufferEditor,&start_find, &end_find);

             // Ubica el Cursor
             gtk_text_buffer_place_cursor (bufferEditor,&start_find);

             // Inserta el Texto Nuevo en el buffer
             gtk_text_buffer_insert_at_cursor(bufferEditor,strTextoReemplazado.c_str(),strlen(strTextoReemplazado.c_str()));

             // Obtiene la Posición Inicial del Buffer
             gtk_text_buffer_get_start_iter (bufferEditor, &iterPosCursor);

             // Establece la posición del cursor
             gtk_text_iter_set_line(&iterPosCursor,row);
             gtk_text_iter_set_line_offset(&iterPosCursor,col);

             // Ubica el Cursor
             gtk_text_buffer_place_cursor (bufferEditor,&iterPosCursor);
         }
      }
   }
   else
   {

       // Obtiene la Información de donde está el cursor
       gtk_text_buffer_get_iter_at_mark(bufferEditor,&iterPosCursor, gtk_text_buffer_get_insert(bufferEditor));

       // Obtiene el Row y la Col
       row = gtk_text_iter_get_line(&iterPosCursor);
       col = gtk_text_iter_get_line_offset(&iterPosCursor);

       // Obtiene los iter al inicio y fin del Texto en el buffer
       gtk_text_buffer_get_start_iter(bufferEditor, &start_find);
       gtk_text_buffer_get_end_iter(bufferEditor, &end_find);

       // Obtiene el texto Seleccionado
       strTextoSeleccionado = (gchar *) gtk_text_buffer_get_text(bufferEditor,
                                                                &start_find,
                                                                &end_find,
                                                                FALSE);


       // Obtiene el texto con el Reemplazo
       strTextoReemplazado = FnStrReplace(strTextoSeleccionado,texto,gstrReplace,0,bExacta,iReemplazos);

       // Verifica si hubo reemplazos
       if (iReemplazos>0)
       {
           // Guarda en el Buffer antes de reemplazar
           FnBufferUndoRedo();

           // Activa Undo
           FnMenuOpcionOnOff(opcEdicionUndo,TRUE);
           FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionUndo),TRUE);

           // Cambia la imagen
           gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionUndo),iconEdicionUndo);

           // Se actualiza la barra de herramientas
           gtk_widget_show_all(GTK_WIDGET(toolbar));

           // Primero Borra el Texto Seleccionado, pero en este caso es todo
           gtk_text_buffer_delete(bufferEditor,&start_find, &end_find);

           // Ubica el Cursor
           gtk_text_buffer_place_cursor (bufferEditor,&start_find);

           // Inserta el Texto Nuevo en el buffer
           gtk_text_buffer_insert_at_cursor(bufferEditor,strTextoReemplazado.c_str(),strlen(strTextoReemplazado.c_str()));

           // Ubica el Cursor
           // Obtiene la Posición Inicial del Buffer
           gtk_text_buffer_get_start_iter (bufferEditor, &iterPosCursor);

           // Establece la posición del cursor
           gtk_text_iter_set_line(&iterPosCursor,row);
           gtk_text_iter_set_line_offset(&iterPosCursor,col);

           // Coloca el Cursor en la posición correspondiente
           gtk_text_buffer_place_cursor (bufferEditor,&iterPosCursor);
        }
   }

}

// Función que busca una cadena en otra para reemplazarla
string FnStrReplace(const char *source,   // La Cadena Origen
                    const char *fromStr,  // El texto a cambiar
                    const char *toStr,    // El texto que reemplaza
                    int   offset,         // a partir de que posición
                    bool  bExacto,        // Si la búsqueda es exacta
                    int   &iMatchs)       // Para indicar cuantas coincidencias hubo
{
  // Declaración de Variables
  string::size_type pos = offset;    // El desplazamiento
  string strSource = source;         // La Cadena Original
  string strFrom   = fromStr;        // Cadena a buscar
  string strTo     = toStr;          // Cadena que reemplaza
  string auxSource = source;         // Conserva cadena original
  string auxtoStr  = toStr;          // Conserva cadena que reemplaza

  // Aseguro coincidencias a 0
  iMatchs=0;

  // Verifica si la búsqueda es exacta
  if (bExacto)
  {
     // Ciclo para buscar y reemplazar
     while ( ( (pos = strSource.find(strFrom, pos)) < string::npos) )
     {
          // Reemplaza la cadena
          strSource.replace(pos, strFrom.length(), strTo);

          // Obtiene el Desplazamiento
          pos+=strTo.size();

          // Incremento coincidencias
          iMatchs++;
     }

     // Retorna la cadena con el reemplazamiento realizado
     return strSource;

  }

  else
  {

     // Convierte a mayúsculas
     std::transform(strSource.begin(), strSource.end(),strSource.begin(), ::toupper);
     std::transform(strFrom.begin(), strFrom.end(),strFrom.begin(), ::toupper);
     std::transform(strTo.begin(), strTo.end(),strTo.begin(), ::toupper);

     // Ciclo para buscar y reemplazar
     while ( ( (pos = strSource.find(strFrom, pos)) < string::npos) )
     {
          // Reemplaza la Cadena
          strSource.replace(pos, strFrom.length(), strTo);

          // Reemplaza la cadena en Original
          auxSource.replace(pos, strFrom.length(), auxtoStr);

          // Obtiene la posición de desplazamiento
          pos+=strTo.size();

          // Incremento coincidencias
          iMatchs++;

     }

     // Retorna la cadena original con el reemplamiento realizado
     return auxSource;

  }

}



// Señales del Menu Edición
void FnSenalesMenuBuscar()
{

    // Controla las Señales del Menu y Barra de Buscar
    g_signal_connect (G_OBJECT (opcBuscarEncontrar), "activate",G_CALLBACK (FnBuscarEncontrar), NULL);
    g_signal_connect (G_OBJECT (itemBuscarEncontrar), "clicked",G_CALLBACK (FnBuscarEncontrar), NULL);
    g_signal_connect (G_OBJECT (opcBuscarReemplazar), "activate",G_CALLBACK (FnBuscarReemplazar), NULL);
    g_signal_connect (G_OBJECT (itemBuscarReemplazar), "clicked",G_CALLBACK (FnBuscarReemplazar), NULL);

}


// --------------------------------------------------------------------------------------------------
// Fin de Funciones
// --------------------------------------------------------------------------------------------------

