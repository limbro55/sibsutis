#ifndef MY_MEMORY_CONTROLLER_H
#define MY_MEMORY_CONTROLLER_H

#include <stdbool.h>

#define CACHE_SIZE 50
#define CELL_IN_CACHE_ROW 10

extern int L2_cache[];
extern int cache_rows[];
extern bool found_in_cache;
extern bool memory_in_cache;
extern bool operand_in_cache;
extern int usage[];

void memory_controller (void);

int mc_cacheGet (int address, int *value);
int mc_cacheSet (int address, int value);

extern int cache_addr[CACHE_SIZE];
extern bool valid[CACHE_SIZE];

#endif
