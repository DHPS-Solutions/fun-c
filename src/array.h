#ifndef ARRAY_H
#define ARRAY_H

/**
 * Generic macro-based array implementation.
 * Authored by Callum Gran 5.4.2023.
 */

/**
 * The standard size of an array.
 */
#define STD_SIZE 32

/**
 * Macro to create an array struct.
 * @param struct_name The name of the struct.
 * @param type The type of the array.
 */
#define ARRAY_T(struct_name, type)\
struct struct_name {\
    type *vals;\
    size_t len;\
    size_t cap;\
};

/**
 * Macro to initialise an array.
 * @param array The array to initialise.
 */
#define ARRAY_INIT(array)\
({\
    (array).vals = malloc(sizeof(*(array).vals) * STD_SIZE);\
    (array).len = 0;\
    (array).cap = STD_SIZE;\
})

/**
 * Macro to free an array.
 * @param array The array to free.
 */
#define ARRAY_FREE(array)\
({\
    free((array).vals);\
    (array).vals = NULL;\
    (array).len = 0;\
    (array).cap = 0;\
})

/**
 * Macro to resize an array if needed.
 * @param array The array to resize.
 */
#define ARRAY_RESIZE_IF_NEEDED(array)\
({\
    if ((array).len == (array).cap) {\
        (array).cap <<= 1;\
        (array).vals = realloc((array).vals, sizeof(*(array).vals) * (array).cap);\
    }\
})

/**
 * Macro to resize an array down if needed.
 * @param array The array to resize.
 */
#define ARRAY_RESIZE_DOWN_IF_NEEDED(array)\
({\
    if ((array).len == (array).cap >> 2) {\
        (array).cap >>= 1;\
        (array).vals = realloc((array).vals, sizeof(*(array).vals) * (array).cap);\
    }\
})

/**
 * Macro to push a value to the end of an array.
 * @param array The array to push to.
 * @param value The value to push.
 */
#define ARRAY_PUSH(array, value)\
({\
    ARRAY_RESIZE_IF_NEEDED(array);\
    *((array).vals + (array).len++) = value;\
})

/**
 * Macro to pop a value from the end of an array.
 * @param array The array to pop from.
 */
#define ARRAY_POP(array)\
({\
    ARRAY_RESIZE_DOWN_IF_NEEDED(array);\
    *((array).vals + --(array).len);\
})

/**
 * Macro to insert a value into an array.
 * @param array The array to insert into.
 * @param index The index to insert at.
 * @param value The value to insert.
 */
#define ARRAY_GET(array, index)\
({\
    *((array).vals + index);\
})

/**
 * Macro to get a value from an array.
 * @param array The array to get from.
 * @param index The index to get from.
 * @param value The value to set.
 */
#define ARRAY_SET(array, index, value)\
({\
    *((array).vals + index) = value;\
})

/**
 * Macro to insert a value into an array.
 * @param array The array to insert into.
 * @param index The index to insert at.
 * @param value The value to insert.
 */
#define ARRAY_LEN(array)\
({\
    (array).len;\
})

/**
 * Macro to get the capacity of an array.
 * @param array The array to get the capacity of.
 */
#define ARRAY_CAP(array)\
({\
    (array).cap;\
})

/**
 * Macro to clear an array.
 * @param array The array to clear.
 */
#define ARRAY_CLEAR(array)\
({\
    (array).len = 0;\
    (array).cap = STD_SIZE;\
    (array).vals = realloc((array).vals, sizeof(*(array).vals) * (array).cap);\
})

/**
 * Macro to create a for loop for an array.
 * @param array The array to create the for loop for.
 */
#define ARRAY_FOR(array, i)\
    for ((i) = 0; (i) < (array).len; (i)++)\

#endif