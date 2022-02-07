#include "client.h"
GtkWidget *entry_login, *entry_for_nickname, *entry_password, *entry_repeat_password, *entry_secret_word;
GtkWidget *Error_login, *Error_nickname, *Error_password, *Error_repeat_password, *Error_secret_word;

void reopen_authorezation(GtkWidget *button)
{
  open_authorezation(button, "registration");
}

int signup_button_clicked(GtkWidget *button, GtkBuilder *builder, GtkWidget **Error_login, GtkWidget **Error_password, GtkWidget **Error_repeat_password, GtkWidget **Error_nickname, GtkWidget **Error_secret_word)
{

  char *login = (char *)gtk_entry_get_text(GTK_ENTRY(widgets_registration.entry_login));
  char *password = (char *)gtk_entry_get_text(GTK_ENTRY(widgets_registration.entry_password));
  char *repeat_password = (char *)gtk_entry_get_text(GTK_ENTRY(widgets_registration.entry_repeat_password));  
  char *nickname = (char *)gtk_entry_get_text(GTK_ENTRY(widgets_registration.entry_nickname));  
  char *secret_word = (char *)gtk_entry_get_text(GTK_ENTRY(widgets_registration.entry_secret_word));  

  /* ПРОВЕРКА ЛОГИНА */
  int length = mx_strlen(login);
  int checker = 0;

  if (length < 6 || length >= 20) 
  {
    gtk_label_set_text(GTK_LABEL(*Error_login),"Login must be from 6 to 20 characters and contain only Latin characters, numbers or underscore");  
    checker++;
  }
  else {
    for (int i = 0; i < length; i++) {
      if (!mx_isdigit(login[i]) && !mx_isalpha(login[i]) && login[i] != '_') {
        gtk_label_set_text(GTK_LABEL(*Error_login),"Login must be from 6 to 20 characters and contain only Latin characters, numbers or underscore");  
        checker++;
        gtk_entry_set_text(GTK_ENTRY(widgets_registration.entry_login),""); 
        break;
      }
      else {
        gtk_label_set_text(GTK_LABEL(*Error_login), ""); 
    
      }
    }
  } 
  /* ПРОВЕРКА ПАРОЛЯ */
  length = mx_strlen(password);
  int digit = 0;
  int alpha = 0;
  int little_letter = 0;
  int main_letter = 0;

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
    gtk_label_set_text(GTK_LABEL(*Error_password),"The password must consist of eight or more characters of the Latin alphabet, contain uppercase and lowercase letters, numbers");  
    checker++;
    gtk_entry_set_text(GTK_ENTRY(widgets_registration.entry_password),"");
    gtk_entry_set_text(GTK_ENTRY(widgets_registration.entry_repeat_password),"");
  }
  else {
    gtk_label_set_text(GTK_LABEL(*Error_password), "");
  }
  /* ПРОВЕРКА НА СХОДИМОСТЬ ПАРОЛЕЙ */
  if (mx_strcmp(password, repeat_password) != 0) {
    gtk_label_set_text(GTK_LABEL(*Error_repeat_password),"Password mismatch");  
    checker++;
    gtk_entry_set_text(GTK_ENTRY(widgets_registration.entry_repeat_password),"");
     gtk_entry_set_text(GTK_ENTRY(widgets_registration.entry_password),"");
  }
  else {
    gtk_label_set_text(GTK_LABEL(*Error_repeat_password), ""); 
  }
  /* ПРОВЕРКА НА НИКНЕЙМ*/
  length = mx_strlen(nickname);
  if (length < 1) {
    gtk_label_set_text(GTK_LABEL(*Error_nickname),"Nickname must be one or more characters");  
    checker++;
    gtk_entry_set_text(GTK_ENTRY(widgets_registration.entry_nickname),"");
  }
  else {
    gtk_label_set_text(GTK_LABEL(*Error_nickname), ""); 
  }
  /* ПРОВЕРКА НА СЕКРЕТНОЕ СЛОВО*/
  length = mx_strlen(secret_word);
  if (length < 3) {
    gtk_label_set_text(GTK_LABEL(*Error_secret_word),"Secret word must be from 3 characters and contain only Latin characters, numbers or underscore");  
    checker++;
    gtk_entry_set_text(GTK_ENTRY(widgets_registration.entry_secret_word),"");
  }
  else
  {
    for (int i = 0; i < length; i++) {
      if(!mx_isdigit(secret_word[i]) && !mx_isalpha(secret_word[i]) && secret_word[i] != '_')
      {
        gtk_label_set_text(GTK_LABEL(*Error_secret_word),"Secret word must be from 3 characters and contain only Latin characters, numbers or underscore");  
        checker++;
        gtk_entry_set_text(GTK_ENTRY(widgets_registration.entry_secret_word),"");
      }
      else 
      {
        gtk_label_set_text(GTK_LABEL(*Error_secret_word), ""); 
      }
    }
  }
  if (checker > 0) {
    return 1;
  }
  data_registration.login = mx_strnew(mx_strlen((char *)login));
  mx_strcpy(data_registration.login, (char *)login);

  data_registration.password = mx_strnew(mx_strlen((char *)password));
  mx_strcpy(data_registration.password, (char *)password);

  data_registration.nickname = mx_strnew(mx_strlen((char *)nickname));
  mx_strcpy(data_registration.nickname, (char *)nickname);

  data_registration.secret_word = mx_strnew(mx_strlen((char *)secret_word));
  mx_strcpy(data_registration.secret_word, (char *)secret_word);

  message_t data1;
  user_t data2;
  chatuser_t data3;

  char *id = register_user(data_registration.login, data_registration.password, data_registration.nickname, data_registration.secret_word);
  
  if (mx_strcmp(id, "0") == 0) {
    gtk_label_set_text(GTK_LABEL(*Error_login),"Login already exists");  
    gtk_entry_set_text(GTK_ENTRY(widgets_registration.entry_login),""); 
    return 1;
  }
  else {
    data1.u_id = mx_strdup(id);
    data2.u_id = mx_strdup(id);
    data3.u_id = mx_strdup(id);
  }
  gtk_entry_set_text(GTK_ENTRY(widgets_registration.entry_login),""); 
  gtk_entry_set_text(GTK_ENTRY(widgets_registration.entry_password),"");
  gtk_entry_set_text(GTK_ENTRY(widgets_registration.entry_repeat_password),"");
  gtk_entry_set_text(GTK_ENTRY(widgets_registration.entry_nickname),"");
  gtk_entry_set_text(GTK_ENTRY(widgets_registration.entry_secret_word),"");
  return 0;
} 

void save_user (GtkWidget *button, GtkBuilder *builder) 
{
  if (!signup_button_clicked(button, builder, &widgets_registration.label_error_login, &widgets_registration.label_error_password, &widgets_registration.label_error_repeat_password, &widgets_registration.label_error_nickname, &widgets_registration.label_error_secret_word))
  {
    reopen_authorezation(button);
  }
}

void open_reg(GtkWidget *button, GdkEvent *event, gpointer user_data)
{
  GtkWidget *window;
  window = gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  GError *error = NULL;
  GtkBuilder *builder = gtk_builder_new();

  if (gtk_builder_add_from_file(builder, "client/src/registration_screen.glade", &error) == 0)
  {
    //g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    exit(0);
  }

  GtkWidget *authorization_layout = GTK_WIDGET(gtk_builder_get_object(builder, "registration_layout"));

  /* LABELS */
  GtkWidget *label_login = GTK_WIDGET(gtk_builder_get_object(builder, "label_login"));
  GtkWidget *label_password = GTK_WIDGET(gtk_builder_get_object(builder, "label_password"));
  GtkWidget *label_repeat_password = GTK_WIDGET(gtk_builder_get_object(builder, "label_repeat_password"));
  GtkWidget *label_nickname = GTK_WIDGET(gtk_builder_get_object(builder, "label_nickname"));
  GtkWidget *label_secret_word = GTK_WIDGET(gtk_builder_get_object(builder, "label_secret_word"));
  GtkWidget *label_registration = GTK_WIDGET(gtk_builder_get_object(builder, "registration"));

  /*ERRORS*/
  widgets_registration.label_error_login = GTK_WIDGET(gtk_builder_get_object(builder, "error_login"));
  widgets_registration.label_error_password = GTK_WIDGET(gtk_builder_get_object(builder, "error_password"));
  widgets_registration.label_error_repeat_password = GTK_WIDGET(gtk_builder_get_object(builder, "error_repeat_password"));
  widgets_registration.label_error_nickname = GTK_WIDGET(gtk_builder_get_object(builder, "error_nickname"));
  widgets_registration.label_error_secret_word = GTK_WIDGET(gtk_builder_get_object(builder, "error_secret_word"));

  /*ENTRY*/
  widgets_registration.entry_login = GTK_WIDGET(gtk_builder_get_object(builder, "entry_login"));
  widgets_registration.entry_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_password"));
  widgets_registration.entry_repeat_password = GTK_WIDGET(gtk_builder_get_object(builder, "repeat_password"));
  widgets_registration.entry_nickname = GTK_WIDGET(gtk_builder_get_object(builder, "enter_nickname"));
  widgets_registration.entry_secret_word = GTK_WIDGET(gtk_builder_get_object(builder, "entry_SW"));

  GtkWidget *apply_btn = GTK_WIDGET(gtk_builder_get_object(builder, "confirm_btn"));
  g_signal_connect(apply_btn, "clicked", G_CALLBACK(save_user), builder);

  gtk_container_add(GTK_CONTAINER(window), authorization_layout);
  g_object_unref(builder);
  Css_include_reg(label_login, label_password, label_repeat_password, label_nickname, label_secret_word, label_registration, apply_btn);
}
