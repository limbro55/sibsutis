#include "myCuAlu.h"
#include "mySimpleComputer.h"

int
ALU (int command, int operand)
{
  int value;
  sc_memoryGet (operand, &value);
  switch (command)
    {
    case ADD:
      if (accumulator + value > 16383)
        {
          accumulator = 16383;
          sc_regSet (FLAG_OVERFLOW_MASK, 1);
        }
      else if (accumulator + value < -16384)
        {
          accumulator = -16384;
          sc_regSet (FLAG_OVERFLOW_MASK, 1);
        }
      else
        {
          accumulator += value;
          sc_regSet (FLAG_OVERFLOW_MASK, 0);
        }
      break;

    case SUB:
      if (accumulator - value < -16384)
        {
          accumulator = -16384;
          sc_regSet (FLAG_OVERFLOW_MASK, 1);
        }
      if (accumulator - value > 16383)
        {
          accumulator = 16383;
          sc_regSet (FLAG_OVERFLOW_MASK, 1);
        }
      else
        {
          accumulator -= value;
          sc_regSet (FLAG_OVERFLOW_MASK, 0);
        }
      break;

    case MUL:
      if (accumulator * value > 16383)
        {
          accumulator = 16383;
          sc_regSet (FLAG_OVERFLOW_MASK, 1);
        }
      else if (accumulator * value < -16384)
        {
          accumulator = -16384;
          sc_regSet (FLAG_OVERFLOW_MASK, 1);
        }
      else
        {
          accumulator *= value;
          sc_regSet (FLAG_OVERFLOW_MASK, 0);
        }
      break;

    case DIVIDE:
      if (value == 0)
        {
          sc_regSet (FLAG_DIVISION_BY_ZERO_MASK, 1);
          return -1;
        }
      accumulator /= value;
      sc_regSet (FLAG_DIVISION_BY_ZERO_MASK, 0);
      break;

    case NOT:
      {
        int invert_accumulator = ~accumulator;
        sc_memorySet (operand, invert_accumulator);
        break;
      }

    case AND:
      {
        int result_and = accumulator & memory[operand];
        sc_accumulatorSet (result_and);
        break;
      }

    case LOGRC:
      {
        int my_sign = 0, my_command = 0, my_operand = 0;
        sc_commandDecode (accumulator, &my_sign, &my_command, &my_operand);
        int mem_sign = 0, mem_command = 0, mem_operand = 0;
        sc_commandDecode (memory[operand], &mem_sign, &mem_command,
                          &mem_operand);
        if (mem_sign == 1)
          {
            int val;
            sc_commandEncode (mem_sign, mem_command, mem_operand, &val);
            accumulator = val >> my_operand;
            break;
          }
        else
          {
            accumulator = memory[operand] >> my_operand;
            break;
          }
      }

    case RCCL:
      {
        int my_sign = 0, my_command = 0, my_operand = 0;
        sc_commandDecode (accumulator, &my_sign, &my_command, &my_operand);
        int val = memory[operand];
        if (val < 0)
          {
            val = ((~abs (val)) + 1) & 0x7FFF;
            val = ((val << my_operand) | (val >> (15 - my_operand))) & 0x7FFF;
            if (val > 16383)
              {
                val = ~(val - 1) & 0x7FFF;
                accumulator = -val;
              }
            else
              {
                accumulator = val;
              }
            break;
          }
        else
          {
            val = ((val << my_operand) | (val >> (15 - my_operand))) & 0x7FFF;
            if (val > 16383)
              {
                val = ~(val - 1) & 0x7FFF;
                accumulator = -val;
              }
            else
              {
                accumulator = val;
              }
            break;
          }
      }

    case RCCR:
      {
        int my_sign = 0, my_command = 0, my_operand = 0;
        sc_commandDecode (accumulator, &my_sign, &my_command, &my_operand);
        int val = memory[operand];
        if (val < 0)
          {
            val = ((~abs (val)) + 1) & 0x7FFF;
            val = ((val >> my_operand) | (val << (15 - my_operand))) & 0x7FFF;
            if (val > 16383)
              {
                val = ~(val - 1) & 0x7FFF;
                accumulator = -val;
              }
            else
              {
                accumulator = val;
              }
            break;
          }
        else
          {
            val = ((val >> my_operand) | (val << (15 - my_operand))) & 0x7FFF;
            if (val > 16383)
              {
                val = ~(val - 1) & 0x7FFF;
                accumulator = -val;
              }
            else
              {
                accumulator = val;
              }
            break;
          }
      }
    }

  return 0;
}
