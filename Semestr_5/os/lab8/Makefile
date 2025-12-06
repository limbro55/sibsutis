CC = gcc
CFLAGS = -O2 -Wall -pthread

all: peterson2

peterson2: peterson2.c
	$(CC) $(CFLAGS) peterson2.c -o peterson2

run:
	./peterson2

clean:
	rm -f peterson2
