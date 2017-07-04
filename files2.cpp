#include <stdlib.h>
#include <gtk/gtk.h>

/* Basic gtk+ text editor */

#define C_STD_CODE 1
#define GLIB_CODE 0

struct data_struct
{
    GtkWidget* window;
    GtkWidget* text_view;
    GtkTextBuffer* text_buffer;
    FILE* file_pointer;
};

static void file_open(GtkWidget* button,struct data_struct* data);
static void file_save(GtkWidget* button,struct data_struct* data);
static void new_doc(GtkWidget* button, struct data_struct* data);

int main (int argc, char *argv[])
{
    GtkWidget* button_new;
    GtkWidget* button_open;
    GtkWidget* button_save;
    GtkWidget* scroll_window;
    GtkWidget* hbox_one;
    GtkWidget* vbox_one;
    struct data_struct data;

    gtk_init (&argc, &argv);

    data.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (data.window), 5);
    gtk_window_set_title (GTK_WINDOW (data.window), "Text Editor.");
    gtk_widget_set_size_request(data.window,500,-1);

    data.file_pointer = NULL;
    data.text_view = gtk_text_view_new();
    data.text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(data.text_view));
    scroll_window = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    gtk_widget_set_size_request(scroll_window,400,450);
    gtk_container_add(GTK_CONTAINER(scroll_window), data.text_view);

    button_new = gtk_button_new_from_stock(GTK_STOCK_NEW);
    button_open = gtk_button_new_from_stock(GTK_STOCK_OPEN);
    button_save = gtk_button_new_from_stock(GTK_STOCK_SAVE);

    hbox_one = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    gtk_box_pack_start(GTK_BOX(hbox_one),button_new,FALSE,TRUE,10);
    gtk_box_pack_start(GTK_BOX(hbox_one),button_open,FALSE,TRUE,10);
    gtk_box_pack_start(GTK_BOX(hbox_one),button_save,FALSE,TRUE,10);

    g_signal_connect (G_OBJECT(data.window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect (G_OBJECT(button_new),"clicked",G_CALLBACK(new_doc),(gpointer)&data);
    g_signal_connect (G_OBJECT(button_open),"clicked",G_CALLBACK(file_open),(gpointer)&data);
    g_signal_connect (G_OBJECT(button_save),"clicked",G_CALLBACK(file_save),(gpointer)&data);

    vbox_one = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
    gtk_box_pack_start(GTK_BOX(vbox_one),hbox_one,FALSE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(vbox_one),scroll_window,FALSE,TRUE,5);

    gtk_container_add(GTK_CONTAINER(data.window), vbox_one);
    gtk_widget_grab_focus(data.text_view);

    gtk_widget_show_all(data.window);
    gtk_main ();

    return 0;
}

static void file_open(GtkWidget* button, struct data_struct* data)
{
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    gint ret_val;
    GError* error = NULL;
    gchar* temp_buff;
    gchar temp_buff2[1000] = {'\0'};
    gint ch;
    gint i;
    gint code_choice = GLIB_CODE;          // C_STD_CODE for alternative code

    dialog = gtk_file_chooser_dialog_new ("Open File",GTK_WINDOW(data->window),GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,GTK_STOCK_OPEN,GTK_RESPONSE_ACCEPT,NULL);

    ret_val = gtk_dialog_run (GTK_DIALOG (dialog));
    if (ret_val == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);

        data->file_pointer = fopen(filename,"r");
        if(data->file_pointer != NULL)
        {
            if(code_choice == GLIB_CODE)
            {
                if(g_file_get_contents (filename,&temp_buff,NULL,&error))
                {
                    gtk_text_buffer_set_text(data->text_buffer,temp_buff,-1);
                }

                g_free(temp_buff);
            }
            else
            {
                i = 0;

                while((ch = fgetc(data->file_pointer)) != EOF && i < 1000)
                {
                    temp_buff2[i] = (gchar)ch;
                    i++;
                }

                temp_buff2[i] = '\0';
                gtk_text_buffer_set_text(data->text_buffer,temp_buff2,-1);
            }

            fclose(data->file_pointer);
        }
        else
        {
            g_print("\nError");
        }

        g_free(filename);
    }

    gtk_widget_destroy(dialog);
    gtk_widget_grab_focus(data->text_view);
}

static void file_save(GtkWidget* button, struct data_struct* data)
{
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkTextIter start, end;
    gchar* temp_buff;
    gchar* filename;
    gint ret_val;

    dialog = gtk_file_chooser_dialog_new ("Save File",GTK_WINDOW(data->window),GTK_FILE_CHOOSER_ACTION_SAVE,GTK_STOCK_CANCEL,
                                          GTK_RESPONSE_CANCEL,GTK_STOCK_SAVE,GTK_RESPONSE_ACCEPT,NULL);
    chooser = GTK_FILE_CHOOSER (dialog);

    gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);
    gtk_file_chooser_set_current_name (chooser,("New Text document.txt"));

    ret_val = gtk_dialog_run (GTK_DIALOG (dialog));
    if (ret_val == GTK_RESPONSE_ACCEPT)
    {
        filename = gtk_file_chooser_get_filename (chooser);

        data->file_pointer = fopen(filename,"w");
        if(data->file_pointer != NULL)
        {
            gtk_text_buffer_get_bounds(data->text_buffer,&start,&end);
            temp_buff = gtk_text_buffer_get_text(data->text_buffer,&start,&end,FALSE);

            if(fputs(temp_buff,data->file_pointer) < 0)
            {
                g_print("\nError");
            }

            g_free(temp_buff);
            fclose(data->file_pointer);

        }
        else
        {
            g_print("\nError");
        }

        g_free(filename);
    }

    gtk_widget_destroy (dialog);
}

static void new_doc(GtkWidget* button, struct data_struct* data)
{
    GtkTextIter start, end;

    gtk_text_buffer_get_bounds(data->text_buffer,&start,&end);

    if(!(gtk_text_iter_equal (&start,&end)))
    {
        gtk_text_buffer_delete (data->text_buffer,&start,&end);
    }

    gtk_widget_grab_focus(data->text_view);
    gtk_text_buffer_set_modified(data->text_buffer,FALSE);
}
