#include "client.h"

void open_chat (GtkWidget *window, GdkEvent *event, gpointer user_data) 
{ 

    gtk_widget_destroy(gtk_widget_get_parent(window));
    /*GtkWidget *p_window;
    GtkWidget *p_v_box;
    GtkWidget *p_entry;

    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(p_window), "Create DB");
    gtk_window_set_default_size(GTK_WINDOW(p_window), 320, 200);

    p_v_box = gtk_box_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(p_window), p_v_box);

    p_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(p_v_box), p_entry, TRUE, FALSE, 0);
    gtk_widget_show_all(p_window);*/
}

void reg_window (GtkApplication *app, gpointer user_data) {
    GtkWidget *window2;
    window2 = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window2), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window2), 500, 500);
    gtk_widget_show_all (window2);
}

static void activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button_log;
  GtkWidget *button_reg;
  GtkWidget *button_box;
 
  //window
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Registration");
  gtk_window_set_default_size (GTK_WINDOW (window), 1000, 500);

//buttons
  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button_log = gtk_button_new_with_label ("LOG IN");
  g_signal_connect (GTK_BUTTON(button_log), "clicked", G_CALLBACK (open_chat), window);
  //g_signal_connect_swapped (button_log, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), button_log);

  button_reg = gtk_button_new_with_label ("REGISTER NOW");
  g_signal_connect (button_reg, "clicked", G_CALLBACK (reg_window), NULL);
  g_signal_connect_swapped (button_reg, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), button_reg);

  //inputs



//css link
GtkCssProvider *provider = gtk_css_provider_new ();
 gtk_css_provider_load_from_path (provider, "/Users/vostroverk/Desktop/uchat/Client/src/base/theme.css", NULL);

//css add selector
GtkStyleContext *context;
 context = gtk_widget_get_style_context(button_reg);
 gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
 gtk_style_context_add_class(context,"button_reg");

 GtkStyleContext *context2;
 context2 = gtk_widget_get_style_context(window);
 gtk_style_context_add_provider (context2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
 gtk_style_context_add_class(context2,"window");

  gtk_widget_show_all (window);
}

int main (int argc, char **argv)
{
  GtkApplication *app;
  int status;
  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run(G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

