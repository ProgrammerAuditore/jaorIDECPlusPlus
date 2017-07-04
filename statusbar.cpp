/* gcc -o status status.c $(pkg-config --cflags --libs gtk+-2.0) */

#include <gtk/gtk.h>

int main (int argc, char *argv[]) {
    GtkWidget *window, *statusbar, *vbox;
    gchar *info;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window, 250, -1);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    statusbar = gtk_statusbar_new();

    /* here comes the color change */
    GdkRGBA font_color;

// Establece el Color
  font_color.red = 0;
  font_color.green = 1;
  font_color.blue = 0;
  font_color.alpha = 1;
  gtk_widget_override_background_color(statusbar, GTK_STATE_FLAG_NORMAL, &font_color);



    /* stack for info messages */
    g_object_set_data(G_OBJECT(statusbar), "info", (gpointer)
                      "1");
    g_object_set_data(G_OBJECT(statusbar), "info",
                      (gpointer) "2");
    g_object_set_data(G_OBJECT(statusbar), "info",
                      (gpointer) "3");

    /* stack for warning messages */
    g_object_set_data(G_OBJECT(statusbar), "warning",
                      (gpointer) "A");
    g_object_set_data(G_OBJECT(statusbar), "warning",
                      (gpointer) "B");
    g_object_set_data(G_OBJECT(statusbar),
                      "warning", (gpointer) "C");

    /* get id for the message at the top of the
     * info stack? */
    guint id = gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar), "info");
    /* show the top message from the info stack
     * ? */
    info = "This was uninitialized";
    gtk_statusbar_push(GTK_STATUSBAR(statusbar), id, info);

    vbox = gtk_vbox_new(FALSE, 5);
    //gtk_box_pack_start_defaults(GTK_BOX(vbox),statusbar);
    gtk_box_pack_end(GTK_BOX(vbox), statusbar, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
