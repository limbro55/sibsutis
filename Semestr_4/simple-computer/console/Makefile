CC := gcc
CFLAGS := -std=c11

TARGET := console.out
SRCS := console.c print.c font.c handleKeyPress.c checkTerminal.c consoleHelpers.c
OBJS := $(SRCS:.c=.o)

LDFLAGS = -L../mySimpleComputer -L../myTerm -L../myBigChars -L../myReadKey \
					-L/usr/lib -L../myCuAlu -L../myMemoryController
LIBS = -lmySimpleComputer -lmyTerm -lmyBigChars -lmyReadKey -lmyCuAlu -lmyMemoryController

ifeq ($(debug), 1)
	CFLAGS += -g
endif

.PHONY: all run clean rebuild

all: $(TARGET)

run:
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ $(LDFLAGS) $(LIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I../include

clean:
	rm -f $(OBJS) $(TARGET) *.bin

rebuild: clean all
