// --------------------------------------------------------------------------------------------------
// IDE C++
// Editor para Lenguaje C++
// Autor y Derechos Reservados:JAOR
// IDE_FUNCIONES.hpp
// Archivo Header de Funciones Globales
// Objetivo: Crear el FrontEnd de la Aplicación; menus, areas de despliegue
// --------------------------------------------------------------------------------------------------

// Incluye las Funciones para el Menu Archivo
#include "IDE_FN_MENUARCHIVO.hpp"

// Incluye las Funciones para el Menu Edicion
#include "IDE_FN_MENUEDICION.hpp"

// Incluye las Funciones para el Menu Buscar
#include "IDE_FN_MENUBUSCAR.hpp"

// Incluye las Funciones para el Menu Crear
#include "IDE_FN_MENUCREAR.hpp"


// --------------------------------------------------------------------------------------------------
// Prototipo de Funciones
// --------------------------------------------------------------------------------------------------
void FnAppInicializa(); // Inicializa la Ventana Principal

// Función para crear un Item
void FnCreaItemDeMenu(GtkWidget  **xOpcion,
                      GtkWidget  **bOpcion,
                      GtkWidget  **iOpcion,
                      GtkWidget  **lOpcion,
                      const char *iconName,
                      const char *opcName);

// Función para Barra de Estado
void FnBarraEstado();

// Función para Establecer el Mensaje en la Barra de Estado
void FnBarraEstadoMensaje(const char *strMensaje);

// Función para crear una imagen Pixbuf para Icono de Aplicación
GdkPixbuf *FnPixbufCreate(const gchar * filename);

// Función para Cambiar la Fuente
void FnEditorFont(string sFont);

// Función para desactivar o activar una opción del Menu
void FnMenuOpcionOnOff(GtkWidget *xOpcion,bool OnOff);

// Función para establecer el Título
void FnAplicacionTitulo();

// Función para desplegar un Error
void FnAplicacionMensajeError(const char *sMensaje);

// Función para crear la Ventana de Compilación
void FnCreaVentanaCompilacion();

// --------------------------------------------------------------------------------------------------
// Fin de Prototipo de Funciones
// --------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------
// Funciones
// --------------------------------------------------------------------------------------------------

// Función para inicializar la Ventana Principal
void FnAppInicializa()
{

  // Para el Título de la Aplicación
  gchar *strTitulo;

  // Variable para el Color
  GdkRGBA font_color;

  // Creamos la Ventana
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // Maximizamos la Ventana
  gtk_window_maximize(GTK_WINDOW(window));

  // Colocamos el Título
  FnAplicacionTitulo();

  // Estableciendo el Ícono de la Aplicación
  gtk_window_set_icon(GTK_WINDOW(window), FnPixbufCreate("js_ico.jpg"));

  // Establece el Color
  font_color.red =   0.50;
  font_color.green = 1.50;
  font_color.blue =  0.50;
  font_color.alpha = 1;
  gtk_widget_override_background_color(window, GTK_STATE_FLAG_NORMAL, &font_color);

  // Creamos el Contenedor
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);

  // Añadimos el Contenedor a la Ventana Principal
  gtk_container_add(GTK_CONTAINER(window), vbox);

  // Llama a la función que crea el Menu
  // Se coloca la instrcció y se llama a Funcion Crea Menu Archivo
  menuBarra = gtk_menu_bar_new();

  toolbarBox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
  gtk_box_pack_start(GTK_BOX(vbox), menuBarra, FALSE, FALSE, 3);

  // Llamamos a Función para crear Menu Archivo
  FnAppMenuArchivo();

  // Llamamos a Función para crear Menu Edición
  FnAppMenuEdicion();

  // Llamamos a Función para crear Menu Buscar
  FnAppMenuBuscar();

  // AVANCE
  // Llamamos a Función para crear Menu Crear
  FnAppMenuCrear();

  // Llama a la función que crea el Status Bar
  FnBarraEstado();

  // Colocamos un Mensaje en la Barra de Estado
  FnBarraEstadoMensaje("En Linea");

  // Crea la Barra de Herramientas
  toolbar = gtk_toolbar_new();
  gtk_container_add(GTK_CONTAINER(toolbarBox), toolbar);
  gtk_box_pack_start(GTK_BOX(vbox), toolbarBox, FALSE, FALSE, 0);

  // Cambia el Color de Fondo de la Barra de Herramientas
  gtk_widget_override_background_color(toolbar, GTK_STATE_FLAG_NORMAL, &font_color);

  // Llama a Función de Barra Menu Archivo
  FnBarraMenuArchivo();

  // Llama a Función de Barra Menú Edición
  FnBarraMenuEdicion();

  // Crea el Menu de Buscar
  FnBarraMenuBuscar();

  // AVANCE
  // Crea Barra Menu de Crear
  FnBarraMenuCrear();

  // Crea el Editor de Texto
  FnCreaEditorTexto();

  // Crea la Ventana del Compilador
  FnCreaVentanaCompilacion();

  // Mostramos los objetos de la Ventana
  gtk_widget_show_all(window);

  // Se establecen las Señales para Menu Archivo
  FnSenalesMenuArchivo();

  // Se establecen las Señales para Menu Edición
  FnSenalesMenuEdicion();

  // Señales del Menu Buscar
  FnSenalesMenuBuscar();

  // AVANCE
  // Señales de Menu Crear
  FnSenalesMenuCrear();

  // Agrega el Tag para poder dar formato al texto cuando se busca
  gtk_text_buffer_create_tag(bufferEditor, "green_bg","background", "lightgreen", NULL);

  // Agrega los tag para dar formato al Código
  gtk_text_buffer_create_tag(bufferEditor, "reservadas","foreground", gstrReservadasColor.c_str(), NULL);
  gtk_text_buffer_create_tag(bufferEditor, "especiales","foreground", gstrEspecialesColor.c_str(), NULL);
  gtk_text_buffer_create_tag(bufferEditor, "comentarios","foreground", gstrComentariosColor.c_str(), NULL);

}


// Función para crear un Item
void FnCreaItemDeMenu(GtkWidget  **xOpcion,
                      GtkWidget  **bOpcion,
                      GtkWidget  **iOpcion,
                      GtkWidget  **lOpcion,
                      const char *iconName,
                      const char *opcName)
{
  // Crea la opción
  *xOpcion       = gtk_menu_item_new();
  *bOpcion       = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
  *iOpcion       = gtk_image_new_from_icon_name (iconName, GTK_ICON_SIZE_MENU);
  *lOpcion       = gtk_label_new (opcName);
  gtk_container_add (GTK_CONTAINER (*bOpcion), *iOpcion);
  gtk_container_add (GTK_CONTAINER (*bOpcion), *lOpcion);
  gtk_container_add (GTK_CONTAINER (*xOpcion), *bOpcion);
}


// Función para Establecer el Mensaje en la Barra de Estado
void FnBarraEstadoMensaje(const char *strMensaje)
{

  // Elimina el Mensaje Actual
  gtk_statusbar_pop(GTK_STATUSBAR(statusbar),statusbarId);

  // Coloca el Mensaje
  gtk_statusbar_push(GTK_STATUSBAR(statusbar),statusbarId, strMensaje);

}

// Función para Crear la Barra de Estado
void FnBarraEstado()
{

  // Variable para el Color
  GdkRGBA font_color;

  // Creamos el  Statusbar
  statusbar = gtk_statusbar_new();

  // Establece el Color
  font_color.red =   0.5;   // Valores de 0.0-1.0
  font_color.green = 1.0;
  font_color.blue =  0.0;
  font_color.alpha = 1.0;   // The opacidad del color: 0.0 para completamente transparente

  // Coloca el Color de la Fuente del StatusBar
  gtk_widget_override_color(statusbar, GTK_STATE_FLAG_NORMAL, &font_color);

  // Creamos un identificador para la Barra de Estado con una descripción
  statusbarId = gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar), "Mensajes del Sistema");

  // Agregamos un Mensaje
  gtk_statusbar_push(GTK_STATUSBAR(statusbar),statusbarId, "Barra Creada ");

  // Crea el EventBox
  eventstatusbox = gtk_event_box_new();

  // Agregamos el statusbar al eventbox
  gtk_container_add(GTK_CONTAINER(eventstatusbox), statusbar);

  // Establece el Color para el fondo Negro
  font_color.red =   0;
  font_color.green = 0;
  font_color.blue =  0;
  font_color.alpha = 1;

  // Modifica el Color de Fondo del eventbox
  gtk_widget_override_background_color(eventstatusbox, GTK_STATE_FLAG_NORMAL, &font_color);

  // Agrega el eventbox a la Barra de Estado
  gtk_box_pack_end(GTK_BOX(vbox),eventstatusbox, FALSE, FALSE, 0);

}

// Rutina para cargar la Imagen del Icono
GdkPixbuf *FnPixbufCreate(const gchar * filename)
{
   // Variable para abrir el Archivo Imagen
   GdkPixbuf *pixbuf;

   // Variable para error
   GError *error = NULL;

   // Crea la Referencia al Archivo Imagen
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);

   // Verifica que no haya habido error
   if(!pixbuf)
   {
      // Despliega el Mensaje de error
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   // Retorna el Objeto
   return pixbuf;
}

// Función para Cambiar la Fuente
void FnEditorFont(string sFont)
{

   // Establecemos la Fuente
   fontEditor = pango_font_description_from_string (sFont.c_str());

   // Modificamos la Fuente
   gtk_widget_override_font (textviewEditor, fontEditor);
}


// Función para desactivar o activar una opción del Menu
void FnMenuOpcionOnOff(GtkWidget *xOpcion,bool OnOff)
{

   // Activa o desactiva el Menu
   gtk_widget_set_sensitive(xOpcion, OnOff);

}


// Función para establecer el título de la Ventana de la Aplicación
void FnAplicacionTitulo()
{

  // Variable para Construir el Título
  gchar *strTitulo;

  // Construye el Título
  strTitulo = g_strdup_printf("%s | %s | %s",
                              gstrArchivo.c_str(),
                              gstrAplicacion.c_str(),
                              gstrVersion.c_str());

  // Establece el Título
  gtk_window_set_title(GTK_WINDOW(window),strTitulo);

}


// Función para desplegar un Error
void FnAplicacionMensajeError(const gchar *sMensaje)
{

   // Variable para generar el MessageDialog
   GtkWidget *dialog;

   // Crea el MessageDialog
   dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,//GTK_MESSAGE_ERROR
            GTK_BUTTONS_OK,
            "%s",sMensaje);

  // Establece el Título de la Ventana
  gtk_window_set_title(GTK_WINDOW(dialog), gstrAplicacion.c_str());

  // Ejecuta el Diálogo y obtiene su respuesta
  gtk_dialog_run(GTK_DIALOG(dialog));

  // Destruye el Diálogo
  gtk_widget_destroy(dialog);

}

// Función para Crear Ventana de Compilación
void FnCreaVentanaCompilacion()
{
   // Variable para el Color
   GdkRGBA font_color;

   // Crea el Scroll
   scrollCompilacion = gtk_scrolled_window_new (NULL, NULL);

   // Crea el objeto TextView para el Editor de Texto
   textviewCompilacion = gtk_text_view_new ();

   // Establece el Color de la Fuente de la Compilación
   font_color.red =   0.0;   // Valores de 0.0-1.0
   font_color.green = 0.0;
   font_color.blue =  0.0;
   font_color.alpha = 1.0;   // The opacidad del color: 0.0 para completamente transparente


   // Coloca el Color de la Fuente de la Ventana de Compilación
   gtk_widget_override_color(textviewCompilacion, GTK_STATE_FLAG_NORMAL, &font_color);

   // Crea el objeto para el buffer del TextView
   bufferCompilacion = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textviewCompilacion));

   // Añade el TextView al Scroll y el Scroll al Contenedor
   gtk_container_add (GTK_CONTAINER (scrollCompilacion), textviewCompilacion);
   gtk_box_pack_start(GTK_BOX(vbox), scrollCompilacion, FALSE, TRUE, 10);

   // Establece el Color de Fondo de la Compilación
   font_color.red =   0.65;   // Valores de 0.0-1.0
   font_color.green = 0.65;
   font_color.blue =  0.65;
   font_color.alpha = 1;   // The opacidad del color: 0.0 para completamente transparente

   // Modifica el Color de Fondo
   gtk_widget_override_background_color(textviewCompilacion, GTK_STATE_FLAG_NORMAL, &font_color);


   // El espacio en pixeles Antes y despues del Enter
   gtk_text_view_set_pixels_above_lines (GTK_TEXT_VIEW (textviewCompilacion), 1);
   gtk_text_view_set_pixels_below_lines (GTK_TEXT_VIEW (textviewCompilacion), 1);

   // El Margen Izquierdo
   gtk_text_view_set_left_margin (GTK_TEXT_VIEW (textviewCompilacion), 10);

   // El Margen Derecho
   gtk_text_view_set_right_margin (GTK_TEXT_VIEW (textviewCompilacion), 10);

   // Establece el Tamaño de la Ventana de Compilación
   gtk_widget_set_size_request (scrollCompilacion, 0, 100);

   // Se indica si es editable o no y se activa o visibiliza el cursor
   gtk_text_view_set_editable (GTK_TEXT_VIEW (textviewCompilacion), false);
   gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (textviewCompilacion),FALSE);

}

// --------------------------------------------------------------------------------------------------
// Fin de Funciones
// --------------------------------------------------------------------------------------------------
