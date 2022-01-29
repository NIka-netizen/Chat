#include "client.h"

void change_password (GtkWidget *button, GdkEvent *event, gpointer user_data) {
  gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(button)));
    /*  ВОТ ТУТ ОКНО СО СМЕНОЙ ПАРОЛЯ */
}

void open_chat (GtkWidget *window, GdkEvent *event, gpointer user_data) 
{ 
   gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(window)));
    /*  ВОТ ТУТ ОКНО С ЧАТОМ */
}

void open_reg (GtkWidget *window, GdkEvent *event, gpointer user_data) 
{ 

   gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(window)));
    /*  ВОТ ТУТ ОКНО С РЕГИСТРАЦИЕЙ */
    
}

static void activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button_log;
  GtkWidget *button_reg;
  GtkWidget *forg_password;
  GtkWidget *button_box;
  GtkWidget *label_edit_box;
  GtkWidget *main_box;
  GtkWidget *change_password_box;
  GtkWidget *label[2];
  GtkWidget *edit[2];


  //window
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Registration");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  gtk_window_set_default_size (GTK_WINDOW (window), 1000, 500);

  

  main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER (window), main_box);
  label_edit_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
  gtk_container_add (GTK_CONTAINER (main_box), label_edit_box);
  button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (main_box), button_box);
  change_password_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (main_box), change_password_box);

  // label and edits
  /*gtk_widget_set_size_request(label_edit_box, 100, 100);*/
  
  for (int i = 0; i < 2; i++) {
    edit[i] = gtk_entry_new();
    if (i == 0)
      label[i] = gtk_label_new("Login");
    if (i == 1)
      label[i] = gtk_label_new("Password");
    gtk_box_pack_start (GTK_BOX (label_edit_box), label[i], 0, 0, 5);
	  gtk_box_pack_start (GTK_BOX (label_edit_box), edit[i], 0, 0, 5);
	  gtk_widget_show (edit[i]);
    gtk_widget_show (label[i]);
  }

  //buttons
  button_log = gtk_button_new_with_label ("LOG IN");
  g_signal_connect (GTK_BUTTON(button_log), "clicked", G_CALLBACK (open_chat), window);
  gtk_container_add (GTK_CONTAINER (button_box), button_log);

  button_reg = gtk_button_new_with_label ("REGISTER NOW");
  g_signal_connect (GTK_BUTTON(button_reg), "clicked", G_CALLBACK (open_reg), window);
  gtk_container_add (GTK_CONTAINER (button_box), button_reg);


  forg_password = gtk_button_new_with_label ("Forgot password");
  g_signal_connect (GTK_BUTTON(forg_password), "clicked", G_CALLBACK (change_password), window);
  gtk_container_add (GTK_CONTAINER (change_password_box), forg_password);

//css link
GtkCssProvider *provider = gtk_css_provider_new ();
 gtk_css_provider_load_from_path (provider, "/Users/vostroverk/Desktop/uchat/Client/src/base/theme.css", NULL);

//css add selector

for (int i = 0; i < 2; i++) {
  GtkStyleContext *context6;
  context6 = gtk_widget_get_style_context(label[i]);
  gtk_style_context_add_provider (context6, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context6,"label");

  GtkStyleContext *context7;
  context7 = gtk_widget_get_style_context(edit[i]);
  gtk_style_context_add_provider (context7, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context7,"edit");
}

GtkStyleContext *context8;
context8 = gtk_widget_get_style_context(button_reg);
gtk_style_context_add_provider (context8, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
gtk_style_context_add_class(context8,"button_log");

GtkStyleContext *context5;
context5 = gtk_widget_get_style_context(button_log);
gtk_style_context_add_provider (context5, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
gtk_style_context_add_class(context5,"button_log");

/* КОНТЕЙНЕРЫ */

GtkStyleContext *context;
context = gtk_widget_get_style_context(button_box);
gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
gtk_style_context_add_class(context,"button");

GtkStyleContext *context2;
context2 = gtk_widget_get_style_context(forg_password);
gtk_style_context_add_provider (context2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
gtk_style_context_add_class(context2,"change_password");

 GtkStyleContext *context3;
 context3 = gtk_widget_get_style_context(window);
 gtk_style_context_add_provider (context3, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
 gtk_style_context_add_class(context3,"window");

GtkStyleContext *context4;
 context4 = gtk_widget_get_style_context(label_edit_box);
 gtk_style_context_add_provider (context4, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
 gtk_style_context_add_class(context4,"label_edit");

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

