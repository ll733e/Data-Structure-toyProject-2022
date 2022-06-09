CC = gcc
CFLAGS = -O -g -Wall -Wextra -pedantic-errors -DTESTS_MAIN

CPPC = g++
CPPFLAGS = -O0 -g -Wall -Wextra -DTESTS_MAIN

all: test testcpp test_hash_collisions

.PHONY: test testcpp test_hash_collisions
test: tests.c parson.c
	$(CC) $(CFLAGS) -o $@ tests.c parson.c
	./$@

clean:
	rm -f test *.o