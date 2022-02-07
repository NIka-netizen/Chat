#include "client.h"

void connection () {
    if (params.argc != 3)
    {
        puts("Usage: ./uchat [ipv4][port]");
        exit(1);
    }
  data.ipv4 = mx_strdup(params.argv[0]);
  data.port = atoi(params.argv[1]);
  server_set_connection();
}

static void activate(GtkApplication *app, gpointer user_data)
{
  GError *error = NULL;
  GtkBuilder *builder = gtk_builder_new();
  if (!gtk_builder_add_from_file(builder, "client/src/main_window.glade", &error))
    {
        //g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        exit(0);
    }
  GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
  g_object_unref(builder);

  connection();

  open_authorezation(window, "start_app");
  gtk_application_add_window(app, GTK_WINDOW(window));
  gtk_widget_show_all(window);
  //window
  // window = gtk_application_window_new(app);
  // gtk_window_set_title(GTK_WINDOW(window), "Registration");
  // gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  // gtk_window_set_default_size(GTK_WINDOW(window), 1000, 500);

  // open_authorezation(window, "start_app");
}

int main(int argc, char **argv)
{
  params.argc = argc;
  params.argv[0] = mx_strdup(argv[1]);
  params.argv[1] = mx_strdup(argv[2]);

  argc = 1;
  char **argv_client = malloc(sizeof(char **));
  argv_client[0] = mx_strdup(argv[0]);

  GtkApplication *app;
  int status;
  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);  
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv_client);
  g_object_unref(app);

  return status;
}
