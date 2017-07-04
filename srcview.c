// Simple IDE
// Copyright 2009 Samuel Pauls

// Compile Instructions
// cc simple_ide.c -o simple_ide `pkg-config --cflags --libs gtk+-2.0 gtksourceview-2.0`

#include <stdlib.h> // includes system, malloc, EXIT_SUCCESS
#include <stdio.h> // includes fopen, fwrite, fseek, ftell
#include <string.h>
#include <gdk/gdkkeysyms.h> // includes GDK_q
#include <gtk/gtk.h>
#include <gtksourceview/gtksourceview.h>

GtkWidget *main_window;

GtkWidget *editor;
gchar *filename = NULL;

GtkWidget *execute_command_menu_item;
char *command = NULL;

// Updates the main window's title, based on the filename.
void refresh_title (void) {
  static const char *TITLE_APP = " - Simple IDE";
  char *title;
  if (filename == NULL) {
    // Set the window title when the document isn't saved.
    static const char *TITLE_EMPTY = "Untitled";
    size_t title_empty_length = strlen (TITLE_EMPTY);
    title = malloc (title_empty_length + strlen (TITLE_APP) + 1);
    strcpy (title, // destination
            TITLE_EMPTY); // source
    strcpy (title + title_empty_length, // destionation
            TITLE_APP); // source
  } else {
    // Set the window title when the document is saved.
    size_t filename_length = strlen (filename);
    title = malloc (filename_length + strlen (TITLE_APP) + 1);
    // strlen doesn't count NULL terminator
    strcpy (title, // destination
            filename); // source
    strcpy (title + filename_length, // destionation
            TITLE_APP); // source
  }
  gtk_window_set_title (GTK_WINDOW (main_window), title);
  free (title);
}

void do_set_command (GtkMenuItem *menu_item, gpointer data) {
  // Create a modal dialog, that is a dialog that prevents its parent from
  // regaining focus until it's closed.
  GtkWidget *dialog = gtk_dialog_new_with_buttons (
                                "Execute Command", // title
                                GTK_WINDOW (main_window), // parent
                                GTK_DIALOG_MODAL, // flags
                                NULL); // button/response list, ending with NULL

  // Fill in the content.
  GtkWidget *content = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
  GtkWidget *label = gtk_label_new (
                   "Enter a command which compiles and executes your program.");
  gtk_container_add (GTK_CONTAINER (content), label);
  GtkWidget *command_entry = gtk_entry_new();
  gtk_container_add (GTK_CONTAINER (content), command_entry);
  gtk_widget_show_all (content);

  // Cancel button.
  GtkWidget *cancel = gtk_dialog_add_button (GTK_DIALOG (dialog),
                                             GTK_STOCK_CANCEL,
                                             GTK_RESPONSE_CANCEL);

  // OK button.
  GtkWidget *ok = gtk_dialog_add_button (GTK_DIALOG (dialog),
                                         GTK_STOCK_OK,
                                         GTK_RESPONSE_ACCEPT);

  if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
    // Set the new command, to be executed later.
    if (command) {
      free (command);
    } else {
      gtk_widget_set_sensitive (execute_command_menu_item, TRUE);
    }
    const gchar *text = gtk_entry_get_text (GTK_ENTRY (command_entry));
    // text points to internally allocated string
    command = malloc (strlen (text) + 1); // strlen doesn't count ending NULL.
    strcpy (command, // destination
            text); // source
  }
  gtk_widget_destroy (dialog);
}

void do_execute_command (GtkMenuItem *menu_item, gpointer data) {
  system (command);
}

void do_new (GtkMenuItem *menu_item, gpointer data) {
  GtkTextBuffer *buffer = gtk_text_buffer_new (NULL);
  gtk_text_view_set_buffer (GTK_TEXT_VIEW (editor),
                            buffer); // unrefs old buffer and references new
  g_object_unref (buffer);
  g_free (filename); // doesn't NULL the pointer
  filename = NULL;
  refresh_title();
}

void do_open (GtkMenuItem *menu_item, gpointer data) {
  GtkWidget *dialog = gtk_file_chooser_dialog_new (
                                             NULL, // title
                                             GTK_WINDOW (main_window), // parent
                                             GTK_FILE_CHOOSER_ACTION_OPEN,
                                             GTK_STOCK_CANCEL, // button text
                                             GTK_RESPONSE_CANCEL, // response id
                                             GTK_STOCK_OPEN, // button text
                                             GTK_RESPONSE_ACCEPT, // response id
                                             NULL); // end button/response list
  // gtk_dialog_run shows a dialog and waits for a response,
  // as opposed to setting up the dialog and sending a signal
  if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
    g_free (filename); // free a possible old filename
    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
    refresh_title();

    // Load the new file into the editor widget.
    FILE *file = fopen (filename, "r");
    fseek (file,
           0, // offset
           SEEK_END); // origin
    long bytes = ftell (file);
    rewind (file); // fread starts reading from file's position
    char *text = malloc (sizeof (char) * bytes);
    fread (text,
           sizeof (char), // element size
           bytes, // number of elements
           file);
    fclose (file);
    if (text[bytes - 1] == '\n') {
      --bytes; // don't use the final end of line character, if it exists
    }
    GtkTextBuffer *buffer = gtk_text_buffer_new (NULL); // default tag table
    gtk_text_buffer_set_text (buffer,
                              text,
                              bytes); // text length
    free (text);
    gtk_text_view_set_buffer (GTK_TEXT_VIEW (editor),
                              buffer); // buffer's ref count increased
    g_object_unref (buffer);
  }
  gtk_widget_destroy (dialog); // implicitly hides dialog
}

void do_save_as (GtkMenuItem *menu_item, gpointer data); // forward declaration

void do_save (GtkMenuItem *menu_item, gpointer data) {
  if (filename == NULL) {
    do_save_as (NULL, NULL); // user has yet to choose a filename
  } else {
    // Save the editor's text, using the given filename.
    FILE *file = fopen (filename, "w");
    GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (editor));
    // buffer's reference count not incremented
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds (buffer, &start, &end);
    char *text = gtk_text_iter_get_text (&start, &end);
    fwrite (text,
            sizeof (char), // element size
            strlen (text), // number of elements, strlen doesn't count NULL end
            file);
    fwrite ("\n", sizeof (char), 1, file); // save extra end of line, like gedit
    g_free (text);
    fclose (file);
  }
}

void do_save_as (GtkMenuItem *menu_item, gpointer data) {
  GtkWidget *dialog = gtk_file_chooser_dialog_new (
                            NULL, // title
                            GTK_WINDOW (main_window), // parent
                            GTK_FILE_CHOOSER_ACTION_SAVE,
                            GTK_STOCK_CANCEL, // button text
                            GTK_RESPONSE_CANCEL, // response id
                            GTK_STOCK_SAVE, // button text
                            GTK_RESPONSE_ACCEPT, // response id
                            NULL); // end button/response list
  if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
    g_free (filename); // freeing NULL has no effect
    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
    refresh_title();
    do_save (NULL, NULL); // now that the filename is set, save the file
  }
  gtk_widget_destroy (dialog); // implicitly hides dialog
}

int main (int argc, char *argv[]) {
  // Use and remove GTK arguments from the application argument list.
  gtk_init (&argc, &argv);

  main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  // all get_*_new functions return GtkWidget*s, as opposed to pointers of their
  // specific types
  refresh_title();
  gtk_window_set_default_icon_name ("text-editor");
  gtk_window_set_default_size (GTK_WINDOW (main_window),
                               800, // width
                               600); // height
  g_signal_connect (G_OBJECT (main_window), // source instance
                   "destroy", // source signal
                   G_CALLBACK (gtk_main_quit), // callback
                   NULL); // extra data to pass to callback

  // Create a vertical box for stacking the menu and editor widgets in.
  GtkWidget *vbox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (main_window), vbox);

  // Create an accelerator group for mapping keyboard shortcuts to features.
  // Accelerators are for things like Ctrl+Q to quit, as opposed to mnemonics
  // which underline a single letter of a label in a UI.
  GtkAccelGroup *accel_group = gtk_accel_group_new();
  gtk_window_add_accel_group (GTK_WINDOW (main_window), accel_group);

  // Create the menu bar.
  GtkWidget *menubar = gtk_menu_bar_new();
  gtk_box_pack_start (GTK_BOX (vbox), // GtkBox to put something in
                      menubar, // GtkWidget to be added
                      FALSE, // don't give the child widget all the space
                      FALSE, // center the child
                      0); // pixels of padding around the child widget

  // Create the file menu.
  GtkWidget *file = gtk_menu_item_new_with_mnemonic ("_File");
  gtk_menu_shell_append (GTK_MENU_SHELL (menubar), file);
  GtkWidget *file_menu = gtk_menu_new();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (file), file_menu);

  // Create the new menu item.
  GtkWidget *new = gtk_image_menu_item_new_from_stock (GTK_STOCK_NEW,
                                                        accel_group);
  //gtk_widget_add_accelerator (new, // widget
  //                            "activate", // signal to emit
  //                            accel_group, // accelerator group
  //                            GDK_n, // key
  //                            GDK_CONTROL_MASK, // modifier keys
  //                            GTK_ACCEL_VISIBLE); // flags
  gtk_menu_shell_append (GTK_MENU_SHELL (file_menu), new);
  g_signal_connect (G_OBJECT (new), // source instance
                    "activate", // source signal
                    G_CALLBACK (do_new), // callback
                    NULL); // extra data to pass to callback

  // Create the open menu item.
  GtkWidget *open = gtk_image_menu_item_new_from_stock (GTK_STOCK_OPEN,
                                                        accel_group);
  //gtk_widget_add_accelerator (open, // widget
  //                            "activate", // signal to emit
  //                            accel_group, // accelerator group
  //                            GDK_o, // key
  //                            GDK_CONTROL_MASK, // modifier keys
  //                            GTK_ACCEL_VISIBLE); // flags
  gtk_menu_shell_append (GTK_MENU_SHELL (file_menu), open);
  g_signal_connect (G_OBJECT (open), // source instance
                    "activate", // source signal
                    G_CALLBACK (do_open), // callback
                    NULL); // extra data to pass to callback

  gtk_menu_shell_append (GTK_MENU_SHELL (file_menu),
                         gtk_separator_menu_item_new ());

  // Create the save menu item.
  GtkWidget *save = gtk_image_menu_item_new_from_stock (GTK_STOCK_SAVE,
                                                        accel_group);
  //gtk_widget_add_accelerator (save, // widget
  //                            "activate", // signal to emit
  //                            accel_group, // accelerator group
  //                            GDK_s, // key
  //                            GDK_CONTROL_MASK, // modifier keys
  //                            GTK_ACCEL_VISIBLE); // flags
  gtk_menu_shell_append (GTK_MENU_SHELL (file_menu), save);
  g_signal_connect (G_OBJECT (save), // source instance
                    "activate", // source signal
                    G_CALLBACK (do_save), // callback
                    NULL); // extra data to pass to callback

  // Create the save as menu item.
  GtkWidget *save_as = gtk_image_menu_item_new_from_stock (GTK_STOCK_SAVE_AS,
                                                           accel_group);
  //gtk_widget_add_accelerator (save_as, // widget
  //                            "activate", // signal to emit
  //                            accel_group, // accelerator group
  //                            GDK_s, // key
  //                            GDK_SHIFT_MASK | GDK_CONTROL_MASK, // mod keys
  //                            GTK_ACCEL_VISIBLE); // flags
  gtk_menu_shell_append (GTK_MENU_SHELL (file_menu), save_as);
  g_signal_connect (G_OBJECT (save_as), // source instance
                    "activate", // source signal
                    G_CALLBACK (do_save_as), // callback
                    NULL); // extra data to pass to callback

  gtk_menu_shell_append (GTK_MENU_SHELL (file_menu),
                         gtk_separator_menu_item_new ());

  // Create the quit menu item.
  GtkWidget *quit = gtk_image_menu_item_new_from_stock (GTK_STOCK_QUIT,
                                                        accel_group);
  //gtk_widget_add_accelerator (quit, // widget
  //                            "activate", // signal to emit
  //                            accel_group, // accelerator group
  //                            GDK_q, // key
  //                            GDK_CONTROL_MASK, // modifier keys
   //                           GTK_ACCEL_VISIBLE); // flags
  gtk_menu_shell_append (GTK_MENU_SHELL (file_menu), quit);
  g_signal_connect (G_OBJECT (quit), // source instance
                   "activate", // source signal
                   G_CALLBACK (gtk_main_quit), // callback
                   NULL); // extra data to pass to callback

  // Create the tools menu.
  GtkWidget *tools = gtk_menu_item_new_with_mnemonic ("_Tools");
  gtk_menu_shell_append (GTK_MENU_SHELL (menubar), tools);
  GtkWidget *tools_menu = gtk_menu_new();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (tools), tools_menu);

  // Create the execute command menu item.
  execute_command_menu_item = gtk_image_menu_item_new_from_stock (
                                                          GTK_STOCK_EXECUTE,
                                                          accel_group);
  gtk_menu_item_set_label (GTK_MENU_ITEM (execute_command_menu_item),
                           "_Execute Command");
  //gtk_widget_add_accelerator (execute_command_menu_item,
  //                            "activate", // signal to emit
  //                            accel_group, // accelerator group
  //                            GDK_e, // key
  //                            GDK_CONTROL_MASK, // modifier keys
  //                            GTK_ACCEL_VISIBLE); // flags
  gtk_widget_set_sensitive (execute_command_menu_item, FALSE);
  gtk_menu_shell_append (GTK_MENU_SHELL (tools_menu),
                         execute_command_menu_item);
  g_signal_connect (G_OBJECT (execute_command_menu_item), // source instance
                    "activate", // source signal
                    G_CALLBACK (do_execute_command), // callback
                    NULL); // extra data to pass to callback

  // Create the set command menu item.
  GtkWidget *set_command_menu_item = gtk_menu_item_new_with_mnemonic (
                                                           "_Set Command");
  gtk_menu_shell_append (GTK_MENU_SHELL (tools_menu), set_command_menu_item);
  g_signal_connect (G_OBJECT (set_command_menu_item), // source instance
                    "activate", // source signal
                    G_CALLBACK (do_set_command), // callback
                    NULL); // extra data to pass to callback

  // Create a scrollable area for the editor.
  GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL, // h adjustment
                                                        NULL); // v adjustment
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_AUTOMATIC, // horizontal
                                  GTK_POLICY_AUTOMATIC); // vertical
  gtk_box_pack_start (GTK_BOX (vbox),
                      scrolled_window,
                      TRUE, // vbox gives widget all remaining space
                      TRUE, // widget expands to fill given space
                      0); // pixel of padding around the widget

  // Create a code editing widget.
  editor = gtk_source_view_new();
  gtk_container_add (GTK_CONTAINER (scrolled_window), editor);
  //gtk_box_pack_start (GTK_BOX (vbox),
  //                    editor,
  //                    TRUE, // vbox gives widget all remaining space
  //                    TRUE, // widget expands to fill given space
  //                    0); // pixel of padding around the widget
  // when pressing enter on a tabbed line, the next will be equally tabbed
  gtk_source_view_set_auto_indent (GTK_SOURCE_VIEW (editor),
                                   TRUE);
  // make a tab be two spaces
  gtk_source_view_set_indent_width (GTK_SOURCE_VIEW (editor),
                                    2);
  gtk_source_view_set_highlight_current_line (GTK_SOURCE_VIEW (editor),
                                              TRUE);
  gtk_source_view_set_show_line_numbers (GTK_SOURCE_VIEW (editor),
                                         TRUE);
  gtk_source_view_set_right_margin_position (GTK_SOURCE_VIEW (editor),
                                             80); // default is 70 chars
  gtk_source_view_set_show_right_margin (GTK_SOURCE_VIEW (editor),
                                         TRUE);
  gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (editor),
                               GTK_WRAP_WORD_CHAR);

  // Set the editor's font.
  PangoFontDescription *font_desc = pango_font_description_new();
  pango_font_description_set_family (font_desc, "monospace");
  gtk_widget_modify_font (editor, font_desc);

  gtk_widget_show_all (main_window); // recursive version of gtk_widget_show

  gtk_main();
  // reached after gtk_main_quit() is called

  g_free (filename);
  free (command);

  return EXIT_SUCCESS;
}
