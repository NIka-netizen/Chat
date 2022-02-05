#include "client.h"
GtkWidget *entry_for_new_password, *entry_for_repeat_password, *edit[2];
GtkWidget *Error_password, *Error_repeat_password, *Error_login, *Error_secret_word;
GtkWidget *entry_login, *entry_for_word;

void reopen_authorezation2(GtkWidget *button){
  open_authorezation(button, "forgot_password");
}

/* КОРРЕКТНОСТЬ ВВОДА ЛОГИНА И СЕКРЕТНОГО СЛОВА И ОТПРАВКА ДАННЫХ */
int validation_login_secWord (GtkWidget *button, GtkBuilder *builder, GtkWidget **error_entry_login, GtkWidget **error_entry_secret_word) 
{ 
  char *login = (char *)gtk_entry_get_text(GTK_ENTRY(widgets_forgot_password.entry_login));
  char *secret_word = (char *)gtk_entry_get_text(GTK_ENTRY(widgets_forgot_password.entry_secret_word));

  /* ПРОВЕРКА ЛОГИНА */
  int length = mx_strlen(login);
  int checker = 0;
  
  if (length < 6 || length >= 20) 
  {
    gtk_label_set_text(GTK_LABEL(*error_entry_login), "Wrong login");  
    checker++;
  }
  else {
    for (int i = 0; i < length; i++) {
      if (!mx_isdigit(login[i]) && !mx_isalpha(login[i]) && login[i] != '_') {
        gtk_label_set_text(GTK_LABEL(*error_entry_login),"Wrong login");  
        checker++;
        gtk_entry_set_text(GTK_ENTRY(widgets_forgot_password.entry_login),""); 
        break;
      }
      else {
        gtk_label_set_text(GTK_LABEL(*error_entry_login), ""); 
    
      }
    }
  } 
  /* ПРОВЕРКА НА СЕКРЕТНОЕ СЛОВО*/
  length = mx_strlen(secret_word);
  if (length < 3) {
    gtk_label_set_text(GTK_LABEL(*error_entry_secret_word),"Wrong secret word");  
    checker++;
    gtk_entry_set_text(GTK_ENTRY(widgets_forgot_password.entry_secret_word),"");
  }
  else
  {
    for (int i = 0; i < length; i++) {
      if(!mx_isdigit(secret_word[i]) && !mx_isalpha(secret_word[i]) && secret_word[i] != '_')
      {
        gtk_label_set_text(GTK_LABEL(*error_entry_secret_word),"Wrong secret word");  
        checker++;
        gtk_entry_set_text(GTK_ENTRY(widgets_forgot_password.entry_secret_word),"");
      }
      else 
      {
        gtk_label_set_text(GTK_LABEL(*error_entry_secret_word), ""); 
      }
    }
  }
  if (checker > 0) {
    return 1;
  }
  check_second.login = mx_strnew(mx_strlen((char *)login));
  mx_strcpy(check_second.login, (char *)login);
  check_start.login = mx_strnew(mx_strlen((char *)login));
  mx_strcpy(check_start.login, (char *)login);
  check_start.secret_word = mx_strnew(mx_strlen((char *)secret_word));
  mx_strcpy(check_start.secret_word, (char *)secret_word);

  /*проверка из бд*/
  if (!check_secret_word(check_second.login, check_start.secret_word))
  {
    gtk_label_set_text(GTK_LABEL(*error_entry_secret_word),"Some information is incorrect");  
    return 1;
  }
  gtk_entry_set_text(GTK_ENTRY(widgets_forgot_password.entry_login),""); 
  gtk_entry_set_text(GTK_ENTRY(widgets_forgot_password.entry_secret_word),"");
  return 0;
}

/* КОРРЕКТНОСТЬ ВВОДА ПАРОЛЯ И ОТПРАВКА ДАННЫХ */
int validation_passwords(GtkWidget *button, GtkBuilder *builder, GtkWidget **Error_password, GtkWidget **Error_repeat_password)
{
  char *password = (char *)gtk_entry_get_text(GTK_ENTRY(widgets_forgot_password.entry_password));
  char *repeat_password = (char *)gtk_entry_get_text(GTK_ENTRY(widgets_forgot_password.entry_repeat_password));

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
    //gtk_label_set_text(GTK_LABEL(*Error_password),"The password must consist of eight or \nmore characters of the Latin alphabet, \ncontain uppercase and lowercase letters, numbers"); 
    gtk_widget_set_visible(GTK_WIDGET(*Error_password), true);
    checker++;
    gtk_entry_set_text(GTK_ENTRY(widgets_forgot_password.entry_password),"");
    gtk_entry_set_text(GTK_ENTRY(widgets_forgot_password.entry_repeat_password),"");
  }
  else {
    gtk_label_set_text(GTK_LABEL(*Error_password), "");
  }
  /* ПРОВЕРКА НА СХОДИМОСТЬ ПАРОЛЕЙ */
  if (mx_strcmp(password, repeat_password) != 0) {
    gtk_label_set_text(GTK_LABEL(*Error_repeat_password),"Password mismatch");  
    checker++;
    gtk_entry_set_text(GTK_ENTRY(widgets_forgot_password.entry_repeat_password),"");
     gtk_entry_set_text(GTK_ENTRY(widgets_forgot_password.entry_password),"");
  }
  else {
    gtk_label_set_text(GTK_LABEL(*Error_repeat_password), ""); 
  }
  if (checker > 0) {
    return 1;
  }
  check_second.password = mx_strnew(mx_strlen((char *)password));
  mx_strcpy(check_second.password, (char *)password);

  /*проверка из бд*/
  if (!change_password(check_start.login, check_second.password)) {
    gtk_label_set_text(GTK_LABEL(*Error_repeat_password),"Some information is incorrect"); 
    gtk_entry_set_text(GTK_ENTRY(widgets_forgot_password.entry_repeat_password),"");
    gtk_entry_set_text(GTK_ENTRY(authorization_log_pass.password),"");
    return 1;
  }
  gtk_entry_set_text(GTK_ENTRY(widgets_forgot_password.entry_password),"");
  gtk_entry_set_text(GTK_ENTRY(widgets_forgot_password.entry_repeat_password),"");
  return 0;
} 

/* ПРОВОДНИК 1 */
void valid_data_SW_login (GtkWidget *button, GtkBuilder *builder) {
  if (!validation_login_secWord(button, builder, &widgets_forgot_password.label_error_login, &widgets_forgot_password.label_error_SW))
  {
    window_change_password(button);
  }
}

/* ПРОВОДНИК 2 */
void valid_data_passwords(GtkWidget *button, GtkBuilder *builder) {
  if (!validation_passwords(button, builder, &widgets_forgot_password.label_error_password, &widgets_forgot_password.label_error_repeat_password)) {
        reopen_authorezation2(button);
  }
}

void validation_authorization_data(GtkWidget *button, GdkEvent *event, gpointer user_data) {
  char *login = (char *)gtk_entry_get_text(GTK_ENTRY(authorization_log_pass.login));
  char *password = (char *)gtk_entry_get_text(GTK_ENTRY(authorization_log_pass.password));

  authorization_data.login = mx_strnew(mx_strlen((char *)login));
  mx_strcpy(authorization_data.login, (char *)login);
  authorization_data.password = mx_strnew(mx_strlen((char *)password));
  mx_strcpy( authorization_data.password, (char *)password);
  
  char *author_user = autorize_user(authorization_data.login, authorization_data.password);
  write(1, author_user, mx_strlen(author_user));

    /*проверка из бд*/
  if (mx_strcmp(author_user, "0") == 0) {
    gtk_label_set_text(GTK_LABEL(authorization_log_pass.Error_message),"Some information is incorrect"); 
    gtk_entry_set_text(GTK_ENTRY(authorization_log_pass.login),"");
    gtk_entry_set_text(GTK_ENTRY(authorization_log_pass.password),"");
  }
  else {
    data.user_id = mx_strdup(author_user);
    open_chat(button);
  }
}

/* ОКНО СО СМЕНОЙ ПАРОЛЯ */
void window_change_password(GtkWidget *button)
{
  GtkWidget *window;
  window = gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  GError *error = NULL;
  GtkBuilder *builder = gtk_builder_new();

  if (gtk_builder_add_from_file(builder, "Client/src/change_password_screen.glade", &error) == 0)
  {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    exit(0);
  }

  GtkWidget *authorization_layout = GTK_WIDGET(gtk_builder_get_object(builder, "change_password_layout"));

  widgets_forgot_password.label_error_password = GTK_WIDGET(gtk_builder_get_object(builder, "error_new_password"));
  widgets_forgot_password.label_error_repeat_password = GTK_WIDGET(gtk_builder_get_object(builder, "error_repeat_password"));

  widgets_forgot_password.entry_password = GTK_WIDGET(gtk_builder_get_object(builder, "new_password_entry"));
  widgets_forgot_password.entry_repeat_password = GTK_WIDGET(gtk_builder_get_object(builder, "repeat_password_entry"));

  GtkWidget *apply_btn = GTK_WIDGET(gtk_builder_get_object(builder, "confirm_btn"));
  g_signal_connect(apply_btn, "clicked", G_CALLBACK(valid_data_passwords), builder);

  gtk_container_add(GTK_CONTAINER(window), authorization_layout);
  g_object_unref(builder);

}

/* ОКНО С СЕКРЕТНЫМ СЛОВОМ И ЛОГИНОМ */
void window_secret_word (GtkWidget *button, GdkEvent *event, gpointer user_data)
{
  GtkWidget *window;
  window = gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  GError *error = NULL;
  GtkBuilder *builder = gtk_builder_new();

  if (gtk_builder_add_from_file(builder, "Client/src/recovery_password_screen.glade", &error) == 0)
  {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    exit(0);
  }

  GtkWidget *authorization_layout = GTK_WIDGET(gtk_builder_get_object(builder, "recovery_password_layout"));

  widgets_forgot_password.label_error_login = GTK_WIDGET(gtk_builder_get_object(builder, "Error_login"));
  widgets_forgot_password.label_error_SW = GTK_WIDGET(gtk_builder_get_object(builder, "error_secret_word"));

  widgets_forgot_password.entry_login = GTK_WIDGET(gtk_builder_get_object(builder, "login_entry"));

  widgets_forgot_password.entry_secret_word = GTK_WIDGET(gtk_builder_get_object(builder, "secret_word_entry"));

  GtkWidget *apply_btn = GTK_WIDGET(gtk_builder_get_object(builder, "confirm_btn"));
  g_signal_connect(apply_btn, "clicked", G_CALLBACK(valid_data_SW_login), builder);

  gtk_container_add(GTK_CONTAINER(window), authorization_layout);
  g_object_unref(builder);
}

/* ОКНО С АВТОРИЗАЦИЕЙ */
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
    window = gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent(button)));
    gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  }
  else {
    window = button;
  }

  GError *error = NULL;
  GtkBuilder *builder = gtk_builder_new();

  if (gtk_builder_add_from_file(builder, "Client/src/authorization_screen.glade", &error) == 0)
  {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    exit(0);
  }

  GtkWidget *authorization_layout = GTK_WIDGET(gtk_builder_get_object(builder, "authorization_layout"));

  //edits
  authorization_log_pass.login = GTK_WIDGET(gtk_builder_get_object(builder, "entry_login"));
  authorization_log_pass.password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_password"));

  authorization_log_pass.Error_message = GTK_WIDGET(gtk_builder_get_object(builder, "error_information"));

  //buttons
  GtkWidget *button_log = GTK_WIDGET(gtk_builder_get_object(builder, "log_in_btn"));
  g_signal_connect(GTK_BUTTON(button_log), "clicked", G_CALLBACK(validation_authorization_data), builder);

  GtkWidget *button_reg = GTK_WIDGET(gtk_builder_get_object(builder, "reg_btn"));
  g_signal_connect(GTK_BUTTON(button_reg), "clicked", G_CALLBACK(open_reg), builder);

  GtkWidget *forg_password = GTK_WIDGET(gtk_builder_get_object(builder, "forg_btn"));
  g_signal_connect(GTK_BUTTON(forg_password), "clicked", G_CALLBACK(window_secret_word), builder);

  gtk_container_add(GTK_CONTAINER(window), authorization_layout);
  g_object_unref(builder);

  // //css link
  // GtkCssProvider *provider = gtk_css_provider_new();
  // gtk_css_provider_load_from_path(provider, "/Users/vostroverk/Desktop/uchat/Client/src/base/theme.css", NULL);

  // //css add selector

  // GtkStyleContext *context6_1;
  // context6_1 = gtk_widget_get_style_context(label[0]);
  // gtk_style_context_add_provider(context6_1, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  // gtk_style_context_add_class(context6_1, "label");

  // GtkStyleContext *context7_1;
  // context7_1 = gtk_widget_get_style_context(edit[0]);
  // gtk_style_context_add_provider(context7_1, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  // gtk_style_context_add_class(context7_1, "edit");

  // GtkStyleContext *context6_2;
  // context6_2 = gtk_widget_get_style_context(label[1]);
  // gtk_style_context_add_provider(context6_2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  // gtk_style_context_add_class(context6_2, "label");

  // GtkStyleContext *context7_2;
  // context7_2 = gtk_widget_get_style_context(edit[1]);
  // gtk_style_context_add_provider(context7_2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  // gtk_style_context_add_class(context7_2, "edit");

  // GtkStyleContext *context8;
  // context8 = gtk_widget_get_style_context(button_reg);
  // gtk_style_context_add_provider(context8, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  // gtk_style_context_add_class(context8, "button_log");

  // GtkStyleContext *context5;
  // context5 = gtk_widget_get_style_context(button_log);
  // gtk_style_context_add_provider(context5, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  // gtk_style_context_add_class(context5, "button_log1");
}
