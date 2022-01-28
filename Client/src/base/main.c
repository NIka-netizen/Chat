#include "client.h"

void open_chat (GtkApplication *app, gpointer user_data) {
    GtkWidget *window1;
    window1 = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window1), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window1), 200, 200);
    gtk_widget_show_all (window1);
}

void reg_window (GtkApplication *app, gpointer user_data) {
    GtkWidget *window1;
    window1 = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window1), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window1), 200, 200);
    gtk_widget_show_all (window1);
}

static void activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button_log;
  GtkWidget *button_reg;
  GtkWidget *button_box;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Registration");
  gtk_window_set_default_size (GTK_WINDOW (window), 400, 400);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button_log = gtk_button_new_with_label ("LOG IN");
  g_signal_connect_swapped (button_log, "clicked", G_CALLBACK (open_chat), window);
  //g_signal_connect_swapped (button_log, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), button_log);

  button_reg = gtk_button_new_with_label ("REGISTER NOW");
  g_signal_connect (button_reg, "clicked", G_CALLBACK (reg_window), NULL);
  g_signal_connect_swapped (button_reg, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), button_reg);

  gtk_widget_show_all (window);
}

int main (int argc, char **argv)
{
  GtkApplication *app;
  int status;
  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

/*static void activate (GtkApplication* app, gpointer user_data)
{
  GtkWidget *window;
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Uchat");
  gtk_window_set_default_size (GTK_WINDOW (window), 1000, 700);
  gtk_widget_show_all (window);
  registration();
}

int main(int argc, char *argv[]) 
{
    GtkApplication *app;
    int status;

    app = gtk_application_new ("uchat", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}*/
