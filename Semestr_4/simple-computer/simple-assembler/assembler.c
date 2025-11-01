#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MEMORY_SIZE 128

#define COMMAND_SIGN_MASK 0b100000000000000
#define COMMAND_OPERATION_CODE_MASK 0b11111110000000
#define COMMAND_OPERAND_MASK 0b1111111

typedef struct
{
  const char *name;
  int code;
} Command;

const Command commands[] = {
  { "READ", 0x0A }, { "WRITE", 0x0B }, { "LOAD", 0x14 },   { "STORE", 0x15 },
  { "ADD", 0x1E },  { "SUB", 0x1F },   { "DIVIDE", 0x20 }, { "MUL", 0x21 },
  { "JUMP", 0x28 }, { "JNEG", 0x29 },  { "JZ", 0x2A },     { "HALT", 0x2B },
  { "NOT", 0x33 },  { "AND", 0x34 },   { "LOGRC", 0x44 },  { "RCCL", 0x45 },
  { "RCCR", 0x46 }, { "MOVA", 0x47 },  { "=", 0x00 }
};

int memory[MEMORY_SIZE];

void
save_memory (char *filename)
{
  if (!filename)
    {
      return;
    }

  FILE *file = fopen (filename, "wb");
  if (!file)
    {
      return;
    }

  size_t count_saved = fwrite (memory, sizeof (int), MEMORY_SIZE, file);
  if (count_saved != MEMORY_SIZE)
    {
      fclose (file);
      return;
    }

  fclose (file);
}

int
get_command_code (char *cmd)
{
  for (size_t i = 0; i < sizeof (commands) / sizeof (commands[0]); i++)
    {
      if (strcmp (commands[i].name, cmd) == 0)
        {
          return commands[i].code;
        }
    }
  return -1;
}

int
parse_value (char *str, int *value)
{
  if (strlen (str) != 5 || (str[0] != '+' && str[0] != '-'))
    {
      return -1;
    }

  int sign = (str[0] == '-') ? 1 : 0;
  char hex_str[5];
  strncpy (hex_str, str + 1, 4);
  hex_str[4] = '\0';

  unsigned int command, operand;
  if (sscanf (hex_str, "%2X%2X", &command, &operand) != 2)
    {
      return -1;
    }

  if (command > 0x7F || operand > 0x7F)
    {
      return -1;
    }

  int val = (sign << 14) | (command << 7) | operand;

  if (val > 16383)
    {
      val -= 16384;
      val = (16383 - val + 1) * -1;
      *value = val;
    }
  else
    {
      *value = (sign << 14) | (command << 7) | operand;
    }

  return 0;
}

void
translate ()
{
  FILE *input_file = fopen ("script.sa", "r");
  if (!input_file)
    {
      return;
    }

  char line[MAX_LINE_LENGTH];
  while (fgets (line, sizeof (line), input_file))
    {
      char *comment = strchr (line, ';');
      if (comment)
        {
          *comment = '\0';
        }

      if (strlen (line) == 0 || line[0] == '\n')
        {
          continue;
        }

      int address;
      char str_command[10];
      char operand_str[20];

      int readed_count
          = sscanf (line, "%X %9s %19s", &address, str_command, operand_str);
      if (readed_count < 2)
        {
          continue;
        }

      if (address < 0 || address >= MEMORY_SIZE)
        {
          continue;
        }

      int command = get_command_code (str_command);
      if (command == -1)
        {
          continue;
        }

      if (strcmp (str_command, "=") == 0)
        {
          int value;
          if (parse_value (operand_str, &value) != 0)
            {
              continue;
            }
          memory[address] = value;
        }
      else
        {
          if (readed_count != 3)
            {
              continue;
            }

          unsigned int operand;
          if (sscanf (operand_str, "%X", &operand) != 1)
            {
              continue;
            }

          if (operand > 0x7F)
            {
              continue;
            }

          memory[address] = (command << 7) | operand;
        }
    }

  fclose (input_file);
  save_memory ("script.o");
}

int
main ()
{
  translate ();

  return 0;
}
