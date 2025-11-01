#include "myBigChars.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TERM_HISTORY 4
static int term_history[TERM_HISTORY] = { -1, -1, -1, -1 };
static int term_input[TERM_HISTORY] = { -1, -1, -1, -1 };
static int term_value[TERM_HISTORY] = { -1, -1, -1, -1 };

void
printMemory ()
{
  int screenX = 1, screenY = 1;
  int cellWidth = 5;
  int cellInRow = 10;
  int forSpaces = cellInRow;
  int forBoxBound = 2;
  int cellInCol = 12;

  bc_box (screenX, screenY, screenX + (cellWidth * cellInRow) + forSpaces,
          screenY + cellInCol + forBoxBound, WHITE, BLACK,
          "Оперативная память", RED, BLACK);

  mt_gotoXY (MEMORY_POS_X + 2, MEMORY_POS_Y);
  for (int i = 0; i < MEMORY_SIZE; ++i)
    {
      printCell (i, BLACK, YELLOW);
    }
}

void
printCell (int address, enum Colors fg, enum Colors bg)
{
  mt_setfgcolor (fg);
  mt_setbgcolor (bg);

  int col = address / 10;
  mt_gotoXY (MEMORY_POS_X + ((address % 10) + 1) * 6 - 5, MEMORY_POS_Y + col);

  int sign = 0, command = 0, operand = 0;
  sc_commandDecode (memory[address], &sign, &command, &operand);
  sign ? printf ("-") : printf ("+");

  printf ("%02X%02X", command, operand);

  mt_setdefaultcolor ();
}

void
printFlags (void)
{
  bc_box (FLAGS_POS_X - PADDING - BORDER_SIZE, FLAGS_POS_Y - BORDER_SIZE,
          FLAGS_POS_X + FLAGS_WIDTH, FLAGS_POS_Y + FLAGS_HEIGHT, WHITE, BLACK,
          "Регистр флагов", RED, BLACK);

  mt_gotoXY (FLAGS_POS_X, FLAGS_POS_Y);

  if (sc_regGet (0, &flag_register) == 0)
    {
      printf ("%c  %c  %c  %c  %c",
              (flag_register & FLAG_OVERFLOW_MASK) ? 'P' : '_',
              (flag_register & FLAG_DIVISION_BY_ZERO_MASK) ? '0' : '_',
              (flag_register & FLAG_OUT_OF_MEMORY_MASK) ? 'M' : '_',
              (flag_register & FLAG_IGNORE_CLOCK_MASK) ? 'T' : '_',
              (flag_register & FLAG_INVALID_COMMAND_MASK) ? 'E' : '_');
    }

  mt_gotoXY (0, INTERFACE_HEIGHT);
}

void
printDecodedCommand (int value)
{
  bc_box (EDIT_POS_X, EDIT_POS_Y, EDIT_POS_X + EDIT_WIDTH,
          EDIT_POS_Y + EDIT_HEIGHT, WHITE, BLACK,
          "Редактируемая ячейка (формат)", RED, BLACK);

  mt_gotoXY (EDIT_POS_X + BORDER_SIZE, EDIT_POS_Y + BORDER_SIZE);

  // Приводим к 15-битному представлению
  value &= 0x7FFF;
  int is_negative = value & 0x4000;

  if (!is_negative)
    {
      printf ("dec: %05d | oct: %05o | hex: %04X | bin: ", value, value,
              value);
      for (int i = 14; i >= 0; i--)
        {
          printf ("%d", (value >> i) & 1);
        }
    }
  else
    {
      // Для отрицательных чисел используем 15-битное представление
      unsigned int uvalue = value;

      printf ("dec: %06d| oct: ", (int)(uvalue | ~0x7FFF));
      // Восьмеричное (5 цифр)
      for (int i = 4; i >= 0; i--)
        {
          printf ("%o", (uvalue >> (i * 3)) & 0x7);
        }

      printf (" | hex: ");
      // Шестнадцатеричное (4 цифры)
      for (int i = 3; i >= 0; i--)
        {
          printf ("%X", (uvalue >> (i * 4)) & 0xF);
        }

      printf (" | bin: ");
      for (int i = 14; i >= 0; i--)
        {
          printf ("%d", (uvalue >> i) & 1);
        }
    }

  mt_gotoXY (EDIT_POS_X, INTERFACE_HEIGHT + 10);
}

void
printAccumulator (void)
{
  bc_box (ACCUMULATOR_POS_X - PADDING - BORDER_SIZE,
          ACCUMULATOR_POS_Y - BORDER_SIZE,
          ACCUMULATOR_POS_X + ACCUMULATOR_WIDTH - BORDER_SIZE,
          ACCUMULATOR_POS_Y + ACCUMULATOR_HEIGHT, WHITE, BLACK, "Аккумулятор",
          RED, BLACK);

  mt_gotoXY (ACCUMULATOR_POS_X, ACCUMULATOR_POS_Y);

  printf ("sc: ");
  int sign, command, operand;
  sc_commandDecode (accumulator, &sign, &command, &operand);
  sign ? printf ("-") : printf ("+");
  printf ("%02X%02X", command, operand);

  printf (" hex: ");
  int value;
  sc_accumulatorGet (&value);

  value &= 0x7FFF;
  int is_negative = value & 0x4000;

  if (!is_negative)
    {
      printf ("%04X", value);
    }
  else
    {
      unsigned int uvalue = value;
      for (int i = 3; i >= 0; i--)
        {
          printf ("%X", (uvalue >> (i * 4)) & 0xF);
        }
    }

  mt_gotoXY (MEMORY_POS_X, INTERFACE_HEIGHT);
}

void
printCounters (void)
{
  bc_box (COUNTERS_POS_X - PADDING - BORDER_SIZE, COUNTERS_POS_Y - BORDER_SIZE,
          COUNTERS_POS_X + COUNTERS_WIDTH - BORDER_SIZE,
          COUNTERS_POS_Y + COUNTERS_HEIGHT, WHITE, BLACK, "Счетчик команд",
          RED, BLACK);

  mt_gotoXY (COUNTERS_POS_X, COUNTERS_POS_Y);

  printf ("T:%02d\tIC: +%04X", t_counter, command_counter);

  mt_gotoXY (MEMORY_POS_X, INTERFACE_HEIGHT);
}

void
printCommands (void)
{
  bc_box (CMD_POS_X - PADDING - CMD_PADDING - BORDER_SIZE,
          CMD_POS_Y - BORDER_SIZE, CMD_POS_X + CMD_WIDTH,
          CMD_POS_Y + CMD_HEIGHT, WHITE, BLACK, "Команда", RED, BLACK);

  mt_gotoXY (CMD_POS_X - 3, CMD_POS_Y);

  int sign, command, operand;
  sc_commandDecode (memory[command_counter], &sign, &command, &operand);

  printf ("%c %02X : %02X", sign ? '-' : '+', command, operand);

  mt_gotoXY (MEMORY_POS_X, INTERFACE_HEIGHT);
}

void
printTerm (int address, int input)
{
  mt_setfgcolor (WHITE);
  mt_setbgcolor (BLACK);
  // input: 0 - вывод (чтение), 1 - ввод (запись)

  // Сдвигаем историю вверх
  for (int i = TERM_HISTORY - 1; i > 0 && address != -1; --i)
    {
      term_history[i] = term_history[i - 1];
      term_input[i] = term_input[i - 1];
      term_value[i] = term_value[i - 1];
    }

  // Записываем текущую операцию
  if (address != -1)
    {
      term_history[0] = address;
      term_input[0] = input;
      int value;
      sc_memoryGet (address, &value);
      term_value[0] = value;
    }

  // Выводим историю
  for (int i = 0; i < TERM_HISTORY; ++i)
    {
      if (term_history[i] == -1)
        {
          mt_gotoXY (IO_POS_X + BORDER_SIZE, IO_POS_Y + BORDER_SIZE + i);
          printf ("%12c", ' ');
          continue;
        }

      mt_gotoXY (IO_POS_X + BORDER_SIZE + 3, IO_POS_Y + BORDER_SIZE + i);

      // Выводим адрес и тип операции
      printf ("%02X%c ", term_history[i], term_input[i] ? '<' : '>');

      int sign, command, operand;
      sc_commandDecode (term_value[i], &sign, &command, &operand);
      printf ("%c%02X%02X", sign ? '-' : '+', command, operand);
    }
}

int font[18][2] = {
  { 0xC3C3C3FF, 0xFFC3C3C3 }, // 0
  { 0x18181C18, 0xFF181818 }, // 1
  { 0xFFC0C0FF, 0xFF030303 }, // 2
  { 0xFEC0C0FF, 0xFFC0C0FE }, // 3
  { 0xFFC3C3C3, 0xC0C0C0C0 }, // 4
  { 0xFF0303FF, 0xFFC0C0C0 }, // 5
  { 0xFF0303FF, 0xFFC3C3C3 }, // 6
  { 0x3030C0FF, 0x0C0C0C30 }, // 7
  { 0xFFC3C3FF, 0xFFC3C3FF }, // 8
  { 0xFFC3C3FF, 0xFFC0C0C0 }, // 9
  { 0xC3C3C3FF, 0xC3C3C3FF }, // a
  { 0xC3C3C37F, 0x7FC3C37F }, // b
  { 0x030303FF, 0xFF030303 }, // c
  { 0xC3C3C33F, 0x3FC3C3C3 }, // d
  { 0xFF0303FF, 0xFF0303FF }, // e
  { 0xFF0303FF, 0x030303FF }, // f
  { 0xFF181800, 0x001818FF }, // +
  { 0x00000000, 0x000000FF }  // -
};

void
printBigCell (int cell, int x, int y)
{
  bc_box (BIG_CELL_POS_X - 1, BIG_CELL_POS_Y - 2,
          BIG_CELL_POS_X + BIG_CELL_WIDTH,
          BIG_CELL_POS_Y + BIG_CELL_HEIGHT + 4, WHITE, BLACK,
          "Редактируемая ячейка (увеличено)", RED, WHITE);

  if (cell < 0)
    {
      bc_printbigchar (font[17], x, y, 0, 0);
    }
  else
    {
      bc_printbigchar (font[16], x, y, 0, 0);
    }

  int cell_id = (cell >> 0) & 0xF;
  bc_printbigchar (font[cell_id], x + (3 + 1) * 9, y, 0, 0);
  cell_id = (cell >> 4) & 0x7;
  bc_printbigchar (font[cell_id], x + (2 + 1) * 9, y, 0, 0);
  cell_id = (cell >> (3 + 4)) & 0xF;
  bc_printbigchar (font[cell_id], x + (1 + 1) * 9, y, 0, 0);
  cell_id = (cell >> (4 + 4 + 3)) & 0x7;
  bc_printbigchar (font[cell_id], x + (0 + 1) * 9, y, 0, 0);

  mt_gotoXY (x, y + 8);
  mt_setfgcolor (BLUE);
  printf ("Номер редактируемой ячейки: %03d", command_counter);
  mt_setdefaultcolor ();
}

void
printKeys ()
{
  bc_box (77, IO_POS_Y, 107, 25, WHITE, BLACK, "Клавиши", RED, BLACK);
  mt_gotoXY (78, IO_POS_Y + 1);
  printf ("l - load s - save i - reset\n");
  mt_gotoXY (78, IO_POS_Y + 2);
  printf ("r - run t - step\n");
  mt_gotoXY (78, IO_POS_Y + 3);
  printf ("esc - exit\n");
  mt_gotoXY (78, IO_POS_Y + 4);
  printf ("F5 - Accumulator\n");
  mt_gotoXY (78, IO_POS_Y + 5);
  printf ("F6 - Command counter\n");
}

void
resetTerm (void)
{
  for (int i = 0; i < TERM_HISTORY; ++i)
    {
      term_history[i] = -1;
      term_input[i] = -1;
      term_value[i] = -1;
    }
  printTerm (-1, 0);
}

#include "myMemoryController.h"

void printCacheCell(int address, enum Colors fg, enum Colors bg) 
{
    mt_setfgcolor(fg);
    mt_setbgcolor(bg);

    int row = address / CELL_IN_CACHE_ROW;
    int col_in_row = address % CELL_IN_CACHE_ROW;
    
    mt_gotoXY(CACHE_POS_X + (col_in_row + 1) * 6 - 5 + 4,
              CACHE_POS_Y + row + BORDER_SIZE);

    if (cache_rows[row] == -1) {
        if (col_in_row == 0) {
            printf("  -1  ");
        } 
        else {
            printf("      ");
        }
    }
    else {
        int sign = 0, command = 0, operand = 0;
        sc_commandDecode(L2_cache[address], &sign, &command, &operand);
        sign ? printf("-") : printf("+");
        printf("%02X%02X", command, operand);
    }

    mt_setdefaultcolor();
}

void
printCache (void)
{
  bc_box (CACHE_POS_X, CACHE_POS_Y, CACHE_POS_X + CACHE_WIDTH,
          CACHE_POS_Y + CACHE_HEIGHT + BORDER_SIZE, WHITE, BLACK,
          "Кэш процессора", RED, BLACK);

  for (int i = 0; i < CACHE_SIZE; ++i)
    {
      if (i % CELL_IN_ROW == 0)
        {
          mt_gotoXY (CACHE_POS_X + ((i % CELL_IN_CACHE_ROW) + 1) * 6 - 5,
                     CACHE_POS_Y + i / CELL_IN_CACHE_ROW + BORDER_SIZE);

          if (cache_rows[i / CELL_IN_CACHE_ROW] == -1)
            printf ("00: ");
          else
            printf ("%02X: ", cache_rows[i / CELL_IN_CACHE_ROW]);
        }
      printCacheCell (i, WHITE, BLACK);
    }
}