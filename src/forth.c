#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forth.h"

Stack stack;
Word *dict = NULL;

void push(Cell x) {
	if (stack.top == STACK_MAX - 1) {
		printf("!overflow\n");
		exit(EXIT_FAILURE); // TODO better error handling
	}

	stack.array[stack.top++] = x;
}

Cell pop(void) {
	if (stack.top == 0) {
		printf("!underflow");
		exit(EXIT_FAILURE); // TODO
	}

	return stack.array[--stack.top];
}

void dict_add_c(const char *name, void (*fn)()) {
	Word *word = malloc(sizeof(*word));
	*word = (Word) {
		.next = dict,
		.name = name,
		.len = strlen(name),
		.is_c = true,
		.code.fn = fn,
	};
	dict = word;
}

Word *find(size_t len, const char *name) {
	for (Word *word = dict; word != NULL; word = word->next) {
		if (word->len == len && memcmp(word->name, name, len) == 0)
			return word;
	}

	return NULL;
}

void execute(Word *word) {
	if (word->is_c) {
		word->code.fn();
	} else {
		printf("TODO: not is_c words!\n");
	}
}

bool number(size_t len, const char *str, Cell *n) {
	char *buf = malloc(len+1);
	strcpy(buf, str);
	buf[len] = '\0';

	char *endptr;
	Cell m = strtol(buf, &endptr, 10);
	if (*endptr == '\0') {
		*n = m;
		return true;
	} else {
		return false;
	}
}
