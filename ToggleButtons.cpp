#include <gtk/gtk.h>

  GtkWidget *window;
  GtkWidget *vbox;

  GtkWidget *toolbar;
  GtkWidget *translateIconUp, *translateIconDown, *rotateIconUp, *rotateIconDown, *scaleIconUp, *scaleIconDown;
  GtkToolItem *translate, *rotate, *scale;

//Functions
gboolean set_manipulator_translate(GtkWidget *widget, gpointer   data)
{

    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(translate), translateIconDown);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(rotate), rotateIconUp);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(scale), scaleIconUp);
    gtk_widget_show_all(GTK_WIDGET(toolbar));

    return false;
}

gboolean set_manipulator_rotate(GtkWidget *widget, gpointer   data)
{

    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(translate), translateIconUp);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(rotate), rotateIconDown);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(scale), scaleIconUp);
    gtk_widget_show_all(GTK_WIDGET(toolbar));

    return false;
}

gboolean set_manipulator_scale(GtkWidget *widget, gpointer   data)
{

    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(translate), translateIconUp);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(rotate), rotateIconUp);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(scale), scaleIconDown);
    gtk_widget_show_all(GTK_WIDGET(toolbar));

    return false;
}


//Main
int main( int argc, char *argv[])
{


  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 250, 200);
  gtk_window_set_title(GTK_WINDOW(window), "toolbar");

  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);


  toolbar = gtk_toolbar_new();
  gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

  gtk_container_set_border_width(GTK_CONTAINER(toolbar), 2);

  // Add three icons
  translateIconDown = gtk_image_new_from_file( "translate_iconx.png" );
  translateIconUp = gtk_image_new_from_file( "translate_icon2x.png" );
  translate = gtk_tool_button_new(translateIconDown, "translate");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), translate, -1);
  g_signal_connect(G_OBJECT(translate), "clicked", G_CALLBACK(set_manipulator_translate), NULL);

  rotateIconDown = gtk_image_new_from_file( "rotate_iconx.png" );
  rotateIconUp = gtk_image_new_from_file( "rotate_icon2x.png" );
  rotate = gtk_tool_button_new(rotateIconUp, "rotate");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), rotate, -1);
  g_signal_connect(G_OBJECT(rotate), "clicked", G_CALLBACK(set_manipulator_rotate), NULL);

  scaleIconDown = gtk_image_new_from_file( "scale_iconx.png" );
  scaleIconUp = gtk_image_new_from_file( "scale_icon2x.png" );
  scale = gtk_tool_button_new(scaleIconUp, "scale");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), scale, -1);
  g_signal_connect(G_OBJECT(scale), "clicked", G_CALLBACK(set_manipulator_scale), NULL);

  //Package
  gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);

  g_signal_connect_swapped(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
