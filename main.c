#include <stdlib.h>
#include <stdio.h>

#include "lambda.h"

int main(int argc, char *argv[]) 
{
    printf("%s\n", LAMBDA(char *, (char *s), { return s; }, "HELLO WORLD!"));
    printf("%d\n", LAMBDA(int, (int a, int b, int c), { return a + b + c; }, 43, 42, 44));
    printf("%f\n", LAMBDA(double, (double a, float b, int c), { return a + b + c; }, 99.2, 42.3, 44));
}