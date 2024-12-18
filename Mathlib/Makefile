CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = src
OBJDIR = obj
INCDIR = Includes

compile:
	$(CC) $(CFLAGS) mathlib_test.c matrix.c vectors.c -I $(INCDIR) -lm -o mathtest

clean:
	rm -rf mathtest

fclean: clean

re: fclean compile
