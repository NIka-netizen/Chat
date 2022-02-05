#include "uchat.h"

char *add_contact_by_login(MYSQL *connection, char *login, char *u_id)
{
    const char *request_parts[] = {"select u_id from user where u_login = \"", login, "\" limit 1;", NULL};
    char *bdrequest = strjoins_arr(request_parts);
    char *answer = NULL;
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
    // printf("nf: --%d--%d\n", num_rows,num_fields);
    if (num_rows > 0)
    {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)))
        {
            answer = strdup(row[0]);
        }
        char *contact_id = strdup(answer);
        mysql_free_result(result);
        puts(contact_id);
        if (strcmp(contact_id, u_id) != 0)
        {
            const char *request_parts2[] = {"SELECT COUNT(c_id) FROM contacts WHERE  c_id = \"", contact_id, "\" and u_id = \"", u_id, "\";", NULL};
            bdrequest = strjoins_arr(request_parts2);
            puts(bdrequest);
            if (mysql_query(connection, bdrequest))
            {
                finish_with_error(connection);
            }
            free(bdrequest);
            result = mysql_store_result(connection);
            if (result == NULL)
            {
                finish_with_error(connection);
            }
            while ((row = mysql_fetch_row(result)))
            {
                answer = strdup(row[0]);
            }
            puts(answer);
            mysql_free_result(result);
            if (strcmp(answer, "0") == 0)
            {
                const char *request_parts1[] = {"INSERT INTO contacts (c_id, u_id, u_blocked) VALUES (\"", contact_id, "\",\"", u_id, "\",\"0\");", NULL};
                bdrequest = strjoins_arr(request_parts1);
                puts(bdrequest);
                if (mysql_query(connection, bdrequest))
                {
                    finish_with_error(connection);
                }
                free(bdrequest);
            }
            else
            {
                puts("Contact already exist.");
                return "1";
            }
        }
        else
        {
            puts("Contact login is equal to user`s login.");
            return "1";
        }
    }
    else
    {
        puts("No user with such login found.");
        return "1";
    }
    puts("Contact added successfully.");
    return "0";
    // if(strcmp(answer,"")==0){
    //     puts("AAA");
    // }
    // puts(answer);
    // char *contact_id =
}

char *add_contact_by_id(MYSQL *connection, char *contact_id, char *u_id)
{
    const char *request_parts[] = {"INSERT INTO contacts (c_id, u_id, u_blocked) VALUES (\"", contact_id, "\",\"", u_id, "\",\"0\");", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    free(bdrequest);
    char *answer = NULL;
    return answer;
}

char *block_contact(MYSQL *connection, char *contact_id, char *u_id)
{
    const char *request_parts2[] = {"SELECT COUNT(c_id) FROM contacts WHERE  c_id = \"", contact_id, "\" and u_id = \"", u_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts2);
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
    char *answer;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        answer = strdup(row[0]);
    }
    puts(answer);
    mysql_free_result(result);
    if (strcmp(answer, "0") != 0) // if contact exist then we can block him
    {
        const char *request_parts[] = {"UPDATE contacts SET u_blocked = \"1\" WHERE u_id = \"", u_id, "\" and c_id = \"", contact_id, "\";", NULL};
        bdrequest = strjoins_arr(request_parts);
        puts(bdrequest);
        if (mysql_query(connection, bdrequest))
        {
            finish_with_error(connection);
        }
        free(bdrequest);
    }
    return strdup("0");
}

char *unblock_contact(MYSQL *connection, char *contact_id, char *u_id)
{
    const char *request_parts2[] = {"SELECT COUNT(c_id) FROM contacts WHERE  c_id = \"", contact_id, "\" and u_id = \"", u_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts2);
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
    char *answer;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        answer = strdup(row[0]);
    }
    puts(answer);
    mysql_free_result(result);
    if (strcmp(answer, "0") != 0) // if contact exist then we can unblock him
    {
        const char *request_parts[] = {"UPDATE contacts SET u_blocked = \"0\" WHERE u_id = \"", u_id, "\" and c_id = \"", contact_id, "\";", NULL};
        bdrequest = strjoins_arr(request_parts);
        puts(bdrequest);
        if (mysql_query(connection, bdrequest))
        {
            finish_with_error(connection);
        }
        free(bdrequest);
    }
    return strdup("0");
}

char *delete_contact(MYSQL *connection, char *contact_id, char *u_id)
{
    const char *request_parts[] = {"delete from contacts where u_id=\"", u_id, "\" and c_id=\"", contact_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    free(bdrequest);
    char *answer = NULL;
    return answer;
}

char *get_contacts(MYSQL *connection, char *u_id)
{
    const char *request_parts[] = {"SELECT c.c_id FROM contacts c JOIN user u ON c.u_id=u.u_id WHERE c.u_id = \"", u_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);
    char **answer = NULL;
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
    answer = (char **)malloc(sizeof(char *) * num_rows);
    // printf("nf: --%d--%d\n", num_rows,num_fields);
    int i = 0;
    if (num_rows > 0)
    {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)))
        {
            answer[i] = strdup(row[0]);
            puts(answer[i]);
            i++;
        }

        mysql_free_result(result);
        char **contacts = (char **)malloc(sizeof(char *) * i + 1);
        int strings_count = i;
        i = 0;
        while (i < num_rows)
        {
            char *answer_1 = NULL;
            const char *request_parts1[] = {"SELECT u_id,concat(u_name,' ',u_surname),u_avatar,u_lastSeen FROM user WHERE u_id = \"", answer[i], "\";", NULL};
            bdrequest = strjoins_arr(request_parts1);
            puts(bdrequest);
            if (mysql_query(connection, bdrequest))
            {
                finish_with_error(connection);
            }
            free(bdrequest);
            result = mysql_store_result(connection);
            if (result == NULL)
            {
                finish_with_error(connection);
            }
            // num_rows = mysql_num_rows(result);
            contact_t contact;
            while ((row = mysql_fetch_row(result)))
            {
                // answer_1 = strdup(row[0]);
                contact.c_id = strdup(row[0]);
                contact.u_name = strdup(row[1]);
                contact.u_avatar = strdup(row[2]);
                contact.u_lastSeen = strdup(row[3]);
                // contacts[j].u_status = strdup(row[4]);
                // puts(row[0]);
                // puts(row[1]);
                // puts(row[2]);
                // puts(row[3]);
                // puts(row[4]);
            }
            mysql_free_result(result);
            contacts[i] = contact_to_json(contact);
            i++;
        }

        char *main_string = strdup("{\"contacts\": [");
        for (int i = 0; i < strings_count; i++)
        {
            main_string = strjoin(main_string, contacts[i]);
            // strjoin(main_string,contacts[i]);
            if (i != strings_count - 1)
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
        puts("That user have no contacts.");
        return strdup("0");
    }
}
