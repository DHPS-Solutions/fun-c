#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../array.h"
#include "../functions/lambda.h"
#include "../functions/foreach.h"
#include "../functions/filter.h"

int main()
{
    // Filter examples

    // Filter int array
    ARRAY_T(int_arr_t, int);
    struct int_arr_t arr;
    ARRAY_INIT(arr);
    for (int i = 0; i < 10; i++) {
        ARRAY_PUSH(arr, i);
    }

    struct int_arr_t filtered_arr = FILTER(int_arr_t, arr, LAMBDA(int, (int i), {
        return i % 2 == 0;
    }));

    FOREACH(filtered_arr, LAMBDA(void, (int i), {
        printf("%d ", i);
    }));
    printf("\n");

    // Filter string array
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

    struct str_arr_t filtered_str_arr = FILTER(str_arr_t, str_arr, LAMBDA(int, (char *s), {
        return strlen(s) > 3;
    }));

    FOREACH(filtered_str_arr, LAMBDA(void, (char *str), {
        printf("%s ", str);
    }));
    printf("\n");

    ARRAY_FREE(arr);
    ARRAY_FREE(str_arr);
    ARRAY_FREE(filtered_arr);
    ARRAY_FREE(filtered_str_arr);
    return 0;
}