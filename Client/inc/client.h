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
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <sys/types.h>
#include <unistd.h>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/md5.h>
#include <openssl/rand.h>

#include "libmx.h"

void open_chat(GtkWidget *window, GdkEvent *event, gpointer user_data);
void open_authorezation(GtkWidget *button, GdkEvent *event, gpointer user_data);
void open_reg(GtkWidget *button, GdkEvent *event, gpointer user_data);
void open_chat(GtkWidget *window, GdkEvent *event, gpointer user_data);
void window_secret_word(GtkWidget *button, GdkEvent *event, gpointer user_data);
void window_change_password(GtkWidget *button, GdkEvent *event, gpointer user_data);

//#define BACKIMAGE_PATH "./Resources/images/back.jpg"
