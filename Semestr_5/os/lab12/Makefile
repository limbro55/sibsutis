CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lrt -lpthread

all: 1 2 3 4 5

1: 1.c
	$(CC) $(CFLAGS) -o 1.out $< $(LDFLAGS)

2: 2.c
	$(CC) $(CFLAGS) -o 2.out $< $(LDFLAGS)

3: 3.c
	$(CC) $(CFLAGS) -o 3.out $< $(LDFLAGS)

4: 4.c
	$(CC) $(CFLAGS) -o 4.out $< $(LDFLAGS)

5: 5.c
	$(CC) $(CFLAGS) -o 5.out $< $(LDFLAGS)

run-1: 1
	./1.out

run-2: 2
	./2.out

run-3: 3
	./3.out

run-4: 4
	./4.out

run-5: 5
	./5.out

clean:
	rm -f *.out
