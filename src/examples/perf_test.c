#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../functions/lambda.h"
#include "../array.h"
#include "../pipe.h"

#define TEST_ARRAY_SIZE 100000
#define TEST_ITERATIONS 10000

// Function to print a split
void print_split(char *str)
{
    printf("========================================\n");
    printf("%s\n", str);
    printf("========================================\n");
}

// Goal: Create a pipe that does the following:
// 1. Filter out all even numbers
// 2. Map all numbers to themselves * 2
// 3. Reduce to the sum of all numbers
double test_one_loop_fmr()
{
    // Create an int array
    ARRAY_T(int_arr_t, int);
    struct int_arr_t arr;
    ARRAY_INIT(arr);
    for (int i = 0; i < TEST_ARRAY_SIZE; i++)
        ARRAY_PUSH(arr, i);

    // Manually do the functions

    clock_t t1 = clock();
    int i = 0;
    int sum = 0;
    ARRAY_FOR(arr, i)
        if (ARRAY_GET(arr, i) % 2 == 0)
            sum += ARRAY_GET(arr, i) * 2;
    t1 = clock() - t1;
    
    // Create a pipe
    PIPE_DEF(int_ret_t, int_arr_t, int);

    clock_t t2 = clock();
    // Pipe functions together and reduce to sum
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
    );
    t2 = clock() - t2;

    ARRAY_FREE(arr);

    return ((((double)t2) - ((double)t1)) / ((double)t1) * 100.0);
}

double test_three_loop_fmr()
{
    // Create an int array
    ARRAY_T(int_arr_t, int);
    struct int_arr_t arr;
    ARRAY_INIT(arr);
    for (int i = 0; i < TEST_ARRAY_SIZE; i++)
        ARRAY_PUSH(arr, i);

    // Manually do the functions

    clock_t t1 = clock();
    int i = 0;
    int sum = 0;
    struct int_arr_t filtered;
    ARRAY_INIT(filtered);
    ARRAY_FOR(arr, i)
        if (ARRAY_GET(arr, i) % 2 == 0)
            ARRAY_PUSH(filtered, ARRAY_GET(arr, i));
    
    struct int_arr_t mapped;
    ARRAY_INIT(mapped);
    ARRAY_FOR(filtered, i)
        ARRAY_PUSH(mapped, ARRAY_GET(filtered, i) * 2);
    
    ARRAY_FREE(filtered);

    ARRAY_FOR(mapped, i)
        sum += ARRAY_GET(mapped, i);
    
    ARRAY_FREE(mapped);
    t1 = clock() - t1;
    
    // Create a pipe
    PIPE_DEF(int_ret_t, int_arr_t, int);

    clock_t t2 = clock();
    // Pipe functions together and reduce to sum
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
    );
    t2 = clock() - t2;

    ARRAY_FREE(arr);

    return ((((double)t2) - ((double)t1)) / ((double)t1) * 100.0);
}

double test_filter_map_filter_map_max()
{
    ARRAY_T(long_arr_t, long);
    struct long_arr_t arr;
    ARRAY_INIT(arr);
    for (long i = 0; i < TEST_ARRAY_SIZE; i++)
        ARRAY_PUSH(arr, (long) rand());

    // Manually do the functions

    clock_t t1 = clock();
    int i = 0;
    long max = 0;
    struct long_arr_t filtered;
    ARRAY_INIT(filtered);
    ARRAY_FOR(arr, i)
        if (ARRAY_GET(arr, i) % 2 == 0)
            ARRAY_PUSH(filtered, ARRAY_GET(arr, i));
    
    struct long_arr_t mapped;
    ARRAY_INIT(mapped);
    ARRAY_FOR(filtered, i)
        ARRAY_PUSH(mapped, ARRAY_GET(filtered, i) * 2);
    
    ARRAY_FREE(filtered);

    ARRAY_INIT(filtered);
    ARRAY_FOR(mapped, i)
        if (ARRAY_GET(mapped, i) % 3 == 0)
            ARRAY_PUSH(filtered, ARRAY_GET(mapped, i));
    
    ARRAY_FREE(mapped);

    ARRAY_INIT(mapped);
    ARRAY_FOR(filtered, i)
        ARRAY_PUSH(mapped, ARRAY_GET(filtered, i) * 5);
    
    ARRAY_FREE(filtered);

    ARRAY_FOR(mapped, i)
        if (ARRAY_GET(mapped, i) > max)
            max = ARRAY_GET(mapped, i);
    
    ARRAY_FREE(mapped);
    t1 = clock() - t1;

    // Create a pipe
    PIPE_DEF(long_ret_t, long_arr_t, long);

    clock_t t2 = clock();
    // Pipe functions together and reduce to sum
    struct long_ret_t piped = long_arr_t_pipe(arr, 5, 
        FILTER_PIPE, LAMBDA(bool, (long e), {
            return e % 2 == 0;
        }),
        MAP_PIPE, LAMBDA(long, (long e), {
            return e * 2;
        }),
        FILTER_PIPE, LAMBDA(bool, (long e), {
            return e % 3 == 0;
        }),
        MAP_PIPE, LAMBDA(long, (long e), {
            return e * 5;
        }),
        MAX_PIPE, LAMBDA(bool, (long max, long e), {
            return max > e;
        })
    );
    t2 = clock() - t2;

    ARRAY_FREE(arr);

    return ((((double)t2) - ((double)t1)) / ((double)t1) * 100.0);
}

int main()
{
    print_split("Test 1: Filter, map, and reduce");
    printf("Test array size: %d test iterations: %d\n", TEST_ARRAY_SIZE, TEST_ITERATIONS);
    printf("Optimal solution for std version in this test.\n");
    srand(time(NULL));
    double diff = 0;
    for (int i = 0; i < TEST_ITERATIONS; i++)
        diff += test_one_loop_fmr() / ((double) TEST_ITERATIONS);
    printf("Average difference: %f percent (%s)\n" , diff, diff > 0 ? "functional is slower" : "std is slower");
    printf("\n");

    print_split("Test 2: Filter, map, and reduce");
    printf("Test array size: %d test iterations: %d\n", TEST_ARRAY_SIZE, TEST_ITERATIONS);
    printf("Un-optimal solution for std version in this test.\n");
    srand(time(NULL));
    diff = 0;
    for (int i = 0; i < TEST_ITERATIONS; i++)
        diff += test_three_loop_fmr() / ((double) TEST_ITERATIONS);
    printf("Average difference: %f percent (%s)\n" , diff, diff > 0 ? "functional is slower" : "std is slower");
    printf("\n");

    print_split("Test 3: Filter, map, filter, map, and max");
    printf("Test array size: %d test iterations: %d\n", TEST_ARRAY_SIZE, TEST_ITERATIONS);
    printf("Un-optimal solution for std version in this test.\n");
    srand(time(NULL));
    diff = 0;
    for (int i = 0; i < TEST_ITERATIONS; i++)
        diff += test_filter_map_filter_map_max() / ((double) TEST_ITERATIONS);
    printf("Average difference: %f percent (%s)\n" , diff, diff > 0 ? "functional is slower" : "std is slower");
    printf("\n");

    return 0;
}