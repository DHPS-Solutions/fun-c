/**
 * Authored by Callum Gran 2023.
 * Collection of macros for functional programming.
 */
#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <stdlib.h>
#include <stdarg.h>

/**
 * Enums to hold the different types of functions.
 */
#define MAP_ENUM 1
#define FOREACH_ENUM 2
#define FILTER_ENUM 3
#define REDUCE_ENUM 4

/**
 * Struct to hold an array.
 * @param arr The array.
 * @param len The length of the array.
 */
struct array_t {
    int *arr;
    int len;
};

/**
 * Macro to create an lambda function.
 * @param return_type The return type of the lambda function.
 * @param func_args The arguments of the lambda function.
 * @param func_body The body of the lambda function.
 * @return A pointer to the lambda function.
 */
#define LAMBDA(return_type, func_args, func_body)\
({\
    return_type __fn_t__ func_args\
    func_body\
    &__fn_t__;\
})

/**
 * Macro to create an anonymous function function.
 * @param return_type The return type of the anonymous function.
 * @param func_args The arguments of the anonymous function.
 * @param func_body The body of the anonymous function.
 * @param ... The arguments to pass to the anonymous function.
 * @return The return value of the anonymous function.
 */
#define ANON(return_type, func_args, func_body, ...)\
    LAMBDA(return_type, func_args, func_body)(__VA_ARGS__)

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
#define MAP(array, func)\
({\
    int *map_arr = malloc(sizeof(int) * array.len);\
    struct array_t mapped = {\
        .arr = map_arr,\
        .len = array.len\
    };\
    for (int i = 0; i < array.len; i++)\
        mapped.arr[i] = func(array.arr[i]);\
    mapped;\
})

/**
 * Function to pipe a value into a function.
 * @param value The value to pipe.
 * @param ... The functions to pipe the value through.
 * @return The return value of the function.
 */
int int_pipe(int value, ...) 
{
    va_list args;
    va_start(args, value);
    
    int (*func)(int);

    while ((func = va_arg(args, int (*)(int))) != NULL)
        value = func(value);

    va_end(args);
    
    return value;
}

/**
 * Macro to pipe a value into a function.
 * @param value The value to pipe.
 * @param ... The functions to pipe the value through.
 * @return The return value of the function.
 */
// #define PIPE(value, ...)\
// ({\
//     va_list args;\
//     va_start(args, value);\
//     int choice;\
//     while ((choice = va_arg(args, void *)) != 0) \
//         va_arg(args, void *)
// })

#endif