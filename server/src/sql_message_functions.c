#include "uchat.h"

char *add_message(MYSQL *connection, char *ch_id, char *u_id, char *text, char *is_media, char *isforwarded, char *isreply, char *isseen, char *isedited)
{
    char *answer = NULL;
    char *datetime = set_date();
    const char *strings_to_request[] = {"insert into message (ch_id, u_id, ms_text, ms_datetime, ms_ismedia, ms_isforwarded, ms_isreply, ms_isseen, ms_isedited) values (", ch_id, ",", u_id, ",\"", text, "\",\"", datetime, "\",", is_media, ",", isforwarded, ",", isreply, ",", isseen, ",", isedited, ");", NULL};
    char *bdrequest = strjoins_arr(strings_to_request);
    MYSQL_RES *result;
    MYSQL_ROW row;
    int num_fields;
    puts(bdrequest); //Вывод запроса в консоль
    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    const char *strings_to_request1[] = {"SELECT max(ms_id) from message limit 1;", NULL};
    bdrequest = strjoins_arr(strings_to_request1);
    puts(bdrequest); //Вывод запроса в консоль
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
    answer = strdup(row[0]);
    return answer; //ms_id;
}

char *forward_message(MYSQL *connection, char *ms_id, char *forward_to_ch_id)
{
    const char *request_parts[] = {"SELECT u_id, ms_text, ms_ismedia from message where ms_id = ", ms_id, ";", NULL};
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
    char *datetime = set_date();
    char *u_id = strdup(row[0]);
    char *ms_text = strdup(row[1]);
    char *ms_ismedia = strdup(row[2]);
    mysql_free_result(result);
    const char *request_parts1[] = {"INSERT INTO message (ch_id, u_id, ms_text, ms_datetime, ms_ismedia, ms_isforwarded, ms_isreply, ms_isseen, ms_isedited) VALUES (", forward_to_ch_id, ",", u_id, ",\"", ms_text, "\",\"", datetime, "\",\"", ms_ismedia, "\",", "\"1\",", "\"0\",", "\"0\",", "\"0\"", ");", NULL};
    bdrequest = strjoins_arr(request_parts1);
    puts(bdrequest); //Вывод запроса в консоль
    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    free(bdrequest);
    char *answer = strdup("OK");
    return answer;
}

char *reply_message(MYSQL *connection, char *ms_id, char *reply_to_ch_id)
{
    const char *request_parts[] = {"SELECT u_id, ms_text, ms_ismedia from message where ms_id = ", ms_id, ";", NULL};
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
    char *datetime = set_date();
    char *u_id = strdup(row[0]);
    char *ms_text = strdup(row[1]);
    char *ms_ismedia = strdup(row[2]);
    mysql_free_result(result);
    const char *request_parts1[] = {"INSERT INTO message (ch_id, u_id, ms_text, ms_datetime, ms_ismedia, ms_isforwarded, ms_isreply, ms_isseen, ms_isedited) VALUES (", reply_to_ch_id, ",", u_id, ",\"", ms_text, "\",\"", datetime, "\",\"", ms_ismedia, "\",", "\"0\",", "\"1\",", "\"0\",", "\"0\"", ");", NULL};
    bdrequest = strjoins_arr(request_parts1);
    puts(bdrequest); //Вывод запроса в консоль
    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    free(bdrequest);
    return "1";
}

char *get_all_messages(MYSQL *connection, char *ch_id, char *last_msg_id, int socket)
{
    if (strcmp(last_msg_id, "0") == 0)
    {
        const char *request_parts2[] = {"select max(ms_id) from message where ch_id = ", ch_id, ";", NULL};
        char *bdrequest = strjoins_arr(request_parts2);
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
        int num_rows = mysql_num_rows(result);
        if (num_rows > 0)
        {
            MYSQL_ROW row1 = mysql_fetch_row(result);
            last_msg_id = strdup(row1[0]);
        }
        else
        {
            puts("Empty chat");
            return strdup("0");
        }
        mysql_free_result(result);
    }

    // if(strcmp(max_ms_id,""))
    const char *request_parts[] = {"select * from message where ch_id = ", ch_id, " and ms_id >= ", last_msg_id, " ORDER BY ms_id LIMIT 50;", NULL};
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
    int num_rows = mysql_num_rows(result);
    if (num_rows > 0)
    {
        char **messages = (char **)malloc(sizeof(char *) * num_rows);
        int i = 0;
        while (i < num_rows)
        {
            message_t message;
            MYSQL_ROW row;
            row = mysql_fetch_row(result);
            message.ms_id = strdup(row[0]);
            message.ch_id = strdup(row[1]);
            message.u_id = strdup(row[2]);
            message.ms_text = strdup(row[3]);
            message.ms_datetime = strdup(row[4]);
            message.ms_ismedia = strdup(row[5]);
            message.ms_isforwarded = strdup(row[6]);
            message.ms_isreply = strdup(row[7]);
            message.ms_isseen = strdup(row[8]);
            message.ms_isedited = strdup(row[9]);
            message.ms_media = strdup(row[10]);
            messages[i] = write_message_to_json(message);
            // puts(messages[i]);
            i++;
        }
        char *main_string = strdup("{\"messages\": [");
        for (int i = 0; i < num_rows; i++)
        {
            main_string = strjoin(main_string, messages[i]);
            // strjoin(main_string,contacts[i]);
            if (i != num_rows - 1)
                main_string = strjoin(main_string, " , ");
            // strjoin(main_string,",");
        }
        main_string = strjoin(main_string, "]}");
        // strjoin(main_string,"]}");
        // int size = sizeof(main_string);
        // printf("%d",size);
        // puts(main_string);
        printf("\n length = %lu, size = %lu\n", strlen(main_string), sizeof(main_string));
        // return main_string;
        main_string[strlen(main_string)] = '\0';
        size_t size = strlen(main_string);
        mysql_free_result(result);
        puts(main_string);
        mkdir("./messages_tmp", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        char *fullpath = strdup("./messages_tmp/");
        fullpath = strjoin(fullpath, ch_id);
        FILE *file = fopen(fullpath, "w");
        // fwrite(main_string, sizeof(char), size, file);
        fputs(main_string, file);
        fclose(file);
        puts("saved to file");
        send_file(socket, fullpath);
        remove(fullpath);
        close(socket);
        return strdup("1");
    }
    else
    {
        puts("Empty chat");
        return strdup("0");
    }
}

char *get_n_messages(MYSQL *connection, char *ch_id, char *n, int socket)
{
    const char *request_parts[] = {"select * from message where ch_id = ", ch_id, " ORDER BY ms_id DESC LIMIT ", n, ";", NULL};
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
    int num_rows = mysql_num_rows(result);
    if (num_rows > 0)
    {
        char **messages = (char **)malloc(sizeof(char *) * num_rows);
        int i = 0;
        while (i < num_rows)
        {
            message_t message;
            MYSQL_ROW row;
            row = mysql_fetch_row(result);
            message.ms_id = strdup(row[0]);
            message.ch_id = strdup(row[1]);
            message.u_id = strdup(row[2]);
            message.ms_text = strdup(row[3]);
            message.ms_datetime = strdup(row[4]);
            message.ms_ismedia = strdup(row[5]);
            message.ms_isforwarded = strdup(row[6]);
            message.ms_isreply = strdup(row[7]);
            message.ms_isseen = strdup(row[8]);
            message.ms_isedited = strdup(row[9]);
            message.ms_media = strdup(row[10]);
            messages[i] = write_message_to_json(message);
            // puts(messages[i]);
            i++;
        }
        char *main_string = strdup("{\"messages\": [");
        for (int i = 0; i < num_rows; i++)
        {
            main_string = strjoin(main_string, messages[i]);
            // strjoin(main_string,contacts[i]);
            if (i != num_rows - 1)
                main_string = strjoin(main_string, " , ");
            // strjoin(main_string,",");
        }
        main_string = strjoin(main_string, "]}");
        // strjoin(main_string,"]}");
        // int size = sizeof(main_string);
        // printf("%d",size);
        // puts(main_string);
        printf("\n length = %lu, size = %lu\n", strlen(main_string), sizeof(main_string));
        // return main_string;
        main_string[strlen(main_string)] = '\0';
        size_t size = strlen(main_string);
        mysql_free_result(result);
        puts(main_string);
        mkdir("./messages_tmp", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        char *fullpath = strdup("./messages_tmp/");
        fullpath = strjoin(fullpath, ch_id);
        FILE *file = fopen(fullpath, "w");
        // fwrite(main_string, sizeof(char), size, file);
        fputs(main_string, file);
        fclose(file);
        puts("saved to file");
        send_file(socket, fullpath);
        remove(fullpath);
        close(socket);
        return strdup("1");
    }
    else
    {
        puts("Empty chat");
        return strdup("0");
    }
}

char *get_message_by_id(MYSQL *connection, char *ms_id)
{
    const char *request_parts[] = {"select * from message where ms_id = ", ms_id, " limit 1;", NULL};
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
    message_t message;
    message.ms_id = strdup(row[0]);
    message.ch_id = strdup(row[1]);
    message.u_id = strdup(row[2]);
    message.ms_text = strdup(row[3]);
    message.ms_datetime = strdup(row[4]);
    message.ms_ismedia = strdup(row[5]);
    message.ms_isforwarded = strdup(row[6]);
    message.ms_isreply = strdup(row[7]);
    message.ms_isseen = strdup(row[8]);
    message.ms_isedited = strdup(row[9]);
    char *message_str = write_message_to_json(message);
    char *main_string = strdup("{\"message\": [");
    main_string = strjoin(main_string, message_str);
    main_string = strjoin(main_string, "]}");

    puts(main_string);
    return main_string;
}

char *delete_message(MYSQL *connection, char *ms_id) //, char *ch_id
{
    const char *request_parts[] = {"delete from message where ms_id=\"", ms_id, "\";", NULL}; //and ch_id=\"", ch_id, "\"
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    free(bdrequest);
    return "1";
}

char *edit_message(MYSQL *connection, char *ms_id, char *new_text)
{

    const char *request_parts[] = {"UPDATE message SET ms_text = \"", new_text, "\", ms_isedited=1 WHERE ms_id = \"", ms_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    free(bdrequest);
    return "1";
}
