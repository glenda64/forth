#include <stdio.h>
#include "forth.h"

static bool isblank(char c) {
	return c == ' ' || c == '\t' || c == '\n';
}

int main(void) {
	dict_add_core();

	for (;;) {
		char c = getc(stdin);
		size_t idx = 0;
		char buffer[WORD_MAX];

		while (isblank(c)) c = getc(stdin);
		while (!isblank(c) && idx < WORD_MAX) {
			buffer[idx++] = c;
			c = getc(stdin);
		}

		Word *word = find(idx, buffer);

		if (word == NULL) {
			Cell n = 0;
			if (!number(idx, buffer, &n)) {
				printf("?%.*s\n", (int)idx, buffer);
			} else {
				push(n);
			}
		} else {
			execute(word);
		}
	}
}
