#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../array.h"
#include "../functions/lambda.h"
#include "../functions/foreach.h"
#include "../functions/matching.h"

int main()
{
    // Any Match examples

    // Match int
    ARRAY_T(int_arr_t, int);
    struct int_arr_t arr;
    ARRAY_INIT(arr);
    for (int i = 0; i <= 10; i++)
        ARRAY_PUSH(arr, i);

    // Match
    int i = 10;
    ANY_MATCH(arr, LAMBDA(bool, (int e), {
        return e == i;
    })) ? printf("Found '%d' in array\n", i) : printf("Did not find '%d' in array\n", i);

    // No match
    i = 11;
    ANY_MATCH(arr, LAMBDA(bool, (int e), {
        return e == i;
    })) ? printf("Found '%d' in array\n", i) : printf("Did not find '%d' in array\n", i);

    // Match string
    ARRAY_T(str_arr_t, char *);
    struct str_arr_t str_arr;
    ARRAY_INIT(str_arr);

    ARRAY_PUSH(str_arr, "Hello");
    ARRAY_PUSH(str_arr, "World");
    ARRAY_PUSH(str_arr, "!");
    
    // Match
    char *str = "World";
    ANY_MATCH(str_arr, LAMBDA(bool, (char *e), {
        return strcmp(e, str) == 0;
    })) ? printf("Found '%s' in array of strings\n", str) 
    : printf("Did not find '%s' in array of strings\n", str);

    // No match
    str = "Goodbye";
    ANY_MATCH(str_arr, LAMBDA(bool, (char *e), {
        return strcmp(e, str) == 0;
    })) ? printf("Found '%s' in array of strings\n", str) 
    : printf("Did not find '%s' in array of strings\n", str);

    ARRAY_FREE(arr);
    ARRAY_FREE(str_arr);

    // All Match examples
    
    // Match int
    ARRAY_INIT(arr);
    for (int i = 0; i <= 10; i++)
        ARRAY_PUSH(arr, i);

    // Match
    i = 10;
    ALL_MATCH(arr, LAMBDA(bool, (int e), {
        return e <= i;
    })) ? printf("All elements in array are less than or equal to '%d'\n", i) 
    : printf("Not all elements in array are less than or equal to '%d'\n", i);

    // Not all match
    i = 9;
    ALL_MATCH(arr, LAMBDA(bool, (int e), {
        return e <= i;
    })) ? printf("All elements in array are less than or equal to '%d'\n", i) 
    : printf("Not all elements in array are less than or equal to '%d'\n", i);

    // Match string
    ARRAY_INIT(str_arr);

    ARRAY_PUSH(str_arr, "Hello");
    ARRAY_PUSH(str_arr, "World");
    ARRAY_PUSH(str_arr, "!");

    // Match
    int len = 6;
    ALL_MATCH(str_arr, LAMBDA(bool, (char *e), {
        return strlen(e) < len;
    })) ? printf("All elements in array of strings are less than '%d' characters long\n", len) 
    : printf("Not all elements in array of strings are less than '%d' characters long\n", len);

    // Not all match
    str = "World";
    ALL_MATCH(str_arr, LAMBDA(bool, (char *e), {
        return strcmp(e, str) == 0;
    })) ? printf("All elements in array of strings are equal to '%s'\n", str)
    : printf("Not all elements in array of strings are equal to '%s'\n", str);

    ARRAY_FREE(arr);
    ARRAY_FREE(str_arr);

    // None Match examples

    // Match int
    ARRAY_INIT(arr);
    for (int i = 0; i <= 10; i++)
        ARRAY_PUSH(arr, i);

    // None Match
    i = 11;
    NONE_MATCH(arr, LAMBDA(bool, (int e), {
        return e == i;
    })) ? printf("No elements in array are equal to '%d'\n", i)
    : printf("At least one element in array is equal to '%d'\n", i);

    // At least one match
    i = 10;
    NONE_MATCH(arr, LAMBDA(bool, (int e), {
        return e == i;
    })) ? printf("No elements in array are equal to '%d'\n", i)
    : printf("At least one element in array is equal to '%d'\n", i);

    // Match string
    ARRAY_INIT(str_arr);

    ARRAY_PUSH(str_arr, "Hello");
    ARRAY_PUSH(str_arr, "World");
    ARRAY_PUSH(str_arr, "!");

    // None match
    str = "Goodbye";
    NONE_MATCH(str_arr, LAMBDA(bool, (char *e), {
        return strcmp(e, str) == 0;
    })) ? printf("No elements in array of strings are equal to '%s'\n", str)
    : printf("At least one element in array of strings is equal to '%s'\n", str);

    // At least one match
    str = "World";
    NONE_MATCH(str_arr, LAMBDA(bool, (char *e), {
        return strcmp(e, str) == 0;
    })) ? printf("No elements in array of strings are equal to '%s'\n", str)
    : printf("At least one element in array of strings is equal to '%s'\n", str);

    ARRAY_FREE(arr);
    ARRAY_FREE(str_arr);

    // Find index

    // Match int
    ARRAY_INIT(arr);
    for (int i = 0; i <= 10; i++)
        ARRAY_PUSH(arr, i);

    // Find
    i = 10;
    int index = FIND_INDEX(arr, LAMBDA(bool, (int e), {
        return e == i;
    }));

    if (index != -1)
        printf("Found '%d' at index '%d' in array\n", i, index);
    else
        printf("Did not find '%d' in array\n", i);

    // Not found
    i = 11;
    index = FIND_INDEX(arr, LAMBDA(bool, (int e), {
        return e == i;
    }));

    if (index != -1)
        printf("Found '%d' at index '%d' in array\n", i, index);
    else
        printf("Did not find '%d' in array\n", i);

    return 0;
}