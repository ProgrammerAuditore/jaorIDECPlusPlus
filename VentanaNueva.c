/*

Autor    : JAOR
Curso    : Library Gtk+
Clase 60 : TextView VIII

Insertando un Widget en el TextView

*/

// Incluye la librería
#include <gtk/gtk.h>
GtkWidget          *window;

// Función que presenta una ventana Nueva
void FnVentanaNueva()
{

   GtkWidget *Ventana;

   g_print("Entro \n");
   // Crea la Ventana Principal y la Configura
   Ventana = gtk_window_new (GTK_WINDOW_TOPLEVEL);

   // Coloca el Título
   gtk_window_set_title (GTK_WINDOW (Ventana), "Nueva Ventana");
   gtk_container_set_border_width (GTK_CONTAINER (Ventana), 10);
   gtk_widget_set_size_request (Ventana, 50, 50);
   gtk_window_set_modal(GTK_WINDOW (Ventana), TRUE);

   gtk_window_set_transient_for (GTK_WINDOW (Ventana),window);
   gtk_widget_show_all (Ventana);

}



// Función Principal
int main (int argc,char *argv[])
{
    // Declaración de Variables
    GtkWidget    *scrolled_win, // Scroll
                     *textview, // TextView
                       *button; // Botón
    GtkTextChildAnchor *anchor; // Anchor
    GtkTextIter           iter; // Item
    GtkTextBuffer      *buffer; // Buffer

    // Inicializa la Librería
    gtk_init (&argc, &argv);

    // Crea la Ventana Principal y la Configura
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Clase 60 - TextView VIII");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (window, 250, 100);

    // Crea el TextView
    textview = gtk_text_view_new ();

    // Crea el Buffer del Textview
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));
    gtk_text_buffer_set_text (buffer, "\n Click para Salir!", -1);

    // Crea el Widget en el especificado Item
    gtk_text_buffer_get_iter_at_offset (buffer, &iter, 15);
    anchor = gtk_text_buffer_create_child_anchor (buffer, &iter);

    // Inserta el GtkButton Widget en el Anchor child
    button = gtk_button_new_with_label ("El Botón");
    gtk_text_view_add_child_at_anchor (GTK_TEXT_VIEW (textview), button, anchor);

    // Captura la Señal
    g_signal_connect_swapped (G_OBJECT (button),
                                      "clicked",
                G_CALLBACK (FnVentanaNueva),
                             (gpointer) window);

    // Crea el Scroll
    scrolled_win = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_add (GTK_CONTAINER (scrolled_win), textview);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    gtk_container_add (GTK_CONTAINER (window), scrolled_win);

    // Muestra todos los objetos
    gtk_widget_show_all (window);

    // Ejecuta el Ciclo Principal
    gtk_main();

    // Finaliza Retornando 0
    return 0;
}
