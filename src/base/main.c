#include "client.h"

void open_chat (GtkWidget *window, GdkEvent *event, gpointer user_data) 
{ 

    gtk_widget_destroy(gtk_widget_get_parent(window));
    /*  ВОТ ТУТ ОКНО С ЧАТОМ */
}

void open_reg (GtkWidget *window, GdkEvent *event, gpointer user_data) 
{ 

    gtk_widget_destroy(gtk_widget_get_parent(window));
    /*  ВОТ ТУТ ОКНО С РЕГИСТРАЦИЕЙ */
}

static void activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button_log;
  GtkWidget *button_reg;
  GtkWidget *button_box;
  GtkWidget *label;

  //window
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Registration");
  gtk_window_set_default_size (GTK_WINDOW (window), 1000, 500);

//buttons
  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button_log = gtk_button_new_with_label ("LOG IN");
  g_signal_connect (GTK_BUTTON(button_log), "clicked", G_CALLBACK (open_chat), window);
  gtk_container_add (GTK_CONTAINER (button_box), button_log);

  button_reg = gtk_button_new_with_label ("REGISTER NOW");
  g_signal_connect (GTK_BUTTON(button_reg), "clicked", G_CALLBACK (open_reg), window);
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

