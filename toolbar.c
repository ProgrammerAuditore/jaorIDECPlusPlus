

/* Create a toolbar with Cut, Copy, Paste and Select All toolbar items. */
static void create_toolbar (GtkWidget *toolbar, GtkWidget *entry)
{
GtkToolItem *cut, *copy, *paste, *selectall, *separator;
cut = gtk_tool_button_new_from_stock (GTK_STOCK_CUT);
copy = gtk_tool_button_new_from_stock (GTK_STOCK_COPY);
paste = gtk_tool_button_new_from_stock (GTK_STOCK_PASTE);
selectall = gtk_tool_button_new_from_stock (GTK_STOCK_SELECT_ALL);
separator = gtk_separator_tool_item_new ();
gtk_toolbar_set_show_arrow (GTK_TOOLBAR (toolbar), TRUE);
gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_BOTH);
gtk_toolbar_insert
gtk_toolbar_insert
gtk_toolbar_insert
gtk_toolbar_insert
gtk_toolbar_insert
(GTK_TOOLBAR
(GTK_TOOLBAR
(GTK_TOOLBAR
(GTK_TOOLBAR
(GTK_TOOLBAR
(toolbar),
(toolbar),
(toolbar),
(toolbar),
(toolbar),
cut, 0);
copy, 1);
paste, 2);
separator, 3);
selectall, 4);
g_signal_connect_swapped (G_OBJECT (cut), "clicked",
G_CALLBACK (gtk_editable_cut_clipboard), entry);
g_signal_connect_swapped (G_OBJECT (copy), "clicked",
G_CALLBACK (gtk_editable_copy_clipboard), entry);
g_signal_connect_swapped (G_OBJECT (paste), "clicked",
G_CALLBACK (gtk_editable_paste_clipboard), entry);
g_signal_connect_swapped (G_OBJECT (selectall), "clicked",
G_CALLBACK (select_all), entry);
}
/* Select all of the text in the GtkEditable. */
static void
select_all (GtkEditable *entry){
gtk_editable_select_region (entry, 0, -1);
}
