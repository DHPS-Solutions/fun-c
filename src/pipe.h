#ifndef PIPE_H
#define PIPE_H

#include "lambda.h"

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
 * @param INT_VAL The integer value.
 * @param ARR_VAL The array value.
 * @param ERR_VAL The error value.
 */
#define BOOL_VAL 1
#define INT_VAL 2
#define ARR_VAL 3
#define ERR_VAL 255

/**
 * Macro that creates a new return value for a pipe.
 * @param struct_name The name of the struct.
 * @param type The type of the array.
*/
#define PIPE_RET(struct_name, array_type, type)\
struct struct_name {\
    uint8_t tag;\
    bool pred;\
    item_type s_val;\
    struct array_type *m_val;\
    char *err;\
};

/**
 * Macro that creates a function definition for a pipe.
 * @param ret_struct_name The name of the return struct.
 * @param in_struct_name The name of the input struct.
 */
#define PIPE(ret_struct_name, in_struct_name)\
struct ret_struct_name in_struct_name##pipe(struct in_struct_name *in, int pipes, ...);

#endif