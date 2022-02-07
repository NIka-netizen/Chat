#include "client.h"

ChatInList *ChatInList_new(char *id_chat_in_db, char *chat_name, char *last_message_text)
{
  ChatInList *chat = malloc(sizeof(ChatInList *));
  chat->id_chat_in_db = mx_strdup(id_chat_in_db);
  chat->chat_name = mx_strdup(chat_name);
  chat->last_message_text = mx_strdup(last_message_text);
  //chat->chat = malloc(sizeof(GtkWidget *));
  return chat;
}

ChatInList *create_one_chat_in_list(char *id_chat, char *url_avatar, char *chat_name_str, char *last_message_str){
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



void open_chat(GtkWidget *button)
{
  GtkWidget *window;
  window = gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(button)));
  /*  ВОТ ТУТ ОКНО С ЧАТОМ */

  GError *error = NULL;
  GtkBuilder *builder1 = gtk_builder_new();
  GtkBuilder *builder2 = gtk_builder_new();

  if (gtk_builder_add_from_file(builder1, "client/src/chats_or_contacts.glade", &error) == 0) 
      //gtk_builder_add_from_file(builder2, "client/src/authorization_screen.glade", &error) == 0 )
  {
    //g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    exit(0);
  }

  GtkWidget *main_screen = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  GtkWidget *chats_or_contacts = GTK_WIDGET(gtk_builder_get_object(builder1, "chat_or_contact_box"));
  GtkWidget *chats_box = GTK_WIDGET(gtk_builder_get_object(builder1, "chats_or_contacts_list_box"));

  //GtkWidget *start_chat_screen = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);


  //GtkWidget *label = GTK_WIDGET(gtk_builder_get_object(builder2, "authorization_layout"));//gtk_label_new("Select a chat to start messaging");
  //gtk_container_add(GTK_CONTAINER(start_chat_screen), GTK_WIDGET(label));

  ChatInList *chat[50];
  for(int i = 0; i<50; i++){
    chat[i] = create_one_chat_in_list(mx_itoa(i), "client/src/settings_icon.png", "Bababui", "hello");
    gtk_container_add(GTK_CONTAINER(chats_box), GTK_WIDGET(chat[i]->chat));
  }

  // gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(chat_layout));
  // gtk_container_add(GTK_CONTAINER(chat_box), GTK_WIDGET(start_chat_screen));
  //gtk_grid_attach(GTK_GRID(chat_layout), chats_and_contacts, 0, 0, 300, 700);
  //gtk_grid_attach(GTK_GRID(chat_layout), start_chat_screen, 0, 1, 1, 1);
  
    gtk_container_add(GTK_CONTAINER(main_screen), GTK_WIDGET(chats_or_contacts));
    //gtk_container_add(GTK_CONTAINER(main_screen), GTK_WIDGET(label));
    
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(main_screen));



  gtk_widget_show_all(window);

  g_object_unref(builder1);
  g_object_unref(builder2);
}
