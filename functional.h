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
#define MAP_PIPE 1
#define FOREACH_PIPE 2
#define FILTER_PIPE 3
#define REDUCE_PIPE 4

/**
 * Struct to hold an array.
 * @param arr The array.
 * @param len The length of the array.
 */
struct int_array_t {
    int *arr;
    int len;
};

typedef void int_consumer(int);
typedef int int_mapper(int);

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
 * Macro to pipe array functions.
 * @param array The array to pipe.
 * @param ... The functions to pipe the array through.
 * @return The return value of the function.
 */
struct int_array_t int_array_pipe(struct int_array_t value, int pipes, ...)
{
    va_list args;
    va_start(args, pipes);
    int choice = 0;
    for (int i = 0; i < pipes; i++) {

        choice = va_arg(args, int);
        switch (choice) {
            case MAP_PIPE: ;
                int (*map_func)(int) = va_arg(args, int (*)(int));
                value = INT_MAP(value, map_func);
                break;
            case FOREACH_PIPE: ;
                void (*foreach_func)(int) = va_arg(args, void (*)(int));
                FOREACH(value, foreach_func);
                break;
            default:
                break;
        }
    }

    va_end(args);
    return value;
}

#endif