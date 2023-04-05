#ifndef PIPE_H
#define PIPE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "array.h"
#include "functions/common.h"
#include "functions/filter.h"
#include "functions/foreach.h"
#include "functions/map.h"
#include "functions/matching.h"
#include "functions/reduce.h"
#include "functions/limits.h"

/**
 * Enums to hold the different types of functions.
 * @param MAP_PIPE The map function.
 * @param FOREACH_PIPE The foreach function.
 * @param FILTER_PIPE The filter function.
 * @param REDUCE_PIPE The reduce function.
 * @param ANY_PIPE The any function.
 * @param ALL_PIPE The all function.
 * @param NONE_PIPE The none function.
 * @param MAX_PIPE The max function.
 * @param MIN_PIPE The min function.
 * @param IS_SORTED_PIPE The is_sorted function.
 * @param IS_EMPTY_PIPE The is_empty function.
 * @param IS_NOT_EMPTY_PIPE The is_not_empty function.
 */
#define MAP_PIPE 1
#define FOREACH_PIPE 2
#define FILTER_PIPE 3
#define REDUCE_PIPE 4
#define ANY_PIPE 5
#define ALL_PIPE 6
#define NONE_PIPE 7
#define MAX_PIPE 8
#define MIN_PIPE 9
#define IS_SORTED_PIPE 10
#define IS_EMPTY_PIPE 11
#define IS_NOT_EMPTY_PIPE 12

/**
 * Enums to hold the different types of values.
 * @param BOOL_VAL The boolean value.
 * @param S_VAL The single value.
 * @param M_VAL The multiple value.
 * @param ERR_VAL The error value.
 */
#define BOOL_VAL 1
#define S_VAL 2
#define M_VAL 3
#define VOID_VAL 4
#define ERR_VAL 255

/**
 * Macro that creates a new return value for a pipe.
 * @param struct_name The name of the struct.
 * @param type The type of the array.
*/
#define PIPE_RET_T(struct_name, array_type, type)\
struct struct_name {\
    uint8_t tag;\
    bool pred;\
    type s_val;\
    struct array_type m_val;\
    char *err;\
};

/**
 * Macro that creates a new return value for a pipe.
 * @param struct_name The name of the struct.
 * @param in The input struct.
*/
#define PIPE_RET_INIT(ret_struct, in)\
({\
    ret_struct.tag = M_VAL;\
    ret_struct.pred = false;\
    ret_struct.s_val = 0;\
    ret_struct.m_val = (in);\
    ret_struct.err = NULL;\
})

/**
 * Macro that creates a function definition for a pipe.
 * @param ret_struct_name The name of the return struct.
 * @param in_struct_name The name of the input struct.
 * @param array_type The type of the elements in the array.
 */
#define PIPE_DEF(ret_struct_name, in_struct, type)\
PIPE_RET_T(int_ret_t, int_arr_t, int);\
struct ret_struct_name in_struct ## _pipe(struct in_struct in, int funcs, ...)\
{\
    va_list args;\
    va_start(args, funcs);\
    struct ret_struct_name ret;\
    PIPE_RET_INIT(ret, in);\
    int choice = 0;\
    int j = 0;\
    bool to_free = false;\
    struct in_struct to_free_arr;\
    for (int i = 0; i < funcs; i++) {\
        choice = va_arg(args, int);\
        if (j > 0 && choice == MAP_PIPE || choice == FILTER_PIPE) {\
            to_free = true;\
            to_free_arr = ret.m_val;\
            if (ret.tag == S_VAL || ret.tag == BOOL_VAL) {\
                ARRAY_FREE(ret.m_val);\
                ret.err = "Cannot map or filter a single value";\
                goto err;\
            }\
        }\
        switch (choice) {\
            case MAP_PIPE: ;\
                type (*map_func)(type) = va_arg(args, type (*)(type));\
                ret.m_val = MAP(in_struct, ret.m_val, map_func);\
                ret.tag = M_VAL;\
                j++;\
                break;\
            case FOREACH_PIPE: ;\
                void (*foreach_func)(type) = va_arg(args, void (*)(type));\
                FOREACH(ret.m_val, foreach_func);\
                ret.tag = VOID_VAL;\
                break;\
            case FILTER_PIPE: ;\
                bool (*filter_func)(type) = va_arg(args, bool (*)(type));\
                ret.m_val = FILTER(in_struct, ret.m_val, filter_func);\
                ret.tag = M_VAL;\
                j++;\
                break;\
            case REDUCE_PIPE: ;\
                type acc = va_arg(args, type);\
                type (*reduce_func)(type, type) = va_arg(args, type (*)(type, type));\
                ret.s_val = REDUCE(type, ret.m_val, acc, reduce_func);\
                ret.tag = S_VAL;\
                break;\
            case ANY_PIPE: ;\
                bool (*any_pred)(type) = va_arg(args, bool (*)(type));\
                ret.pred = ANY_MATCH(ret.m_val, any_pred);\
                ret.tag = BOOL_VAL;\
                break;\
            case ALL_PIPE: ;\
                bool (*all_pred)(type) = va_arg(args, bool (*)(type));\
                ret.pred = ALL_MATCH(ret.m_val, all_pred);\
                ret.tag = BOOL_VAL;\
                break;\
            case NONE_PIPE: ;\
                bool (*none_pred)(type) = va_arg(args, bool (*)(type));\
                ret.pred = NONE_MATCH(ret.m_val, none_pred);\
                ret.tag = BOOL_VAL;\
                break;\
            case MAX_PIPE: ;\
                bool (*max_pred)(type, type) = va_arg(args, bool (*)(type, type));\
                ret.s_val = 0;\
                ARR_MAX(ret.m_val, ret.s_val, max_pred);\
                ret.tag = S_VAL;\
                break;\
            case MIN_PIPE: ;\
                bool (*min_pred)(type, type) = va_arg(args, bool (*)(type, type));\
                ret.s_val = 0;\
                ARR_MIN(ret.m_val, ret.s_val, min_pred);\
                ret.tag = S_VAL;\
                break;\
            default: ;\
                ret.err = "Invalid function";\
                goto err;\
        }\
    }\
    va_end(args);\
    return ret;\
    err:\
        ret.tag = ERR_VAL;\
        if (to_free)\
            ARRAY_FREE(to_free_arr);\
        return ret;\
}

#endif