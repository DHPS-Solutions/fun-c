#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../functions/lambda.h"

int main()
{
    // Lambda functions
    
    int (*add)(int, int) = LAMBDA(int, (int a, int b), {
        return a + b;
    });

    printf("Sum of 1 + 2 = %d\n", add(1, 2));

    char *(*to_upper)(char *) = LAMBDA(char *, (char *s), {
        char *str = strdup(s);
        for (int i = 0; i < strlen(str); i++) {
            if((str[i] > 96) && (str[i] < 123)) str[i] ^=0x20;
        }
        
        return str;
    });

    printf("String to uppercase: %s\n", to_upper("hello world!"));
    
    return 0;    
}