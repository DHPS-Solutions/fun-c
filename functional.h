/**
 * Authored by Callum Gran 2023.
 * Collection of macros for functional programming.
 */
#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <stdlib.h>
#include <stdbool.h>

/**
 * Enums to hold the different types of functions.
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

#define BOOL_VAL 1
#define INT_VAL 2
#define ARR_VAL 3
#define ERR_VAL 255

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

struct gen_array_t {
    void **arr;
    int len;
};

/**
 * Macro to create a consumer foeach loop.
 * @param type The type of the array.
 * @param arr The array to iterate over.
 * @param func The function to call for each element.
 */
#define GEN_FOREACH(type, gen_array, func) \
({\
    for (int i = 0; i < gen_array.len; i++) { \
        type e = *(type *)gen_array.arr[i]; \
        func(e); \
    }\
})

#endif