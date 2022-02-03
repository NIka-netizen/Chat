#include "client.h"

void data_to_str_registration () {

   char **reg_data = malloc(sizeof(char **)* 4);
    char *num_func = "1";

    for (int i = 0; i < 4; i++) {
        if ((reg_data[i] = malloc(128)) == NULL) {
            exit(1);
        }
        if (i == 0) {
            reg_data[i] = data_registration.login;
        }
        if (i == 1) {
            reg_data[i] = data_registration.password;
        }
        if (i == 2) {
            reg_data[i] = data_registration.nickname;
        }
        if (i == 3) {
            reg_data[i] = data_registration.secret_word;
        }
    }

    // for (int i = 0; i < 4; i++) {
    //      write(1, reg_data[i], mx_strlen(reg_data[i]));
    //      write(1, "\n", 1);
    // }

    /* ФОРМИРОВАНИЕ ДЖИСОНОВСКОЙ СТРОКИ */
    //char *answer = write_to_json(num_func, new_str);

    /* Джисоновская строка передается на клиент*/
    //set_connection(answer);
}

void data_to_str_check_SW () {

     char **login_SW = malloc(sizeof(char **)* 2);
    for (int i = 0; i < 2; i++) {
        if ((login_SW[i] = malloc(128)) == NULL) {
            exit(1);
        }
        if (i == 0) {
            login_SW[i] = check_start.login;
        }
        if (i == 1) {
            login_SW[i] = check_start.secret_word;
        }
    }

    // for (int i = 0; i < 2; i++) {
    //      write(1, login_SW[i], mx_strlen(login_SW[i]));
    //      write(1, "\n", 1);
    // }

    /* ФОРМИРОВАНИЕ ДЖИСОНОВСКОЙ СТРОКИ */
    //char *answer = write_to_json(num_func, new_str);

    /* Джисоновская строка передается на клиент*/
    //set_connection(answer);
}

void data_to_str_change_password () { 
    char **login_password = malloc(sizeof(char **)* 2);
    for (int i = 0; i < 2; i++) {
        if ((login_password[i] = malloc(128)) == NULL) {
            exit(1);
        }
        if (i == 0) {
            login_password[i] = check_second.login;
        }
        if (i == 1) {
            login_password[i] = check_second.password;  
        }
    }

    // for (int i = 0; i < 2; i++) {
    //      write(1, login_password[i], mx_strlen(login_password[i]));
    //      write(1, "\n", 1);
    // }
     
   /* ФОРМИРОВАНИЕ ДЖИСОНОВСКОЙ СТРОКИ */
    //char *answer = write_to_json(num_func, new_str);

    /* Джисоновская строка передается на клиент*/
    //set_connection(answer);
}

void data_to_str_authorization () {
    char **str_authorization_data = malloc(sizeof(char **)* 2);
    for (int i = 0; i < 2; i++) {
        if ((str_authorization_data[i] = malloc(128)) == NULL) {
            exit(1);
        }
        if (i == 0) {
            str_authorization_data[i] = authorization_data.login;
        }
        if (i == 1) {
            str_authorization_data[i] = authorization_data.password;  
        }
    }

    // for (int i = 0; i < 2; i++) {
    //     write(1, str_authorization_data[i], mx_strlen(str_authorization_data[i]));
    //     write(1, "\n", 1);
    // }

      /* ФОРМИРОВАНИЕ ДЖИСОНОВСКОЙ СТРОКИ */
    //char *answer = write_to_json(num_func, new_str);

    /* Джисоновская строка передается на клиент*/
    //set_connection(answer);
}
