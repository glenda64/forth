#ifndef FORTH_H
#define FORTH_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

enum {
    STACK_MAX = 256,
    WORD_MAX = 32,
    LINE_MAX = 4096,
};

typedef intptr_t Cell;

typedef struct {
    size_t top;
    Cell array[STACK_MAX];
} Stack;

typedef struct {
    void (**thread)(void);
    size_t len;
} Thread;

typedef struct Word {
    struct Word *next;
    const char *name;
    size_t name_len;
    bool is_c;
    union {
        Thread thread;
        void (*fn)(void);
    } code;
} Word;

extern Stack stack;
extern Word *dict;

void push(Cell);
Cell pop(void);

void dict_add_c(const char *, void (*)(void));
void dict_add_core(void);

Word *find(size_t, const char *);
void execute(Word *);
bool number(size_t, const char *, Cell *);

#endif
