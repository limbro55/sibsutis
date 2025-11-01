CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11 -I../include

LIB_SRCS := $(wildcard mc_*.c)
LIB_OBJS := $(LIB_SRCS:.c=.o)
LIB := libmyMemoryController.a

.PHONY: all clean rebuild

all: $(LIB)

$(LIB): $(LIB_OBJS)
	ar rcs $@ $^

$(LIB_OBJS): $(LIB_SRCS)
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f $(LIB)
	rm -f $(LIB_OBJS)

rebuild:  clean all
