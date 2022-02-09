#include "uchat.h"

char *add_personal_chat(MYSQL *connection, char *my_id, char *contact_id)
{
    char *answer = NULL;
    char *bdrequest = NULL;
    if(strcmp(my_id,contact_id) == 0)
    {
        const char *strings_to_request[] = {"insert into chat (ch_name,ch_avatar) values (\"Saved messages\",\"no_avatar\");", NULL};
        bdrequest = strjoins_arr(strings_to_request);
    }else 
    {
        const char *strings_to_request[] = {"insert into chat (ch_name,ch_avatar) values ((select u_name from user where u_id = ", contact_id, "),\"no_avatar\");", NULL};
        bdrequest = strjoins_arr(strings_to_request);
    }
    MYSQL_RES *result;
    MYSQL_ROW row;
    int num_fields;
    puts(bdrequest); //Вывод запроса в консоль
    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }

    char request_for_ch_id[] = "select max(ch_id) from chat limit 1;";
    puts(request_for_ch_id); //Вывод запроса в консоль

    if (mysql_query(connection, request_for_ch_id))
    {
        finish_with_error(connection);
    }

    result = mysql_store_result(connection);

    if (result == NULL)
    {
        finish_with_error(connection);
    }

    num_fields = mysql_num_fields(result);

    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            answer = row[i];
        }
    }
    char *ch_id = strdup(answer);
    puts(ch_id);
    // printf("%d",uid);
    mysql_free_result(result);

    const char *strings_to_request1[] = {"insert into chatusers (ch_id,u_id,ch_isadmin) values (", ch_id, ",", my_id, ",1);", NULL};
    bdrequest = strjoins_arr(strings_to_request1);
    puts(bdrequest); //Вывод запроса в консоль
    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    if (strcmp(my_id, contact_id) != 0)
    {
        const char *strings_to_request2[] = {"insert into chatusers (ch_id,u_id,ch_isadmin) values (", ch_id, ",", contact_id, ",1);", NULL};
        bdrequest = strjoins_arr(strings_to_request2);
        if (mysql_query(connection, bdrequest))
        {
            finish_with_error(connection);
        }
    }

    return "1";
}

char *create_group_chat(MYSQL *connection, char *my_id, char *chat_name, char *avatar)
{
    const char *strings_to_request[] = {"insert into chat (ch_name,ch_avatar) values (\"",chat_name,"\",\"",avatar,"\");", NULL};
    char *bdrequest = strjoins_arr(strings_to_request);
    puts(bdrequest); //Вывод запроса в консоль
    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    const char *strings_to_request1[] = {"SELECT max(ch_id) FROM chat limit 1;", NULL};
    bdrequest = strjoins_arr(strings_to_request1);
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
    MYSQL_ROW row = mysql_fetch_row(result);
    puts(row[0]);
    char *ch_id = strdup(row[0]);
    add_user_to_chat(connection, ch_id, my_id, "1");
    return ch_id;
}

char *edit_chat_name(MYSQL *connection, char *ch_id, char *new_name)
{
    const char *request_parts[] = {"UPDATE chat SET ch_name = \"", new_name, "\" WHERE ch_id = \"", ch_id, "\";", NULL};
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

char *delete_chat(MYSQL *connection, char *ch_id)
{
    const char *request_parts[] = {"delete from message where ch_id = ", ch_id, ";", NULL};
    char *bdrequest = strjoins_arr(request_parts);
    puts(bdrequest); //Вывод запроса в консоль
    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }

    free(bdrequest);
    const char *request_parts1[] = {"delete from chatusers where ch_id=", ch_id, ";", NULL};
    bdrequest = strjoins_arr(request_parts1);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }

    free(bdrequest); 
    const char *request_parts2[] = {"delete from chat where ch_id=", ch_id, ";", NULL};
    bdrequest = strjoins_arr(request_parts2);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    free(bdrequest); 
    return strdup("1");;
}

char *get_chats(MYSQL *connection, char *u_id)
{
    const char *request_parts[] = {"SELECT c.ch_id,c.ch_name,c.ch_avatar FROM chat c JOIN chatusers cu ON c.ch_id = cu.ch_id WHERE cu.u_id = \"", u_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);
    puts(bdrequest);
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
    int num_rows = mysql_num_rows(result);
    char **answer = NULL;
    if (num_rows > 0)
    {
        answer = (char **)malloc(sizeof(char *) * num_rows);
        int i = 0;
        
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)))
        {
            chat_t chat;
            chat.ch_id = strdup(row[0]);
            chat.ch_name = strdup(row[1]);
            chat.ch_avatar = strdup(row[2]);
            answer[i] = strdup(chat_to_json(chat));
            i++;
        }
        mysql_free_result(result);
        char *main_string = strdup("{\"chats\": [");
        for (i = 0; i < num_rows; i++)
        {
            main_string = strjoin(main_string, answer[i]);
            // strjoin(main_string,contacts[i]);
            if (i != num_rows - 1)
                main_string = strjoin(main_string, ",");
            // strjoin(main_string,",");
        }
        main_string = strjoin(main_string, "]}");
        // strjoin(main_string,"]}");
        puts(main_string);
        return main_string;
    }
    else
    {
        puts("This user have no chats");
        return strdup("0");
    }
}

char *get_users_from_chat(MYSQL *connection, char *ch_id)
{
    const char *request_parts[] = {"SELECT * FROM chatusers WHERE ch_id = \"", ch_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);
    puts(bdrequest);
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
    int num_rows = mysql_num_rows(result);
        char **answer = NULL;
    if (num_rows > 0)
    {
        answer = (char **)malloc(sizeof(char *) * num_rows);
        int i = 0;
        
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)))
        {
            chatuser_t chatuser;
            chatuser.ch_id = strdup(row[0]);
            chatuser.u_id = strdup(row[1]);
            chatuser.ch_isadmin = strdup(row[2]);
            answer[i] = strdup(chatuser_to_json(chatuser));
            i++;
        }
        mysql_free_result(result);
        char *main_string = strdup("{\"chatusers\": [");
        for (i = 0; i < num_rows; i++)
        {
            main_string = strjoin(main_string, answer[i]);
            // strjoin(main_string,contacts[i]);
            if (i != num_rows - 1)
                main_string = strjoin(main_string, ",");
            // strjoin(main_string,",");
        }
        main_string = strjoin(main_string, "]}");
        // strjoin(main_string,"]}");
        puts(main_string);
        return main_string;
    }
    else
    {
        puts("This chat have no users ?");
        return strdup("0");
    }
}

char *add_user_to_chat(MYSQL *connection, char *ch_id, char *u_id, char *ch_isadmin)
{
    const char *strings_to_request[] = {"insert into chatusers (ch_id,u_id,ch_isadmin) values (\"",ch_id,"\",\"",u_id,"\",\"",ch_isadmin,"\");", NULL};
    char *bdrequest = strjoins_arr(strings_to_request);
    puts(bdrequest); //Вывод запроса в консоль
    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    return strdup("1");
}
