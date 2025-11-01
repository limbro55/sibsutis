#include "mySimpleComputer.h"

#include <stdio.h>

int
sc_memoryInit (void)
{
  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      memory[i] = 0;
    }

  return 0;
}

int
sc_memorySet (int address, int value)
{
  if (address < 0 || address >= MEMORY_SIZE || value < -16384 || value > 16383)
    {
      return -1;
    }

  memory[address] = value;

  int sign, command, operand;
  sc_commandDecode (memory[address], &sign, &command, &operand);
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

int
sc_memoryGet (int address, int *value)
{
  if (address < 0 || address >= MEMORY_SIZE || !value)
    {
      return -1;
    }

  *value = memory[address];

  return 0;
}

int
sc_memorySave (char *filename)
{
  if (!filename)
    {
      return -1;
    }

  FILE *file = fopen (filename, "wb");
  if (!file)
    {
      return -1;
    }

  size_t count_saved = fwrite (memory, sizeof (int), MEMORY_SIZE, file);
  if (count_saved != MEMORY_SIZE)
    {
      fclose (file);
      return -1;
    }

  fclose (file);
  return 0;
}

int
sc_memoryLoad (char *filename)
{
  if (!filename)
    {
      return -1;
    }

  FILE *file = fopen (filename, "rb");
  if (!file)
    {
      return -1;
    }

  size_t count_loaded = fread (memory, sizeof (int), MEMORY_SIZE, file);
  if (count_loaded != MEMORY_SIZE)
    {
      fclose (file);
      return -1;
    }

  fclose (file);
  return 0;
}
