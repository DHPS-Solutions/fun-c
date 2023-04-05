#ifndef MATCHING_H
#define MATCHING_H

#include <stdbool.h>

#include "common.h"
#include "../array.h"

/**
 * Macro to iterate and check if any elements match.
 * @param arr The array to iterate over.
 * @param func The function to call for each element.
 */
#define ANY_MATCH(arr, func) \
({\
    bool any = false;\
    int ITER = 0;\
    ARRAY_FOR((arr), ITER) {\
        if (func(ARRAY_GET((arr), ITER))) {\
            any = true;\
            break;\
        }\
    }\
    any;\
})

/**
 * Macro to iterate and check if all elements match.
 * @param arr The array to iterate over.
 * @param func The function to call for each element.
 */
#define ALL_MATCH(arr, func) \
({\
    bool any = true;\
    int ITER = 0;\
    ARRAY_FOR((arr), ITER) {\
        if (!func(ARRAY_GET((arr), ITER))) {\
            any = false;\
            break;\
        }\
    }\
    any;\
})

/**
 * Macro to iterate and check if no elements match.
 * @param arr The array to iterate over.
 * @param func The function to call for each element.
 */
#define NONE_MATCH(arr, func) \
({\
    bool any = true;\
    int ITER = 0;\
    ARRAY_FOR((arr), ITER) {\
        if (func(ARRAY_GET((arr), ITER))) {\
            any = false;\
            break;\
        }\
    }\
    any;\
})

/**
 * Macro to iterate and find the index of first element that matches.
 * @param arr The array to iterate over.
 * @param func The function to call for each element.
 */
#define FIND_INDEX(arr, func) \
({\
    int found = -1;\
    int ITER = 0;\
    ARRAY_FOR((arr), ITER) {\
        if (func(ARRAY_GET((arr), ITER))) {\
            found = ITER;\
            break;\
        }\
    }\
    found;\
})

#endif