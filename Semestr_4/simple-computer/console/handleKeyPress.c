#include "myCuAlu.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

#include <signal.h>
#include <string.h>
#include <sys/time.h>

void
handleKeyPress (enum Keys *key)
{
  switch (*key)
    {
    case KEY_I:
      raise (SIGUSR1);
      break;
    }

  switch (*key)
    {
    case KEY_UP:
      printCell (command_counter, BLACK, YELLOW);
      (command_counter <= 9)
          ? (command_counter += (command_counter >= 8 ? 110 : 120))
          : (command_counter -= 10);
      break;
    case KEY_RIGHT:
      printCell (command_counter, BLACK, YELLOW);
      (!((command_counter + 1) % (command_counter >= 120 ? 8 : 10)))
          ? (command_counter -= (command_counter >= 120 ? 7 : 9))
          : (command_counter += 1);
      break;
    case KEY_DOWN:
      printCell (command_counter, BLACK, YELLOW);
      (command_counter >= 118)
          ? (command_counter -= (command_counter < 120 ? 110 : 120))
          : (command_counter += 10);
      break;
    case KEY_LEFT:
      printCell (command_counter, BLACK, YELLOW);
      (!(command_counter % 10))
          ? (command_counter += (command_counter >= 120 ? 7 : 9))
          : (command_counter -= 1);
      break;

    case KEY_L:
      {
        isig_generator_stop ();
        rk_mytermregime (0, 30, 0, 1, 0);
        char filename[101];
        printf ("Enter load file name: ");
        fgets (filename, 101, stdin);
        mt_clrscr ();
        mt_gotoXY (0, 26);
        filename[strlen (filename) - 1] = '\0';
        if (sc_memoryLoad (filename))
          {
            printf ("\nFailed to load memory!               ");
          }
        else
          {
            printf ("\nSuccessful load memory!             ");
          }

        printMemory ();
        resetTerm ();
        printTerm (-1, 0);
        rk_mytermregime (0, 30, 0, 0, 0);
        isig_generator_start ();
        break;
      }

    case KEY_S:
      {
        isig_generator_stop ();
        rk_mytermregime (0, 30, 0, 1, 0);
        char filename[101];
        printf ("Enter save file name: ");
        fgets (filename, 101, stdin);
        mt_clrscr ();
        mt_gotoXY (0, 26);
        filename[strlen (filename) - 1] = '\0';

        if (sc_memorySave (filename))
          {
            printf ("\nFailed to save memory!                         ");
          }
        else
          {
            printf ("\nSuccessful saving memory!                     ");
          }
        printMemory ();
        printTerm (-1, 0);
        rk_mytermregime (0, 30, 0, 0, 0);
        isig_generator_start ();
        break;
      }

    case KEY_F5:
      {
        mt_gotoXY (ACCUMULATOR_POS_X + 4, ACCUMULATOR_POS_Y);
        int number;
        rk_readvalue (&number);
        sc_accumulatorSet (number);
        break;
      }

    case KEY_F6:
      {
        printCell (command_counter, BLACK, YELLOW);
        mt_gotoXY (COUNTERS_POS_X + 14, COUNTERS_POS_Y);
        int number;
        rk_readvalue (&number);
        sc_icounterSet (number);
        break;
      }

    case KEY_ENTER:
      {
        int cursorX = command_counter % 10, cursorY = command_counter / 10;
        int number;
        const int cell_and_space_size = 6;

        mt_gotoXY (cursorX * cell_and_space_size + MEMORY_POS_X + 1,
                   cursorY + MEMORY_POS_Y);
        mt_setfgcolor (WHITE);
        mt_setbgcolor (RED);

        if (rk_readvalue (&number) != -1)
          {
            sc_memorySet (command_counter, number);
            printTerm (command_counter, 1);
          }
        break;
      }

    case KEY_OTHER:
      break;

    case KEY_ESC:
      break;

    case KEY_R:
      sc_regSet (FLAG_IGNORE_CLOCK_MASK, 0);
      break;

    case KEY_T:
      CU ();
      break;
    }
}
