#include "client.h"

void open_reg(GtkWidget *button, GdkEvent *event, gpointer user_data)
{
 GtkWidget *window;
  window = gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  /*  ВОТ ТУТ ОКНО С РЕГИСТРАЦИЕЙ */

  GtkWidget *main_layout;

  GtkWidget *label_login;
  GtkWidget *label_for_nickname;
  GtkWidget *label_password;
  GtkWidget *label_repeat_password;
  GtkWidget *label_secret_word;
  
  
  GtkWidget *entry_login;
  GtkWidget *entry_for_nickname;
  GtkWidget *entry_password;
  GtkWidget *entry_repeat_password;
  GtkWidget *entry_secret_word;

  GtkButton *apply_btn;

  main_layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window), main_layout);

  label_login = gtk_label_new("Please enter your login");
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(label_login));
  entry_login = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_login), "Enter your login");
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(entry_login));

  label_for_nickname = gtk_label_new("Please enter your nickname");
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(label_for_nickname));
  entry_for_nickname = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_for_nickname), "Enter your nickname");
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(entry_for_nickname));

  label_password = gtk_label_new("Please enter the password");
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(label_password));
  entry_password = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_password), "Enter the password");
  gtk_entry_set_visibility(GTK_ENTRY(entry_password), FALSE);
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(entry_password));

  label_repeat_password = gtk_label_new("Please repeat the password");
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(label_repeat_password));
  entry_repeat_password = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_repeat_password), "Repeat the password");
  gtk_entry_set_visibility(GTK_ENTRY(entry_repeat_password), FALSE);
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(entry_repeat_password));

  label_secret_word = gtk_label_new("Please enter your nickname");
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(label_secret_word));
  entry_secret_word = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_secret_word), "Enter your nickname");
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(entry_secret_word));

  apply_btn = GTK_BUTTON(gtk_button_new());
  gtk_button_set_label(apply_btn, "OK");
  g_signal_connect(apply_btn, "clicked", G_CALLBACK(open_authorezation), window); 
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(apply_btn));

  gtk_widget_show_all(window);
}
