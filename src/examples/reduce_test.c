#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../array.h"
#include "../functions/lambda.h"
#include "../functions/foreach.h"
#include "../functions/reduce.h"

int main()
{
    // Reduce examples

    // Reduce int array to sum
    ARRAY_T(int_arr_t, int);
    struct int_arr_t arr;
    ARRAY_INIT(arr);
    for (int i = 0; i < 10; i++)
        ARRAY_PUSH(arr, i);

    int sum = REDUCE(int, arr, 0, LAMBDA(int, (int acc, int i), {
        return acc + i;
    }));

    printf("Sum: %d\n", sum);

    // Reduce string array to string
    ARRAY_T(str_arr_t, char *);
    struct str_arr_t str_arr;
    ARRAY_INIT(str_arr);

    ARRAY_PUSH(str_arr, "Hello");
    ARRAY_PUSH(str_arr, "World");
    ARRAY_PUSH(str_arr, "!");

    char buf[256] = "";
    char *buf_ptr = buf;

    char *str = REDUCE(char *, str_arr, buf_ptr, LAMBDA(char *, (char *acc, char *str), {
        return strcat(acc, str);
    }));

    printf("Result: %s\n", str);

    ARRAY_FREE(arr);
    ARRAY_FREE(str_arr);
    return 0;
}