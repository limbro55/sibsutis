#include "mySimpleComputer.h"

int
sc_icounterInit (void)
{
  command_counter = 0;

  return 0;
}

int
sc_icounterSet (int value)
{
  if (value < 0 || value > 127)
    {
      return -1;
    }

  command_counter = value;

  int sign, command, operand;
  sc_commandDecode (memory[command_counter], &sign, &command, &operand);
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
sc_icounterGet (int *value)
{
  if (!value)
    {
      return -1;
    }

  *value = command_counter;

  return 0;
}
