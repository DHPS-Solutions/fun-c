#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>

#include "int_functional.h"

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

struct int_array_option_t int_array_pipe(struct int_array_t value, int pipes, ...)
{
    struct int_array_option_t optional = {
        .tag = ARR_VAL,
        .pred = false,
        .s_value = 0,
        .m_value = value
    };

    va_list args;
    va_start(args, pipes);
    int choice = 0;
    int j = 0;
    bool to_free = false;
    int *to_free_arr;
    for (int i = 0; i < pipes; i++) {            
        choice = va_arg(args, int);
        if (j > 0 && choice == MAP_PIPE || choice == FILTER_PIPE) {
            to_free = true;
            to_free_arr = optional.m_value.arr;
        }
        switch (choice) {
            case MAP_PIPE: ;
                j++;
                int (*map_func)(int) = va_arg(args, int (*)(int));
                optional.m_value = INT_MAP(optional.m_value, map_func);
                optional.tag = ARR_VAL;
                if (to_free) {
                    free(to_free_arr);
                    to_free = false;
                }
                break;
            case FOREACH_PIPE: ;
                void (*foreach_func)(int) = va_arg(args, void (*)(int));
                FOREACH(optional.m_value, foreach_func);
                break;
            case FILTER_PIPE: ;
                j++;
                bool (*filter_func)(int) = va_arg(args, bool (*)(int));
                struct int_array_t temp = INT_FILTER(optional.m_value, filter_func);
                optional.tag = ARR_VAL;
                optional.m_value.arr = temp.arr;
                optional.m_value.len = temp.len;
                if (to_free) {
                    free(to_free_arr);
                    to_free = false;
                }
                break;
            case REDUCE_PIPE: ;
                int (*left_reduce_func)(int, int) = va_arg(args, int (*)(int, int));
                optional.s_value = INT_REDUCE(optional.m_value, left_reduce_func);
                optional.m_value.arr[0] = optional.s_value;
                optional.m_value.len = 1;
                optional.tag = INT_VAL;
                break;
            case ANY_PIPE: ;
                bool (*any_func)(int) = va_arg(args, bool (*)(int));
                optional.pred = INT_ANY(value, any_func);
                optional.tag = BOOL_VAL;
                break;
            case ALL_PIPE: ;
                bool (*all_func)(int) = va_arg(args, bool (*)(int));
                optional.pred = INT_ALL(value, all_func);
                optional.tag = BOOL_VAL;
                break;
            default:
                break;
        }
    }

end:
    va_end(args);
    if (optional.tag == ARR_VAL) {
        optional.tag = ARR_VAL;
        optional.m_value = value;
    } else if (optional.tag == INT_VAL) {
        optional.tag = INT_VAL;
        optional.s_value = value.arr[0];
    } else if (optional.tag == BOOL_VAL) {
        optional.tag = BOOL_VAL;
        optional.pred = value.arr[0];
    } else {
        optional.tag = ERR_VAL;
    }
    return optional;
}