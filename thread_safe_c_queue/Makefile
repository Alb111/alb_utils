# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -fsanitize=thread

# Source files and objects
SRC = main.c queue.c
OBJ = $(SRC:.c=.o)

# Final executable
program: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rule: how to build .o from .c
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Cleanup
clean:
	rm -f $(OBJ) program
