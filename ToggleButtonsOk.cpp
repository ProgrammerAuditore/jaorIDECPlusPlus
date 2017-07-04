#include <gtk/gtk.h>

  GtkWidget *window;
  GtkWidget *vbox;

  GtkWidget *toolbar;
  GtkWidget *translateIconUp, *translateIconDown, *rotateIconUp, *rotateIconDown, *scaleIconUp, *scaleIconDown;
  GtkToolItem *translate, *rotate, *scale;

//Functions
gboolean set_manipulator_translate(GtkWidget *widget, gpointer   data)
{
    //Set translate to Active
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(translate), translateIconUp);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(rotate), rotateIconDown);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(scale), scaleIconDown);
    gtk_widget_show_all(GTK_WIDGET(toolbar));

    return false;
}

gboolean set_manipulator_rotate(GtkWidget *widget, gpointer   data)
{
    //Set Rotate to Active
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(translate), translateIconDown);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(rotate), rotateIconUp);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(scale), scaleIconDown);
    gtk_widget_show_all(GTK_WIDGET(toolbar));

    return false;
}

gboolean set_manipulator_scale(GtkWidget *widget, gpointer   data)
{
    //Set Scale to active
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(translate), translateIconDown);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(rotate), rotateIconDown);
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(scale), scaleIconUp);
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

  // load icons and make them permanent
  translateIconDown = gtk_image_new_from_file( "translate_iconx.png" );
  translateIconUp = gtk_image_new_from_file( "translate_icon2x.png" );
  rotateIconDown = gtk_image_new_from_file( "rotate_iconx.png" );
  rotateIconUp = gtk_image_new_from_file( "rotate_icon2x.png" );
  scaleIconDown = gtk_image_new_from_file( "scale_iconx.png" );
  scaleIconUp = gtk_image_new_from_file( "scale_icon2x.png" );
  g_object_ref_sink(G_OBJECT(scaleIconDown));
  g_object_ref_sink(G_OBJECT(scaleIconUp));
  g_object_ref_sink(G_OBJECT(rotateIconDown));
  g_object_ref_sink(G_OBJECT(rotateIconUp));
  g_object_ref_sink(G_OBJECT(translateIconDown));
  g_object_ref_sink(G_OBJECT(translateIconUp));

  //Seperate
  GtkToolItem *sep= gtk_separator_tool_item_new();
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);

  //Make 3 buttons for the manipulation widgets
  translate = gtk_tool_button_new(translateIconUp, "translate");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), translate, -1);
  g_signal_connect(G_OBJECT(translate), "clicked", G_CALLBACK(set_manipulator_translate), NULL);

  rotate = gtk_tool_button_new(rotateIconDown, "rotate");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), rotate, -1);
  g_signal_connect(G_OBJECT(rotate), "clicked", G_CALLBACK(set_manipulator_rotate), NULL);

  scale = gtk_tool_button_new(scaleIconDown, "scale");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), scale, -1);
  g_signal_connect(G_OBJECT(scale), "clicked", G_CALLBACK(set_manipulator_scale), NULL);

  //Package
  gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);

  g_signal_connect_swapped(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
