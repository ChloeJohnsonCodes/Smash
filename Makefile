CFLAGS = -Wall -std=c99 -g -o0

all: rules.d smash

smash: smash.o
	gcc $(CFLAGS) smash.c -o smash

rules.d: $(wildcard *.c) $(wildcard *.h)
	gcc -MM $(wildcard *.c) >rules.d

-include rules.d

clean:
	rm -f *.o smash rules.d