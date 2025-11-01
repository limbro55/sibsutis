CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11 -I../include

LIB_SRCS := $(wildcard bc_*.c)
LIB_OBJS := $(LIB_SRCS:.c=.o)
LIB_OBJS += ../myTerm/mt_terminal.o
LIB := libmyBigChars.a

.PHONY: all clean rebuild

all: $(LIB)

$(LIB): $(LIB_OBJS)
	ar rcs $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(LIB) $(LIB_OBJS)

rebuild: clean all
