#ifndef FOREACH_H
#define FOREACH_H

#include "common.h"
#include "../array.h"

/**
 * Macro to create a consumer foeach loop.
 * @param arr The array to iterate over.
 * @param func The function to call for each element.
 */
#define FOREACH(arr, func)\
({\
    int ITER = 0;\
    ARRAY_FOR((arr), ITER)\
        func(ARRAY_GET((arr), ITER));\
})

#endif