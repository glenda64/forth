TARGET := forth

OBJ := ./obj
SRC := ./src

SRCS := $(shell find $(SRC) -name '*.c')
OBJS := $(SRCS:$(SRC)/%=$(OBJ)/%.o)

CC := clang
CFLAGS := -std=c99 -Wall -Wextra -Wpedantic -O2
LDFLAGS := -flto

$(TARGET): $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $(OBJS)

$(OBJ)/%.c.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean
clean:
	rm -r $(OBJ)
	rm $(TARGET)
