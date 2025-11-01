#ifndef MY_SIMPLE_COMPUTER_H
#define MY_SIMPLE_COMPUTER_H

#include "myReadKey.h"
#include "myTerm.h"

#define FLAG_OVERFLOW_MASK 1         // 0b1
#define FLAG_DIVISION_BY_ZERO_MASK 2 // 0b10
#define FLAG_OUT_OF_MEMORY_MASK 4    // 0b100
#define FLAG_IGNORE_CLOCK_MASK 8     // 0b1000
#define FLAG_INVALID_COMMAND_MASK 16 // 0b10000

#define COMMAND_SIGN_MASK 16384           // 0b100000000000000
#define COMMAND_OPERATION_CODE_MASK 16256 // 0b011111110000000
#define COMMAND_OPERAND_MASK 127          // 0b000000001111111

#define MEMORY_SIZE 128
#define CELL_IN_ROW 10
#define CACHE_SIZE 50
#define CELL_IN_ROW 10
#define CELL_IN_CACHE_ROW 10
extern int memory[];
extern int accumulator;
extern int command_counter;
extern int flag_register;
extern int running_mode;
extern int t_counter;

int sc_memoryInit (void);
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);

int sc_regInit (void);
int sc_regSet (int reg, int value);
int sc_regGet (int reg, int *value);

int sc_accumulatorInit (void);
int sc_accumulatorSet (int value);
int sc_accumulatorGet (int *value);

int sc_icounterInit (void);
int sc_icounterSet (int value);
int sc_icounterGet (int *value);

int sc_commandValidate (int command);
int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandDecode (int value, int *sign, int *command, int *operand);

void printCell (int address, enum Colors fg, enum Colors bg);
void printFlags (void);
void printDecodedCommand (int value);
void printAccumulator (void);
void printCounters (void);

void searching_incorrect_command (enum Keys key);
void display_console (enum Keys key, int rm);
void check_console_params (void);
void init_console (void);

#endif
