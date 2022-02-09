#include "uchat.h"
char *get_my_id(MYSQL *connection, char *login)
{
    const char *request_parts[] = {"SELECT count(u_id) from user where u_login = \"", login, "\" limit 1;", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }

    free(bdrequest); //IR

    MYSQL_RES *result = mysql_store_result(connection);

    if (result == NULL)
    {
        finish_with_error(connection);
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    if (strcmp(row[0], "1") == 0) // if no such user
    {
        mysql_free_result(result);
        const char *request_parts2[] = {"SELECT u_id from user where u_login = \"", login, "\" limit 1;", NULL};
        bdrequest = strjoins_arr(request_parts2);
        if (mysql_query(connection, bdrequest))
        {
            finish_with_error(connection);
        }
        result = mysql_store_result(connection);
        if (result == NULL)
        {
            finish_with_error(connection);
        }
        row = mysql_fetch_row(result);
        char *my_id = strdup(row[0]);
        puts(my_id);
        return my_id;
    }
    return "0";
    
}
