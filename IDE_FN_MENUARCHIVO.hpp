// --------------------------------------------------------------------------------------------------
// IDE C++
// Editor para Lenguaje C++
// Autor y Derechos Reservados:JAOR
// IDE_FN_MENUARCHIVO.hpp
// Archivo Header de Funciones Menu Archivo
// --------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------
// Funciones Externas
// --------------------------------------------------------------------------------------------------

// Estructura para grabar espacios de Indent
struct DispatchData {
    GtkTextBuffer *buffer;
    char *output_str;
};

// Función para Cambiar la Fuente
extern void FnEditorFont(string sFont);
// Función para desactivar o activar una opción del Menu
extern void FnMenuOpcionOnOff(GtkWidget *xOpcion,bool OnOff);

// Función para Establecer el Mensaje en la Barra de Estado
extern void FnBarraEstadoMensaje(const char *strMensaje);
// Función para establecer el Título
extern void FnAplicacionTitulo();
// Función para desplegar un Error
extern void FnAplicacionMensajeError(const char *sMensaje);
// Función para crear Items de Menu
extern void FnCreaItemDeMenu(GtkWidget  **xOpcion,
                      GtkWidget  **bOpcion,
                      GtkWidget  **iOpcion,
                      GtkWidget  **lOpcion,
                      const char *iconName,
                      const char *opcName);


// Función para grabar en el Undo
extern void FnBufferUndoRedo();

// --------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------
// Prototipo de Funciones
// --------------------------------------------------------------------------------------------------

// Funcion para las Señales
void FnSenalesMenuArchivo();

// Menu
void FnAppMenuArchivo();       // Construye el Menu

// Función para crear la Barra de Herramientas
void FnBarraMenuArchivo();

// Función para Habilitar-Deshabilitar Editor
void FnEditorOnOff(bool bHabilita);

// Función para Crear el Editor de Texto
void FnCreaEditorTexto();

// Función para Actualizar Linea y Columna cuando el contenido cambia
void FnEditorTextChange(GtkTextBuffer *buffer, GtkStatusbar  *statusbar);

// Funcion para controlar Archivo Nuevo
void FnMenuArchivoNuevo(GtkWidget *widget);

// Funcion para Guardar Archivo
void FnMenuArchivoGuardar(GtkToolItem *item,GtkWindow *window);

// Función para obtener la Ruta y el Nombre del Archivo que se edita
void FnArchivoRutaNombre(string sArchivo);

// Funcion de Grabar en Disco
void FnArchivoGrabar();

// Funcion para Guardar Como Archivo
void FnMenuArchivoGuardarComo(GtkToolItem *item,GtkWindow *window);

// Función para Actualizar Linea y Columna cuando el cursor Cambia
void FnEditorCursorChange(GtkTextBuffer *buffer,const GtkTextIter *new_location, GtkTextMark *mark, gpointer data);

// Función para Cerrar el Archivo
void FnMenuArchivoCerrar(GtkWidget *opcCerrar,GtkWindow *window);
void FnMenuArchivoSalir(GtkWidget *opcSalir, GtkWindow *window);

// Funciones para Leer el Archivo
void FnMenuArchivoAbrir(GtkWidget *opcAbrir,GtkWindow *window);
void FnArchivoLeer();

// Función para Inicializar Vectores para Codificación en Color
void FnInicializaVectoresCodigoColor();

// Función para verificar si es un caracter especial
bool FnBoolCaracterEspecial(char *xChar);

// Función para verificar que solo tenga espacios la cadena
bool FnBoolVerificaSoloEspacios(char *strCadena);

// Función para Codificar el Texto
void FnCodificaCodigoColor();

// Función que procesa una línea para codificar el Color
void FnProcesaLinea(gint giLinea);

// Función para controlar cuando se ha realizado un paste del ClipBoard
void FnEditorPasteDone();


// Función para crear la Ventana de Compilación
//void FnCreaVentanaCompilacion();

// --------------------------------------------------------------------------------------------------
// Fin de Prototipo de Funciones
// --------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------
// Funciones
// --------------------------------------------------------------------------------------------------

// Función que realiza inserción del Indent de Espacios en el Buffer
static gboolean FnBoolInsertSpaceIndentBuffer(struct DispatchData *data)
{
    //gtk_text_buffer_set_text(data->buffer, data->output_str, strlen(data->output_str));
    gtk_text_buffer_insert_at_cursor(data->buffer, data->output_str, strlen(data->output_str));
    g_free(data);
    return G_SOURCE_REMOVE;
}

// Función que llama a la Función que inserta espacios Indent en el Buffer
void FnInsertSpaceIndent()
{
    struct DispatchData *data = g_new0(struct DispatchData, 1);
    data->output_str=gStrSpaces;
    data->buffer = bufferEditor;
    gdk_threads_add_idle(FnBoolInsertSpaceIndentBuffer, data);
}

// Función para control de Señales
void FnSenalesMenuArchivo()
{

  // Captura la Señal para destruir la Ventana Principal
  g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(FnMenuArchivoSalir), (gpointer) window);

  // Establece que el Item quit ejecute la salida de la Ventana
  g_signal_connect(G_OBJECT(opcArchivoSalir), "activate",G_CALLBACK(FnMenuArchivoSalir), (gpointer) window);

  // Establece señal cuando el cursor cambia en el Buffer
  g_signal_connect_object(bufferEditor, "mark_set", G_CALLBACK(FnEditorCursorChange), statusbar, G_CONNECT_AFTER);

  // Establece señal de pegado de texto
  g_signal_connect_object(bufferEditor, "paste_done", G_CALLBACK(FnEditorPasteDone), statusbar, G_CONNECT_AFTER);

  // Señal del Cambio de datos en el buffer
  g_signal_connect(bufferEditor, "changed",G_CALLBACK(FnEditorTextChange), statusbar);

  // Establecemos la función para controlar la opcion de Archivo Nuevo
  g_signal_connect(G_OBJECT(opcArchivoNuevo), "activate",G_CALLBACK(FnMenuArchivoNuevo),NULL);
  g_signal_connect(G_OBJECT(itemNuevo), "clicked",G_CALLBACK(FnMenuArchivoNuevo),NULL);

  // Establecemos la función para controlar la opcion Guardar
  g_signal_connect(G_OBJECT(opcArchivoGuardar), "activate",G_CALLBACK(FnMenuArchivoGuardar),(gpointer) window);
  g_signal_connect(G_OBJECT(itemGuardar), "clicked",G_CALLBACK(FnMenuArchivoGuardar),(gpointer) window);
  g_signal_connect(G_OBJECT(opcArchivoGuardarComo), "activate",G_CALLBACK(FnMenuArchivoGuardarComo),(gpointer) window);
  g_signal_connect(G_OBJECT(itemGuardarComo), "clicked",G_CALLBACK(FnMenuArchivoGuardarComo),(gpointer) window);
  g_signal_connect(G_OBJECT(opcArchivoCerrar), "activate",G_CALLBACK(FnMenuArchivoCerrar),(gpointer) window);
  g_signal_connect(G_OBJECT(opcArchivoAbrir), "activate",G_CALLBACK(FnMenuArchivoAbrir),(gpointer) window);
  g_signal_connect(G_OBJECT(itemAbrir), "clicked",G_CALLBACK(FnMenuArchivoAbrir),(gpointer) window);

}

// Función para Crear el Menu Principal
void FnAppMenuArchivo()
{

  // Creamos el Menu Archivo
  menuArchivo   = gtk_menu_new();

  // Creamos las Opciones de Archivo
  opcArchivo            = gtk_menu_item_new_with_mnemonic("_Archivo");

  // Crea el Item de Archivo Nuevo
  FnCreaItemDeMenu(&opcArchivoNuevo,&boxArchivoNuevo,&icoArchivoNuevo,
                   &lblArchivoNuevo,"document-new","Nuevo");

  // El Separador de Opciones
  separador1            = gtk_separator_menu_item_new();

  // Crea el Item de Archivo Abrir
  FnCreaItemDeMenu(&opcArchivoAbrir,&boxArchivoAbrir,&icoArchivoAbrir,
                   &lblArchivoAbrir,"document-open","Abrir");

  // El Separador de Opciones
  separador2            = gtk_separator_menu_item_new();

  // Crea el Item de Archivo Guardar
  FnCreaItemDeMenu(&opcArchivoGuardar,&boxArchivoGuardar,&icoArchivoGuardar,
                   &lblArchivoGuardar,"document-save","Guardar");

  // Crea el Item de Archivo Guardar Como
  FnCreaItemDeMenu(&opcArchivoGuardarComo,&boxArchivoGuardarComo,&icoArchivoGuardarComo,
                   &lblArchivoGuardarComo,"document-save-as","Guardar como ...");

  // El Separador de Opciones
  separador3            = gtk_separator_menu_item_new();

  // Crea el Item de Archivo Cerrar
  FnCreaItemDeMenu(&opcArchivoCerrar,&boxArchivoCerrar,&icoArchivoCerrar,
                   &lblArchivoCerrar,"document-close","Cerrar");

  // El Separador de Opciones
  separador4            = gtk_separator_menu_item_new();

  // Función que sustituye a las anteriores líneas
  FnCreaItemDeMenu(&opcArchivoSalir,&boxArchivoSalir,&icoArchivoSalir,
                   &lblArchivoSalir,"application-exit","Salir");

  // Establecemos el Item File como una opción de la Barra de Menu
  gtk_menu_shell_append(GTK_MENU_SHELL(menuBarra), opcArchivo);

  // Agregamos la opcion del Menu Archivo
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(opcArchivo), menuArchivo);

  // Establecemos la opción Quit como una opción del Menu
  gtk_menu_shell_append(GTK_MENU_SHELL(menuArchivo), opcArchivoNuevo);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuArchivo), separador1);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuArchivo), opcArchivoAbrir);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuArchivo), separador2);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuArchivo), opcArchivoGuardar);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuArchivo), opcArchivoGuardarComo);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuArchivo), separador3);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuArchivo), opcArchivoCerrar);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuArchivo), separador4);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuArchivo), opcArchivoSalir);


  // Crea el Acelerador se agrego el nombre
  accel_group_archivo = gtk_accel_group_new();
  gtk_window_add_accel_group(GTK_WINDOW(window), accel_group_archivo);

  // Agregamos un Acelerador a la Salida
  gtk_widget_add_accelerator(opcArchivoNuevo,"activate",accel_group_archivo,
                             GDK_KEY_N,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator(opcArchivoAbrir,"activate",accel_group_archivo,
                             GDK_KEY_O,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator(opcArchivoCerrar,"activate",accel_group_archivo,
                             GDK_KEY_W,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator(opcArchivoGuardar,"activate",accel_group_archivo,
                             GDK_KEY_S,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator(opcArchivoGuardarComo,"activate",accel_group_archivo,
                             GDK_KEY_D,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator(opcArchivoSalir,"activate",accel_group_archivo,
                             GDK_KEY_Q,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);

  // Desactivamos las opciones de Guardar, Guardar Como y Cerrar del Menu Archivo
  FnMenuOpcionOnOff(opcArchivoGuardar,FALSE);
  FnMenuOpcionOnOff(opcArchivoGuardarComo,FALSE);
  FnMenuOpcionOnOff(opcArchivoCerrar,FALSE);
}

// Función para crear la Barra de Herramientas
void FnBarraMenuArchivo()
{
  // Cargamos la imagen que deseamos
  iconNuevo       = gtk_image_new_from_file ("document-new.png");
  iconAbrir       = gtk_image_new_from_file ("document-open.png");
  iconGuardar     = gtk_image_new_from_file ("document-save.png");
  iconGuardarComo = gtk_image_new_from_file ("document-save-as.png");

  // Cargamos las imagenes gray
  iconNuevoGray       = gtk_image_new_from_file ("document-new-gray.png");
  iconAbrirGray       = gtk_image_new_from_file ("document-open-gray.png");
  iconGuardarGray     = gtk_image_new_from_file ("document-save-gray.png");
  iconGuardarComoGray = gtk_image_new_from_file ("document-save-as-gray.png");

  // Hace a los iconos permanentes
  g_object_ref_sink(G_OBJECT(iconNuevo));
  g_object_ref_sink(G_OBJECT(iconNuevoGray));
  g_object_ref_sink(G_OBJECT(iconAbrir));
  g_object_ref_sink(G_OBJECT(iconAbrirGray));
  g_object_ref_sink(G_OBJECT(iconGuardar));
  g_object_ref_sink(G_OBJECT(iconGuardarGray));
  g_object_ref_sink(G_OBJECT(iconGuardarComo));
  g_object_ref_sink(G_OBJECT(iconGuardarComoGray));

  // Creamos los Item
  itemNuevo       = gtk_tool_button_new(iconNuevo,NULL);
  gtk_tool_item_set_tooltip_text (itemNuevo,"Nuevo Archivo");

  itemAbrir       = gtk_tool_button_new(iconAbrir,NULL);
  gtk_tool_item_set_tooltip_text (itemAbrir,"Abrir Archivo");

  itemGuardar     = gtk_tool_button_new(iconGuardar,NULL);
  gtk_tool_item_set_tooltip_text (itemGuardar,"Guardar Archivo");

  itemGuardarComo = gtk_tool_button_new(iconGuardarComo,NULL);
  gtk_tool_item_set_tooltip_text (itemGuardarComo,"Guardar Archivo Como ...");

  itemSeparador1  = gtk_separator_tool_item_new ();
  itemSeparador2  = gtk_separator_tool_item_new ();




  // Agrega los Item a la barra de Herramientas
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemNuevo, 0);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemSeparador1, 1);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemAbrir, 2);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemSeparador2, 3);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemGuardar, 4);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemGuardarComo, 5);

  // Funciona con la de opciones del Menu
  FnMenuOpcionOnOff(GTK_WIDGET(itemGuardar),FALSE);
  FnMenuOpcionOnOff(GTK_WIDGET(itemGuardarComo),FALSE);
  gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemGuardar),iconGuardarGray);
  gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemGuardarComo),iconGuardarComoGray);
  gtk_widget_show_all(GTK_WIDGET(toolbar));


}



// Función para Habilitar-Deshabilitar Editor
void FnEditorOnOff(bool bHabilita)
{
   // Variables
   GtkTextIter iterInicio;  // Ubicación

   // Se indica si es editable o no y se activa o visibiliza el cursor
   gtk_text_view_set_editable (GTK_TEXT_VIEW (textviewEditor), bHabilita);
   gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (textviewEditor),bHabilita);

   // Si habilita coloca el foco
   if (bHabilita)
      gtk_widget_grab_focus(textviewEditor);

   // Obtiene la Posición Inicial del Buffer
   gtk_text_buffer_get_start_iter (bufferEditor, &iterInicio);

   // Coloca el Cursor en la posición Inicial
   gtk_text_buffer_place_cursor (bufferEditor,&iterInicio);

}

// Función para Crear el Editor de Texto
void FnCreaEditorTexto()
{

   // Crea el Scroll
   scrollEditor = gtk_scrolled_window_new (NULL, NULL);

   // Crea el objeto TextView para el Editor de Texto
   textviewEditor = gtk_text_view_new ();

   // Crea el objeto para el buffer del TextView
   bufferEditor = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textviewEditor));

   // Añade el TextView al Scroll y el Scroll al Contenedor
   gtk_container_add (GTK_CONTAINER (scrollEditor), textviewEditor);
   gtk_box_pack_start(GTK_BOX(vbox), scrollEditor, TRUE, TRUE, 0);


   // El espacio en pixeles Antes y despues del Enter
   gtk_text_view_set_pixels_above_lines (GTK_TEXT_VIEW (textviewEditor), 1);
   gtk_text_view_set_pixels_below_lines (GTK_TEXT_VIEW (textviewEditor), 1);

   // El Margen Izquierdo
   gtk_text_view_set_left_margin (GTK_TEXT_VIEW (textviewEditor), 10);

   // El Margen Derecho
   gtk_text_view_set_right_margin (GTK_TEXT_VIEW (textviewEditor), 10);

   // Se indica si es editable o no
   FnEditorOnOff(false);

   // Establece la Fuente
   FnEditorFont(gstrFont);

   // Inicializa los Vectores de Código
   FnInicializaVectoresCodigoColor();


}

// Función para actualizar la Barra de Estado
void FnEditorTextChange(GtkTextBuffer *buffer, GtkStatusbar  *statusbar)
{

   // Verifica que esté editable
   if (gtk_text_view_get_editable(GTK_TEXT_VIEW(textviewEditor)))
   {
       // Verifica procesamiento
       if (! gBoolProcesando)
       {
          // Declaración de Variables
          gchar *msg;           // Mensaje
          int   iCtaSpaces;     // Para contar los Espacios

          // Se pasaron a globales
          //gint row, col;  // Renglon y Columna
          GtkTextIter iter; // Item
          gboolean bResult; // Para Resultado

          // Llama a las Funciones
          bResult = gtk_text_buffer_get_has_selection(bufferEditor);
          FnMenuOpcionOnOff(opcEdicionCortar,bResult);
          FnMenuOpcionOnOff(opcEdicionCopiar,bResult);
          FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionCortar),bResult);
          FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionCopiar),bResult);


          // Establece las imagenes de la Barra de Herramientas
          if (bResult)

          {
             // Imágenes Normales
             gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionCortar),iconEdicionCortar);
             gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionCopiar),iconEdicionCopiar);
          }
          else
          {
             // Imágenes Gray
             gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionCortar),iconEdicionCortarGray);
             gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionCopiar),iconEdicionCopiarGray);
          }

          // Actualiza Imagenes
          gtk_widget_show_all(GTK_WIDGET(toolbar));

          // Verifica bandera de modificado para activar opción
          if (gintArchivoModificado==1)
          {
             // Activamos
             gintArchivoModificado=0;


          }
          else
             if (gintArchivoModificado==2)
                // Disminuye
                gintArchivoModificado--;

          // Verifica si está insertado el Texto
          if (gbTextoInsertado)
          {
               // Desactivamos opción de Guardar
               FnMenuOpcionOnOff(opcArchivoGuardar,true);
               FnMenuOpcionOnOff(GTK_WIDGET(itemGuardar),true);

               // Establece imagen normal
               gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemGuardar),iconGuardar);
               gtk_widget_show_all(GTK_WIDGET(toolbar));
          }

          // Obtiene la Información de donde está el cursor
          gtk_text_buffer_get_iter_at_mark(buffer,&iter, gtk_text_buffer_get_insert(buffer));


          // Obtiene el Row y la Col
          gIntRow = gtk_text_iter_get_line(&iter);
          gIntCol = gtk_text_iter_get_line_offset(&iter);

          // Construye el Mensaje
          msg = g_strdup_printf("%s%s | Lin: %d Col: %d", gstrRuta.c_str(),gstrArchivo.c_str(), gIntRow+1, gIntCol+1);

          // Coloca la Información en el Status Bar
          FnBarraEstadoMensaje(msg);

          // Libera la Memoria
          g_free(msg);

          // Se insertan los espacios del Indent
          if (gIntIndent > 0)
          {

             // Ciclo para Crear el Vector con Espacios
             for (iCtaSpaces=0; iCtaSpaces<gIntIndent; iCtaSpaces++)

                 // Coloca el Espacio
                 gStrSpaces[iCtaSpaces]=' ';

             // Coloca el Caracter Nulo
             gStrSpaces[iCtaSpaces]='\0';

             // IMPORTANTE Lo coloca en 0 para inicializar y evitar que entrara en Ciclo Infinito
             gIntIndent=0;

             // Deshabilita Procesando
             gBoolProcesando=true;

             // Inserta Espacios
             FnInsertSpaceIndent();

             //gtk_text_view_new_with_buffer (bufferEditor);
             gBoolProcesando=false;


          }

          // Función que codifica el Texto a Color
          FnCodificaCodigoColor();

       }
    }
}


// Funcion para controlar Archivo Nuevo
void FnMenuArchivoNuevo(GtkWidget *widget)
{
   // Coloca el nombre del Archivo Nuevo
   gstrArchivo="SinTitulo.cpp";

   // Llama a la función que establece el Titulo de la App
   FnAplicacionTitulo();

   // Coloca un Mensaje en la Barra de Estado
   FnBarraEstadoMensaje(gstrArchivo.c_str());

   // Establece el Editor Habilitado
   FnEditorOnOff(true);

   // Desactiva las opciones de Nuevo y Abrir
   FnMenuOpcionOnOff(opcArchivoNuevo,false);
   FnMenuOpcionOnOff(opcArchivoAbrir,false);
   FnMenuOpcionOnOff(GTK_WIDGET(itemNuevo),false);
   FnMenuOpcionOnOff(GTK_WIDGET(itemAbrir),false);

   // Imagenes Gray
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemNuevo),iconNuevoGray);
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemAbrir),iconAbrirGray);
   gtk_widget_show_all(GTK_WIDGET(toolbar));

   // Activa las opciones de Guardar, Guardar Como y Cerrar
   FnMenuOpcionOnOff(opcArchivoGuardar,true);
   FnMenuOpcionOnOff(opcArchivoGuardarComo,true);
   FnMenuOpcionOnOff(opcArchivoCerrar,true);
   FnMenuOpcionOnOff(GTK_WIDGET(itemGuardar),true);
   FnMenuOpcionOnOff(GTK_WIDGET(itemGuardarComo),true);

   // Imagenes Normales
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemGuardar),iconGuardar);
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemGuardarComo),iconGuardarComo);
   gtk_widget_show_all(GTK_WIDGET(toolbar));

   // Archivo Creado
   gbTextoInsertado=true;

   // Se Activa la opción de Pegar del Menu Edición
   FnMenuOpcionOnOff(opcEdicionPegar,TRUE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionPegar),TRUE);
   // Imagen normal
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionPegar),iconEdicionPegar);
   gtk_widget_show_all(GTK_WIDGET(toolbar));

   // Se activan las opciones de buscar y reemplazar
   FnMenuOpcionOnOff(opcBuscarEncontrar,TRUE);
   FnMenuOpcionOnOff(opcBuscarReemplazar,TRUE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemBuscarEncontrar),TRUE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemBuscarReemplazar),TRUE);
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemBuscarEncontrar),iconBuscarEncontrar);
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemBuscarReemplazar),iconBuscarReemplazar);

   // Se actualiza la barra de herramientas
   gtk_widget_show_all(GTK_WIDGET(toolbar));

}


// Función para Guardar el Archivo
void FnMenuArchivoGuardar(GtkToolItem *item,GtkWindow *window)
{

    // Variable para el Diálogo
    GtkWidget *dialog;

    // Variable para el Nombre del Archivo
    gchar *filename;
    string sArchivo;

    // Verifica primeramente si el archivo ya fue guardado
    if (! gbArchivoGuardado)
    {

        // Ejecuta el Diálogo
        dialog = gtk_file_chooser_dialog_new (
                 "Save File As ...",                   // Titulo de la Ventana
                 window,                               // Ventana Padre
                 GTK_FILE_CHOOSER_ACTION_SAVE,         // La acción que intenta realizar
                 ("_Cancel"),GTK_RESPONSE_CANCEL,      // Botón y su Respuesta
                 ("_Save"), GTK_RESPONSE_ACCEPT,       // Botón y su Respuesta
                 NULL);

        // Establece el Archivo por Default antes de ejecutar el Diálogo
        gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER(dialog),gstrArchivo.c_str());

        // Establece confirmación de overwrite en caso de que el archivo exista
        gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(dialog), TRUE);

        // Obtiene el Resultado
        gint result = gtk_dialog_run (GTK_DIALOG (dialog));

        // Verifica que haya aceptado la indicación del Archivo
        if (result == GTK_RESPONSE_ACCEPT)
        {
            // Obtiene el Nombre del Archivo
            filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));

            // Colocamos el Nombre del Archivo en la variable Global
            sArchivo = filename;

            // LLama a la función que obtiene la ruta y el nombre del Archivo
            FnArchivoRutaNombre(sArchivo);

            // Llama a función que graba el Archivo a Disco
            FnArchivoGrabar(); // Aguas con esto verificar si hubo error

            // Verifico que no hay error
            if (! gbError)
            {
                // Llama a función que actualiza el titulo de la Ventana
                FnAplicacionTitulo();

                // Actualiza la Barra de Estado
                FnEditorTextChange(bufferEditor, GTK_STATUSBAR(statusbar));

                // Cambia el Status de la Variable global
                gbArchivoGuardado=true;

            }
            else
                // Actualiza el Error
                gbError=FALSE;


        }
        // Destruye el diálogo
        gtk_widget_destroy (dialog);

    }
    else

        // Llama a función que graba el Archivo a Disco
        FnArchivoGrabar();

    // AVANCE
    if (gbArchivoGuardado)
    {
        // Se activan las opciones de Crear
        FnMenuOpcionOnOff(opcCrearCompilar,TRUE);
        FnMenuOpcionOnOff(opcCrearEjecutar,TRUE);
        FnMenuOpcionOnOff(opcCrearCompilarEjecutar,TRUE);
        FnMenuOpcionOnOff(GTK_WIDGET(itemCrearCompilar),TRUE);
        FnMenuOpcionOnOff(GTK_WIDGET(itemCrearEjecutar),TRUE);
        FnMenuOpcionOnOff(GTK_WIDGET(itemCrearCompilarEjecutar),TRUE);
        gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemCrearCompilar),iconCrearCompilar);
        gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemCrearEjecutar),iconCrearEjecutar);
        gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemCrearCompilarEjecutar),iconCrearCompilarEjecutar);
    }
}


// Función para obtener la Ruta y el Nombre del Archivo que se edit
void FnArchivoRutaNombre(string sArchivo)
{
   // Desplegamos para Visualización
   size_t found = sArchivo.find_last_of("/\\");

   // Coloca la ruta y el Archivo en las Variables Globales
   gstrRuta    = sArchivo.substr(0,found+1);
   gstrArchivo = sArchivo.substr(found+1);

   // AVANCE
   size_t found2= gstrArchivo.find_last_of(".");
   gstrExecutable =gstrArchivo.substr(0,found2);


}

// Función que Graba la Información del Archivo en Disco--------------------------------------------------------------------------------------------------
void FnArchivoGrabar()
{
   // Definición de Variables
   GtkTextIter iterInicio,iterFinal;  // Ubicación
   gchar      *strTexto;              // Obtener el Texto
   gchar      *strFile;               // Nombre del Archivo
   GError *error = NULL;

   // Obtiene el Inicio y Final del Buffer
   gtk_text_buffer_get_start_iter (bufferEditor, &iterInicio);
   gtk_text_buffer_get_end_iter   (bufferEditor, &iterFinal);

   // Obtiene el Texto del Buffer
   strTexto = gtk_text_buffer_get_text (bufferEditor, &iterInicio, &iterFinal, FALSE);

   // Construyo el Nombre del Archivo
   strFile = g_strdup_printf("%s%s", gstrRuta.c_str(), gstrArchivo.c_str());

   // Graba el Contenido al archivo
   g_file_set_contents (strFile,strTexto, -1, &error);

   // Verifica si hay error
   if (error != NULL)
   {
      // Despliega el Dialogo con el Error
      FnAplicacionMensajeError(error->message);

      // Despliega el Error en la Consola y lo manda al status bar
      g_print("%s \n",error->message);
      g_clear_error (&error);

      // Actualiza variable global de Error
      gbError=TRUE;

   }

   // Se modifica bandera de que no se ha modificado
   gintArchivoModificado=2;

   // Desactivamos opción de Guardar
   FnMenuOpcionOnOff(opcArchivoGuardar,false);
   FnMenuOpcionOnOff(GTK_WIDGET(itemGuardar),false);

   // Imagen Gray
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemGuardar),iconGuardarGray);
   gtk_widget_show_all(GTK_WIDGET(toolbar));

   // Se libera la Memoria
   g_free (strTexto);
   g_free (strFile);



}

// Función para Guardar el Archivo
void FnMenuArchivoGuardarComo(GtkToolItem *item,GtkWindow *window)
{

    // Variable para el Diálogo
    GtkWidget *dialog;

    // Variable para el Nombre del Archivo
    gchar *filename;
    string sArchivo;


    // Ejecuta el Diálogo
    dialog = gtk_file_chooser_dialog_new (
             "Save File As ...",                   // Titulo de la Ventana
             window,                               // Ventana Padre
             GTK_FILE_CHOOSER_ACTION_SAVE,         // La acción que intenta realizar
             ("_Cancel"),GTK_RESPONSE_CANCEL,      // Botón y su Respuesta
             ("_Save"), GTK_RESPONSE_ACCEPT,       // Botón y su Respuesta
             NULL);

    // Establece el Archivo por Default antes de ejecutar el Diálogo
    gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER(dialog),gstrArchivo.c_str());

    // Establece confirmación de overwrite en caso de que el archivo exista
    gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(dialog), TRUE);

    // Obtiene el Resultado
    gint result = gtk_dialog_run (GTK_DIALOG (dialog));


    // Verifica que haya aceptado la indicación del Archivo
    if (result == GTK_RESPONSE_ACCEPT)
    {
        // Obtiene el Nombre del Archivo
        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));

        // Colocamos el Nombre del Archivo en la variable Global
        sArchivo = filename;

        // LLama a la función que obtiene la ruta y el nombre del Archivo
        FnArchivoRutaNombre(sArchivo);

        // Llama a función que graba el Archivo a Disco
        FnArchivoGrabar();

        // Verifico que no hay error
        if (! gbError)
        {
            // Llama a función que actualiza el titulo de la Ventana
            FnAplicacionTitulo();

            // Actualiza la Barra de Estado
            FnEditorTextChange(bufferEditor, GTK_STATUSBAR(statusbar));

            // Cambia el Status de la Variable global
            gbArchivoGuardado=true;
        }
        else
            gbError=FALSE;

    }
    // Destruye el diálogo
    gtk_widget_destroy (dialog);

}


// Función para controlar el Cambio del Cursor
void FnEditorCursorChange(GtkTextBuffer *buffer,const GtkTextIter *new_location,GtkTextMark *mark,
                           gpointer data)
{

    // Actualiza Como si hubiera cambiado el Texto
    FnEditorTextChange(buffer, GTK_STATUSBAR(data));
}

// Función para Cerrar el Archivo
void FnMenuArchivoCerrar(GtkWidget *opcCerrar,GtkWindow *window)
{
   // Variable para la Respuesta
   gint giRespuesta;

   // Definición de Variables
   GtkTextIter iterInicio,iterFinal;  // Ubicación

   // Variable para el Diálogo
   GtkWidget *dialog;

   // Verifica que el Archivo no esté modificado
   if (gintArchivoModificado==0)
   {

      // Crea el Diálogo
      dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_WARNING,
                GTK_BUTTONS_YES_NO,
                "El Archivo ha sido modificado. \n ¿ Desea Guardar antes de Cerrar ?");

      // Coloca el Título para la Ventana de Pregunta
      gtk_window_set_title(GTK_WINDOW(dialog), gstrAplicacion.c_str());

      // Ejecuta el Diálogo
      giRespuesta=gtk_dialog_run(GTK_DIALOG(dialog));

      // Verifica la Respuesta
      if (giRespuesta==GTK_RESPONSE_YES)
      {

         // Verifica si ya se ha grabado el archivo
         if (gbArchivoGuardado)
            // Llama a la función de Grabar
            FnArchivoGrabar();
         else
            // Llama a función Guardar Como
            FnMenuArchivoGuardarComo(itemGuardar,window);

         // Limpia los Vectores del Undo y Redo
         gvecUndoRedo.clear();
         gvecCursorCol.clear();
         gvecCursorRow.clear();

         // Actualiza las variables de Control del Undo y Redo
         gintUndoRedoIndice=-1;
         gbTextoInsertado=false;

     }
      // Destruye el Diálogo
      gtk_widget_destroy(dialog);
   }


   // Desactiva y Activa las opciones Adecuadas
   FnMenuOpcionOnOff(opcArchivoAbrir,true);
   FnMenuOpcionOnOff(opcArchivoNuevo,true);
   FnMenuOpcionOnOff(GTK_WIDGET(itemAbrir),TRUE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemNuevo),TRUE);
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemAbrir),iconAbrir);
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemNuevo),iconNuevo);


   FnMenuOpcionOnOff(opcArchivoGuardar,false);
   FnMenuOpcionOnOff(opcArchivoGuardarComo,false);
   FnMenuOpcionOnOff(opcArchivoCerrar,false);
   FnMenuOpcionOnOff(GTK_WIDGET(itemGuardar),FALSE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemGuardarComo),FALSE);
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemGuardar),iconGuardarGray);
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemGuardarComo),iconGuardarComoGray);


   // Obtiene el Inicio y Final del Buffer para borrar
   gtk_text_buffer_get_start_iter (bufferEditor, &iterInicio);
   gtk_text_buffer_get_end_iter   (bufferEditor, &iterFinal);

   // Elimina del BUffer
   gtk_text_buffer_delete (bufferEditor, &iterInicio,&iterFinal);

   // Deshabilita el Editor
   FnEditorOnOff(FALSE);

   // Desactiva bandera de Creado
   // OJO gbCapturaIniciada=false;
   gbTextoInsertado=false;
   gbArchivoGuardado=false;

   // Actualizamos las variables globales de Archivo
   gstrArchivo="";
   gstrRuta="";

   // Actualizamos Título y Barra de Estado
   FnAplicacionTitulo();
   FnBarraEstadoMensaje("Listo");

   // Se Desactiva la opción de Pegar del Menu Edición
   FnMenuOpcionOnOff(opcEdicionPegar,FALSE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionPegar),FALSE);
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionPegar),iconEdicionPegarGray);



   // Se desactivan las opciones de buscar y reemplazar
   FnMenuOpcionOnOff(opcBuscarEncontrar,FALSE);
   FnMenuOpcionOnOff(opcBuscarReemplazar,FALSE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemBuscarEncontrar),FALSE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemBuscarReemplazar),FALSE);
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemBuscarEncontrar),iconBuscarEncontrarGray);
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemBuscarReemplazar),iconBuscarReemplazarGray);


   // Se desactivan la edición
   FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionUndo),FALSE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionRedo),FALSE);
   FnMenuOpcionOnOff(GTK_WIDGET(opcEdicionUndo),FALSE);
   FnMenuOpcionOnOff(GTK_WIDGET(opcEdicionRedo),FALSE);
   FnMenuOpcionOnOff(GTK_WIDGET(opcEdicionUndoClear),FALSE);
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionUndo),iconEdicionUndoGray);
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionRedo),iconEdicionRedoGray);


   // Se desactivan las opciones de Crear
   FnMenuOpcionOnOff(opcCrearCompilar,FALSE);
   FnMenuOpcionOnOff(opcCrearEjecutar,FALSE);
   FnMenuOpcionOnOff(opcCrearCompilarEjecutar,FALSE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemCrearCompilar),FALSE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemCrearEjecutar),FALSE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemCrearCompilarEjecutar),FALSE);
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemCrearCompilar),iconCrearCompilarGray);
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemCrearEjecutar),iconCrearEjecutarGray);
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemCrearCompilarEjecutar),iconCrearCompilarEjecutarGray);

   // Se actualiza la barra de herramientas
   gtk_widget_show_all(GTK_WIDGET(toolbar));

}

// Función para Salir de la Aplicación
void FnMenuArchivoSalir(GtkWidget *opcSalir, GtkWindow *window)
{
  // Variable para la Respuesta
  gint giRespuesta;

  // Definición de Variables
  GtkTextIter iterInicio,iterFinal;  // Ubicación

  // Variable para el Diálogo
  GtkWidget *dialog;

  // Verifica que el Archivo no esté modificado
  // OJO if (gbCapturaIniciada && gintArchivoModificado==0)
  if (gbTextoInsertado && gintArchivoModificado==0)
  {

      // Crea el Diálogo
      dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_WARNING,
                GTK_BUTTONS_YES_NO,
                "El Archivo ha sido Iniciado. \n ¿ Desea Guardar antes de Cerrar ?");

      // Coloca el Título para la Ventana de Pregunta
      gtk_window_set_title(GTK_WINDOW(dialog), gstrAplicacion.c_str());

      // Ejecuta el Diálogo
      giRespuesta=gtk_dialog_run(GTK_DIALOG(dialog));

      // Verifica la Respuesta
      if (giRespuesta==GTK_RESPONSE_YES)

         // Verifica si ya se ha grabado el archivo
         if (gbArchivoGuardado)
            // Llama a la función de Grabar
            FnArchivoGrabar();
         else
            // Llama a función Guardar Como
            FnMenuArchivoGuardarComo(itemGuardar,window);

      // Destruye el Diálogo
      gtk_widget_destroy(dialog);
  }

    // Llama a la función de la Librería que sale del Ciclo Main
    gtk_main_quit();
}

// Función para Abrir el Archivo
void FnMenuArchivoAbrir(GtkWidget *opcAbrir,GtkWindow *window)
{
    // Variable para el Diálogo
    GtkWidget *dialog;

    // Variable para el Nombre del Archivo
    gchar *filename;
    string sArchivo;


    // Ejecuta el Diálogo
    dialog = gtk_file_chooser_dialog_new (
             "Open File ...",                   // Titulo de la Ventana
             window,                               // Ventana Padre
             GTK_FILE_CHOOSER_ACTION_OPEN,         // La acción que intenta realizar
             ("_Cancel"),GTK_RESPONSE_CANCEL,      // Botón y su Respuesta
             ("_Open"), GTK_RESPONSE_ACCEPT,       // Botón y su Respuesta
             NULL);

    // Obtiene el Resultado
    gint result = gtk_dialog_run (GTK_DIALOG (dialog));

    // Verifica que haya aceptado la indicación del Archivo
    if (result == GTK_RESPONSE_ACCEPT)
    {
        // Obtiene el Nombre del Archivo
        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));

        // Colocamos el Nombre del Archivo en la variable Global
        sArchivo = filename;

        // LLama a la función que obtiene la ruta y el nombre del Archivo
        FnArchivoRutaNombre(sArchivo);

        // Llama a función que lee el Archivo de Disco
        FnArchivoLeer();

        if (!gbError)
        {
            // Llama a función que actualiza el titulo de la Ventana
            FnAplicacionTitulo();

            // Actualiza la Barra de Estado
            FnEditorTextChange(bufferEditor, GTK_STATUSBAR(statusbar));

            // Se Activa la opción de Pegar del Menu Edición
            FnMenuOpcionOnOff(opcEdicionPegar,TRUE);
            FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionPegar),TRUE);
            gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionPegar),iconEdicionPegar);
            gtk_widget_show_all(GTK_WIDGET(toolbar));

            // Llama a función que llena el buffer con el texto
            FnBufferUndoRedo();

            // Como el Archivo ya existe, ya está guardado
            gbArchivoGuardado=true;

            // AVANCE
            // Obtengo las Lineas Totales
            gIntRow = gtk_text_buffer_get_line_count (bufferEditor)-1;

            // Inicializo Pegado de Texto a LInea 0
            gIntRowPegadoTexto=0;

            // Codifica el color
            FnCodificaCodigoColor();

        }
        else

            // Inicializa variable de Error
            gbError=FALSE;


    }
    // Destruye el diálogo
    gtk_widget_destroy (dialog);

    // Se activan las opciones de buscar y reemplazar
    FnMenuOpcionOnOff(opcBuscarEncontrar,TRUE);
    FnMenuOpcionOnOff(opcBuscarReemplazar,TRUE);
    FnMenuOpcionOnOff(GTK_WIDGET(itemBuscarEncontrar),TRUE);
    FnMenuOpcionOnOff(GTK_WIDGET(itemBuscarReemplazar),TRUE);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemBuscarEncontrar),iconBuscarEncontrar);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemBuscarReemplazar),iconBuscarReemplazar);


    // AVANCE
    // Se activan las opciones de Crear
    FnMenuOpcionOnOff(opcCrearCompilar,TRUE);
    FnMenuOpcionOnOff(opcCrearEjecutar,TRUE);
    FnMenuOpcionOnOff(opcCrearCompilarEjecutar,TRUE);
    FnMenuOpcionOnOff(GTK_WIDGET(itemCrearCompilar),TRUE);
    FnMenuOpcionOnOff(GTK_WIDGET(itemCrearEjecutar),TRUE);
    FnMenuOpcionOnOff(GTK_WIDGET(itemCrearCompilarEjecutar),TRUE);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemCrearCompilar),iconCrearCompilar);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemCrearEjecutar),iconCrearEjecutar);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemCrearCompilarEjecutar),iconCrearCompilarEjecutar);

    // Se actualiza la barra de herramientas
    gtk_widget_show_all(GTK_WIDGET(toolbar));

}


// Función para Leer un Archivo
void FnArchivoLeer()
{
   // Variables
   gsize bytes;                       // Bytes Leidos
   gchar      *strFile;               // Nombre del Archivo
   gchar      *strContenido;          // Nombre del Archivo
   GError *error = NULL;              // Variable para el Control del Error

   // Construyo el Nombre del Archivo
   strFile = g_strdup_printf("%s%s", gstrRuta.c_str(), gstrArchivo.c_str());

   // Lee el Archivo
   g_file_get_contents (strFile, &strContenido, &bytes, &error);

   // Verifica si hay error
   if (error != NULL)
   {
      // Despliega el Dialogo con el Error
      FnAplicacionMensajeError(error->message);

      // Despliega el Error en la Consola y lo manda al status bar
      g_print("%s \n",error->message);
      g_clear_error (&error);

      // Actualiza variable global de Error
      gbError=TRUE;
   }
   else
   {
       // Activamos y Desactivamos opción de Guardar
       FnMenuOpcionOnOff(opcArchivoGuardarComo,true);
       FnMenuOpcionOnOff(GTK_WIDGET(itemGuardarComo),true);
       gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemGuardarComo),iconGuardarComo);
       FnMenuOpcionOnOff(opcArchivoCerrar,true);
       FnMenuOpcionOnOff(opcArchivoNuevo,false);
       FnMenuOpcionOnOff(GTK_WIDGET(itemNuevo),false);
       gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemNuevo),iconNuevoGray);
       FnMenuOpcionOnOff(opcArchivoAbrir,false);
       FnMenuOpcionOnOff(GTK_WIDGET(itemAbrir),false);
       gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemAbrir),iconAbrirGray);
       gtk_widget_show_all(GTK_WIDGET(toolbar));

       // Insertamos el Text
       gtk_text_buffer_set_text (bufferEditor, strContenido, -1);

       // Habilita el Editor
       FnEditorOnOff(TRUE);

       // Se modifica bandera de que no se ha modificado
       gintArchivoModificado=2;
   }

   // Se libera la memoria
   g_free (strContenido);
   g_free (strFile);

}


// Función para Inicializar Vectores de Código de Color
void FnInicializaVectoresCodigoColor()
{

   // Inicializa el vector con palabras reservadas
   gvecReservadas.push_back("auto");
   gvecReservadas.push_back("break");
   gvecReservadas.push_back("case");
   gvecReservadas.push_back("char");
   gvecReservadas.push_back("const");
   gvecReservadas.push_back("continue");
   gvecReservadas.push_back("default");
   gvecReservadas.push_back("do");
   gvecReservadas.push_back("double");
   gvecReservadas.push_back("else");
   gvecReservadas.push_back("enum");
   gvecReservadas.push_back("extern");
   gvecReservadas.push_back("float");
   gvecReservadas.push_back("for");
   gvecReservadas.push_back("goto");
   gvecReservadas.push_back("if");
   gvecReservadas.push_back("int");
   gvecReservadas.push_back("long");
   gvecReservadas.push_back("register");
   gvecReservadas.push_back("return");
   gvecReservadas.push_back("short");
   gvecReservadas.push_back("signed");
   gvecReservadas.push_back("sizeof");
   gvecReservadas.push_back("static");
   gvecReservadas.push_back("struct");
   gvecReservadas.push_back("switch");
   gvecReservadas.push_back("typedef");
   gvecReservadas.push_back("union");
   gvecReservadas.push_back("unsigned");
   gvecReservadas.push_back("void");
   gvecReservadas.push_back("volatile");
   gvecReservadas.push_back("while");

   // Inicializa el vector de Caracteres Especiales
   gvecEspeciales.push_back(",");
   gvecEspeciales.push_back(".");
   gvecEspeciales.push_back(";");
   gvecEspeciales.push_back(":");
   gvecEspeciales.push_back("'");
   gvecEspeciales.push_back("\"");
   gvecEspeciales.push_back("(");
   gvecEspeciales.push_back(")");
   gvecEspeciales.push_back("[");
   gvecEspeciales.push_back("]");
   gvecEspeciales.push_back("{");
   gvecEspeciales.push_back("}");
   gvecEspeciales.push_back("<");
   gvecEspeciales.push_back("!");
   gvecEspeciales.push_back("|");
   gvecEspeciales.push_back("/");
   gvecEspeciales.push_back("\\");
   gvecEspeciales.push_back("~");
   gvecEspeciales.push_back("+");
   gvecEspeciales.push_back("#");
   gvecEspeciales.push_back("%");
   gvecEspeciales.push_back("&");
   gvecEspeciales.push_back("^");
   gvecEspeciales.push_back("*");
   gvecEspeciales.push_back("-");
   gvecEspeciales.push_back("=");
   gvecEspeciales.push_back(">");

}

// Función para validar que es caracter especial
bool FnBoolCaracterEspecial(char *xChar)
{
   // Busca el Elemento en el Vector
   bool bResult = find(gvecEspeciales.begin(), gvecEspeciales.end(), xChar)!=gvecEspeciales.end();

   // Retorna el Valor
   return bResult;
}


// Función para verifica si solo tiene espacios
bool FnBoolVerificaSoloEspacios(char *strCadena)
{

    // Variables
    int  iPosCadena;              // Indice de la Cadena a Procesar
    bool bResult=true;            // Para retornar

    // Verifica si hay caracteres en la cadena
    if (strlen(strCadena)>0)

        // Ciclo para recorrer la Cadena a Procesar
        for (iPosCadena=0; iPosCadena < (int)strlen(strCadena); iPosCadena++)
        {
            // Verifica que no sea espacio en blanco
            if (strCadena[iPosCadena]!=32)
            {
               // Cambia el Result y sale del Proceso
               bResult = false;

               // Sale del Ciclo
               break;
            }
        }
    else
       bResult=false;

    // Retorna el Resultado
    return bResult;

}

// Función para Codificar el Código Fuente a Color
void FnCodificaCodigoColor()
{

  // Declaración de Variables
  int         iCtaLineas;      // Contador de Líneas

  // Verifica si hubo pegado de texto
  if (gIntRowPegadoTexto>=0)
  {

     // Mensaje
     //g_print("Hubo Pegado de Texto %d - %d \n", gIntRowPegadoTexto, gIntRow);

     // Procesa las lineas pegadas
     for (iCtaLineas=gIntRowPegadoTexto; iCtaLineas<gIntRow; iCtaLineas++)
     {
         // Llama a la función
         //g_print("Lin:%d \n",iCtaLineas);
         FnProcesaLinea(iCtaLineas);

     }

     // Coloca de nuevo la Variable en -1
     gIntRowPegadoTexto=-1;

  }
  else
  {
     // Llama a la Función con la Línea Actual
     FnProcesaLinea(gIntRow);
  }


}


// Función que procesa una línea para codificar el Color
void FnProcesaLinea(gint giLinea)
{
  // Variables
  GtkTextIter iterLineaIni;    // Para el Inicio de la Linea
  GtkTextIter iterLineaFin;    // Para el Final de la Línea
  GtkTextIter iterLineaIniTmp; // Inicial Temporal
  GtkTextIter start_match;     // Inicio del Match
  GtkTextIter end_match;       // Final de Match
  gint        giOffIni;        // Offset Inicial
  gint        giOffFin;        // Offset Final
  GtkTextIter iterNextChar;    // iter del Caracter Siguiente
  GtkTextIter iterPrevChar;    // iter del Caracter Previo
  gchar       *xNextChar;      // El siguiente caracter
  gchar       *xPrevChar;      // El caracter previo
  bool        bTagOk;          // Aplicar el Tag
  int         iLineasTotales;  // Obtener las Lineas Totales del Buffer

  // Obtengo el iter al Inicio de la Línea
  gtk_text_buffer_get_iter_at_line (bufferEditor,&iterLineaIni,giLinea);

  // Obtengo las Lineas Totales
  iLineasTotales = gtk_text_buffer_get_line_count (bufferEditor)-1;


  // Verifico las lineas
  if ( giLinea+1 < iLineasTotales)


     // Obtengo el iter de la Linea Siguiente que es el fin de la presente
     gtk_text_buffer_get_iter_at_line (bufferEditor,&iterLineaFin,giLinea+1);


  else


     // Obtengo el Iter Final del Texto
     gtk_text_buffer_get_end_iter(bufferEditor,&iterLineaFin);


  // Obtengo el texto de la Linea
  gchar *xLinea = gtk_text_buffer_get_text (bufferEditor,&iterLineaIni,&iterLineaFin,false);


  // Remueve el tag de Comentarios
  gtk_text_buffer_remove_tag_by_name(bufferEditor, "comentarios",&iterLineaIni, &iterLineaFin);

  // Inicializamos Desplazamiento
  giOffIni = 0;


  // Primero buscamos comentarios
  if (gtk_text_iter_forward_search(&iterLineaIni,
                               "//", // El Símbolo para los comentarios
                               GtkTextSearchFlags(GTK_TEXT_SEARCH_TEXT_ONLY |
                               GTK_TEXT_SEARCH_VISIBLE_ONLY),
                               &start_match,
                               &end_match,
                               &iterLineaFin))
  {

     // Obtenemos Desplazamiento para verificar si está al Inicio
     giOffIni = gtk_text_iter_get_offset(&start_match);

     // A partir de donde se encontró hasta el final de la linea, se aplican comentarios
     gtk_text_buffer_apply_tag_by_name(bufferEditor, "comentarios",&start_match, &iterLineaFin);

  }


  // Verifica si no lo encontró al Inicio
  if (giOffIni > 0)
  {
     // Coloca el inicio del Primer Match como fin de la Linea
     iterLineaFin = start_match;
  }


  // Obtengo el texto de la Linea
  xLinea = gtk_text_buffer_get_text (bufferEditor,&iterLineaIni,&iterLineaFin,false);


  // Despliego la Linea obtenida
  //g_print("Linea Sin Comentarios: [%s] \n",xLinea);


  // Verifica que no tenga solo espacios
  if (! FnBoolVerificaSoloEspacios(xLinea))
  {

      // Remueve el Tag de la palabra reservada
      gtk_text_buffer_remove_tag_by_name(bufferEditor, "reservadas",&iterLineaIni, &iterLineaFin);



      // Ciclo para buscar cada una de las palabras reservadas
      //mostrar las componentes con un ciclo
      for (unsigned int i=0; i<gvecReservadas.size(); i++)
      {

          // Guarda el Inicio en el temporal
          iterLineaIniTmp = iterLineaIni;


          // Ciclo para buscar en el Texto del Buffer
          while (gtk_text_iter_forward_search(&iterLineaIniTmp,
                                               gvecReservadas[i].c_str(),
                                               GtkTextSearchFlags(GTK_TEXT_SEARCH_TEXT_ONLY |
                                                                  GTK_TEXT_SEARCH_VISIBLE_ONLY),
                                              &start_match,
                                              &end_match,
                                              &iterLineaFin))
          {

              // Obtengo los desplazamiento del inicio y final donde lo encontro
              giOffIni = gtk_text_iter_get_offset(&start_match);
              giOffFin = gtk_text_iter_get_offset(&end_match);

              // Obtiene el Desplazamiento al siguiente caracter
              gtk_text_buffer_get_iter_at_offset(bufferEditor,&iterNextChar, giOffFin+1);

              // Obtengo
              xNextChar = gtk_text_buffer_get_text (bufferEditor,&end_match,&iterNextChar,false);

              // Inicializa el Tag a False
              bTagOk=false;

              // Verifica si debe aplicar el tag
              // Si está al Inicio
              if (giOffIni==0)
              {

                 // Está al Final
                 if (strlen(xNextChar)==0)

                    // Tag Ok
                    bTagOk=true;

                 else

                    // Compara si es espacio en blanco o Caracter Especial o Cambio de Linea
                    if (strcmp(xNextChar," ")==0 || FnBoolCaracterEspecial(xNextChar) || xNextChar[0]==10)
                       bTagOk=true;
              }

              else
              {

                 // Obtiene el Desplazamiento al caracter previo
                 gtk_text_buffer_get_iter_at_offset(bufferEditor,&iterPrevChar, giOffIni-1);

                 // Obtengo el Caracter Previo
                 xPrevChar = gtk_text_buffer_get_text (bufferEditor,&iterPrevChar,&start_match,false);

                 // Verifica si debe aplicar el Tag
                 if (strcmp(xPrevChar," ")==0 || FnBoolCaracterEspecial(xPrevChar) || xPrevChar[0]==10)

                     // Está al Final
                     if (strlen(xNextChar)==0)

                        // Tag Ok
                        bTagOk=true;

                     else

                        // Compara si es espacio en blancp
                        if (strcmp(xNextChar," ")==0 || FnBoolCaracterEspecial(xNextChar) || xNextChar[0]==10)
                           bTagOk=true;

              }

              // Si TagOk aplica
              if (bTagOk)
                 // Aplica el Tag al buffer, en donde encotré el texto; start_match y end_match
                 gtk_text_buffer_apply_tag_by_name(bufferEditor, "reservadas",&start_match, &end_match);

              // ----------------------------------------------------------------------------------
              // Obtiene el desplazamiento al final del match
              gint offset = gtk_text_iter_get_offset(&end_match);

              // Obtiene el nuevo start_find, a partir del offset
              gtk_text_buffer_get_iter_at_offset(bufferEditor,&iterLineaIniTmp, offset);

          }

      }


      // Remueve el Tag de especiales
      gtk_text_buffer_remove_tag_by_name(bufferEditor, "especiales",&iterLineaIni, &iterLineaFin);

      // Ciclo para buscar cada una de las palabras reservadas
      //mostrar las componentes con un ciclo
      for (unsigned int i=0; i<gvecEspeciales.size(); i++)
      {

          // Guarda el Inicio en el temporal
          iterLineaIniTmp = iterLineaIni;

          // Ciclo para buscar en el Texto del Buffer
          while (gtk_text_iter_forward_search(&iterLineaIniTmp,
                                               gvecEspeciales[i].c_str(),
                                               GtkTextSearchFlags(GTK_TEXT_SEARCH_TEXT_ONLY |
                                                                  GTK_TEXT_SEARCH_VISIBLE_ONLY),
                                              &start_match,
                                              &end_match,
                                              &iterLineaFin))
          {

              // Aplica el Tag al buffer, en donde encotré el texto; start_match y end_match
              gtk_text_buffer_apply_tag_by_name(bufferEditor, "especiales",&start_match, &end_match);

              // ----------------------------------------------------------------------------------
              // Obtiene el desplazamiento alel final del match
              gint offset = gtk_text_iter_get_offset(&end_match);

              // Obtiene el nuevo start_find, a partir del offset
              gtk_text_buffer_get_iter_at_offset(bufferEditor,&iterLineaIniTmp, offset);
          }

      }
  }
}

// Función para controlar el Pegado de texto
void FnEditorPasteDone()
{

   // Procesa las lineas pegadas
   for (int iCtaLineas=0; iCtaLineas<gIntRow; iCtaLineas++)
   {
         // Llama a la función
         FnProcesaLinea(iCtaLineas);

   }

   // Verifica si no hay algo guardado en el Buffer
   if (gintUndoRedoIndice==-1)
   {
      // Si no hay guardado pone algo en blanco
      // Agregando al vector de Undo
      gvecUndoRedo.push_back("");
      gintUndoRedoIndice=gvecUndoRedo.size()-1;

   }

   // Activa Undo
   FnMenuOpcionOnOff(opcEdicionUndo,TRUE);
   FnMenuOpcionOnOff(GTK_WIDGET(itemEdicionUndo),TRUE);

   // Cambia la imagen
   gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemEdicionUndo),iconEdicionUndo);

   // Se actualiza la barra de herramientas
   gtk_widget_show_all(GTK_WIDGET(toolbar));


}



// --------------------------------------------------------------------------------------------------
// Fin de Funciones
// --------------------------------------------------------------------------------------------------
