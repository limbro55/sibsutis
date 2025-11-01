#include "myCuAlu.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include <stdbool.h>

static bool
is_err (int code, int line)
{
  if (code)
    fprintf (stderr, "ошибка с кодом %d в строке %d\n", code, line);
  return code ? true : false;
}

static bool
is_alu_command (int command)
{
  return ((command >= 0x1e && command <= 0x21) || command == 0x33
          || command == 0x34 || command == 0x44 || command == 0x45
          || command == 0x46);
}

static void
handle_cu_commands (int sign, int command, int operand)
{

  // чтобы sign не был unused
  int temp = sign;
  sign = 0;
  sign = temp;

  switch (command)
    {
    case READ:
      if (operand >= 0 && operand <= 127)
        {
          printTerm (operand, 0);
          sc_regSet (FLAG_OUT_OF_MEMORY_MASK, 0);
        }
      else
        {
          sc_regSet (FLAG_OUT_OF_MEMORY_MASK, 1);
        }
      break;

    case WRITE:
      isig_generator_stop ();
      if (operand >= 0 && operand <= 127)
        {
          mt_gotoXY (67, 26);
          printf ("%02X<      ", operand);
          rk_mytermrestore ();
          mt_gotoXY (71, 26);
          int number;
          if (rk_readvalue (&number) != -1)
            {
              mt_gotoXY (67, 20);
              sc_memorySet (operand, number);
              mt_gotoXY (67, 26);
              printTerm (operand, 1);
              printf ("            ");
              sc_regSet (FLAG_OVERFLOW_MASK, 0);
            }
        }
      else
        {
          sc_regSet (FLAG_OUT_OF_MEMORY_MASK, 1);
        }
      mt_gotoXY (67, 26);
      printf ("            ");
      isig_generator_start ();
      break;

    case LOAD:
      sc_accumulatorSet (memory[operand]);
      break;

    case STORE:
      sc_memorySet (operand, accumulator);
      break;

    case JUMP:
      sc_icounterSet (operand - 1);
      break;

    case JNEG:
      {

        if (accumulator < 0)
          {
            sc_icounterSet (operand - 1);
          }
        break;
      }

    case JZ:
      {
        if (accumulator == 0)
          {
            sc_icounterSet (operand - 1);
          }
        break;
      }

    case HALT:
      sc_regSet (FLAG_IGNORE_CLOCK_MASK, 1);
      command_counter--;
      break;

    case MOVA:
      {
        int my_sign = 0, my_command = 0, my_operand = 0;
        sc_commandDecode (accumulator, &my_sign, &my_command, &my_operand);
        memory[my_operand] = memory[operand];
        break;
      }

    default:
      break;
    }
}

void
CU (void)
{
  printCell (command_counter, BLACK, YELLOW);
  int res_code = 0;

  int value;
  if (sc_memoryGet (command_counter, &value))
    res_code = -1;

  int sign, command, operand;
  if (!is_err (res_code, __LINE__)
      && sc_commandDecode (value, &sign, &command, &operand))
    res_code = -1;

  if (!is_err (res_code, __LINE__) && is_alu_command (command) && sign == 0)
    {
      ALU (command, operand);
      printMemory ();
    }

  if (!is_err (res_code, __LINE__) && sign == 0)
    {
      handle_cu_commands (sign, command, operand);
      printMemory ();
    }

  if (!is_err (res_code, __LINE__) && (command_counter + 1) < MEMORY_SIZE)
    {
      command_counter++;
    }
  else
    {
      sc_regSet (FLAG_OUT_OF_MEMORY_MASK, 1);
      sc_regSet (FLAG_IGNORE_CLOCK_MASK, 1);
      running_mode = 0;
    }
}
