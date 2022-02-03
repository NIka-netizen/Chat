#include "client.h"

static void activate(GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;

  //window
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Registration");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_window_set_default_size(GTK_WINDOW(window), 1000, 500);

  open_authorezation(window, "start_app");
}

int main(int argc, char **argv)
{
  GtkApplication *app;
  int status;
  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
