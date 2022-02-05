#include "client.h"

char *write_to_json(char* num_f,char **arr_new)
{
	struct json_object *array;
	struct json_object *object;
	struct json_object *tmp;
	array = json_object_new_array();
	object = json_object_new_object();
	int size = 0;
	
	for (size_t i = 0; arr_new[i]; i++)
	{
		size++;
	}
	
	char **arr = (char **)malloc(sizeof(char *) * (size + 1));
	arr[size] = NULL;
	
	for (int i = 0; i < size; i++)
	{
		arr[i] = mx_strnew(strlen(arr_new[i]));
		strcpy(arr[i], arr_new[i]);

	}
	
	for (size_t i = 0; arr[i]; i++)
	{
		tmp = json_object_new_string(arr[i]);
		json_object_array_add(array, tmp);
	}

	// string_array_clear(arr,size);
	tmp = json_object_new_string(num_f);
	json_object_object_add(object, "function_number", tmp);
	json_object_object_add(object, "data", array);
	array = tmp = NULL;
	char *answer = (char *)json_object_to_json_string(object);
	return answer;
}

char *request_to_server(char *json_str)
{
    
    int a = write(data.socket_desc, json_str, strlen(json_str));
    puts(json_str);
    if (a == (int)strlen(json_str)) {
        char answer[1024];
        size_t bytes_readed = read(data.socket_desc, answer, 1024);
        answer[bytes_readed] = '\0'; 
        puts(answer);
        return strdup(answer);
    }
    else {
        // //g_print("Request to server error!\n");
        puts("Request to server error");
        return strdup("Request to server error");
    }
}

char *register_user (char *login, char *password, char *nickname, char *secret_word) { // "0" IF LOGIN TAKEN, "USER_ID" IF ADDED SUCESSFULLY

    char *surname = "";
   char *reg_data[] = {login,password,nickname,surname,secret_word,NULL};

    // for (int i = 0; i < 4; i++) {
    //      write(1, reg_data[i], mx_strlen(reg_data[i]));
    //      write(1, "\n", 1);
    // }
    
    /* ФОРМИРОВАНИЕ ДЖИСОНОВСКОЙ СТРОКИ */
    char *json_str = write_to_json("1", reg_data);
    char *response = request_to_server(json_str); 
    // int answer = atoi(response);
    puts(response);
    return response;
    /* Джисоновская строка передается на клиент*/
    //set_connection(answer);
}

// void data_to_str_check_SW () {
//      char **login_SW = malloc(sizeof(char **)* 2);
//     for (int i = 0; i < 2; i++) {
//         if ((login_SW[i] = malloc(128)) == NULL) {
//             exit(1);
//         }
//         if (i == 0) {
//             login_SW[i] = login;//check_start.login;
//         }
//         if (i == 1) {
//             login_SW[i] = secret_word;//check_start.secret_word;
//         }
//     }
//     // for (int i = 0; i < 2; i++) {
//     //      write(1, login_SW[i], mx_strlen(login_SW[i]));
//     //      write(1, "\n", 1);
//     // }
//     /* ФОРМИРОВАНИЕ ДЖИСОНОВСКОЙ СТРОКИ */
//     //char *answer = write_to_json(num_func, new_str);
//     /* Джисоновская строка передается на клиент*/
//     //set_connection(answer);
// }

bool change_password (char *login, char *new_password, char *secret_word) { // "0" IF LOGIN doesnt exist or secret_word incorrect, "USER_ID" IF updated SUCESSFULLy
    char *login_a[] = {login,NULL};
    char *json_str = write_to_json("18",login_a);
    puts(json_str);
    char *u_id = "0";
    u_id = request_to_server(json_str);
    puts(u_id);
    if(strcmp(u_id, "0") == 0)
    {
        return false;
    }
    char *data[] = {u_id,new_password,secret_word,NULL};
    // for (int i = 0; i < 2; i++) {
    //     if ((login_password[i] = malloc(128)) == NULL) {
    //         exit(1);
    //     }
    //     if (i == 0) {
    //         login_password[i] = login;//check_second.login;
    //     }
    //     if (i == 1) {
    //         login_password[i] = new_password;//check_second.password;  
    //     }
    // }

    // for (int i = 0; i < 2; i++) {
    //      write(1, login_password[i], mx_strlen(login_password[i]));
    //      write(1, "\n", 1);
    // }
     
   /* ФОРМИРОВАНИЕ ДЖИСОНОВСКОЙ СТРОКИ */
    json_str = write_to_json("22", data); //edit_password
    char *response = "0";
    response = request_to_server(json_str);
    int answer = atoi(response);
    return answer;
    /* Джисоновская строка передается на клиент*/
    //set_connection(answer);
}

char *autorize_user (char *login, char *password) {  // USER_ID if sucess, "0" IF something incorrect
    char **str_authorization_data = malloc(sizeof(char **)* 2);
    for (int i = 0; i < 2; i++) {
        if ((str_authorization_data[i] = malloc(128)) == NULL) {
            exit(1);
        }
        if (i == 0) {
            str_authorization_data[i] = login;// authorization_data.login;
        }
        if (i == 1) {
            str_authorization_data[i] = password;//authorization_data.password;  
        }
    }

    // for (int i = 0; i < 2; i++) {
    //     write(1, str_authorization_data[i], mx_strlen(str_authorization_data[i]));
    //     write(1, "\n", 1);
    // }

      /* ФОРМИРОВАНИЕ ДЖИСОНОВСКОЙ СТРОКИ */
    char *json_str = write_to_json("32", str_authorization_data);
    char *response = request_to_server(json_str);
    puts(response); 
    return response;
    /* Джисоновская строка передается на клиент*/
    //set_connection(answer);
}

bool add_message(char *ch_id, char *u_id, char *text)
{
    // ["ch_id", "u_id", "text", "is_media", "isforwarded", "isreply", "isseen", "isedited"]
    char *data[] = {ch_id, u_id, text, "0","0","0","0","0",NULL};
    char *json_str = write_to_json("3", data);
    char *response = request_to_server(json_str);
    if(atoi(response) > 0)
    {
        return 1;
    } else return 0;
    
}

bool delete_message(char *ms_id)
{
    char *data[] = {ms_id,NULL};
    char *json_str = write_to_json("4", data);
    char *response = request_to_server(json_str);
    if(strcmp(response,"1")==0)
    {
        return 1;
    } else return 0;
}

bool edit_message(char *ms_id)
{
    char *data[] = {ms_id,NULL};
    char *json_str = write_to_json("5", data);
    char *response = request_to_server(json_str);
    if(strcmp(response,"1")==0)
    {
        return 1;
    } else return 0;    
}

bool reply_message(char *ms_id, char *ch_id_to_reply)
{
    char *data[] = {ms_id,ch_id_to_reply,NULL};
    char *json_str = write_to_json("7", data);
    char *response = request_to_server(json_str);
    if(strcmp(response,"1")==0)
    {
        return 1;
    } else return 0;     
}

bool forward_message(char *ms_id, char *ch_id_to_reply)
{
    char *data[] = {ms_id,ch_id_to_reply,NULL};
    char *json_str = write_to_json("6", data);
    char *response = request_to_server(json_str);
    if(strcmp(response,"1")==0)
    {
        return 1;
    } else return 0;  
}

bool make_message_seen(char *ms_id)
{
    char *data[] = {ms_id,NULL};
    char *json_str = write_to_json("11", data);
    char *response = request_to_server(json_str);
    if(strcmp(response,"1")==0)
    {
        return 1;
    } else return 0;      
}

bool create_personal_chat(char *u_id, char *contact_id)
{
    char *data[] = {u_id,contact_id,NULL};
    char *json_str = write_to_json("2", data);
    char *response = request_to_server(json_str);
    if(strcmp(response,"1")==0)
    {
        return 1;
    } else return 0; 
}

// RETURNS NULL IF NO CHATS
chat_t **get_chats(char *u_id)
{
    char *data[] = {u_id,NULL};
    char *json_str = write_to_json("26", data);
    char *response = request_to_server(json_str);
        if(strcmp(response,"0") == 0)
    {
        return NULL;
    }
    int exist = 0;
    json_object *jobj, *values_obj, *tmp_values, *values_name;
    jobj = json_tokener_parse(response);
    exist = json_object_object_get_ex(jobj, "chats", &values_obj);
    int length = json_object_array_length(values_obj);
    if (length > 0)
    {
        int last_msg_index = 0;
        chat_t **chats = malloc(sizeof(chat_t *) * (length + 1));
        chats[length] = NULL;
        for (ssize_t i = 0; i < length; i++)
        {
            tmp_values = json_object_array_get_idx(values_obj, i);
            chats[i] = malloc(sizeof(chat_t));
            json_object_object_get_ex(tmp_values, "ch_id", &values_name);
            chats[i]->ch_id = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ch_name", &values_name);
            chats[i]->ch_name = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ch_avatar", &values_name);
            chats[i]->ch_avatar = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            free(tmp_values);
        }
        free(values_obj);
        free(jobj);

        return chats;
    }
    free(values_obj);
    free(jobj);
    return NULL;  // if no chats    
}

//RETURNS NULL IF NO SUCH CHAT 
chatuser_t **get_chat_users(char *ch_id)
{
    char *data[] = {ch_id,NULL};
    char *json_str = write_to_json("27", data);
    char *response = request_to_server(json_str);
    if(strcmp(response,"0") == 0)
    {
        return NULL;
    }
    int exist = 0;
    json_object *jobj, *values_obj, *tmp_values, *values_name;
    jobj = json_tokener_parse(response);
    exist = json_object_object_get_ex(jobj, "chatusers", &values_obj);
    int length = json_object_array_length(values_obj);
    if (length > 0)
    {
        int last_msg_index = 0;
        chatuser_t **chatusers = malloc(sizeof(chatuser_t *) * (length + 1));
        chatusers[length] = NULL;
        for (ssize_t i = 0; i < length; i++)
        {
            tmp_values = json_object_array_get_idx(values_obj, i);
            chatusers[i] = malloc(sizeof(chatuser_t));
            json_object_object_get_ex(tmp_values, "ch_id", &values_name);
            chatusers[i]->ch_id = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "u_id", &values_name);
            chatusers[i]->u_id = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ch_isadmin", &values_name);
            chatusers[i]->ch_isadmin = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            free(tmp_values);
        }
        free(values_obj);
        free(jobj);

        return chatusers;
    }
    free(values_obj);
    free(jobj);
    return NULL;  // if no chats            
}

// RETURNS NULL IF someshit happens
user_t *get_user_info(char *u_id)
{
    char *data[] = {u_id, NULL};
    char *json_str = write_to_json("19", data);
    char *response = request_to_server(json_str);
    // if(strcmp(response,"0") == 0)
    // {
    //     return NULL;
    // }
    int exist = 0;
    json_object *jobj, *values_obj, *tmp_values, *values_name;
    jobj = json_tokener_parse(response);
    exist = json_object_object_get_ex(jobj, "user", &values_obj);
    int length = json_object_array_length(values_obj);
    // printf("%d",length);
    if (length > 0)
    {
        int last_msg_index = 0;
        user_t *user = malloc(sizeof(user_t) * (length + 1));

        tmp_values = json_object_array_get_idx(values_obj, 0);
        json_object_object_get_ex(tmp_values, "u_id", &values_name);
        user->u_id = strdup((char *)json_object_get_string(values_name));
        free(values_name);
        json_object_object_get_ex(tmp_values, "u_login", &values_name);
        user->u_login = strdup((char *)json_object_get_string(values_name));
        free(values_name);
        json_object_object_get_ex(tmp_values, "u_name", &values_name);
        user->u_name = strdup((char *)json_object_get_string(values_name));
        free(values_name);
        json_object_object_get_ex(tmp_values, "u_surname", &values_name);
        user->u_surname = strdup((char *)json_object_get_string(values_name));
        free(values_name);
        json_object_object_get_ex(tmp_values, "u_avatar", &values_name);
        user->u_avatar = strdup((char *)json_object_get_string(values_name));
        free(values_name);
        json_object_object_get_ex(tmp_values, "u_lastSeen", &values_name);
        user->u_lastSeen = strdup((char *)json_object_get_string(values_name));
        free(values_name);
        free(tmp_values);
        free(values_obj);
        free(jobj);

        return user;
    }
    free(values_obj);
    free(jobj);
    return NULL;
}

bool edit_user_name(char *u_id, char *new_name)
{
    char *data[] = {u_id,new_name,NULL};
    char *json_str = write_to_json("20", data);
    char *response = request_to_server(json_str);
    if(strcmp(response,"1")==0)
    {
        return 1;
    } else return 0;     
}

bool edit_chat_name(char *ch_id, char *new_name)
{
    char *data[] = {ch_id,new_name,NULL};
    char *json_str = write_to_json("23", data);
    char *response = request_to_server(json_str);
    if(strcmp(response,"1")==0)
    {
        return 1;
    } else return 0; 
}

bool delete_chat(char *ch_id) // also clears chat
{
    char *data[] = {ch_id,NULL};
    char *json_str = write_to_json("24", data);
    char *response = request_to_server(json_str);
    if(strcmp(response,"1")==0)
    {
        return 1;
    } else return 0; 
}

bool add_contact_by_id(char *contact_id, char *u_id)
{
    char *data[] = {contact_id,u_id,NULL};
    char *json_str = write_to_json("24", data);
    char *response = request_to_server(json_str);
    if(strcmp(response,"1")==0)
    {
        return 1;
    } else return 0; 
}

bool add_contact_by_login(char *contact_login, char *u_id)
{
    char *data[] = {contact_login,u_id,NULL};
    char *json_str = write_to_json("24", data);
    char *response = request_to_server(json_str);
    if(strcmp(response,"1")==0)
    {
        return 1;
    } else return 0; 
}

bool block_contact(char *contact_id, char *u_id)
{
    char *data[] = {contact_id,u_id, NULL};
    char *json_str = write_to_json("14", data);
    char *response = request_to_server(json_str);
    if(strcmp(response,"1")==0)
    {
        return 1;
    } else return 0;     
}

bool unblock_contact(char *contact_id, char *u_id)
{
    char *data[] = {contact_id,u_id,NULL};
    char *json_str = write_to_json("15", data);
    char *response = request_to_server(json_str);
    if(strcmp(response,"1")==0)
    {
        return 1;
    } else return 0;     
}

void server_set_connection()
{
    struct sockaddr_in client_addr;
    data.socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    int port = data.port;
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(data.ipv4);
    client_addr.sin_port = htons(port);

    if (connect(data.socket_desc, (struct sockaddr *)&client_addr, sizeof(client_addr)) == 0)
    {
        //printf("Connected to server, port is %d\n", port);
    }
    else
    {
        // сверстать окно об ошибке и вызывать здесь и вызывать функцию которая будет каждые 60 секунд вызывать повторное соединение с сервером рекурсией
        // server_set_connection();
        //printf("Something wrong!\n");
        exit(1);
    }
}

void string_array_clear(char **arr, int size)
{
    if (arr != NULL)
    {
        for (int i = 0; i < size; ++i)
            free(arr[i]);
        free(arr);
        arr = NULL;
    }
}

// last object in this massive is NULL
contact_t **get_all_contacts(char *function_number, char **data) // n17
{   
    // json_str = {"function_number":"17","data":["u_id"]};
    char *json_str = write_to_json(function_number,data);
    // response = {"contacts": [{ "c_id": "9", "u_name": "name surname", "u_avatar": "avatar_link", "u_lastSeen": "2022-02-01 15:37:00" }]}
    char *response = request_to_server(json_str);
    int exist = 0;
    json_object *jobj, *values_obj, *tmp_values, *values_name;
    jobj = json_tokener_parse(response);
    exist = json_object_object_get_ex(jobj, "contacts", &values_obj);
    int length = json_object_array_length(values_obj);
    printf("\n length = %d \n",length);
    if (length > 0)
    { 
        contact_t **contacts = malloc(sizeof(contact_t *) * (length + 1));
        contacts[length] = NULL;
        /* поменять int на size_t */
        for (int i = 0; i < length; i++)
        {
            tmp_values = json_object_array_get_idx(values_obj, i);
            contacts[i] = malloc(sizeof(contact_t));
            json_object_object_get_ex(tmp_values, "c_id", &values_name);
            contacts[i]->c_id = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "u_name", &values_name);
            contacts[i]->c_name = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "u_avatar", &values_name);
            contacts[i]->c_avatar = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "u_lastSeen", &values_name);
            contacts[i]->c_lastSeen = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            free(tmp_values);
        }
        free(values_obj);
        free(jobj);
        return contacts;
    }
    free(values_obj);
    free(jobj);
    return NULL;
}

char *strjoins_arr(const char **str_arr)
{
    if (str_arr == NULL)
        return NULL;
    const char **tmp = str_arr;
    char *endstr = NULL;
    ssize_t endlen = 0, i = 0;
    while ((*tmp))
    {
        endlen += strlen(*tmp);
        tmp++;
    }
    endstr = mx_strnew(endlen);
    tmp = str_arr;

    while ((*tmp))
    {
        strcpy(&endstr[i], *tmp);
        i += strlen(*tmp);
        tmp++;
    }
    // printf("\n%s \n", endstr);
    return endstr;
}

char *strjoin(char *a, char *b)
{
    size_t sumlen = strlen(a)+strlen(b)+4;
    char *concat = (char *)malloc(sizeof(char) * sumlen);
    snprintf(concat, sumlen, "%s%s", a, b);
    return concat;
}

char *request_to_get_messages(char *request)
{
    puts(request);
    write(data.socket_desc, request, strlen(request));
    size_t recv_size = 0;
    uint32_t size ;
    int rc = -1;
    write(data.socket_desc, &recv_size, sizeof(size_t));
    do {
        rc = read(data.socket_desc, &size, sizeof(uint32_t));
    } while (rc < 0);
    size = ntohl(size);
    write(data.socket_desc, &recv_size, sizeof(size_t));
    printf("%u -- total size\n", size);
    printf("Reading Picture Byte Array\n");
    char p_array[1025];
    FILE *image = fopen("tmp", "w");
    printf("Sending %u\n", size);
    int  nb = 0;
    uint32_t  packet_size = 1024;
    int real_size = 0;
    do
    {
        if (packet_size > size)
        {
            packet_size = size;
        }
        printf("PS %u\n", packet_size);
        nb = recv(data.socket_desc, p_array, packet_size, 0);
        fwrite(p_array, 1, nb, image);
        size -= nb;
        real_size +=nb;
        printf("Sending %u\n", size);
    } while (size > 0);
    puts("file recieved");
    fclose(image);
    // char *str = mx_file_to_str("tmp");
    FILE *file = fopen("tmp", "r");
    
    printf("size %d",real_size);
    // char *str;
    char *str = malloc(sizeof(char) * real_size);
    fgets(str,real_size,file);
    char *strstr = strdup(str);
    strstr = strjoin(strstr,"}");
    remove("tmp");
    return strstr;
}

// The most newer message will be the last in this array
message_arr * get_50_messages(char *ch_id, char *last_msg_id) //n8
{
    // json_str = {"function_number":"8","data":["ch_id", "last_message_id"]};
    char *data[] ={ch_id, last_msg_id, NULL};
    char *json_str = write_to_json("8",data);
    // response = {"messages": [{ "ch_id": "4", "ms_id": "438", "u_id": "8", "ms_text": 
    // "abobus", "ms_datetime": "2022-02-03 13:33:03", "ms_isedited": "0", "ms_isforwarded": "0", "ms_ismedia": "0", "ms_isreply": "0", "ms_isseen": "0" }, ... ]}
    char *response = request_to_get_messages(json_str);
    puts(response);
    // ////puts(str);
    json_object *jobj, *values_obj, *tmp_values, *values_name;
    jobj = json_tokener_parse(response);
    if (jobj == NULL)
    {
        return NULL;
    }
    int exist = json_object_object_get_ex(jobj, "messages", &values_obj);
    int length = json_object_array_length(values_obj);
    // printf("%d",length);
    if (length > 0)
    {
        int i = 0;
        message_arr *arr_msgs = malloc(sizeof(message_arr));
        arr_msgs->messages = malloc(sizeof(message_t *));
        char *tmp;
        /* тут тоже нужно поменять int на size_t */
        for (int j = 0; j < length; j++)
        {
            tmp_values = json_object_array_get_idx(values_obj, j);

            arr_msgs->messages[i] = malloc(sizeof(message_t));
            json_object_object_get_ex(tmp_values, "ch_id", &values_name);
            arr_msgs->messages[i]->ch_id = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ms_id", &values_name);
            arr_msgs->messages[i]->ms_id = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "u_id", &values_name);
            arr_msgs->messages[i]->u_id = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            // json_object_object_get_ex(tmp_values, "u_name", &values_name);
            // arr_msgs->messages[i]->u_name = strdup((char *)json_object_get_string(values_name));
            // free(values_name);
            json_object_object_get_ex(tmp_values, "ms_text", &values_name);
            arr_msgs->messages[i]->ms_text = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ms_datetime", &values_name);
            arr_msgs->messages[i]->ms_datetime = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ms_isedited", &values_name);
            arr_msgs->messages[i]->ms_isedited = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ms_isforwarded", &values_name);
            arr_msgs->messages[i]->ms_isforwarded = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ms_ismedia", &values_name);
            arr_msgs->messages[i]->ms_ismedia = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ms_isreply", &values_name);
            arr_msgs->messages[i]->ms_isreply = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ms_isseen", &values_name);
            arr_msgs->messages[i]->ms_isseen = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            arr_msgs->messages = realloc(arr_msgs->messages, (i + 2) * sizeof(message_t *));
            free(tmp_values);
            i++;
        }
        arr_msgs->messages[i] = NULL;
        arr_msgs->length = length;
        free(values_obj);
        free(jobj);
        return arr_msgs;
    }
    free(values_obj);
    free(jobj);
    return NULL;
}

char *create_group_chat(char *u_id, char *chat_name)
{
    char *data[] = {u_id,chat_name,"",NULL};
    char *json_str = write_to_json("28", data);
    char *response = request_to_server(json_str);
    int a = atoi(response);
    if (a > 0){
        return response;
    }   else return "0";
}

bool add_user_to_chat(char *ch_id, char *u_id)
{
    char *data[] = {ch_id,u_id,NULL};
    char *json_str = write_to_json("29", data);
    char *response = request_to_server(json_str);
    if(strcmp(response,"1")==0)
    {
        return 1;
    } else return 0;       
}
