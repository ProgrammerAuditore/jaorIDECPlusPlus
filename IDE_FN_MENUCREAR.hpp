// --------------------------------------------------------------------------------------------------
// IDE C++
// Editor para Lenguaje C++
// Autor y Derechos Reservados:JAOR
// IDE_FN_MENUCREAR.hpp
// Archivo Header de Funciones del Menu Crear
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

// --------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------
// Prototipo de Funciones
// --------------------------------------------------------------------------------------------------

// Menu
void FnAppMenuCrear();       // Construye el Menu

// Función para crear las opciones correspondientes
void FnBarraMenuCrear();

// Funcion para las Señales
void FnSenalesMenuCrear();

// Función para Compilar
void FnCrearCompilar(GtkWidget *compilar);

// Función para Ejecutar
void FnCrearEjecutar(GtkWidget *ejecutar);

// Función para Compilar y Ejecutar
void FnCrearCompilarEjecutar(GtkWidget *compilar_ejecutar);

// --------------------------------------------------------------------------------------------------
// Fin de Prototipo de Funciones
// --------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------
// Funciones
// --------------------------------------------------------------------------------------------------

// Función para Crear el Menu Crear
void FnAppMenuCrear()
{

  // Creamos el Menu Crear
  menuCrear   = gtk_menu_new();

  // Creamos las Opciones de Crear
  opcCrear            = gtk_menu_item_new_with_mnemonic("_Crear");

  // Crea el Item de Crear-Compilar
  FnCreaItemDeMenu(&opcCrearCompilar,&boxCrearCompilar,&icoCrearCompilar,
                   &lblCrearCompilar,"gtk-convert","Compilar");

  // Crea el Item de Crear-Ejecutar
  FnCreaItemDeMenu(&opcCrearEjecutar,&boxCrearEjecutar,&icoCrearEjecutar,
                   &lblCrearEjecutar,"gtk-execute","Ejecutar");

  // Crea el Item de Crear-CompilarEjecutar
  FnCreaItemDeMenu(&opcCrearCompilarEjecutar,&boxCrearCompilarEjecutar,&icoCrearCompilarEjecutar,
                   &lblCrearCompilarEjecutar,"gtk-connect","Compilar-Ejecutar");

  // Establecemos el Item File como una opción de la Barra de Menu
  gtk_menu_shell_append(GTK_MENU_SHELL(menuBarra), opcCrear);


  // Agregamos la opcion del Menu Crear
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(opcCrear), menuCrear);

  // Establecemos las opciones del Menu
  gtk_menu_shell_append(GTK_MENU_SHELL(menuCrear), opcCrearCompilar);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuCrear), opcCrearEjecutar);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuCrear), opcCrearCompilarEjecutar);


  // Crea el Acelerador
  accel_group_crear = gtk_accel_group_new();
  gtk_window_add_accel_group(GTK_WINDOW(window), accel_group_crear);


  // Agregamos un Acelerador a las Opciones
  gtk_widget_add_accelerator(opcCrearCompilar,"activate",accel_group_buscar,
                             GDK_KEY_F5,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator(opcCrearEjecutar,"activate",accel_group_edicion,
                             GDK_KEY_F6,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator(opcCrearCompilarEjecutar,"activate",accel_group_edicion,
                             GDK_KEY_F7,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);

  // Desactivamos las opciones de Guardar, Guardar Como y Cerrar del Menu Archivo
  FnMenuOpcionOnOff(opcCrearCompilar,FALSE);
  FnMenuOpcionOnOff(opcCrearEjecutar,FALSE);
  FnMenuOpcionOnOff(opcCrearCompilarEjecutar,FALSE);

}

// Función para crear la Barra de Herramientas con las opciones de Crear
void FnBarraMenuCrear()
{

  // Cargamos la imagen que deseamos
  iconCrearCompilar             = gtk_image_new_from_file ("build-compile.png");
  iconCrearEjecutar             = gtk_image_new_from_file ("build-execute.png");
  iconCrearCompilarEjecutar     = gtk_image_new_from_file ("build-compile-execute.png");
  iconCrearCompilarGray         = gtk_image_new_from_file ("build-compile-gray.png");
  iconCrearEjecutarGray         = gtk_image_new_from_file ("build-execute-gray.png");
  iconCrearCompilarEjecutarGray = gtk_image_new_from_file ("build-compile-execute-gray.png");

  // Hace a los iconos permanentes
  g_object_ref_sink(G_OBJECT(iconCrearCompilar));
  g_object_ref_sink(G_OBJECT(iconCrearEjecutar));
  g_object_ref_sink(G_OBJECT(iconCrearCompilarEjecutar));
  g_object_ref_sink(G_OBJECT(iconCrearCompilarGray));
  g_object_ref_sink(G_OBJECT(iconCrearEjecutarGray));
  g_object_ref_sink(G_OBJECT(iconCrearCompilarEjecutarGray));


  // Creamos los Item para la Barra de Herramientas
  itemCrearCompilar          = gtk_tool_button_new(iconCrearCompilar,NULL);
  gtk_tool_item_set_tooltip_text (itemCrearCompilar,"Compilar ...");
  itemCrearEjecutar          = gtk_tool_button_new(iconCrearCompilar,NULL);
  gtk_tool_item_set_tooltip_text (itemCrearEjecutar,"Ejecutar ...");
  itemCrearCompilarEjecutar  = gtk_tool_button_new(iconCrearCompilar,NULL);
  gtk_tool_item_set_tooltip_text (itemCrearCompilarEjecutar,"Compilar y Ejecutar ...");


  // Separador
  itemSeparador6  = gtk_separator_tool_item_new ();

  // Agrega el Separador y los Item de Encontrar y Reemplazar
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemSeparador6, 16);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemCrearCompilar, 17);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemCrearEjecutar, 18);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar),itemCrearCompilarEjecutar, 19);

  // Activa-Desactiva las opciones e item's correspondientes
  FnMenuOpcionOnOff(GTK_WIDGET(itemCrearCompilar),FALSE);
  FnMenuOpcionOnOff(GTK_WIDGET(itemCrearEjecutar),FALSE);
  FnMenuOpcionOnOff(GTK_WIDGET(itemCrearCompilarEjecutar),FALSE);
  gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemCrearCompilar),iconCrearCompilarGray);
  gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemCrearEjecutar),iconCrearEjecutarGray);
  gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(itemCrearCompilarEjecutar),iconCrearCompilarEjecutarGray);


  // Se actualiza la barra de herramientas
  gtk_widget_show_all(GTK_WIDGET(toolbar));

}


// Señales del Menu Crear
void FnSenalesMenuCrear()
{
    // Controla las Señales del Menu y Barra de Buscar
    g_signal_connect (G_OBJECT (opcCrearCompilar), "activate",G_CALLBACK (FnCrearCompilar), NULL);
    g_signal_connect (G_OBJECT (itemCrearCompilar), "clicked",G_CALLBACK (FnCrearCompilar), NULL);
    g_signal_connect (G_OBJECT (opcCrearEjecutar), "activate",G_CALLBACK (FnCrearEjecutar), NULL);
    g_signal_connect (G_OBJECT (itemCrearEjecutar), "clicked",G_CALLBACK (FnCrearEjecutar), NULL);
    g_signal_connect (G_OBJECT (opcCrearCompilarEjecutar), "activate",G_CALLBACK (FnCrearCompilarEjecutar), NULL);
    g_signal_connect (G_OBJECT (itemCrearCompilarEjecutar), "clicked",G_CALLBACK (FnCrearCompilarEjecutar), NULL);

}


// Función para Compilar
void FnCrearCompilar(GtkWidget *compilar)
{

    // Declara una variable de tipo FILE
    FILE *fp;

    // Variables para los Comandos
    string sComando;
    string sComandoMostrar;

    // Para mensajes
    string sMensaje;

    // Para llamar a Proceso de Grabar
    GtkWindow *window;
    GtkToolItem *item;

    // Verifica si el archivo ya está guardado
    if (gbTextoInsertado)
    {
       // Llama a función que graba el Archivo a Disco
       FnMenuArchivoGuardar(item,window);
    }

    // Para leer del Archivo
    char path[1024];

    // Para el Retorno de la aplicación
    int iExitCode;

    // Definición de Variables
    GtkTextIter iterInicio,iterFinal;  // Ubicación

    // Obtiene el Inicio y Final del Buffer para borrar
    gtk_text_buffer_get_start_iter (bufferCompilacion, &iterInicio);
    gtk_text_buffer_get_end_iter   (bufferCompilacion, &iterFinal);

    // Elimina del BUffer
    gtk_text_buffer_delete (bufferCompilacion, &iterInicio,&iterFinal);

    // Construyo el Comando
    //sComando = "g++ " + gstrArchivo + " -o "+ gstrExecutable;
    sComando = "g++ " + gstrArchivo + " `pkg-config --cflags gtk+-3.0` -fpermissive -std=c++11 `pkg-config --libs gtk+-3.0` -o "+ gstrExecutable;
    sComandoMostrar= sComando + "\n";
    sComando = sComando + " 2>&1";

    // Abro y ejecuto el Comando
    fp = popen(sComando.c_str(), "r");

    // Verifica que haya ejecutado el Comando
    if (fp == NULL)
    {
       // Manda el Mensaje de Error a la Ventana de Crear
       sMensaje = "Falla al ejecutar comando ...\n";
       gtk_text_buffer_insert_at_cursor(bufferCompilacion,sMensaje.c_str(),strlen(sMensaje.c_str()));
    }
    else
    {

        // Despliega el Comando de Compilación
        gtk_text_buffer_insert_at_cursor(bufferCompilacion,sComandoMostrar.c_str(),strlen(sComandoMostrar.c_str()));

        // Lee la salida que da el Comando al Ejecutarse
        while (fgets(path, sizeof(path)-1, fp) != NULL)
        {
           // Inserta el Mensaje en el Buffer
           gtk_text_buffer_insert_at_cursor(bufferCompilacion,path,strlen(path));
        }

        // Obtiene el Código de Salida al Cerrar el Archivo
        //iExitCode = pclose(fp) / 256;
        iExitCode = WEXITSTATUS2(pclose(fp));

        // Verifica si hubo errores
        if (iExitCode==0)
        {
           // Construye el Mensaje
           sMensaje ="Se realizó con éxito la creación de Ejecutable ...";

           // Inserta Mensaje de que compilación se realizó con éxito
           gtk_text_buffer_insert_at_cursor(bufferCompilacion,sMensaje.c_str(),strlen(sMensaje.c_str()));
        }
        else
        {

           // Construye el Mensaje
           sMensaje ="Hubo errores en la creación del Ejecutable ...";

           // Inserta Mensaje de que compilación se realizó con éxito
           gtk_text_buffer_insert_at_cursor(bufferCompilacion,sMensaje.c_str(),strlen(sMensaje.c_str()));

        }
    }
}

// Función para Ejecutar
void FnCrearEjecutar(GtkWidget *ejecutar)
{

    // Declara una variable para el Comando
    string sComando;

    // Construye el Mensaje
    sComando ="Ejecutando ... \n";

    // Inserta Mensaje de que compilación se realizó con éxito
    gtk_text_buffer_insert_at_cursor(bufferCompilacion,sComando.c_str(),strlen(sComando.c_str()));

    // Construye el Comando para ejecución
    //sComando = "gnome-terminal -x sh -c './" + gstrExecutable +";echo presiona para continuar; read x'";

    // Con xterm
    sComando = "xterm -T 'IDE C++' -e './" + gstrExecutable +";echo presiona para continuar; read x'";

    // Ejecuta el Programa
    system(sComando.c_str());

}

// Función para Compilar y Ejecutar
void FnCrearCompilarEjecutar(GtkWidget *compilar_ejecutar)
{

    // Declara una variable de tipo FILE
    FILE *fp;
    string sComando;
    string sComandoMostrar;
    string sMensaje;
    char   buffer[1024];
    int    iExitCode;

    // Para llamar a Proceso de Grabar
    GtkWindow *window;
    GtkToolItem *item;

    // Verifica si el archivo ya está guardado
    if (gbTextoInsertado)
    {
       // Llama a función que graba el Archivo a Disco
       FnMenuArchivoGuardar(item,window); // Aguas con esto verificar si hubo error
    }

    // Definición de Variables
    GtkTextIter iterInicio,iterFinal;  // Ubicación

    // Obtiene el Inicio y Final del Buffer para borrar
    gtk_text_buffer_get_start_iter (bufferCompilacion, &iterInicio);
    gtk_text_buffer_get_end_iter   (bufferCompilacion, &iterFinal);

    // Elimina del BUffer
    gtk_text_buffer_delete (bufferCompilacion, &iterInicio,&iterFinal);

    // Construyo el Comando
    //sComando = "g++ " + gstrArchivo + " -o "+ gstrExecutable;
    sComando = "g++ " + gstrArchivo + " `pkg-config --cflags gtk+-3.0` -fpermissive -std=c++11 `pkg-config --libs gtk+-3.0` -o "+ gstrExecutable;
    sComandoMostrar= sComando + "\n";
    sComando = sComando + " 2>&1";

    // Abro y ejecuto el Comando
    fp = popen(sComando.c_str(), "r");

    // Verifica que haya ejecutado el Comando
    if (fp == NULL)
    {
       // Manda el Mensaje de Error a la Ventana de Crear
       sMensaje = "Falla al ejecutar comando ... \n";
       gtk_text_buffer_insert_at_cursor(bufferCompilacion,sMensaje.c_str(),strlen(sMensaje.c_str()));
    }
    else
    {

        // Despliega el Comando de Compilación
        gtk_text_buffer_insert_at_cursor(bufferCompilacion,sComandoMostrar.c_str(),strlen(sComandoMostrar.c_str()));

        // Lee la salida que da el Comando al Ejecutarse
        while (fgets(buffer, sizeof(buffer)-1, fp) != NULL)
        {
           // Inserta el Mensaje en el Buffer
           gtk_text_buffer_insert_at_cursor(bufferCompilacion,buffer,strlen(buffer));
        }

        // Obtiene el Código de Salida al Cerrar el Archivo
        iExitCode = WEXITSTATUS2(pclose(fp));

    }

    // Verifica si no hubo errores
    if (iExitCode==0)
    {
       // Construye el Mensaje
       sMensaje ="Se realizó con éxito la creación de Ejecutable \nEjecutando  ...";

       // Inserta Mensaje de que compilación se realizó con éxito
       gtk_text_buffer_insert_at_cursor(bufferCompilacion,sMensaje.c_str(),strlen(sMensaje.c_str()));

       // Construye el Comando para ejecución
       //sComando = "gnome-terminal -x sh -c './" + gstrExecutable +";echo presiona para continuar; read x'";

       // Con xterm
       sComando = "xterm -T 'IDE C++' -e './" + gstrExecutable +";echo presiona para continuar; read x'";

       // Ejecuta el Programa
       system(sComando.c_str());

    }
    else
    {

       // Construye el Mensaje
       sMensaje ="Hubo errores en la creación del Ejecutable ...";

       // Inserta Mensaje de que compilación se realizó con éxito
       gtk_text_buffer_insert_at_cursor(bufferCompilacion,sMensaje.c_str(),strlen(sMensaje.c_str()));

    }

}

// --------------------------------------------------------------------------------------------------
// Fin de Funciones
// --------------------------------------------------------------------------------------------------

