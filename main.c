#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "functional.h"

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
    struct array_t arr = {
        .arr = (int []) { 1, 2, 3, 4, 5 },
        .len = 5
    };

    void (*print_int)(int) = LAMBDA(void, (int i), {
        printf("%d ", i);
    });

    FOREACH(arr, print_int);

    printf("\n");

    // Map
    int *mapped = MAP(arr, LAMBDA(int, (int i), {
        return i * 2;
    })).arr;

    printf("Mapped: ");
    print_int_array(mapped, 5);
    
    free(mapped);

    // Pipe
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

    return 0;
}