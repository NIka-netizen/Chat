#include "uchat.h"

char *itobase10(char *buf, int value)
{
    sprintf(buf, "%d", value);
    return buf;
}

char *mx_strnew(const int size)
{
    char *str = (char *)malloc(sizeof(char) * (size + 1));
    if (str == NULL)
        return NULL;
    str[size] = '\0';
    return str;
}

char *strjoin(char *a, char *b)
{
    size_t sumlen = strlen(a)+strlen(b)+4;
    char *concat = (char *)malloc(sizeof(char) * sumlen);
    snprintf(concat, sumlen, "%s%s", a, b);
    return concat;
}

char *mx_strcat(char *restrict s1, const char *restrict s2){
    int str1len = strlen(s1);
    int i=0;
    while (s2[i]!='\0'){
        s1[str1len+i]=s2[i];
        i++;
    }
    s1[str1len+i]='\0';
    return s1;
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

char *set_date()
{
    char *date;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t); //*gmtime(&t);
    //char *answer = (char *)malloc(sizeof(char) * 60);
    char *year = mx_strnew(4);
    char *month = mx_strnew(2);
    char *day = mx_strnew(2);
    char *hour = mx_strnew(2);
    char *min = mx_strnew(2);
    char *sec = mx_strnew(2);
    itobase10(year, tm.tm_year + 1900);
    itobase10(month, tm.tm_mon + 1);
    itobase10(day, tm.tm_mday);
    itobase10(hour, tm.tm_hour);
    itobase10(min, tm.tm_min);
    itobase10(sec, tm.tm_sec);
    const char *request_parts[] = {year, "-", month, "-", day, " ", hour, ":", min, ":", sec, NULL};
    date = strjoins_arr(request_parts);
    free(year); 
    free(month); 
    free(day);   
    free(hour); 
    free(min);   
    free(sec);   

    return date;
}

char *get_filename_extension(char *filename){
 
    int index = 0;
    for (int i = strlen(filename) - 1; i >= 0; i--)
    {
        if(filename[i] == '.'){
            index = i;
            break;
        }
    }
   char *result = strdup(&filename[index]);
   return result;
}
