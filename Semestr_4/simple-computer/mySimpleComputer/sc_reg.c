#include "mySimpleComputer.h"

int
sc_regInit (void)
{
  sc_regSet (FLAG_OVERFLOW_MASK, 0);
  sc_regSet (FLAG_DIVISION_BY_ZERO_MASK, 0);
  sc_regSet (FLAG_OUT_OF_MEMORY_MASK, 0);
  sc_regSet (FLAG_IGNORE_CLOCK_MASK, 1);
  sc_regSet (FLAG_INVALID_COMMAND_MASK, 0);

  return 0;
}

int
sc_regSet (int reg, int value)
{
  if (reg == FLAG_OVERFLOW_MASK || reg == FLAG_DIVISION_BY_ZERO_MASK
      || reg == FLAG_OUT_OF_MEMORY_MASK || reg == FLAG_INVALID_COMMAND_MASK
      || reg == FLAG_IGNORE_CLOCK_MASK)
    {
      if (value == 0 || value == 1)
        {
          if (value)
            flag_register |= reg;
          else
            flag_register &= ~reg;
          return 0;
        }
    }
  return -1;
}

int
sc_regGet (int reg, int *value)
{
  if (!value)
    {
      return -1;
    }

  if (reg == FLAG_OVERFLOW_MASK || reg == FLAG_DIVISION_BY_ZERO_MASK
      || reg == FLAG_OUT_OF_MEMORY_MASK || reg == FLAG_INVALID_COMMAND_MASK
      || reg == FLAG_IGNORE_CLOCK_MASK)
    {
      *value = (flag_register & reg) ? 1 : 0;
      return 0;
    }
  else if (reg == 0)
    {
      *value = flag_register;
      return 0;
    }

  return -1;
}
