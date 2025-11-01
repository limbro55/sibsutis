#include "myMemoryController.h"

int L2_cache[CACHE_SIZE];
bool found_in_cache = 0;
bool memory_in_cache = 0;
bool operand_in_cache = 0;
int cache_rows[CACHE_SIZE / CELL_IN_CACHE_ROW] = { -1, -1, -1, -1, -1 };
int usage[CACHE_SIZE / CELL_IN_CACHE_ROW] = { 0, 0, 0, 0, 0 };
