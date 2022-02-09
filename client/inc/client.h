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

#include <sys/stat.h>


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
    GtkWidget *main_box;

    GtkWidget *entry_login;
    GtkWidget *entry_secret_word;
    GtkWidget *label_error_login;
    GtkWidget *label_error_SW;

    GtkWidget *entry_password;
    GtkWidget *entry_repeat_password;
    GtkWidget *label_error_password;
    GtkWidget *label_error_repeat_password;
} widgets_forgot_password;

struct widgets_check_registration{
    GtkWidget *entry_login;
    GtkWidget *entry_password;
    GtkWidget *entry_repeat_password;
    GtkWidget *entry_nickname;
    GtkWidget *entry_secret_word;

    GtkWidget *label_error_login;
    GtkWidget *label_error_password;
    GtkWidget *label_error_repeat_password;
    GtkWidget *label_error_nickname;
    GtkWidget *label_error_secret_word;
} widgets_registration;

struct data_authorization{
    GtkWidget *login;
    GtkWidget *password;

    GtkWidget *Error_message;
} authorization_log_pass;


static struct data_params{
    int argc;
    char *argv[2];
} params;

typedef struct _ChatInList{ 
    GtkWidget *chat; 
    char *id_chat_in_db; 
    char *chat_name; 
    char *last_message_text; 
}       ChatInList;

static struct data_settings{
    GtkWidget *entry_login;
    GtkWidget *entry_nickname;
} data_set;


gboolean for_timer_chats;

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
  GtkWidget *message_btn;
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
  GtkWidget *contact;
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
  GtkWidget *chat;
} chat_t;

static gboolean for_closing_prev_chat = true;

typedef struct chatuser_s
{
  char *ch_id;
  char *u_id;
  char *ch_isadmin;
} chatuser_t;


char *request_to_server(char *json_str);
char *register_user (char *login, char *password, char *nickname, char *secret_word); // "0" IF LOGIN TAKEN, "USER_ID" IF ADDED SUCESSFULLY
bool change_password(char *login, char *new_password);
bool check_secret_word(char *login, char *secret_word);

char *autorize_user (char *login, char *password); // USER_ID if sucess, "0" IF something incorrect
char *add_message(char *ch_id, char *u_id, char *text); // returns ms_id if added successfully, 0 if no;
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
contact_t **get_all_contacts(char *u_id);
char *request_to_get_messages(char *request, int socket);

// The most newer message will be the last in this array
message_arr * get_50_messages(char *ch_id, char *last_msg_id);
message_arr *get_n_messages(char *ch_id, char *n);

char *create_group_chat(char *u_id, char *chat_name);
bool add_user_to_chat(char *ch_id, char *u_id);
void server_set_connection();
char *get_filename_extension(char *filename);
bool request_send_file(char *json_str, char *fullfilename);
bool recieve_file(char *fullfilename, char *info, int number);
bool set_user_avatar(char *u_id, char *fullfilename);
bool set_chat_avatar(char *ch_id, char *fullfilename);
bool set_message_file(char *ms_id, char *fullfilename);
/*---------------------------------------------------------------------------*/

void data_to_str_authorization();
void data_to_str_change_password();
void data_to_str_check_SW();
void data_to_str_registration();

void open_authorezation(GtkWidget *button, char *event);
void open_reg(GtkWidget *button, GdkEvent *event, gpointer user_data);
void open_chat(GtkWidget *button, char  *panel);
void window_secret_word(GtkWidget *button, GdkEvent *event, gpointer user_data);
void window_change_password(GtkWidget *button);
bool edit_user_data(char *u_id, char *name, char *login);


void validation_authorization_data(GtkWidget *button, GdkEvent *event, gpointer user_data);
void window_secret_word (GtkWidget *button, GdkEvent *event, gpointer user_data);
bool check_secret_word(char *login, char *secret_word);
void Css_include_auth(GtkWidget *authorization_layout, GtkWidget *image, GtkWidget *button_log, GtkWidget *button_reg, GtkWidget *forg_password,
                   GtkWidget *label_login, GtkWidget *label_password, GtkWidget *label_cookiechat, GtkWidget *label_authorization);
void Css_include_SW(GtkWidget *authorization_layout, GtkWidget *label_login, GtkWidget *label_secret_word, GtkWidget *label_recovery, GtkWidget *btn_apply);
void Css_include_reg(GtkWidget *label_login, GtkWidget *label_password, GtkWidget *label_repeat_password, GtkWidget *label_nickname, GtkWidget *label_secret_word, GtkWidget *label_registration, GtkWidget *apply_btn);
void Css_include_change_password(GtkWidget *label_password, GtkWidget *label_repeat_password, GtkWidget *create_new_pass, GtkWidget *apply_btn);
void css_include_window_chat(GtkWidget *bottom_panel2, GtkWidget *bottom_entry);
void css_include_window_left(GtkWidget *bottom_panel, GtkWidget *bottom_button1, GtkWidget *bottom_button2, GtkWidget *bottom_button3, GtkWidget *top_searching); 
void css_include_start_window_chat(GtkWidget *start_message, GtkWidget *chat_box);
void css_include_window_setting(GtkWidget *save_changes, GtkWidget *label_setting, GtkWidget *label_nickname, GtkWidget *entry_nickname, GtkWidget *label_login, GtkWidget *entry_login, GtkWidget *button_change_password, GtkWidget *button_change_avatar, GtkWidget *button_log_outs);
void css_button_contacts(GtkWidget *contact_button);
//#define BACKIMAGE_PATH "./Resources/images/back.jpg"
