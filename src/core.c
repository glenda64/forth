#include <stdio.h>
#include <string.h>
#include "forth.h"

static void add(void)      { push(pop() + pop()); }
static void subtract(void) { push(pop() - pop()); }
static void multiply(void) { push(pop() * pop()); }
static void divide(void)   { push(pop() / pop()); }
static void print(void)    { printf("%ld ", pop()); }
static void cr(void)       { printf("\n"); }

void dict_add_core(void) {
	dict_add_c("+", add);
	dict_add_c("-", subtract);
	dict_add_c("*", multiply);
	dict_add_c("/", divide);
	dict_add_c(".", print);
	dict_add_c("cr", cr);
}
