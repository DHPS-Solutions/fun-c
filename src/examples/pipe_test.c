#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../functions/lambda.h"
#include "../pipe.h"

void print_split(char *str)
{
    printf("========================================\n");
    printf("%s\n", str);
    printf("========================================\n");
}

int main()
{
    // Create an int array
    ARRAY_T(int_arr_t, int);
    struct int_arr_t arr;
    ARRAY_INIT(arr);
    for (int i = 0; i < 10; i++)
        ARRAY_PUSH(arr, i);

    // Create a pipe
    PIPE_DEF(int_ret_t, int_arr_t, int);

    print_split("Filter, map, and print");

    // Pipe functions together and print with a foreach
    struct int_ret_t piped = int_arr_t_pipe(arr, 3, 
        FILTER_PIPE, LAMBDA(bool, (int e), {
            return e % 2 == 0;
        }),
        MAP_PIPE, LAMBDA(int, (int e), {
            return e * 2;
        }),
        FOREACH_PIPE, LAMBDA(void, (int e), {
            printf("Element: '%d'\n", e);
        })
    );

    print_split("Filter, map and sum by reduction");

    // Pipe functions together and reduce to sum
    struct int_ret_t piped2 = int_arr_t_pipe(arr, 3, 
        FILTER_PIPE, LAMBDA(bool, (int e), {
            return e % 3 == 0;
        }),
        MAP_PIPE, LAMBDA(int, (int e), {
            return e * 10;
        }),
        REDUCE_PIPE, 0, LAMBDA(int, (int acc, int e), {
            return acc + e;
        })
    );

    // Print the sum
    printf("Sum of reduction: '%d'\n", PIPE_RET_VAL(int, piped2));

    // Free the array
    ARRAY_FREE(arr);

    // Create a string array
    ARRAY_T(str_arr_t, char *);
    struct str_arr_t str_arr;
    ARRAY_INIT(str_arr);
    ARRAY_PUSH(str_arr, "Hello");
    ARRAY_PUSH(str_arr, "World");
    ARRAY_PUSH(str_arr, "!");

    // Define a pipe
    PIPE_DEF(str_ret_t, str_arr_t, char *);

    print_split("Filter, map, and print");

    // Pipe functions together and print with a foreach
    struct str_ret_t piped3 = str_arr_t_pipe(str_arr, 3, 
        FILTER_PIPE, LAMBDA(bool, (char *e), {
            return e[0] == 'H';
        }),
        MAP_PIPE, LAMBDA(char *, (char *e), {
            char *str = strdup(e);
            for (int i = 0; i < strlen(str); i++)
                if((str[i] > 96) && (str[i] < 123)) 
                    str[i] ^=0x20;
                    
            return str;
        }),
        FOREACH_PIPE, LAMBDA(void, (char *e), {
            printf("Element: '%s'\n", e);
        })
    );

    print_split("Filter, map and sum by reduction");

    // Pipe functions together and reduce to sum
    char buf[256] = "";
    char *buf_ptr = buf;

    struct str_ret_t piped4 = str_arr_t_pipe(str_arr, 3,
        MAP_PIPE, LAMBDA(char *, (char *e), {
            char *str = strdup(e);
            for (int i = 0; i < strlen(str); i++)
                if((str[i] > 96) && (str[i] < 123)) 
                    str[i] ^=0x20;
                    
            return str;
        }),
        FOREACH_PIPE, LAMBDA(void, (char *e), {
            printf("Element: '%s'\n", e);
        }),
        REDUCE_PIPE, buf_ptr, LAMBDA(char *, (char *acc, char *str), {
            return strcat(acc, strcat(str, " "));
        })
    );

    // Print the sum
    printf("Sum of reduction: '%s'\n", PIPE_RET_VAL(char *, piped4));

    // Free the array
    ARRAY_FREE(str_arr);

    return 0;
}