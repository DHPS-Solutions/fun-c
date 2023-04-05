#ifndef INT_FUNCTIONAL_H
#define INT_FUNCTIONAL_H

#include <stdlib.h>
#include <stdint.h>

#include "functional.h"

/**
 * Struct to hold an array.
 * @param arr The array.
 * @param len The length of the array.
 */
struct int_array_t {
    int *arr;
    int len;
};

/**
 * Struct to hold an optional value.
 * @param tag The tag of the value.
 * @param pred The predicate of the value.
 * @param s_value The value if it is a single value.
 * @param m_value The value if it is an array.
 */
struct int_array_option_t {
    uint8_t tag;
    bool pred;
    int s_value;
    struct int_array_t m_value;
};

/**
 * Macro to create a consumer foreach loop.
 * @param array The array to iterate over.
 * @param func The function to call for each element.
 */
#define FOREACH(array, func)\
({\
    for (int i = 0; i < array.len; i++)\
        func(array.arr[i]);\
})

/**
 * Macro to iterate and create a map.
 * @param array The array to iterate over.
 * @param func The function to call for each element.
 */
#define INT_MAP(array, func)\
({\
    int *map_arr = malloc(sizeof(int) * array.len);\
    struct int_array_t mapped = {\
        .arr = map_arr,\
        .len = array.len\
    };\
    for (int i = 0; i < array.len; i++)\
        mapped.arr[i] = func(array.arr[i]);\
    mapped;\
})

/**
 * Macro to iterate and create a filter.
 * @param array The array to iterate over.
 * @param func The function to call for each element.
 */
#define INT_FILTER(array, func)\
({\
    int *filter_arr = malloc(sizeof(int) * array.len);\
    struct int_array_t filtered = {\
        .arr = filter_arr,\
        .len = array.len\
    };\
    int j = 0;\
    for (int i = 0; i < array.len; i++) {\
        if (func(array.arr[i])) {\
            filtered.arr[j] = array.arr[i];\
            j++;\
        }\
    }\
    filtered.len = j;\
    if (filtered.len < array.len)\
        filtered.arr = realloc(filtered.arr, sizeof(int) * filtered.len);\
    filtered;\
})

/**
 * Macro to iterate and create a reduce from left to right.
 * @param array The array to iterate over.
 * @param func The function to call for each element.
 */
#define INT_REDUCE(array, func)\
({\
    int reduced = array.arr[0];\
    for (int i = 1; i < array.len; i++)\
        reduced = func(reduced, array.arr[i]);\
    reduced;\
})

/**
 * Macro to iterate and check if any element satisfies a predicate.
 * @param array The array to iterate over.
 * @param func The function to call for each element.
 */
#define INT_ANY(array, func)\
({\
    bool any = false;\
    for (int i = 0; i < array.len; i++) {\
        if (func(array.arr[i])) {\
            any = true;\
            break;\
        }\
    }\
    any;\
})

/**
 * Macro to iterate and check if all elements satisfy a predicate.
 * @param array The array to iterate over.
 * @param func The function to call for each element.
 */
#define INT_ALL(array, func)\
({\
    bool all = true;\
    for (int i = 0; i < array.len; i++) {\
        if (!func(array.arr[i])) {\
            all = false;\
            break;\
        }\
    }\
    all;\
})


/**
 * Function to pipe a value into a function.
 * @param value The value to pipe.
 * @param ... The functions to pipe the value through.
 * @return The return value of the function.
 */
int int_pipe(int value, ...);

/**
 * Function to pipe array functions.
 * @param array The array to pipe.
 * @param pipes The number of functions to pipe.
 * @param ... The functions to pipe the array through.
 * @return The return value of the function.
 */
struct int_array_option_t int_array_pipe(struct int_array_t value, int pipes, ...);


#endif