#include "uchat.h"

char *add_user(MYSQL *connection, char *login, char *pass, char *name, char *surname, char *secret_word)
{
    // char *login = data.data_array[0];
    // char *pass = data.data_array[1]; // NEEDS ENCRYPTION
    // char *name = data.data_array[2];
    // char *surname = data.data_array[3];
    char *avatar = "avatar_link"; // data.data_array[3];
    char *datetime = set_date();
    char *database_request;
    char *answer = NULL;

    const char *strings_to_request[] = {"SELECT count(*) from user where u_login=\"", login, "\";", NULL};
    char *bdrequest = strjoins_arr(strings_to_request);
    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL)
    {
        finish_with_error(connection);
    }
    free(bdrequest);
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        answer = strdup(row[0]);
    }
    puts(answer);
    if (strcmp(answer, "0") == 0)
    {
        answer = NULL;
        mysql_free_result(result);
        const char *strings_to_request1[] = {"INSERT INTO user (u_login, u_name, u_surname, u_avatar, u_lastseen) VALUES (\"", login, "\",\"", name, "\",\"", surname, "\",\"", avatar, "\",\"", datetime, "\");", NULL};
        bdrequest = strjoins_arr(strings_to_request1);
        puts(bdrequest); //Вывод запроса в консоль

        if (mysql_query(connection, bdrequest))
        {
            finish_with_error(connection);
        }
        // if(mysql_field_count(connection) >0){
        // result = mysql_store_result(connection);
        // if (result == NULL)
        // {
        //     finish_with_error(connection);
        // }
        // free(bdrequest);
        // num_fields = mysql_num_fields(result);
        // while ((row = mysql_fetch_row(result)))
        // {
        //     answer = strdup(row[0]);
        // }
        // // puts(answer);
        // answer = NULL;
        // mysql_free_result(result);
        // }
        char *request_for_u_id = "select max(u_id) from user limit 1;";
        puts(request_for_u_id); //Вывод запроса в консоль
        if (mysql_query(connection, request_for_u_id))
        {
            finish_with_error(connection);
        }
        result = mysql_store_result(connection);
        if (result == NULL)
        {
            finish_with_error(connection);
        }
        // free(request_for_u_id);
        // num_fields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result)))
        {
            answer = strdup(row[0]);
        }
        puts(answer);
        char *uid = strdup(answer);
        // printf("%d",uid);
        mysql_free_result(result);
        free(bdrequest);
        const char *strings_to_request2[] = {"INSERT INTO credentials (u_id, cr_password, cr_secret_word) VALUES (", uid, ",\"", pass, "\"",",\"", secret_word, "\");", NULL};
        bdrequest = strjoins_arr(strings_to_request2);
        puts(bdrequest); //Вывод запроса в консоль
        if (mysql_query(connection, bdrequest))
        {
            finish_with_error(connection);
        }
        add_personal_chat(connection, uid, uid);
        // answer = strdup(uid);
    }
    else
    {
        puts("User with such login already exist");
        answer = strdup("0");
    }

    return answer;
}

char *get_user_info(MYSQL *connection, char *u_id)
{
    const char *request_parts[] = {"select * from user where u_id = ", u_id, " limit 1;", NULL};
    char *bdrequest = strjoins_arr(request_parts);
    puts(bdrequest); //Вывод запроса в консоль
    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    free(bdrequest);
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL)
    {
        finish_with_error(connection);
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    user_t user;
    user.u_id = strdup(row[0]);
    user.u_login = strdup(row[1]);
    user.u_name = strdup(row[2]);
    user.u_surname = strdup(row[3]);
    user.u_avatar = strdup(row[4]);
    user.u_lastSeen = strdup(row[5]);
    user.u_secret_word = strdup(row[6]);
    char *user_str = write_user_info_to_json(user);
    char *main_string = strdup("{\"user\": [");
    main_string = strjoin(main_string, user_str);
    main_string = strjoin(main_string, "]}");
    mysql_free_result(result);
    puts(main_string);
    return main_string;
}

char *edit_user_name(MYSQL *connection, char *u_id, char *new_name)
{
    const char *request_parts[] = {"UPDATE user SET u_name = \"", new_name, "\" WHERE u_id = \"", u_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    free(bdrequest);
    char *answer = strdup("1");
    return answer;
}

char *edit_user_surname(MYSQL *connection, char *u_id, char *new_surname)
{
    const char *request_parts[] = {"UPDATE user SET u_surname = \"", new_surname, "\" WHERE u_id = \"", u_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    free(bdrequest);
    char *answer = strdup("OK");
    return answer;
}

char *edit_password(MYSQL *connection, char *u_id, char *new_pass)
{
    const char *request_parts2[] = {"UPDATE credentials SET cr_password = \"", new_pass, "\" WHERE u_id = \"", u_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts2);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    free(bdrequest);
    return strdup("1"); // if ok
}
