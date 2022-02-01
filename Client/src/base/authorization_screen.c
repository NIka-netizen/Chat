#include "client.h"
GtkWidget *entry_for_new_password, *entry_for_repeat_password;
GtkWidget *Error_password, *Error_repeat_password;

void reopen_authorezation2(GtkWidget *button){
  open_authorezation(button, "forgot_password");
}

int validation()
{
  const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry_for_new_password)); 
  const gchar *repeat_password = gtk_entry_get_text(GTK_ENTRY(entry_for_repeat_password));
/* ПРОВЕРКА ПАРОЛЯ */
  int length = mx_strlen(password);
  int digit = 0;
  int alpha = 0;
  int little_letter = 0;
  int main_letter = 0;
  int checker = 0;

  for (int i = 0; i < length; i++) {
    if (mx_isdigit(password[i])) 
      digit++;
    if (mx_isalpha(password[i])) 
       alpha++;
    if (mx_isupper(password[i])) 
      main_letter++;
    if (mx_islower(password[i])) 
      little_letter++;
  }
  
  if (mx_strlen(password) <= 8 || digit < 1 || alpha < 8 || main_letter < 1 || little_letter < 1) {
    gtk_label_set_text(GTK_LABEL(Error_password),"The password must consist of eight or more characters of the Latin alphabet, contain uppercase and lowercase letters, numbers");  
    checker++;
    gtk_entry_set_text(GTK_ENTRY(entry_for_new_password),"");
    gtk_entry_set_text(GTK_ENTRY(entry_for_repeat_password),"");
  }
  else {
    gtk_label_set_text(GTK_LABEL(Error_password), "");
  }
/* ПРОВЕРКА НА СХОДИМОСТЬ ПАРОЛЕЙ */
  if (mx_strcmp(password, repeat_password) != 0) {
    gtk_label_set_text(GTK_LABEL(Error_repeat_password),"Password mismatch");  
    checker++;
    gtk_entry_set_text(GTK_ENTRY(entry_for_repeat_password),"");
     gtk_entry_set_text(GTK_ENTRY(entry_for_new_password),"");
  }
  else {
    gtk_label_set_text(GTK_LABEL(Error_repeat_password), ""); 
  }
  if (checker > 0) {
    return 1;
  }
  gtk_entry_set_text(GTK_ENTRY(entry_for_new_password),"");
  gtk_entry_set_text(GTK_ENTRY(entry_for_repeat_password),"");
  return 0;
} 

void save_user2 (GtkWidget *button, GdkEvent *event, gpointer user_data) {
  GtkWidget *window;
  window = gtk_widget_get_parent(gtk_widget_get_parent(button));

  if (!validation()) {
    reopen_authorezation2(button);
  }
}

void window_change_password(GtkWidget *button, GdkEvent *event, gpointer user_data)
{
  GtkWidget *window;
  window = gtk_widget_get_parent(gtk_widget_get_parent(button));
  gtk_widget_destroy(gtk_widget_get_parent(button));
  /*  ВОТ ТУТ ОКНО СО СМЕНОЙ ПАРОЛЯ */

  GtkWidget *main_layout;
  GtkWidget *label_new_password;
  GtkWidget *label_repeat_password;
  GtkButton *apply_btn;

  Error_password = gtk_label_new("");
  Error_repeat_password = gtk_label_new("");

  main_layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window), main_layout);

  label_new_password = gtk_label_new("New password");
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(label_new_password));

  entry_for_new_password = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_for_new_password), "Password");
  gtk_entry_set_visibility(GTK_ENTRY(entry_for_new_password), FALSE);
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(entry_for_new_password));
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(Error_password));

  label_repeat_password = gtk_label_new("Repeat the password");
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(label_repeat_password));

  entry_for_repeat_password = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_for_repeat_password), "Repeat password");
  gtk_entry_set_visibility(GTK_ENTRY(entry_for_repeat_password), FALSE);
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(entry_for_repeat_password));
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(Error_repeat_password));

  apply_btn = GTK_BUTTON(gtk_button_new());
  gtk_button_set_label(apply_btn, "OK");

  g_signal_connect(apply_btn, "clicked", G_CALLBACK(save_user2), window); 

  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(apply_btn));

  gtk_widget_show_all(window);
}

void window_secret_word (GtkWidget *button, GdkEvent *event, gpointer user_data)
{
  GtkWidget *window;
  window = gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  /*  ВОТ ТУТ ОКНО С ВВОДОМ СЕКРЕТНОГО СЛОВА */

  GtkWidget *main_layout;

  GtkWidget *label_secret_word;
  GtkWidget *label_login;

  GtkButton *apply_btn;

  GtkWidget *entry_for_word;
  GtkWidget *entry_login;

  main_layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window), main_layout);

  label_login = gtk_label_new("Enter your login");
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(label_login));

  entry_login = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_login), "Login");
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(entry_login));

  label_secret_word = gtk_label_new("Enter the secret word");
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(label_secret_word));

  entry_for_word = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_for_word), "Secret word");
  //gtk_entry_set_text(GTK_ENTRY(emailEntry),"");
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(entry_for_word));

  apply_btn = GTK_BUTTON(gtk_button_new());
  gtk_button_set_label(apply_btn, "OK");
  g_signal_connect(apply_btn, "clicked", G_CALLBACK(window_change_password), window);
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(apply_btn));

  gtk_widget_show_all(window);
}

void open_authorezation(GtkWidget *button, char *event)
{
  GtkWidget *window;
  if (mx_strcmp(event, "registration") == 0){
    window = gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent(button)));
    gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  }
  else if (mx_strcmp(event, "start_app") == 0) {
     window = button;
  }
  else if (!mx_strcmp(event, "forgot_password")) {
    window = gtk_widget_get_parent(gtk_widget_get_parent(button));
    gtk_widget_destroy(gtk_widget_get_parent(button));
  }
  else {
    window = button;
  }

  GtkWidget *button_log;
  GtkWidget *button_reg;
  GtkWidget *forg_password;
  GtkWidget *button_box;
  GtkWidget *label_edit_box;
  GtkWidget *main_box;
  GtkWidget *change_password_box;
  GtkWidget *label[2];
  GtkWidget *edit[2];

  main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window), main_box);

  // label_edit_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
  // gtk_container_add (GTK_CONTAINER (main_box), label_edit_box);

  // label and edits
  //gtk_widget_set_size_request(GTK_WIDGET(label_edit_box), 700, 100);

  for (int i = 0; i < 2; i++)
  {
    edit[i] = gtk_entry_new();
    if (i == 0)
      label[i] = gtk_label_new("Login");
    if (i == 1)
    {
      label[i] = gtk_label_new("Password");
      gtk_entry_set_visibility(GTK_ENTRY(edit[1]), FALSE);
    }

    gtk_box_pack_start(GTK_BOX(main_box), label[i], 0, 0, 5);
    gtk_box_pack_start(GTK_BOX(main_box), edit[i], 0, 0, 5);

    gtk_widget_set_size_request(GTK_WIDGET(edit[i]), 100, 50);

    gtk_widget_show(edit[i]);
    gtk_widget_show(label[i]);
  }

  button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add(GTK_CONTAINER(main_box), button_box);
  change_password_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add(GTK_CONTAINER(main_box), change_password_box);

  //buttons
  button_log = gtk_button_new_with_label("LOG IN");
  g_signal_connect(GTK_BUTTON(button_log), "clicked", G_CALLBACK(open_chat), window);
  gtk_container_add(GTK_CONTAINER(button_box), button_log);
  gtk_widget_set_size_request(GTK_WIDGET(button_log), 100, 100);

  button_reg = gtk_button_new_with_label("REGISTER NOW");
  g_signal_connect(GTK_BUTTON(button_reg), "clicked", G_CALLBACK(open_reg), window);
  gtk_container_add(GTK_CONTAINER(button_box), button_reg);

  forg_password = gtk_button_new_with_label("Forgot password");
  g_signal_connect(GTK_BUTTON(forg_password), "clicked", G_CALLBACK(window_secret_word), window);
  gtk_container_add(GTK_CONTAINER(change_password_box), forg_password);

  //css link
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "/Users/vostroverk/Desktop/uchat/Client/src/base/theme.css", NULL);

  //css add selector

  GtkStyleContext *context6_1;
  context6_1 = gtk_widget_get_style_context(label[0]);
  gtk_style_context_add_provider(context6_1, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context6_1, "label");

  GtkStyleContext *context7_1;
  context7_1 = gtk_widget_get_style_context(edit[0]);
  gtk_style_context_add_provider(context7_1, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context7_1, "edit");

  GtkStyleContext *context6_2;
  context6_2 = gtk_widget_get_style_context(label[1]);
  gtk_style_context_add_provider(context6_2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context6_2, "label");

  GtkStyleContext *context7_2;
  context7_2 = gtk_widget_get_style_context(edit[1]);
  gtk_style_context_add_provider(context7_2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context7_2, "edit");

  GtkStyleContext *context8;
  context8 = gtk_widget_get_style_context(button_reg);
  gtk_style_context_add_provider(context8, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context8, "button_log");

  GtkStyleContext *context5;
  context5 = gtk_widget_get_style_context(button_log);
  gtk_style_context_add_provider(context5, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context5, "button_log1");

  /* КОНТЕЙНЕРЫ */

  GtkStyleContext *context2;
  context2 = gtk_widget_get_style_context(forg_password);
  gtk_style_context_add_provider(context2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context2, "Forgot password");

  GtkStyleContext *context3;
  context3 = gtk_widget_get_style_context(window);
  gtk_style_context_add_provider(context3, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context3, "window");

  GtkStyleContext *context3_1;
  context3_1 = gtk_widget_get_style_context(main_box);
  gtk_style_context_add_provider(context3_1, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context3_1, "main_box");

  gtk_widget_show_all(window);
}
