#include "uchat.h"

char *write_user_info_to_json(user_t user)
{
    struct json_object *array;
    struct json_object *object;
    struct json_object *tmp;
    array = json_object_new_array();
    object = json_object_new_object();
    tmp = json_object_new_string(user.u_id);
    json_object_object_add(object, "u_id", tmp);
    tmp = json_object_new_string(user.u_login);
    json_object_object_add(object, "u_login", tmp);
    tmp = json_object_new_string(user.u_name);
    json_object_object_add(object, "u_name", tmp);
    tmp = json_object_new_string(user.u_surname);
    json_object_object_add(object, "u_surname", tmp);
    tmp = json_object_new_string(user.u_avatar);
    json_object_object_add(object, "u_avatar", tmp);
    tmp = json_object_new_string(user.u_lastSeen);
    json_object_object_add(object, "u_lastSeen", tmp);
        tmp = json_object_new_string(user.u_secret_word);
    json_object_object_add(object, "u_secret_word", tmp);

    char *answer = (char *)json_object_to_json_string(object);
    return answer;
}

char *write_message_to_json(message_t message)
{
    struct json_object *array;
    struct json_object *object;
    struct json_object *tmp;
    array = json_object_new_array();
    object = json_object_new_object();
    tmp = json_object_new_string(message.ch_id);
    json_object_object_add(object, "ch_id", tmp);
    tmp = json_object_new_string(message.ms_id);
    json_object_object_add(object, "ms_id", tmp);
    tmp = json_object_new_string(message.u_id);
    json_object_object_add(object, "u_id", tmp);
    tmp = json_object_new_string(message.ms_text);
    json_object_object_add(object, "ms_text", tmp);
    tmp = json_object_new_string(message.ms_datetime);
    json_object_object_add(object, "ms_datetime", tmp);
    tmp = json_object_new_string(message.ms_isedited);
    json_object_object_add(object, "ms_isedited", tmp);
    tmp = json_object_new_string(message.ms_isforwarded);
    json_object_object_add(object, "ms_isforwarded", tmp);
    tmp = json_object_new_string(message.ms_ismedia);
    json_object_object_add(object, "ms_ismedia", tmp);
    tmp = json_object_new_string(message.ms_isreply);
    json_object_object_add(object, "ms_isreply", tmp);
    tmp = json_object_new_string(message.ms_isseen);
    json_object_object_add(object, "ms_isseen", tmp);
    tmp = json_object_new_string(message.ms_media);
    json_object_object_add(object, "ms_media", tmp);
    char *answer = (char *)json_object_to_json_string(object);
    return answer;
}

char *chat_to_json(chat_t chat)
{
    struct json_object *array;
    struct json_object *object;
    struct json_object *tmp;
    array = json_object_new_array();
    object = json_object_new_object();
    tmp = json_object_new_string(chat.ch_id);
    json_object_object_add(object, "ch_id", tmp);
    tmp = json_object_new_string(chat.ch_name);
    json_object_object_add(object, "ch_name", tmp);
    tmp = json_object_new_string(chat.ch_avatar);
    json_object_object_add(object, "ch_avatar", tmp);

    char *answer = (char *)json_object_to_json_string(object);
    // puts(answer);
    return answer;
}

char *chatuser_to_json(chatuser_t chatuser)
{
    struct json_object *array;
    struct json_object *object;
    struct json_object *tmp;
    array = json_object_new_array();
    object = json_object_new_object();
    tmp = json_object_new_string(chatuser.ch_id);
    json_object_object_add(object, "ch_id", tmp);
    tmp = json_object_new_string(chatuser.u_id);
    json_object_object_add(object, "u_id", tmp);
    tmp = json_object_new_string(chatuser.ch_isadmin);
    json_object_object_add(object, "ch_isadmin", tmp);

    char *answer = (char *)json_object_to_json_string(object);
    // puts(answer);
    return answer;
}

char *contact_to_json(contact_t contact)
{
    struct json_object *array;
    struct json_object *object;
    struct json_object *tmp;
    array = json_object_new_array();
    object = json_object_new_object();
    tmp = json_object_new_string(contact.c_id);
    json_object_object_add(object, "c_id", tmp);
    tmp = json_object_new_string(contact.u_name);
    json_object_object_add(object, "u_name", tmp);

    tmp = json_object_new_string(contact.u_avatar);
    json_object_object_add(object, "u_avatar", tmp);
    tmp = json_object_new_string(contact.u_lastSeen);
    json_object_object_add(object, "u_lastSeen", tmp);

    char *answer = (char *)json_object_to_json_string(object);
    // puts(answer);
    return answer;
}
