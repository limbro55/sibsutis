#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

void
searching_incorrect_command (enum Keys key)
{
  if (key != KEY_L)
    return;

  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      int sign, command, operand;
      sc_commandDecode (memory[i], &sign, &command, &operand);
      if (sc_commandValidate (command) == -1)
        {
          sc_regSet (FLAG_INVALID_COMMAND_MASK, 1);
          break;
        }
      else
        {
          sc_regSet (FLAG_INVALID_COMMAND_MASK, 0);
        }
    }
}

void
display_console (enum Keys key, int rm)
{
  if (key == KEY_OTHER && !rm)
    return;
  if (rm)
    pause ();

  printCell (command_counter, WHITE, RED);
  printAccumulator ();
  printFlags ();
  printCounters ();
  printCommands ();
  printDecodedCommand (memory[command_counter]);
  printBigCell (memory[command_counter], BIG_CELL_POS_X, BIG_CELL_POS_Y);
  printKeys ();
  // печать in-out
  bc_box (IO_POS_X + 3, IO_POS_Y, IO_POS_X + IO_WIDTH, IO_POS_Y + IO_HEIGHT,
          WHITE, BLACK, "IN--OUT", RED, BLACK);

  printCache ();
  mt_gotoXY (0, INTERFACE_HEIGHT + 1);
}

void
check_console_params (void)
{
  checkTerminal ();
  checkScreenSize ();
}

void
init_console (void)
{
  clearScreen ();
  sc_memoryInit ();
  sc_memoryLoad ("../simple-assembler/script.o");
  sc_regInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  generateFont ();

  rk_mytermsave ();
  rk_mytermregime (0, 30, 0, 0, 0);
}
