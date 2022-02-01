#include "uchat.h"

MYSQL *db_connection_open()
{
    MYSQL *connection = mysql_init(NULL);
    puts("DB connecting...");   
    if (connection == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(connection));
        exit(1);
    }
    //178.165.107.43   192.168.0.104
    if (mysql_real_connect(connection, "178.165.107.43", "root", "12345",
                           "socket", 3306, NULL, 0) == NULL)
    {
        connection_close_error(connection);
    }

    // if (mysql_query(connection, "SET NAMES utf8mb4;"))
    // {
    //     connection_close_error(con);
    // }
    puts("DB connected");
    return connection;
}

void db_connection_close(MYSQL *connection)
{
    mysql_close(connection);
}
