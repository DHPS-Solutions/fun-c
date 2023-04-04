/**
 * Authored by Callum Gran 2023.
 * Simple macro to allow for lambda functions in C.
 */

#ifndef LAMBDA_H
#define LAMBDA_H

/**
 * Macro to create a lambda function.
 * @param return_type The return type of the lambda function.
 * @param func_args The arguments of the lambda function.
 * @param func_body The body of the lambda function.
 * @param ... The arguments to pass to the lambda function.
 * @return The return value of the lambda function.
 */
#define LAMBDA(return_type, func_args, func_body, ...)\
({\
    return_type __fn_t__ func_args\
    func_body\
    &__fn_t__;\
})(__VA_ARGS__)

#endif