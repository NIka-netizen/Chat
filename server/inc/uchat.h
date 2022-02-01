#ifndef CHAT_H
#define CHAT_H


#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <locale.h>
#include <time.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <stdarg.h> 

#include <errno.h>
#include <fcntl.h>
// #include <sys/sendfile.h>
#include <sys/uio.h>
//ext libs headers
#include "json-c/json.h"
#include "mysql/mysql.h"

#include <sys/types.h>
#include <sys/stat.h>

typedef struct
{
  int function_number;
  char **data_array;
  int counter;
} data_from_json_t;

typedef struct contact_s
{
  char *c_id;
  char *u_name;
  char *u_avatar;
  char *u_lastSeen;
  char *u_status; //online/offline
} contact_t;

typedef struct
{
  char *u_id;
  char *u_login;
  char *u_name;
  char *u_surname;
  char *u_avatar;
  char *u_lastSeen;
  char *u_secret_word;
} user_t;

typedef struct message_s
{
  char *ch_id;
  char *ms_id;
  char *u_id;
  // char *u_name;
  char *ms_text;
  char *ms_datetime;
  char *ms_isedited;
  char *ms_isforwarded;
  char *ms_ismedia;
  char *ms_isreply;
  char *ms_isseen;
} message_t;

typedef struct chat_s
{
  char *ch_id;
  char *ch_name;
  char *ch_avatar;
} chat_t;

typedef struct chatuser_s
{
  char *ch_id;
  char *u_id;
  char *ch_isadmin;
} chatuser_t;

//utility
char *mx_strnew(const int);
char *itobase10(char *, int);
char *strjoin(char *, char *);
char *mx_strcat(char *restrict , const char *restrict );
char *strjoins_arr(const char **str_arr);
char *set_date(); // gets curdate
char *get_filename_extension(char *filename);

//parser
data_from_json_t parse_json_to_data(char *json_str);

//functions handler
char *handle_functions(MYSQL *connection, data_from_json_t data, int sock);

//validators
char *validate_password(MYSQL *connection, char *login, char *password); //log in
char *is_login_already_taken(MYSQL *connection, char *login); //check is login free


//formatting answer_strings
char *write_message_to_json(message_t message);
char *contact_to_json(contact_t contact);
char *write_user_info_to_json(user_t user);
char *chat_to_json(chat_t chat);
char *chatuser_to_json(chatuser_t chatuser);

//errors
void connection_close_error(MYSQL *connection);
void finish_with_error(MYSQL *con);

//connections
void *connection_handler(void *socket_descriptor);
MYSQL *db_connection_open();
void db_connection_close(MYSQL *connection);

//files reciever

//mysql_requests 

//chats
char *add_personal_chat(MYSQL *connection, char *my_id, char *contact_id);
char *edit_chat_name(MYSQL *connection, char *ch_id, char *new_name);
char *delete_chat(MYSQL *connection, char *ch_id); //also clears chat messages
char *get_chats(MYSQL *connection, char *u_id);
char *get_users_from_chat(MYSQL *connection, char *ch_id);
char *create_group_chat(MYSQL *connection, char *my_id, char *chat_name, char *avatar);
char *add_user_to_chat(MYSQL *connection, char *ch_id, char *u_id, char *ch_isadmin);
char *set_chat_avatar(MYSQL *connection, char *ch_id, char *avatar_path);

//user
char *get_my_id(MYSQL *connection, char *login);
char *add_user(MYSQL *connection, char *login, char *pass, char *name, char *surname, char *secret_word);
char *get_user_info(MYSQL *connection, char *u_id);
char *edit_user_name(MYSQL *connection, char *u_id , char *new_name);
char *edit_user_surname(MYSQL *connection, char *u_id , char *new_surname);
char *edit_password(MYSQL *connection, char *u_id, char *new_pass);
char *set_user_avatar(MYSQL *connection, char *u_id, char *avatar_path);

//contacts
char *add_contact_by_id(MYSQL *connection,char *contact_id, char *u_id);
char *add_contact_by_login(MYSQL *connection, char *login, char *u_id);
char *block_contact(MYSQL *connection, char *contact_id, char *u_id);
char *unblock_contact(MYSQL *connection, char *contact_id, char *u_id);
char *delete_contact(MYSQL *connection, char *contact_id, char *u_id);
char *get_contacts(MYSQL *connection, char *u_id);

//messages
char *add_message(MYSQL *connection, char *ch_id, char *u_id, char *text, char *is_media, char *isforwarded, char *isreply, char *isseen, char *isedited);
char *delete_message(MYSQL *connection, char *ms_id);
char *edit_message(MYSQL *connection, char *ms_id, char *new_text);
char *forward_message(MYSQL *connection, char *ms_id, char *forward_to_ch_id);
char *reply_message(MYSQL *connection, char *ms_id, char *reply_to_ch_id);
char *get_all_messages(MYSQL *connection, char *ch_id);
char *get_message_by_id(MYSQL *connection, char *ms_id);
char *get_messages_by_ids(MYSQL *connection, char **ids_mas);
char *make_message_seen(MYSQL *connection, char *ms_id);
char *set_message_file(MYSQL *connection, char *ms_id, char *file_path);




#endif