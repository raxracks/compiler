#include "std.h"
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int divide(int a, int b) {
    return a / b;
}

int multiply(int a, int b) {
    return a * b;
}

void print_str(const char* s) {
    printf("%s\n", s);
}

void print_num(int n) {
    printf("%d\n", n);
}