#ifndef FILTER_H
#define FILTER_H

#include "common.h"
#include "../array.h"

/**
 * Macro to iterate and create a filter.
 * @param struct_type The type of the struct to return.
 * @param arr The array to iterate over.
 * @param func The function to call for each element.
 */
#define FILTER(struct_type, arr, func) \
({\
    struct struct_type filtered;\
    ARRAY_INIT(filtered);\
    int ITER = 0;\
    ARRAY_FOR((arr), ITER)\
        if (func(ARRAY_GET((arr), ITER)))\
            ARRAY_PUSH(filtered, ARRAY_GET((arr), ITER));\
    filtered;\
})

#endif