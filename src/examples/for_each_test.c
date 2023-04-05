#include <stdio.h>
#include <stdlib.h>

#include "../array.h"
#include "../functions/lambda.h"
#include "../functions/foreach.h"

int main()
{
    // For each example

    // For each int array
    ARRAY_T(int_arr_t, int);
    struct int_arr_t arr;
    ARRAY_INIT(arr);
    for (int i = 0; i < 10; i++) {
        ARRAY_PUSH(arr, i);
    }

    FOREACH(arr, LAMBDA(void, (int i), {
        printf("%d ", i);
    }));
    printf("\n");

    // For each string array
    ARRAY_T(str_arr_t, char *);
    struct str_arr_t str_arr;
    ARRAY_INIT(str_arr);

    ARRAY_PUSH(str_arr, "Hello");
    ARRAY_PUSH(str_arr, "World");
    ARRAY_PUSH(str_arr, "!");

    FOREACH(str_arr, LAMBDA(void, (char *str), {
        printf("%s ", str);
    }));
    printf("\n");

    ARRAY_FREE(arr);
    ARRAY_FREE(str_arr);
    return 0;
}