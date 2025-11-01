#ifndef MY_TERM_H
#define MY_TERM_H

#include <stdio.h>
#include <unistd.h>

#define BORDER_SIZE 1

#define MEMORY_POS_X BORDER_SIZE
#define MEMORY_POS_Y BORDER_SIZE + 1
#define MEMORY_HEIGHT 13
#define MEMORY_WIDTH (10 * 6) + BORDER_SIZE

#define PADDING 2
#define ACCUMULATOR_POS_X (MEMORY_POS_X + MEMORY_WIDTH + BORDER_SIZE + PADDING)
#define ACCUMULATOR_POS_Y (MEMORY_POS_Y)
#define ACCUMULATOR_HEIGHT 1
#define ACCUMULATOR_WIDTH 21 + BORDER_SIZE

#define FLAGS_POS_X                                                           \
  (ACCUMULATOR_POS_X + ACCUMULATOR_WIDTH + BORDER_SIZE + PADDING)
#define FLAGS_POS_Y (MEMORY_POS_Y)
#define FLAGS_HEIGHT 1
#define FLAGS_WIDTH 15 + BORDER_SIZE

#define COUNTERS_POS_X (ACCUMULATOR_POS_X)
#define COUNTERS_POS_Y (FLAGS_POS_Y + ACCUMULATOR_HEIGHT + BORDER_SIZE * 2)
#define COUNTERS_WIDTH (ACCUMULATOR_WIDTH)
#define COUNTERS_HEIGHT 1

#define CMD_PADDING 5
#define CMD_POS_X (FLAGS_POS_X + CMD_PADDING)
#define CMD_POS_Y (COUNTERS_POS_Y)
#define CMD_WIDTH (FLAGS_WIDTH - CMD_PADDING)
#define CMD_HEIGHT 1

#define BIG_CELL_POS_X (COUNTERS_POS_X - PADDING)
#define BIG_CELL_POS_Y (COUNTERS_POS_Y + COUNTERS_HEIGHT + 3)
#define BIG_CELL_WIDTH (COUNTERS_WIDTH + CMD_WIDTH + BORDER_SIZE * 2 + 8 + 1)
#define BIG_CELL_HEIGHT 5

#define IO_POS_X (COUNTERS_POS_X - PADDING)
#define IO_POS_Y (BIG_CELL_POS_Y + BIG_CELL_HEIGHT + 5)
#define IO_WIDTH 13
#define IO_HEIGHT 6

#define EDIT_POS_X MEMORY_POS_X
#define EDIT_POS_Y (MEMORY_POS_Y + MEMORY_HEIGHT + BORDER_SIZE)
#define EDIT_HEIGHT 2
#define EDIT_WIDTH (MEMORY_WIDTH - BORDER_SIZE)

#define CACHE_POS_X EDIT_POS_X
#define CACHE_POS_Y (EDIT_POS_Y + EDIT_HEIGHT + BORDER_SIZE)
#define CACHE_HEIGHT 5
#define CACHE_WIDTH EDIT_WIDTH + 4

#define INTERFACE_WIDTH (FLAGS_POS_X + FLAGS_WIDTH)
#define INTERFACE_HEIGHT (CACHE_POS_Y + CACHE_HEIGHT + BORDER_SIZE)

enum Colors
{
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
};

int mt_clrscr (void);
int mt_gotoXY (int x, int y);
int mt_getscreensize (int *rows, int *cols);
int mt_setfgcolor (enum Colors color);
int mt_setbgcolor (enum Colors color);
int mt_setdefaultcolor (void);
int mt_setcursorvisible (int value);
int mt_delline (void);

void printMemory ();
void printCommands ();
void printTerm (int address, int input);
void printCache (void);
void printCacheCell (int address, enum Colors fg, enum Colors bg);
void resetTerm (void);

void checkTerminal ();
void checkScreenSize ();
void clearScreen ();

#endif
