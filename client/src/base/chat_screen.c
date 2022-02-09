#include "client.h"

int count_of_messages = 25;
guint source_id;
char *chat_id_for_mes = NULL;

GtkWidget *chats_or_contacts;
// GtkWidget *mes_box;
GtkWidget *chat_panel;

void chat_window(GtkWidget *button, chat_t *chat);
void window_password (GtkWidget *button, gpointer builder){
  window_secret_word(widgets_forgot_password.main_box, (GdkEvent *)"from_settings", builder);
}

void window_log_out(GtkWidget *button, gpointer builder){
  for_timer_chats = false;
  open_authorezation(widgets_forgot_password.main_box, "from_settings");
}

int rewrite_data() {
  char *login = (char *)gtk_entry_get_text(GTK_ENTRY(data_set.entry_login));
  char *nickname = (char *)gtk_entry_get_text(GTK_ENTRY(data_set.entry_nickname));  

  /* ПРОВЕРКА ЛОГИНА */
  int length = mx_strlen(login);
  int checker = 0;

  if (length < 6 || length >= 20) 
  {
    gtk_label_set_text(GTK_LABEL(widgets_registration.label_error_login),"Login must be from 6 to 20 characters and contain\nonly Latin characters, numbers or underscore");  
    checker++;
  }
  else {
    for (int i = 0; i < length; i++) {
      if (!mx_isdigit(login[i]) && !mx_isalpha(login[i]) && login[i] != '_') {
        gtk_label_set_text(GTK_LABEL(widgets_registration.label_error_login),"Login must be from 6 to 20 characters and contain\n only Latin characters, numbers or underscore");  
        checker++;
        gtk_entry_set_text(GTK_ENTRY(data_set.entry_login),""); 
        break;
      }
      else {
        gtk_label_set_text(GTK_LABEL(widgets_registration.label_error_login), ""); 
    
      }
    }
  } 
  /* ПРОВЕРКА НА НИКНЕЙМ*/
  length = mx_strlen(nickname);

  if (length < 1) {
    gtk_label_set_text(GTK_LABEL(widgets_registration.label_error_nickname),"Nickname must be one or more characters");  
    checker++;
    gtk_entry_set_text(GTK_ENTRY(data_set.entry_nickname),"");
  }
  else {
    gtk_label_set_text(GTK_LABEL(widgets_registration.label_error_nickname), ""); 
  }
  if (checker > 0) {
    return 1;
  }
  data_registration.login = mx_strnew(mx_strlen((char *)login));
  mx_strcpy(data_registration.login, (char *)login);
  data_registration.nickname = mx_strnew(mx_strlen((char *)nickname));
  mx_strcpy(data_registration.nickname, (char *)nickname);

  user_t data2;

  int id = edit_user_data(data.user_id, data_registration.nickname, data_registration.login);
  
  if (id == 0) {
    gtk_label_set_text(GTK_LABEL(widgets_registration.label_error_login), "Data wasn't change");  
    gtk_entry_set_text(GTK_ENTRY(data_set.entry_login),""); 
    gtk_entry_set_text(GTK_ENTRY(data_set.entry_nickname),""); 
  }
  else if (id == 1) {
    data2.u_login = mx_strdup(data_registration.login);
    data2.u_name = mx_strdup(data_registration.nickname);
  }
  return 0;
}

//ФУНКЦИЯ ОБНОВЛЕНИЯ СООБЩЕНИЙ В ЧАТЕ ПОКА ОН ОТКРЫТ У ПОЛЬЗОВАТЕЛЯ
gboolean update_messages(gpointer box)
{
  GList *iter;
  GList *messages_list = gtk_container_get_children(GTK_CONTAINER(box));
  for (iter = messages_list; iter != NULL; iter = g_list_next(iter))
    gtk_widget_destroy(GTK_WIDGET(iter->data));
  g_list_free(messages_list);
  if (for_closing_prev_chat)
  {
    message_arr *obj = get_n_messages(chat_id_for_mes, mx_itoa(count_of_messages));
    if (obj)
    {
      for (int i = obj->length - 1; i >= 0; i--)
      {
        obj->messages[i]->message_btn = gtk_button_new_with_label(obj->messages[i]->ms_text);
        gtk_container_add(GTK_CONTAINER(box), GTK_WIDGET(obj->messages[i]->message_btn));
      }
      gtk_widget_show_all(box);
    }

    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

//ФНКЦИЯ ОБНОВЛЕНИЯ СПИСКА ЧАТОВ В БОКОВОМ МЕНЮ ПОКА ПОЛЬЗОВАТЕЛЬ ОТКРЫЛ И НЕ ЗАКРЫЛ ВКЛАДКУ С ЧАТАМИ
gboolean update_chats(gpointer box)
{
  GList *iter;
  GList *chats_list = gtk_container_get_children(GTK_CONTAINER(box));
  for (iter = chats_list; iter != NULL; iter = g_list_next(iter))
    gtk_widget_destroy(GTK_WIDGET(iter->data));
  g_list_free(chats_list);
  if (for_timer_chats)
  {
    chat_t **chats = get_chats(data.user_id);
    for (int i = 0; chats[i]; i++)
    {
      puts(chats[i]->ch_id);
      chats[i]->chat = gtk_button_new();
      GtkWidget *box_for_chat = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
      // char *url_image = recieve_file(chats[i]->ch_avatar, chats[i]->ch_id, 2);
      // GtkWidget *avatar = gtk_image_new_from_file(url_image);

      GtkWidget *chat_name = gtk_label_new(chats[i]->ch_name);

      // gtk_container_add(GTK_CONTAINER(box_for_chat), GTK_WIDGET(avatar));
      gtk_container_add(GTK_CONTAINER(box_for_chat), GTK_WIDGET(chat_name));
      gtk_container_add(GTK_CONTAINER(chats[i]->chat), GTK_WIDGET(box_for_chat));

      g_signal_connect(GTK_WIDGET(chats[i]->chat), "clicked", G_CALLBACK(chat_window), chats[i]);
      gtk_container_add(GTK_CONTAINER(box), GTK_WIDGET(chats[i]->chat));
    }
    gtk_widget_show_all(box);
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

void setting_window (GtkWidget *button, gpointer right_panel) {
  if (source_id)
    g_source_remove(source_id);
  GtkWidget *window;
  window = gtk_widget_get_parent(right_panel);
  GList *iter;
  GList *content_list = gtk_container_get_children(GTK_CONTAINER(right_panel));
    for (iter = content_list; iter != NULL; iter = g_list_next(iter))
      gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(content_list);
  //gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(right_panel)));
  /*  ВОТ ТУТ ОКНО С ЧАТОМ */

  GError *error = NULL;
  GtkBuilder *builder1 = gtk_builder_new();
  

  if (gtk_builder_add_from_file(builder1, "client/src/settings_screen.glade", &error) == 0) 
  {
    g_clear_error(&error);
    exit(0);
  }

  GtkWidget *chat_box = GTK_WIDGET(gtk_builder_get_object(builder1, "settings_layout"));
  
  gtk_container_add(GTK_CONTAINER(right_panel), GTK_WIDGET(chat_box));

  GtkWidget *label_setting = GTK_WIDGET(gtk_builder_get_object(builder1, "label_setting"));
  GtkWidget *label_nickname = GTK_WIDGET(gtk_builder_get_object(builder1, "nickname"));
  data_set.entry_nickname = GTK_WIDGET(gtk_builder_get_object(builder1, "entry_nickname"));

  GtkWidget *label_login = GTK_WIDGET(gtk_builder_get_object(builder1, "label_login"));
  data_set.entry_login = GTK_WIDGET(gtk_builder_get_object(builder1, "entry_login"));

  GtkWidget *save_changes = GTK_WIDGET(gtk_builder_get_object(builder1, "save_changes"));

  widgets_registration.label_error_login = GTK_WIDGET(gtk_builder_get_object(builder1, "error_login"));
  widgets_registration.label_error_nickname = GTK_WIDGET(gtk_builder_get_object(builder1, "error_nickname"));

  user_t *data1 = get_user_info(data.user_id);
  gtk_entry_set_text(GTK_ENTRY(data_set.entry_login), data1->u_login);
  gtk_entry_set_text(GTK_ENTRY(data_set.entry_nickname), data1->u_name);

  GtkWidget *button_change_password = GTK_WIDGET(gtk_builder_get_object(builder1, "change_password"));
  GtkWidget *button_change_avatar = GTK_WIDGET(gtk_builder_get_object(builder1, "change_avatar"));
  GtkWidget *button_log_outs = GTK_WIDGET(gtk_builder_get_object(builder1, "log_out"));

  g_signal_connect(GTK_WIDGET(button_change_password), "clicked", G_CALLBACK(window_password), builder1);
  g_signal_connect(GTK_WIDGET(button_log_outs), "clicked", G_CALLBACK(window_log_out), builder1);

  g_signal_connect(GTK_WIDGET(save_changes), "clicked", G_CALLBACK(rewrite_data), NULL);

  g_object_unref(builder1);
  css_include_window_setting(save_changes, label_setting, label_nickname, data_set.entry_nickname, label_login, data_set.entry_login, button_change_password, button_change_avatar, button_log_outs);
}

ChatInList *ChatInList_new(char *id_chat_in_db, char *chat_name, char *last_message_text)
{
  ChatInList *chat = malloc(sizeof(ChatInList *));
  chat->id_chat_in_db = mx_strdup(id_chat_in_db);
  chat->chat_name = mx_strdup(chat_name);
  chat->last_message_text = mx_strdup(last_message_text);
  //chat->chat = malloc(sizeof(GtkWidget *));
  return chat;
}

ChatInList *create_one_chat_in_list(char *id_chat, char *url_avatar, char *chat_name_str, char *last_message_str)
{
  ChatInList *chats = ChatInList_new(id_chat, chat_name_str, last_message_str);
  chats->chat = gtk_button_new();

  //ОТРИСОВКА СОДЕРЖИМОГО ТУТ ДОЛЖНА БЫТЬ, АНАЛОГИЧНО НУЖНО БУДЕТ СДЕЛАТЬ И С СООБЩЕНИЯМИ
  GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  GtkWidget *avatar = gtk_image_new_from_file(url_avatar);

  gtk_container_add(GTK_CONTAINER(box1), GTK_WIDGET(avatar));

  GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *chat_name = gtk_label_new(chat_name_str);
  GtkWidget *last_message = gtk_label_new(last_message_str);

  gtk_container_add(GTK_CONTAINER(box2), GTK_WIDGET(chat_name));
  gtk_container_add(GTK_CONTAINER(box2), GTK_WIDGET(last_message));

  gtk_container_add(GTK_CONTAINER(box1), box2);

  gtk_container_add(GTK_CONTAINER(chats->chat), GTK_WIDGET(box1));
  return chats;
}

void send_message(GtkWidget *button, gpointer entry)
{
  char *text_mes = mx_strdup(gtk_entry_get_text(GTK_ENTRY(entry)));
  if (text_mes)
  {
    add_message(chat_id_for_mes, data.user_id, text_mes);
    gtk_entry_set_text(entry, "");
    count_of_messages++;
  }
}

void chats_print_in_list()
{
  GList *iter;
  GList *messages_list = gtk_container_get_children(GTK_CONTAINER(chats_or_contacts));
  for (iter = messages_list; iter != NULL; iter = g_list_next(iter))
    gtk_widget_destroy(GTK_WIDGET(iter->data));
  g_list_free(messages_list);
  chat_t **chats = get_chats(data.user_id);
  for (int i = 0; chats[i]; i++)
  {
    chats[i]->chat = gtk_button_new();
    GtkWidget *box_for_chat = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    // char *url_image = recieve_file(chats[i]->ch_avatar, chats[i]->ch_id, 2);
    // GtkWidget *avatar = gtk_image_new_from_file(url_image);

    GtkWidget *chat_name = gtk_label_new(chats[i]->ch_name);

    // gtk_container_add(GTK_CONTAINER(box_for_chat), GTK_WIDGET(avatar));
    gtk_container_add(GTK_CONTAINER(box_for_chat), GTK_WIDGET(chat_name));
    gtk_container_add(GTK_CONTAINER(chats[i]->chat), GTK_WIDGET(box_for_chat));

    g_signal_connect(GTK_WIDGET(chats[i]->chat), "clicked", G_CALLBACK(chat_window), chats[i]);
    gtk_container_add(GTK_CONTAINER(chats_or_contacts), GTK_WIDGET(chats[i]->chat));
  }
  gtk_widget_show_all(chats_or_contacts);

  for_timer_chats = true;
  g_timeout_add(2000, update_chats, chats_or_contacts);
}

void contatcs_print_in_list()
{
  GList *iter;
  GList *contacts_list = gtk_container_get_children(GTK_CONTAINER(chats_or_contacts));
  for (iter = contacts_list; iter != NULL; iter = g_list_next(iter))
    gtk_widget_destroy(GTK_WIDGET(iter->data));
  g_list_free(contacts_list);
  for_timer_chats = false;
  contact_t **contacts = get_all_contacts(data.user_id);
  if (contacts)
  {
    for (int i = 0; contacts[i]; i++)
    {
      contacts[i]->contact = gtk_button_new_with_label(contacts[i]->c_name);
      g_signal_connect(GTK_WIDGET(contacts[i]->contact), "clicked", G_CALLBACK(chat_window), contacts[i]);
      gtk_container_add(GTK_CONTAINER(chats_or_contacts), GTK_WIDGET(contacts[i]->contact));
    }
    gtk_widget_show_all(chats_or_contacts);
  }
}

void print_in_sidebar_list(GtkWidget *button, char *type)
{
  puts(type);
  if (mx_strcmp(type, "chats") == 0)
  {
    chats_print_in_list();
  }
  else if (mx_strcmp(type, "contacts") == 0)
  {
    contatcs_print_in_list();
  }
}

void left_window(GtkWidget *left_panel, GtkWidget *right_panel, char *type_of_content)
{
  GError *error = NULL;
  GtkBuilder *builder = gtk_builder_new();

  if (gtk_builder_add_from_file(builder, "client/src/chats_or_contacts.glade", &error) == 0)
  {
    g_clear_error(&error);
    exit(0);
  }

  GtkWidget *chats_or_contacts_box = GTK_WIDGET(gtk_builder_get_object(builder, "chat_or_contact_box"));
  chats_or_contacts = GTK_WIDGET(gtk_builder_get_object(builder, "chats_or_contacts_list_box"));
  gtk_container_add(GTK_CONTAINER(left_panel), GTK_WIDGET(chats_or_contacts_box));

  /*screen chats and contacts*/
  GtkWidget *bottom_panel = GTK_WIDGET(gtk_builder_get_object(builder, "bottom_panel"));
  GtkWidget *bottom_button1 = GTK_WIDGET(gtk_builder_get_object(builder, "contacts_btn"));
  GtkWidget *bottom_button2 = GTK_WIDGET(gtk_builder_get_object(builder, "chats_btn"));
  GtkWidget *bottom_button3 = GTK_WIDGET(gtk_builder_get_object(builder, "settings_btn"));

  g_signal_connect(GTK_WIDGET(bottom_button3), "clicked", G_CALLBACK(setting_window), right_panel);
  g_signal_connect(GTK_WIDGET(bottom_button2), "clicked", G_CALLBACK(print_in_sidebar_list), "chats");
  g_signal_connect(GTK_WIDGET(bottom_button1), "clicked", G_CALLBACK(print_in_sidebar_list), "contacts");

  GtkWidget *top_searching = GTK_WIDGET(gtk_builder_get_object(builder, "search_in_chat_or_contacts"));

  g_object_unref(builder);
  css_include_window_left(bottom_panel, bottom_button1, bottom_button2, bottom_button3, top_searching);
}

void chat_window(GtkWidget *button, chat_t *chat)
{
  GList *iter;
  GList *content_list = gtk_container_get_children(GTK_CONTAINER(chat_panel));
  for (iter = content_list; iter != NULL; iter = g_list_next(iter))
    gtk_widget_destroy(GTK_WIDGET(iter->data));
  g_list_free(content_list);
  GError *error = NULL;
  GtkBuilder *builder1 = gtk_builder_new();

  if (gtk_builder_add_from_file(builder1, "client/src/chat_screen.glade", &error) == 0)
  {
    g_clear_error(&error);
    exit(0);
  }

  /*screen chat*/
  GtkWidget *bottom_panel2 = GTK_WIDGET(gtk_builder_get_object(builder1, "bottom_panel"));
  GtkWidget *bottom_entry = GTK_WIDGET(gtk_builder_get_object(builder1, "message_entry"));
  GtkWidget *send_mes_btn = GTK_WIDGET(gtk_builder_get_object(builder1, "send_message_btn"));

  g_signal_connect(GTK_WIDGET(send_mes_btn), "clicked", G_CALLBACK(send_message), bottom_entry);
  GtkWidget *mes_box = GTK_WIDGET(gtk_builder_get_object(builder1, "mes_box"));

  //printf("\n\n\n\n%d\n\n\n\n", value);

  /*///////////////////////////////////////////////////////////////////////////////////*/

  GtkWidget *chat_box = GTK_WIDGET(gtk_builder_get_object(builder1, "chat_layout"));
  gtk_container_add(GTK_CONTAINER(chat_panel), GTK_WIDGET(chat_box));

  //---------------------------------------------
  //puts(chat->ch_id);
  message_arr *obj = get_n_messages(chat->ch_id, mx_itoa(count_of_messages));
  if (obj)
  {
    for (int i = obj->length - 1; i >= 0; i--)
    {
      obj->messages[i]->message_btn = gtk_button_new_with_label(obj->messages[i]->ms_text);
      gtk_container_add(GTK_CONTAINER(mes_box), GTK_WIDGET(obj->messages[i]->message_btn));
      if (i == obj->length - 1)
        gtk_widget_grab_focus(GTK_WIDGET(obj->messages[i]->message_btn));
    }

    GtkScrolledWindow *scrolledwin = GTK_SCROLLED_WINDOW(gtk_builder_get_object(builder1, "scrolled_win_chat"));
    GtkAdjustment *adj = GTK_ADJUSTMENT(gtk_builder_get_object(builder1, "adjustment2"));
    gint upper = gtk_adjustment_get_upper(adj);
    gint size_page = gtk_adjustment_get_page_size(adj);
    gtk_adjustment_set_value(adj, upper - size_page);
    gint value = gtk_adjustment_get_value(adj);
    printf("\n\n\n\n%d\n\n\n\n", value);
    gtk_widget_show_all(mes_box);
  }

  //----------------------------------------------

  if (source_id)
    g_source_remove(source_id);
  chat_id_for_mes = mx_strdup(chat->ch_id);
  source_id = g_timeout_add(2000, update_messages, mes_box);

  g_object_unref(builder1);
  css_include_window_chat(bottom_panel2, bottom_entry);
}

void start_chat_window(GtkWidget *chat_panel)
{
  GError *error = NULL;
  GtkBuilder *builder1 = gtk_builder_new();

  if (gtk_builder_add_from_file(builder1, "client/src/start_chat_screen.glade", &error) == 0)
  {
    g_clear_error(&error);
    exit(0);
  }

  GtkWidget *start_message = GTK_WIDGET(gtk_builder_get_object(builder1, "start_message"));

  GtkWidget *chat_box = GTK_WIDGET(gtk_builder_get_object(builder1, "start_chat_layout"));
  gtk_container_add(GTK_CONTAINER(chat_panel), GTK_WIDGET(chat_box));
  g_object_unref(builder1);
  css_include_start_window_chat(start_message, chat_box);
}

void open_chat(GtkWidget *button, char *panel)
{
  GtkWidget *window;
  window = gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  /*  ВОТ ТУТ ОКНО С ЧАТОМ */

  widgets_forgot_password.main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add(GTK_CONTAINER(window), widgets_forgot_password.main_box);

  GtkWidget *left_panel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add(GTK_CONTAINER(widgets_forgot_password.main_box), left_panel);
  chat_panel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add(GTK_CONTAINER(widgets_forgot_password.main_box), chat_panel);

  if (mx_strcmp(panel, "chats") == 0)
  {
    start_chat_window(chat_panel);
    left_window(left_panel, chat_panel, "chats");
  }

  gtk_widget_show_all(window);
}
