#ifndef REDUCE_H
#define REDUCE_H

#include "common.h"
#include "../array.h"

/**
 * Macro to iterate and create a reduce.
 * @param acctype The type of the accumulator.
 * @param arr The array to iterate over.
 * @param init_val The initial value of the accumulator.
 * @param func The function to apply to each element.
 */
#define REDUCE(acctype, arr, init_val, func) \
({\
    acctype acc = init_val;\
    int ITER = 0;\
    ARRAY_FOR((arr), ITER)\
        acc = func(acc, ARRAY_GET((arr), ITER));\
    acc;\
})

#endif