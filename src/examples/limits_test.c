#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../array.h"
#include "../functions/lambda.h"
#include "../functions/limits.h"

int main()
{
    bool (*int_cmp)(int, int) = LAMBDA(bool, (int e, int f), {
        return e > f;
    });

    bool (*str_cmp)(char *, char *) = LAMBDA(bool, (char *e, char *f), {
        return strcmp(e, f) > 0;
    });

    ARRAY_T(int_arr_t, int);
    struct int_arr_t arr;
    ARRAY_INIT(arr);
    for (int i = 0; i < 10; i++) {
        ARRAY_PUSH(arr, i);
    }

    int max = 0;
    ARR_MAX(arr, max, int_cmp);

    printf("Max: '%d'\n", max);

    int min = 0;
    ARR_MIN(arr, min, int_cmp);

    printf("Min: '%d'\n", min);

    ARRAY_T(str_arr_t, char *);
    struct str_arr_t str_arr;
    ARRAY_INIT(str_arr);

    ARRAY_PUSH(str_arr, "Hello");
    ARRAY_PUSH(str_arr, "World");
    ARRAY_PUSH(str_arr, "!");
    ARRAY_PUSH(str_arr, "Goodbye");

    char *max_str = ARRAY_GET(str_arr, 0);
    ARR_MAX(str_arr, max_str, str_cmp);

    printf("Max: '%s'\n", max_str);

    char *min_str = ARRAY_GET(str_arr, 0);
    ARR_MIN(str_arr, min_str, str_cmp);

    printf("Min: '%s'\n", min_str);

    ARRAY_FREE(arr);
}