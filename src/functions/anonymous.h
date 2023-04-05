#ifndef ANONYMOUS_FUNCTION_H
#define ANONYMOUS_FUNCTION_H

#include "lambda.h"

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

#endif