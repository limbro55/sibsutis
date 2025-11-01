#include "myBigChars.h"
#include "myCuAlu.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

#include <signal.h>
#include <time.h>

int
main ()
{
  isig_generator_start ();

  srand (time (NULL));
  check_console_params ();
  init_console ();

  printMemory ();
  display_console (KEY_I, running_mode);

  enum Keys key = KEY_OTHER;
  while (key != KEY_ESC)
    {
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
      // обработчик тактовых импульсов
      signal (SIGALRM, IRC);
      signal (SIGUSR1, IRC);

      // обработка нажатия клавиш
      sc_regGet (FLAG_IGNORE_CLOCK_MASK, &running_mode);
      running_mode = !running_mode;

      if (!running_mode)
        {
          t_counter = 0;
          display_console (key, running_mode);

          rk_readkey (&key);
          handleKeyPress (&key);
        }

      searching_incorrect_command (key);
      display_console (key, running_mode);
    }

  rk_mytermrestore ();

  return 0;
}
