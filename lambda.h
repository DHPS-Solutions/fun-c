/**
 * Authored by Callum Gran 2023.
 * Simple macro's to allow for lambda functions in C.
 */

#ifndef LAMBDA_H
#define LAMBDA_H

#include <stdlib.h>
#include <stdarg.h>

#define __lambda_fn__(return_type, func_args, func_body)\
({\
    return_type __fn_t__ func_args\
    func_body\
    &__fn_t__;\
})

#define LAMBDA(return_type, func_args, func_body, ...)\
    (return_type) __lambda_fn__(return_type, func_args, func_body)(__VA_ARGS__)

#endif