#include "mySimpleComputer.h"

int
sc_commandValidate (int command)
{
  switch (command)
    {
    case 0:
    case 1:
    case 10:
    case 11:
    case 20:
    case 21:
    case 30:
    case 31:
    case 32:
    case 33:
    case 40:
    case 41:
    case 42:
    case 43:
      return 0;
    default:
      if (command >= 51 && command <= 76)
        {
          return 0;
        }
      return -1;
    }
}

int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  *value = (sign << 14) | (command << 7) | operand;

  return 0;
}

int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{
  if (value < -16384 || value > 16383)
    {
      return -1;
    }

  *sign = (value & COMMAND_SIGN_MASK) ? 1 : 0;
  *command = (value & COMMAND_OPERATION_CODE_MASK) >> 7;
  *operand = value & COMMAND_OPERAND_MASK;

  return 0;
}
