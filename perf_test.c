#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "int_functional.h"

#define TEST_TIMES 100
#define TEST_SIZE 1000000

double test()
{
    int arr_func[TEST_SIZE] = {0};
    int arr_std[TEST_SIZE] = {0};
    for (int i = 0; i < TEST_SIZE; i++) {
        int random = (int) rand();
        arr_func[i] = random;
        arr_std[i] = random;
    }

    struct int_array_t array = {
        .arr = arr_func,
        .len = TEST_SIZE
    };

    struct int_array_t array2 = {
        .arr = arr_std,
        .len = TEST_SIZE
    };

    int (*map_func)(int) = LAMBDA(int, (int x), {
        return x * 3;
    });

    bool (*filt_func)(int) = LAMBDA(bool, (int x), {
        return x % 2 == 0;
    });

    int (*reduce_func)(int, int) = LAMBDA(int, (int a, int b), {
        return a + b;
    });

    // Time the standard method
    clock_t t1 = clock();
    for (int i = 0; i < TEST_SIZE; i++) {
        array2.arr[i] = map_func(array2.arr[i]);
    }
    struct int_array_t new_arr; 
    new_arr.arr = malloc(sizeof(int) * (array2.len));
    int j = 0;
    for (int i = 0; i < TEST_SIZE; i++) {
        if (filt_func(array2.arr[i])) {
            new_arr.arr[j++] = array2.arr[i];
        }
    }
    new_arr.len = j;
    new_arr.arr = realloc(new_arr.arr, sizeof(int) * j);
    int val = 0;
    for (int i = 0; i < new_arr.len; i++) {
        val = reduce_func(val, new_arr.arr[i]);
    }
    t1 = clock() - t1;

    // Time the functional method
    clock_t t2 = clock();
    struct int_array_option_t piped = int_array_pipe(array, 3, 
        MAP_PIPE, map_func,
        FILTER_PIPE, filt_func,
        REDUCE_PIPE, reduce_func
    );
    t2 = clock() - t2;

    // printf("Normal method: Time: %f seconds, Value: %d\n" , ((double)t1)/CLOCKS_PER_SEC, val);
    // printf("Functional method: Time: %f seconds, Value: %d\n" , ((double)t2)/CLOCKS_PER_SEC, piped.s_value);
    // printf("Difference: %f seconds (func is slower)\n" , ((double)t2)/CLOCKS_PER_SEC - ((double)t1)/CLOCKS_PER_SEC);

    double diff_per = ((((double)t2) - ((double)t1)) / ((double)t1) * 100.0);

    // printf("Difference: %f percent (func is slower)\n" , diff_per);

    return diff_per;
}

int main()
{
    srand(time(NULL));
    double diff = 0;
    for (int i = 0; i < TEST_TIMES; i++) {
        diff += test();
    }
    printf("Average difference: %f percent (func is slower)\n" , diff / ((double) TEST_TIMES));
    return 0;
}