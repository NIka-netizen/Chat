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

void data_to_str_authorization();
void data_to_str_change_password();
void data_to_str_check_SW();
void data_to_str_registration();
void set_connection(char *answer);
void open_authorezation(GtkWidget *button);
void open_reg(GtkWidget *button, GdkEvent *event, gpointer user_data);
void open_chat(GtkWidget *button);
void window_secret_word(GtkWidget *button, GdkEvent *event, gpointer user_data);
void window_change_password(GtkWidget *button);


void validation_authorization_data(GtkWidget *button, GdkEvent *event, gpointer user_data);
void window_secret_word (GtkWidget *button, GdkEvent *event, gpointer user_data);
//#define BACKIMAGE_PATH "./Resources/images/back.jpg"
