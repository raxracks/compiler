#include <stdio.h>

#ifndef __RUNTIME_H__
#define __RUNTIME_H__

int add(int a, int b);
int subtract(int a, int b);
int divide(int a, int b);
int multiply(int a, int b);

void print_str(const char* s);
void print_num(int n);

#endif