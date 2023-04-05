#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "functional.h"
#include "int_functional.h"

void print_int_array(int *arr, int len) {
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

int main(int argc, char *argv[]) 
{
    // Lambda functions
    int (*combine_two)(int, int) = LAMBDA(int, (int a, int b), {
        return a + b; 
    });

    printf("%d\n", combine_two(1, 2));
    
    char *(*to_upper)(char *) = LAMBDA(char *, (char *s), {
        char *str = strdup(s);
        for (int i = 0; i < strlen(str); i++) {
            if((str[i] > 96) && (str[i] < 123)) str[i] ^=0x20;
        }
        
        return str;
    });

    printf("%s\n", to_upper("hello world!"));

    // Anonymous functions
    printf("%s\n", ANON(char *, (char *s), { 
        return s; 
    }, "HELLO WORLD!"));

    printf("%d\n", ANON(int, (int a, int b, int c), { 
        return a + b + c;
    }, 43, 42, 44));

    printf("%f\n", ANON(double, (double a, float b, int c), { 
        return a + b + c;
    }, 99.2, 42.3, 44));

    // For each
    struct int_array_t arr = {
        .arr = (int []) { 1, 2, 3, 4, 5 },
        .len = 5
    };

    void (*print_int)(int) = LAMBDA(void, (int i), {
        printf("%d ", i);
    });

    FOREACH(arr, print_int);

    printf("\n");

    // Map
    int *mapped = INT_MAP(arr, LAMBDA(int, (int i), {
        return i * 2;
    })).arr;

    printf("Mapped: ");
    print_int_array(mapped, 5);
    
    free(mapped);

    // Filter
    bool (*filter_even)(int) = LAMBDA(bool, (int i), {
        return i % 2 == 0;
    });

    struct int_array_t filtered = INT_FILTER(arr, filter_even);

    printf("Filtered: ");
    print_int_array(filtered.arr, filtered.len);

    free(filtered.arr);

    // Integer pipe
    int (*add_one)(int) = LAMBDA(int, (int i), {
        return i + 1;
    });

    int (*add_two)(int) = LAMBDA(int, (int i), {
        return i + 2;
    });

    int (*add_three)(int) = LAMBDA(int, (int i), {
        return i + 3;
    });

    printf("Piped: %d\n", int_pipe(1, add_one, add_two, add_three));

    // Reduce
    int (*sum)(int, int) = LAMBDA(int, (int a, int b), {
        return a + b;
    });

    printf("Reduced: %d\n", INT_REDUCE(arr, sum));

    // Any match
    bool (*is_even)(int) = LAMBDA(bool, (int i), {
        return i % 2 == 0;
    });

    printf("Any even: %s\n", INT_ANY(arr, is_even) ? "true" : "false");

    // All match
    printf("All even: %s\n", INT_ALL(arr, is_even) ? "true" : "false");

    // None match
    printf("None even: %s\n", INT_NONE(arr, is_even) ? "true" : "false");

    // Max value
    printf("Max value: %d\n", INT_MAX(arr));

    // Min value
    printf("Min value: %d\n", INT_MIN(arr));

    // Sorted
    printf("Sorted: %s\n", INT_IS_SORTED(arr) ? "true" : "false");

    // Is empty
    printf("Is empty: %s\n", int_array_pipe(arr, 1, IS_EMPTY_PIPE).pred ? "true" : "false");

    // Is not empty
    printf("Is not empty: %s\n", int_array_pipe(arr, 1, IS_NOT_EMPTY_PIPE).pred ? "true" : "false");

    // Piping from map to foreach
    printf("Piping int array\n");

    struct int_pipe_opt_t int_arr_ans = int_array_pipe(arr, 5,
        MAP_PIPE, add_two,
        FILTER_PIPE, filter_even,
        MAP_PIPE, add_one,
        FOREACH_PIPE, print_int,
        REDUCE_PIPE, sum
    );

    printf("\n");

    if (int_arr_ans.tag == ERR_VAL) {
        printf("Error: %s\n", int_arr_ans.err);
    } else {
        printf("Answer of full function = %d\n", int_arr_ans.m_value.arr[0]);
    }

    // Piping from map to single to filter
    printf("Piping int array\n");

    struct int_pipe_opt_t int_arr_ans2 = int_array_pipe(arr, 4,
        MAP_PIPE, add_three,
        FOREACH_PIPE, print_int,
        REDUCE_PIPE, sum,
        FILTER_PIPE, filter_even
    );

    printf("\n");

    if (int_arr_ans2.tag == ERR_VAL) {
        printf("Error: %s\n", int_arr_ans2.err);
    } else {
        printf("Answer of full function = %d\n", int_arr_ans2.m_value.arr[0]);
    }

    // Generic for each
    char * hello = "hello";
    char * world = "world";
    char * exclamation = "!";
    struct gen_array_t str_generic_arr = {
        .arr = (void *[]) { &hello, &world, &exclamation },
        .len = 3
    };

    void (*print_str)(char *) = LAMBDA(void, (char *s), {
        printf("%s ", s);
    });

    GEN_FOREACH(char *, str_generic_arr, print_str);

    int one = 1;
    int two = 2;
    int three = 3;
    struct gen_array_t int_generic_arr = {
        .arr = (void *[]) { &one, &two, &three },
        .len = 3,
    };

    GEN_FOREACH(int, int_generic_arr, print_int);

    return 0;
}