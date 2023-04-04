#include <stdlib.h>
#include <stdio.h>

#include "functional.h"

int main(int argc, char *argv[]) 
{
    printf("%s\n", ANON(char *, (char *s), { return s; }, "HELLO WORLD!"));
    printf("%d\n", ANON(int, (int a, int b, int c), { return a + b + c; }, 43, 42, 44));
    printf("%f\n", ANON(double, (double a, float b, int c), { return a + b + c; }, 99.2, 42.3, 44));
}