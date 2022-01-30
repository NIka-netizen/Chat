#include "client.h"

void open_reg(GtkWidget *window, GdkEvent *event, gpointer user_data)
{
  gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(window)));
  /*  ВОТ ТУТ ОКНО С РЕГИСТРАЦИЕЙ */
}
