#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../functions/lambda.h"
#include "../pipe.h"

int main()
{
    // Create an array
    ARRAY_T(int_arr_t, int);
    struct int_arr_t arr;
    ARRAY_INIT(arr);
    for (int i = 4; i < 10; i++)
        ARRAY_PUSH(arr, i);

    // Create a pipe
    PIPE_DEF(int_ret_t, int_arr_t, int);

    // Pipe functions together
    struct int_ret_t piped = int_arr_t_pipe(arr, 3, 
        FILTER_PIPE, LAMBDA(bool, (int e), {
            return e % 2 == 0;
        }),
        MAP_PIPE, LAMBDA(int, (int e), {
            return e * 2;
        }),
        REDUCE_PIPE, 0, LAMBDA(int, (int acc, int e), {
            return acc + e;
        })
        // FOREACH_PIPE, LAMBDA(void, (int e), {
        //     printf("Element: '%d'\n", e);
        // })
    );

    printf("Result: '%d'\n", piped.s_val);
    
    // Free the array
    ARRAY_FREE(arr);

    return 0;
}