#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#include "int_functional.h"

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
 * Function to pipe array functions.
 * @param array The array to pipe.
 * @param pipes The number of functions to pipe.
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
            case FILTER_PIPE: ;
                bool (*filter_func)(int) = va_arg(args, bool (*)(int));
                value = INT_FILTER(value, filter_func);
                break;
            case REDUCE_PIPE: ;
                int (*left_reduce_func)(int, int) = va_arg(args, int (*)(int, int));
                value.arr[0] = INT_REDUCE(value, left_reduce_func);
                goto end;
                break;
            default:
                break;
        }
    }

end:
    va_end(args);
    return value;
}