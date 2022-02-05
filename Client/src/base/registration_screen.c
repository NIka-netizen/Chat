#include "client.h"
GtkWidget *entry_login, *entry_for_nickname, *entry_password, *entry_repeat_password, *entry_secret_word;
GtkWidget *Error_login, *Error_nickname, *Error_password, *Error_repeat_password, *Error_secret_word;

void reopen_authorezation(GtkWidget *button)
{
  open_authorezation(button, "registration");
}

int signup_button_clicked()
{
  const gchar *login = gtk_entry_get_text(GTK_ENTRY(entry_login)); 
  const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry_password)); 
  const gchar *repeat_password = gtk_entry_get_text(GTK_ENTRY(entry_repeat_password)); 
  const gchar *nickname = gtk_entry_get_text(GTK_ENTRY(entry_for_nickname)); 
  const gchar *secret_word = gtk_entry_get_text(GTK_ENTRY(entry_secret_word));  

  /* ПРОВЕРКА ЛОГИНА */
  int length = mx_strlen(login);
  int checker = 0;

  if (length < 6 || length >= 20) 
  {
    gtk_label_set_text(GTK_LABEL(Error_login),"Login must be from 6 to 20 characters and contain only Latin characters, numbers or underscore");  
    checker++;
  }
  else {
    for (int i = 0; i < length; i++) {
      if (!mx_isdigit(login[i]) && !mx_isalpha(login[i]) && login[i] != '_') {
        gtk_label_set_text(GTK_LABEL(Error_login),"Login must be from 6 to 20 characters and contain only Latin characters, numbers or underscore");  
        checker++;
        gtk_entry_set_text(GTK_ENTRY(entry_login),""); 
        break;
      }
      else {
        gtk_label_set_text(GTK_LABEL(Error_login), ""); 
    
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
    gtk_label_set_text(GTK_LABEL(Error_password),"The password must consist of eight or more characters of the Latin alphabet, contain uppercase and lowercase letters, numbers");  
    checker++;
    gtk_entry_set_text(GTK_ENTRY(entry_password),"");
    gtk_entry_set_text(GTK_ENTRY(entry_repeat_password),"");
  }
  else {
    gtk_label_set_text(GTK_LABEL(Error_password), "");
  }
  /* ПРОВЕРКА НА СХОДИМОСТЬ ПАРОЛЕЙ */
  if (mx_strcmp(password, repeat_password) != 0) {
    gtk_label_set_text(GTK_LABEL(Error_repeat_password),"Password mismatch");  
    checker++;
    gtk_entry_set_text(GTK_ENTRY(entry_repeat_password),"");
     gtk_entry_set_text(GTK_ENTRY(entry_password),"");
  }
  else {
    gtk_label_set_text(GTK_LABEL(Error_repeat_password), ""); 
  }
  /* ПРОВЕРКА НА НИКНЕЙМ*/
  length = mx_strlen(nickname);
  if (length < 1) {
    gtk_label_set_text(GTK_LABEL(Error_nickname),"Nickname must be one or more characters");  
    checker++;
    gtk_entry_set_text(GTK_ENTRY(entry_for_nickname),"");
  }
  else {
    gtk_label_set_text(GTK_LABEL(Error_nickname), ""); 
  }
  /* ПРОВЕРКА НА СЕКРЕТНОЕ СЛОВО*/
  length = mx_strlen(secret_word);
  if (length < 3) {
    gtk_label_set_text(GTK_LABEL(Error_secret_word),"Secret word must be from 3 characters and contain only Latin characters, numbers or underscore");  
    checker++;
    gtk_entry_set_text(GTK_ENTRY(entry_secret_word),"");
  }
  else
  {
    for (int i = 0; i < length; i++) {
      if(!mx_isdigit(secret_word[i]) && !mx_isalpha(secret_word[i]) && secret_word[i] != '_')
      {
        gtk_label_set_text(GTK_LABEL(Error_secret_word),"Secret word must be from 3 characters and contain only Latin characters, numbers or underscore");  
        checker++;
        gtk_entry_set_text(GTK_ENTRY(entry_secret_word),"");
      }
      else 
      {
        gtk_label_set_text(GTK_LABEL(Error_secret_word), ""); 
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

  //register_user(data_registration.login, data_registration.password, data_registration.nickname, data_registration.secret_word);
  gtk_entry_set_text(GTK_ENTRY(entry_login),""); 
  gtk_entry_set_text(GTK_ENTRY(entry_for_nickname),"");
  gtk_entry_set_text(GTK_ENTRY(entry_password),"");
  gtk_entry_set_text(GTK_ENTRY(entry_repeat_password),"");
  gtk_entry_set_text(GTK_ENTRY(entry_secret_word),"");
  return 0;
} 

void save_user (GtkWidget *button, GdkEvent *event, gpointer user_data) 
{
  GtkWidget *window;
  window = gtk_widget_get_parent(gtk_widget_get_parent(button));

  if (!signup_button_clicked()) {
    reopen_authorezation(button);
  }
}

void open_reg(GtkWidget *button, GdkEvent *event, gpointer user_data)
{
  GtkWidget *label_login, *label_for_nickname, *label_password, *label_repeat_password, *label_secret_word;
  GtkWidget *apply_btn;
  GtkWidget *window;
  window = gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(button)));

  GtkWidget *button_layout;
  button_layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  label_login = gtk_label_new("Please enter your login");
  entry_login = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_login), "Enter your login");
  

  label_for_nickname = gtk_label_new("Please enter your nickname");
  
  entry_for_nickname = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_for_nickname), "Enter your nickname");
 

  label_password = gtk_label_new("Please enter the password");
  
  entry_password = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_password), "Enter the password");
  gtk_entry_set_visibility(GTK_ENTRY(entry_password), FALSE);
  

  label_repeat_password = gtk_label_new("Please repeat the password");
  
  entry_repeat_password = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_repeat_password), "Repeat the password");
  gtk_entry_set_visibility(GTK_ENTRY(entry_repeat_password), FALSE);
  

  label_secret_word = gtk_label_new("Please enter your secret word");
  
  entry_secret_word = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_secret_word), "Secret word");
  
  apply_btn = gtk_button_new_with_label("OK");

  Error_login = gtk_label_new("");
  Error_password = gtk_label_new("");
  Error_repeat_password = gtk_label_new("");
  Error_nickname = gtk_label_new("");
  Error_secret_word = gtk_label_new("");

  g_signal_connect(apply_btn, "clicked", G_CALLBACK(save_user), window);
  
  gtk_container_add(GTK_CONTAINER(button_layout), GTK_WIDGET(apply_btn));

  GtkWidget *main_layout;
  main_layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(label_login));
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(entry_login));
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(Error_login));

  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(label_password));
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(entry_password));
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(Error_password));

  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(label_repeat_password));
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(entry_repeat_password));
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(Error_repeat_password));

  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(label_for_nickname));
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(entry_for_nickname));
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(Error_nickname));

  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(label_secret_word));
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(entry_secret_word));
  gtk_container_add(GTK_CONTAINER(main_layout), GTK_WIDGET(Error_secret_word));

  
  gtk_container_add(GTK_CONTAINER(main_layout), button_layout);

  gtk_container_add(GTK_CONTAINER(window), main_layout);

  gtk_widget_show_all(window);
}
