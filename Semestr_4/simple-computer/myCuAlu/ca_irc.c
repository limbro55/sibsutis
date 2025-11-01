#include "myCuAlu.h"
#include "myMemoryController.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

#include <signal.h>
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>

#include <stdio.h>

static void
reset_console (void)
{
  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_regInit ();
  resetTerm ();
  printMemory ();
}

void
IRC (int signum)
{
  if (signum == SIGALRM)
    {
      int isig_ign = 0;
      sc_regGet (FLAG_IGNORE_CLOCK_MASK, &isig_ign);

      if (!isig_ign)
        {
          isig_generator_stop ();

          t_counter++;
          memory_controller ();

          isig_generator_start ();
        }
    }
  else if (signum == SIGUSR1)
    {
      reset_console ();
    }
}

struct itimerval nval, oval;

void
isig_generator_start (void)
{
  nval.it_interval.tv_sec = 0;
  nval.it_interval.tv_usec = 200000;
  nval.it_value.tv_sec = 0;
  nval.it_value.tv_usec = 200000;
  setitimer (ITIMER_REAL, &nval, &oval);
}

void
isig_generator_stop (void)
{
  nval.it_value.tv_sec = 0;
  nval.it_value.tv_usec = 0;
  setitimer (ITIMER_REAL, &nval, &oval);
}
