#include "myCuAlu.h"
#include "myMemoryController.h"
#include "mySimpleComputer.h"

#include <stdbool.h>

static void
reset_flags (void)
{
  t_counter = 0;
  found_in_cache = 0;
  memory_in_cache = 0;
  operand_in_cache = 0;
}

void
memory_controller (void)
{
  int operand, sign, cmd;
  sc_commandDecode (memory[command_counter], &sign, &cmd, &operand);

  if (t_counter == 1)
    { // обход кэша
      int memory_row = (command_counter / CELL_IN_ROW) * CELL_IN_ROW;
      int operand_row = (operand / CELL_IN_ROW) * CELL_IN_ROW;
      int current_row_idx = 0;

      int cache_value = 0;
      int memory_value = memory[command_counter];
      int operand_value = memory[operand];
      int rewrite_mem_idx = -1;
      int rewrite_cache_idx = -1;

      for (int i = 0; i < CACHE_SIZE; ++i)
        {
          current_row_idx = i / CELL_IN_CACHE_ROW;
          mc_cacheGet (i, &cache_value);
          if (memory_row == cache_rows[current_row_idx])
            {
              if (memory_value == cache_value)
                {
                  usage[current_row_idx]++;
                  memory_in_cache = 1;
                }
              rewrite_mem_idx = current_row_idx;
            }

          if (operand_row == cache_rows[current_row_idx])
            {
              if (operand_value == cache_value)
                {
                  usage[current_row_idx]++;
                  operand_in_cache = 1;
                }
              rewrite_cache_idx = current_row_idx;
            }
        }

      if (memory_in_cache && operand_in_cache)
        found_in_cache = 1;

      if (!memory_in_cache)
        usage[rewrite_mem_idx] = -1;
      if (!operand_in_cache)
        usage[rewrite_cache_idx] = -1;
    }

  if (found_in_cache)
    {
      if (t_counter == 3)
        {
          reset_flags ();
          CU ();
        }
    }
  else
    {
      if (t_counter == 9)
        {
          int min_usage_row_idx = 0;
          // находим строку, которая использовалась меньше всего
          for (int i = 1; i < (CACHE_SIZE / CELL_IN_CACHE_ROW); ++i)
            {
              if (usage[i] < usage[min_usage_row_idx])
                {
                  min_usage_row_idx = i;
                }
            }
          int pos = !memory_in_cache ? command_counter : operand;
          int current_row = pos / CELL_IN_ROW;
          usage[min_usage_row_idx] = 1;
          cache_rows[min_usage_row_idx] = current_row * CELL_IN_CACHE_ROW;
          int cache_idx = min_usage_row_idx * CELL_IN_CACHE_ROW;
          int memory_begin = current_row * CELL_IN_ROW;
          int memory_end = memory_begin + CELL_IN_ROW;

          if (!memory_in_cache)
            {
              // записываем новые значения в кэш
              for (int i = memory_begin; i < memory_end && i < MEMORY_SIZE;
                   ++i)
                {
                  mc_cacheSet (cache_idx++, memory[i]);
                }
            }
          else if (!operand_in_cache)
            {
              reset_flags ();
              CU ();

              // записываем новые значения в кэш
              for (int i = memory_begin; i < memory_end && i < MEMORY_SIZE;
                   ++i)
                {
                  mc_cacheSet (cache_idx++, memory[i]);
                }
            }

          reset_flags ();
        }
    }
}

int
mc_cacheGet (int address, int *value)
{
  if (address < 0 || address >= CACHE_SIZE || !value)
    {
      return -1;
    }

  *value = L2_cache[address];

  return 0;
}

int
mc_cacheSet (int address, int value)
{
  if (address < 0 || address >= CACHE_SIZE)
    {
      return -1;
    }

  L2_cache[address] = value;

  int sign, command, operand;
  sc_commandDecode (L2_cache[address], &sign, &command, &operand);
  if (sc_commandValidate (command) == -1)
    {
      sc_regSet (FLAG_INVALID_COMMAND_MASK, 1);
    }
  else
    {
      sc_regSet (FLAG_INVALID_COMMAND_MASK, 0);
    }

  return 0;
}