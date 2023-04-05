#ifndef MAP_H
#define MAP_H

#include "common.h"
#include "../array.h"

/**
 * Macro to iterate and create a map.
 * @param struct_type The type of the struct to return.
 * @param arr The array to iterate over.
 * @param func The function to call for each element.
 */
#define MAP(struct_type, arr, func)\
({\
    struct struct_type mapped;\
    ARRAY_INIT(mapped);\
    int ITER = 0;\
    ARRAY_FOR((arr), ITER)\
        ARRAY_PUSH(mapped, func(ARRAY_GET((arr), ITER)));\
    mapped;\
})

#endif