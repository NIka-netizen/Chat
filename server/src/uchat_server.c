#include "uchat.h"

char *get_messages_by_ids(MYSQL *connection, char **ids_mas)
{
    //
    return strdup("kekw");
}


char *validate_password(MYSQL *connection, char *login, char *password)
{
    const char *request_parts[] = {"select count(u.u_id) from user u join credentials c on c.u_id = u.u_id where u.u_login = \"", login, "\" and c.cr_password = \"", password, "\"limit 1;", NULL};
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
    if (atoi(row[0]) == 0)
    { //user exist and password correct
        return "OK";
    }
    else // user doesn`t exist or password is incorrect
    {
        return "NE OK";
    }
}

char *make_message_seen(MYSQL *connection, char *ms_id)
{
    const char *request_parts[] = {"UPDATE message SET ms_isseen = \"1\" WHERE ms_id = \"", ms_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    free(bdrequest);
    // mysql_close(connection);
    return strdup("OK");
    ;
}

char *is_login_already_taken(MYSQL *connection, char *login)
{
    const char *request_parts[] = {"SELECT count(u_id) FROM user WHERE u_login = \"", login, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);
    puts(bdrequest); //Вывод запроса в консоль
    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    free(bdrequest);
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
    MYSQL_ROW row = row = mysql_fetch_row(result);
    if (atoi(row[0]) > 0)
    {
        return strdup("1"); //taken
    }
    else
        return strdup("0"); //ok
}

char *set_user_avatar(MYSQL *connection, char *u_id, char *avatar_path)
{
    const char *request_parts[] = {"UPDATE user SET u_avatar = \"", avatar_path, "\" WHERE u_id = \"", u_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    free(bdrequest);
    char *answer = "OK";
    return answer;
}

char *set_chat_avatar(MYSQL *connection, char *ch_id, char *avatar_path)
{
    const char *request_parts[] = {"UPDATE chat SET ch_avatar = \"", avatar_path, "\" WHERE ch_id = \"", ch_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    free(bdrequest);
    char *answer = "OK";
    return answer;
}

char *set_message_file(MYSQL *connection, char *ms_id, char *file_path)
{
    const char *request_parts[] = {"UPDATE message SET ms_media = \"", file_path, "\", ms_ismedia = \"1\" WHERE ms_id = \"", ms_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(connection, bdrequest))
    {
        finish_with_error(connection);
    }
    free(bdrequest);
    char *answer = "OK";
    return answer; 
}

char *recieve_file(MYSQL *connection, int socket, char *number, char *info, char *base_filename) // info is "u_id", or "ch_id", or "ms_id"
{
    ssize_t read_return;
    char buffer[BUFSIZ];
    int num = atoi(number);
    char *path = NULL;
    char *filename = NULL;
    switch (num)
    {
    case 1:
        path = strdup("./user_info/");
        path = strjoin(path, info);
        mkdir("./user_info", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        path = strjoin(path, "/");
        filename = strdup(info);
        filename = strjoin(filename, "_avatar");
        break;
    case 2:
        path = strdup("./chat_info/");
        path = strjoin(path, info);
        mkdir("./chat_info", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        path = strjoin(path, "/");
        filename = strdup(info);
        filename = strjoin(filename, "_avatar");
        break;
    case 3:
        path = strdup("./messages_files/");
        path = strjoin(path, info);
        mkdir("./messages_files", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        path = strjoin(path, "/");
        filename = strdup(info);
        filename = strjoin(filename, "_file");
        break;
    
    default:
        break;
    }
    puts("Path:");
    puts(path);
    puts("Filename:");
    puts(filename);
    puts("Fullpath:");
    path = strjoin(path,filename);
    char *fullpath = strdup("");
    fullpath = strjoin(fullpath,path);
    char *ext = get_filename_extension(base_filename);
    fullpath = strjoin(fullpath,ext);
    puts(fullpath);
    
    puts("Recieving file...");
    int filefd = open(fullpath,
                  O_WRONLY | O_CREAT | O_TRUNC,
                  S_IRUSR | S_IWUSR);
    if (filefd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    do
    {
        read_return = read(socket, buffer, sizeof(buffer));
        if (read_return == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        if (write(filefd, buffer, sizeof(buffer)) == -1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
    } while (read_return > 0);
    // close(socket);
    puts("File recieved and saved to:");
    puts(fullpath);
    switch (num)
    {
    case 1:
        set_user_avatar(connection, info, fullpath);
        break;
    case 2:
        set_chat_avatar(connection, info, fullpath);
        break;
    case 3:
        set_message_file(connection, info, fullpath);
        break;
    default:
        break;
    }
    return strdup("OK");
}

char *send_file(int socket, char *fullfilename)
{
    ssize_t read_return;
    char buffer[BUFSIZ];
    puts(fullfilename);
    int filefd = open(fullfilename, O_RDONLY);
    if (filefd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (filefd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    puts("file opened");
    while (1) {
        read_return = read(filefd, buffer, sizeof(buffer));
        if (read_return == 0)
            break;
        if (read_return == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        // printf("\n%d\n",read_return);
        /* TODO use write loop: https://stackoverflow.com/questions/24259640/writing-a-full-buffer-using-write-system-call */
        if (write(socket, buffer, sizeof(buffer)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }
    puts("file delivered");
    return strdup("OK");
}

char *handle_functions(MYSQL *connection, data_from_json_t data, int sock)
{
    int function_number = data.function_number;
    char *answer = NULL;
    switch (function_number)
    {
    case 1:
        // data.data_array = ["login", "password", "name", "surname(NULL), "secret_word"];
        answer = add_user(connection, data.data_array[0], data.data_array[1], data.data_array[2], data.data_array[3], data.data_array[4]);
        break;
    case 2:
        // data.data_array = ["u_id" (my_id),"contact_id"];
        answer = add_personal_chat(connection, data.data_array[0], data.data_array[1]);
        break;
    case 3:
        // data.data_array = ["ch_id", "u_id", "text", "is_media", "isforwarded", "isreply", "isseen", "isedited"];
        answer = add_message(connection, data.data_array[0], data.data_array[1], data.data_array[2], data.data_array[3], data.data_array[4], data.data_array[5], data.data_array[6], data.data_array[7]);
        break;
    case 4:
        // data.data_array = ["ms_id"];
        answer = delete_message(connection, data.data_array[0]);
        break;
    case 5:
        // data.data_array = ["ms_id", "new_text"];
        answer = edit_message(connection, data.data_array[0], data.data_array[1]);
        break;
    case 6:
        // data.data_array = ["ms_id", "forward_to_ch_id"];
        answer = forward_message(connection, data.data_array[0], data.data_array[1]);
        break;
    case 7:
        // data.data_array = ["ms_id", "reply_to_ch_id"];
        answer = reply_message(connection, data.data_array[0], data.data_array[1]);
        break;
    case 8:
        // data.data_array = ["ch_id"];
        answer = get_all_messages(connection, data.data_array[0]);
        break;
    case 9:
        // data.data_array = ["ms_id"];
        answer = get_message_by_id(connection, data.data_array[0]);
        break;
    case 10:
        // data.data_array = ["ms_id1","ms_id2","ms_id3", ... ];
        answer = get_messages_by_ids(connection, data.data_array);
        break;
    case 11:
        // data.data_array = ["ms_id"];
        answer = make_message_seen(connection, data.data_array[0]);
        break;
    case 12:
        // data.data_array = ["contact_id","u_id"];
        answer = add_contact_by_id(connection,data.data_array[0], data.data_array[1]);
        break;
    case 13:
        // data.data_array = ["login","u_id"];
        answer = add_contact_by_login(connection, data.data_array[0], data.data_array[1]);
        break;
    case 14:
        // data.data_array = ["contact_id","u_id"];
        answer = block_contact(connection, data.data_array[0], data.data_array[1]);
        break;
    case 15:
        // data.data_array = ["contact_id","u_id"];
        answer = unblock_contact(connection, data.data_array[0], data.data_array[1]);
        break;
    case 16:
        // data.data_array = ["contact_id","u_id"];
        answer = delete_contact(connection, data.data_array[0], data.data_array[1]);
        break;
    case 17:
        // data.data_array = ["u_id"];
        answer = get_contacts(connection, data.data_array[0]);
        break;
    case 18:
        // data.data_array = ["login"];
        answer = get_my_id(connection, data.data_array[0]);
        break;
    case 19:
        // data.data_array = ["u_id"];
        answer = get_user_info(connection, data.data_array[0]);
        break;
    case 20:
        // data.data_array = ["u_id", "new_name"];
        answer = edit_user_name(connection, data.data_array[0], data.data_array[1]);
        break;
    case 21:
        // data.data_array = ["u_id", "new_name"];
        answer = edit_user_surname(connection, data.data_array[0], data.data_array[1]);
        break;
    case 22:
        // data.data_array = ["u_id", "new_pass"];
        answer = edit_password(connection, data.data_array[0], data.data_array[1]);
        break;
    case 23:
        // data.data_array = ["ch_id", "new_name"];
        answer = edit_chat_name(connection, data.data_array[0], data.data_array[1]);
        break;
    case 24:
        // data.data_array = ["ch_id"];
        answer = delete_chat(connection, data.data_array[0]);
        break;
    case 25:
        // data.data_array = ["login"];
        answer = is_login_already_taken(connection, data.data_array[0]);
    case 26:
        // data.data_array = ["u_id"];
        answer = get_chats(connection, data.data_array[0]);
        break;
    case 27:
        // data.data_array = ["ch_id"];
        answer = get_users_from_chat(connection, data.data_array[0]);
        break;
    case 28:
        // data.data_array = ["my_id","chat_name","avatar_link"];
        answer = create_group_chat(connection, data.data_array[0], data.data_array[1], data.data_array[2]);
        break;
    case 29:
        // data.data_array = ["ch_id","u_id","ch_isadmin"];
        answer = add_user_to_chat(connection, data.data_array[0], data.data_array[1], data.data_array[2]);
        break;
    case 30:
        //  data.data_array = ["number", "info", "base_filename"]; // info is "u_id", or "ch_id", or "ms_id", number = 1 is for adding_user_avatar, 2 is for chat_avatar, 3 is for message_file_adding;
        answer = recieve_file(connection,sock,data.data_array[0], data.data_array[1], data.data_array[2]);
        break;
    case 31:
        //
        answer = send_file(sock, data.data_array[0]);
        break;
    default:
        puts("Function not found fuck");
        break;
    }
    return answer;
}

void *connection_handler(void *socket_descriptor)
{
    int socket = *(int *)socket_descriptor;
    int read_size;
    char client_message[2000];
    char *server_answer_message = "someshit";
    puts("<-------------[Processing the recv]------------->");
    // server_answer_message = recieve_file(socket,"test");
    while ((read_size = recv(socket, client_message, 2000, 0)) > 0)
    {
        puts("<-------------[Processing the client_message]------------->");

        client_message[read_size] = '\0';
        printf("%s\n", client_message);
        // memset(client_message,0,2000);
        puts("<-------------[Processing the db connection and parsing the request]------------->");
        MYSQL *handler_con = db_connection_open();
        //Тут нужно получить номер запроса и вызвать по нему нужную функцию
        if (strlen(client_message) > 2)
        {
            data_from_json_t query = parse_json_to_data(client_message);
            puts("<-------------[Processing the request]------------->");
            server_answer_message = handle_functions(handler_con, query, socket);
            // for (int i = 0; i < query.counter - 1; i++)
            // {
            //     printf("%s ", query.data_array[i]);
            // }
            puts(server_answer_message);
            puts("\n<-------------[Waiting for next query]------------->");
            printf("Server mess:%s\n", server_answer_message);
            write(socket, server_answer_message, strlen(server_answer_message));
        }
        // if (server_answer_message != NULL)
        // {
        //     free(server_answer_message);
        //     server_answer_message = NULL;
        // } raskomentit kogda server_ans_mess
        // puts("DB connection closed");
        // mysql_close(handler_con);
        memset(&client_message, 0, sizeof(client_message));
        if (read_size == 0)
        {
            puts("Client off");
        }
        else if (read_size == -1)
        {
            puts("Сбой при recv");
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    // ----------------------------------------- TESTs field
    // char *json_str = "{\"function_number\":\"1\",\"data\":[\"bebra\", \"test_pass\", \"test_name\", \"NULL\"]}";
    // char *json_str = "{\"function_number\":\"3\",\"data\":[\"8\", \"12\", \"this is text of message\", \"0\", \"0\", \"0\",\"0\", \"0\"]}";
    // data_from_json_t data = parse_json_to_data(json_str);
    // MYSQL *handler_con = db_connection_open();
    // get_users_from_chat(handler_con,"6");
    // recieve_file()
    // create_group_chat()
    // get_chats(handler_con,"8");
    // forward_message(handler_con, "510", "4");
    // block_contact(handler_con,"8","9");
    // add_personal_chat(handler_con,"8","9");
    // add_user(handler_con,"user3","1234","user3","surname","secret_word");
    // get_user_info(handler_con,"8");
    // char *json_str1 = get_contacts(handler_con,"8");
    // for (int i = 0; i < 2000; i++)
    // {
    //     add_message(handler_con,"8","12","abobus","0","0","0","0","0");
    // }

    // get_all_messages(handler_con, "8");
    // add_contact_by_login(handler_con, "test_login", "16");
    // handle_functions(handler_con, data);
    // int i = 0;
    // while(strings_to_request[i]!=NULL){
    //     printf("%s ",strings_to_request[i]);
    //     i++;
    // }
    // char *answer;

// -------------------------------------------- CONNECTION below raskomentit to test something.
    if (argc != 2)
    {
        write(2,"Usage: ./server [port]\n",24);
        // return 1;
        exit(1);
    }
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;

    //Creating socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
        perror("Error while socket creating\n");
    puts("Socket created.");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));
    //Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Bind failed. Server shutdown.");
        return 1;
    }
    puts("Bind sucess.");

    // //Listening
    listen(socket_desc, 10); //second parametr - maximum of clients;

    puts("Server is ready, waiting for new connections...");
    c = sizeof(struct sockaddr_in);
    pthread_t thread_id;

    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c)))
    {
        puts("Connection created.");

        if (pthread_create(&thread_id, NULL, connection_handler, (void *)&client_sock) < 0)
        {
            perror("Error while creating thread.\n");
            exit(1);
        }
        puts("Handled successfully.");
    }

    if (client_sock < 0)
    {
        perror("Accept failed. Server shutdown.");
        return 1;
    }
}
