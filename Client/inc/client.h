#pragma once

#include <arpa/inet.h> //close
#include <arpa/inet.h>
#include <errno.h>
#include <gtk/gtk.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <sys/types.h>
#include <unistd.h>


#include "json-c/json.h"
#include "mysql/mysql.h"

#include <netdb.h>
#define SA struct sockaddr

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/md5.h>
#include <openssl/rand.h>

#include "libmx.h"
struct data_check_SW{
    char *login;
    char *secret_word;
} check_start;

struct data_change_password{
    char *login;
    char *password;
} check_second;

struct data_input_registration {
    char *login;
    char *password;
    char *nickname;
    char *secret_word;
} data_registration;

struct data_input_authorization{
    char *login;
    char *password;
} authorization_data;

struct widgets_check_SW{
    GtkWidget *entry_login;
    GtkWidget *entry_secret_word;
} widgets_SW_login;

/*---------------------------------------------------------------------------*/

typedef struct
{
	// GtkApplication *restrict app;
	// GtkWidget *restrict win;
	char *user_id;
	int socket_desc;
	char *user_login;
	char *picture_name;
	char *auth_theme_path;
	char *main_theme_path;
	char *theme;
	// bool isBottomed;
	char *language;
	int port;
	char *ipv4;
} appdata;

appdata data;

typedef struct
{
	char *ch_id;
	char *ms_id;
	char *u_id;
	char *u_name;
	char *ms_text;
	char *ms_datetime;
	char *ms_isedited;
	char *ms_isforwarded;
	char *ms_ismedia;
	char *ms_isreply;
	char *ms_isseen;
    char *ms_media;
} message_t;

typedef struct
{
	message_t **messages;
	int length;
} message_arr;

typedef struct contact_s
{
  char *c_id;
  char *c_name;
  char *c_avatar;
  char *c_lastSeen;
//   char *u_status; //online/offline
} contact_t;

typedef struct
{
  char *u_id;
  char *u_login;
  char *u_name;
  char *u_surname;
  char *u_avatar;
  char *u_lastSeen;
} user_t;

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

/*---------------------------------------------------------------------------*/
char *request_to_server(char *json_str);
char *register_user (char *login, char *password, char *nickname, char *secret_word); // "0" IF LOGIN TAKEN, "USER_ID" IF ADDED SUCESSFULLY
bool change_password (char *login, char *new_password, char *secret_word); // "0" IF LOGIN doesnt exist or secret_word incorrect, "USER_ID" IF updated SUCESSFULLy
char *autorize_user (char *login, char *password); // USER_ID if sucess, "0" IF something incorrect
bool add_message(char *ch_id, char *u_id, char *text);
bool delete_message(char *ms_id);
bool edit_message(char *ms_id);
bool reply_message(char *ms_id, char *ch_id_to_reply);
bool forward_message(char *ms_id, char *ch_id_to_reply);
bool make_message_seen(char *ms_id);
bool create_personal_chat(char *u_id, char *contact_id);
// RETURNS NULL IF NO CHATS
chat_t **get_chats(char *u_id);

//RETURNS NULL IF NO SUCH CHAT 
chatuser_t **get_chat_users(char *ch_id);

// RETURNS NULL IF someshit happens
user_t *get_user_info(char *u_id);

bool edit_user_name(char *u_id, char *new_name);
bool edit_chat_name(char *ch_id, char *new_name);
bool delete_chat(char *ch_id); // also clears chat
bool add_contact_by_id(char *contact_id, char *u_id);
bool add_contact_by_login(char *contact_login, char *u_id);
bool block_contact(char *contact_id, char *u_id);
bool unblock_contact(char *contact_id, char *u_id);


char *strjoins_arr(const char **str_arr);
void string_array_clear(char **arr, int size);
char *strjoin(char *a, char *b);


// last object in this massive is NULL
contact_t **get_all_contacts(char *function_number, char **data);
char *request_to_get_messages(char *request);

// The most newer message will be the last in this array
message_arr * get_50_messages(char *ch_id, char *last_msg_id);
char *create_group_chat(char *u_id, char *chat_name);
bool add_user_to_chat(char *ch_id, char *u_id);
void server_set_connection();
/*---------------------------------------------------------------------------*/

char *write_to_json(char* num_f,char **arr_new);
void data_to_str_authorization();
void data_to_str_change_password();
void data_to_str_check_SW();
void data_to_str_registration();

void open_authorezation(GtkWidget *button, char *event);
void open_reg(GtkWidget *button, GdkEvent *event, gpointer user_data);
void open_chat(GtkWidget *button);
void window_secret_word(GtkWidget *button, GdkEvent *event, gpointer user_data);
void window_change_password(GtkWidget *button);


void validation_authorization_data(GtkWidget *button, GdkEvent *event, gpointer user_data);
void window_secret_word (GtkWidget *button, GdkEvent *event, gpointer user_data);
//#define BACKIMAGE_PATH "./Resources/images/back.jpg"
