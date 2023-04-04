#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "functional.h"

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
}