CC := gcc

SAT := $(wildcard *.sa)
SAT_TARGET := $(SAT:.sa=.o)

SRC := $(wildcard *.c)
SRC_TARGET := $(SRC:.c=.out)

.PHONY: all clean

all: $(SRC_TARGET) $(SAT_TARGET)

$(SRC_TARGET): $(SRC)
	$(CC) $^ -o $@

$(SAT_TARGET): $(SAT)
	./$(SRC_TARGET) sat $(SAT) $(SAT_TARGET)

clean:
	rm -f $(SRC_TARGET) $(SAT_TARGET)