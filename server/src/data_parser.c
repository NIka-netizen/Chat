#include "uchat.h"

data_from_json_t parse_json_to_data(char *json_str)
{
    // string to server should look like { "function_number":1, "data":["field1","field2",...] }
    struct json_object *json_object;
    struct json_object *func_number;
    struct json_object *data;
    struct json_object *data_item;
    json_object = json_tokener_parse(json_str);
    json_object_object_get_ex(json_object, "function_number", &func_number);
    json_object_object_get_ex(json_object, "data", &data);
    int data_arr_length = json_object_array_length(data);
    char **data_items = (char **)malloc(sizeof(char *) * (data_arr_length + 2));
    ;
    int i = 0;
    for (i = 0; i < data_arr_length; i++)
    {
        data_item = json_object_array_get_idx(data, i);
        const char *temp = json_object_get_string(data_item);
        char *d_item = (char *)malloc(sizeof(char *) * strlen((char *)temp));
        strcpy(d_item, temp);
        data_items[i] = d_item;
    }
    i++;
    data_items[i] = NULL;
    data_from_json_t data_obj;
    const char *temp = json_object_get_string(func_number);
    // printf(temp);
    data_obj.function_number = atoi(temp);
    data_obj.counter = i;
    data_obj.data_array = data_items;
    return data_obj;
}
