#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../array.h"
#include "../functions/lambda.h"
#include "../functions/map.h"
#include "../functions/foreach.h"

int main()
{
    // Map examples

    // Map int array
    ARRAY_T(int_arr_t, int);
    struct int_arr_t arr;
    ARRAY_INIT(arr);
    for (int i = 0; i < 10; i++) {
        ARRAY_PUSH(arr, i);
    }

    struct int_arr_t mapped_arr = MAP(int_arr_t, arr, LAMBDA(int, (int i), {
        return i * 2;
    }));

    FOREACH(mapped_arr, LAMBDA(void, (int i), {
        printf("%d ", i);
    }));
    printf("\n");


    // Map string array
    ARRAY_T(str_arr_t, char *);
    struct str_arr_t str_arr;
    ARRAY_INIT(str_arr);

    ARRAY_PUSH(str_arr, "Hello");
    ARRAY_PUSH(str_arr, "World");
    ARRAY_PUSH(str_arr, "!");
    ARRAY_PUSH(str_arr, "This");
    ARRAY_PUSH(str_arr, "is");
    ARRAY_PUSH(str_arr, "a");
    ARRAY_PUSH(str_arr, "test");

    struct str_arr_t mapped_str_arr = MAP(str_arr_t, str_arr, LAMBDA(char *, (char *s), {
        char *str = strdup(s);
        for (int i = 0; i < strlen(str); i++) {
            if((str[i] > 96) && (str[i] < 123)) str[i] ^=0x20;
        }
        
        return str;
    }));

    FOREACH(mapped_str_arr, LAMBDA(void, (char *str), {
        printf("%s ", str);
    }));
    printf("\n");

    // Map string to int array
    struct int_arr_t mapped_str_to_int_arr = MAP(int_arr_t, str_arr, LAMBDA(int, (char *s), {
        return strlen(s);
    }));

    FOREACH(mapped_str_to_int_arr, LAMBDA(void, (int i), {
        printf("%d ", i);
    }));

    printf("\n");

    ARRAY_FREE(arr);
    ARRAY_FREE(str_arr);
    ARRAY_FREE(mapped_arr);
    ARRAY_FREE(mapped_str_arr);
    ARRAY_FREE(mapped_str_to_int_arr);
    return 0;
}