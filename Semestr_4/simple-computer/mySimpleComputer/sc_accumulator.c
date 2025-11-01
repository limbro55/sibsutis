#include "mySimpleComputer.h"

int
sc_accumulatorInit (void)
{
  accumulator = 0;

  return 0;
}

int
sc_accumulatorSet (int value)
{
  if (value < -16384 || value > 16383)
    {
      return -1;
    }

  accumulator = value;

  return 0;
}

int
sc_accumulatorGet (int *value)
{
  if (!value)
    {
      return -1;
    }

  *value = accumulator;

  return 0;
}
