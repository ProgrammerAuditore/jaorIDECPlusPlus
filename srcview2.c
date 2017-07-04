#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gtksourceview/gtksourceview.h>
#include <gtksourceview/gtksourcebuffer.h>
#include <gtksourceview/gtksourcelanguage.h>
#include <gtksourceview/gtksourcelanguage.h>
#include <gtksourceview/gtksourcelanguagemanager.h>

/* Joe Arose updated code to gtk3 and gtksourceview-3.0. */

static gboolean open_file (GtkSourceBuffer *sBuf, const gchar *filename);

int
main( int argc, char *argv[] )
{
static GtkWidget *window, *pScrollWin, *sView;
PangoFontDescription *font_desc;
GtkSourceLanguageManager *lm;
GtkSourceBuffer *sBuf;

/* Create a Window. */
gtk_init (&argc, &argv);
window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
g_signal_connect (G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
gtk_container_set_border_width (GTK_CONTAINER (window), 10);
gtk_window_set_default_size (GTK_WINDOW(window), 660, 500);
gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);

/* Create a Scrolled Window that will contain the GtkSourceView */
pScrollWin = gtk_scrolled_window_new (NULL, NULL);
gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (pScrollWin),
GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

/* Now create a GtkSourceLanguageManager */
lm = gtk_source_language_manager_new();

/* and a GtkSourceBuffer to hold text (similar to GtkTextBuffer) */
sBuf = GTK_SOURCE_BUFFER (gtk_source_buffer_new (NULL));
g_object_ref (lm);
g_object_set_data_full ( G_OBJECT (sBuf), "languages-manager",
lm, (GDestroyNotify) g_object_unref);

/* Create the GtkSourceView and associate it with the buffer */
sView = gtk_source_view_new_with_buffer(sBuf);
/* Set default Font name,size */
font_desc = pango_font_description_from_string ("mono 8");
gtk_widget_modify_font (sView, font_desc);
pango_font_description_free (font_desc);

/* Attach the GtkSourceView to the scrolled Window */
gtk_container_add (GTK_CONTAINER (pScrollWin), GTK_WIDGET (sView));
/* And the Scrolled Window to the main Window */
gtk_container_add (GTK_CONTAINER (window), pScrollWin);
gtk_widget_show_all (pScrollWin);

/* Finally load an example file to see how it works */
open_file (sBuf, "srcview.c");

gtk_widget_show (window);

gtk_main();
return 0;
}


static gboolean
open_file (GtkSourceBuffer *sBuf, const gchar *filename)
{
GtkSourceLanguageManager *lm;
GtkSourceLanguage *language = NULL;
GError *err = NULL;
gboolean reading;
GtkTextIter iter;
GIOChannel *io;
gchar *buffer;

g_return_val_if_fail (sBuf != NULL, FALSE);
g_return_val_if_fail (filename != NULL, FALSE);
g_return_val_if_fail (GTK_SOURCE_BUFFER (sBuf), FALSE);

/* get the Language for C source mimetype */
lm = g_object_get_data (G_OBJECT (sBuf), "languages-manager");

language = gtk_source_language_manager_get_language (lm,"c");
g_print("Language: [%s]\n", gtk_source_language_get_name(language));

if (language == NULL)
{
g_print ("No language found for mime type `%s'\n", "text/x-c");
g_object_set (G_OBJECT (sBuf), "highlight", FALSE, NULL);
}
else
{
gtk_source_buffer_set_language (sBuf, language);
g_object_set (G_OBJECT (sBuf), "highlight", TRUE, NULL);
}

/* Now load the file from Disk */
io = g_io_channel_new_file (filename, "r", &err);
if (!io)
{
g_print("error: %s %s\n", (err)->message, filename);
return FALSE;
}

if (g_io_channel_set_encoding (io, "utf-8", &err) != G_IO_STATUS_NORMAL)
{
g_print("err: Failed to set encoding:\n%s\n%s", filename, (err)->message);
return FALSE;
}

gtk_source_buffer_begin_not_undoable_action (sBuf);

//gtk_text_buffer_set_text (GTK_TEXT_BUFFER (sBuf), "", 0);
buffer = g_malloc (4096);
reading = TRUE;
while (reading)
{
gsize bytes_read;
GIOStatus status;

status = g_io_channel_read_chars (io, buffer, 4096, &bytes_read, &err);
switch (status)
{
case G_IO_STATUS_EOF: reading = FALSE;

case G_IO_STATUS_NORMAL:
if (bytes_read == 0) continue;
gtk_text_buffer_get_end_iter ( GTK_TEXT_BUFFER (sBuf), &iter);
gtk_text_buffer_insert (GTK_TEXT_BUFFER(sBuf),&iter,buffer,bytes_read);
break;

case G_IO_STATUS_AGAIN: continue;

case G_IO_STATUS_ERROR:

default:
g_print("err (%s): %s", filename, (err)->message);
/* because of error in input we clear already loaded text */
gtk_text_buffer_set_text (GTK_TEXT_BUFFER (sBuf), "", 0);

reading = FALSE;
break;
}
}
g_free (buffer);

gtk_source_buffer_end_not_undoable_action (sBuf);
g_io_channel_unref (io);

if (err)
{
g_error_free (err);
return FALSE;
}

gtk_text_buffer_set_modified (GTK_TEXT_BUFFER (sBuf), FALSE);

/* move cursor to the beginning */
gtk_text_buffer_get_start_iter (GTK_TEXT_BUFFER (sBuf), &iter);
gtk_text_buffer_place_cursor (GTK_TEXT_BUFFER (sBuf), &iter);

g_object_set_data_full (G_OBJECT (sBuf),"filename", g_strdup (filename),
(GDestroyNotify) g_free);

return TRUE;
}
