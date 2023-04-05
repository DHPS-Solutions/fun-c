#ifndef LIMITS_FUNCTIONS_H
#define LIMITS_FUNCTIONS_H

#include "common.h"
#include "../array.h"

/**
 * Macro to iterate and find the max element.
 * @param max The variable to store the max element.
 * @param arr The array to iterate.
 * @param func The function to compare the elements.
 */
#define ARR_MAX(arr, max, func) \
({\
    int ITER = 0;\
    ARRAY_FOR((arr), ITER)\
        if (func(ARRAY_GET((arr), ITER), (max)))\
            (max) = ARRAY_GET((arr), ITER);\
    (max);\
})

/**
 * Macro to iterate and find the min element.
 * @param min The variable to store the min element.
 * @param arr The array to iterate.
 * @param func The function to compare the elements.
 */
#define ARR_MIN(arr, min, func) \
({\
    int ITER = 0;\
    ARRAY_FOR((arr), ITER)\
        if (func((min), ARRAY_GET((arr), ITER)))\
            (min) = ARRAY_GET((arr), ITER);\
    (min);\
})

#endif