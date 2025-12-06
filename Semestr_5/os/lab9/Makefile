CC = gcc
CFLAGS = -O2 -Wall -pthread

N ?= 5

all: petersonN

petersonN: petersonN.c
	$(CC) $(CFLAGS) -DN=$(N) petersonN.c -o petersonN

run:
	./petersonN

clean:
	rm -f petersonN
