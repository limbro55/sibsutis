#include "myTerm.h"

#include <sys/ioctl.h>

int
mt_clrscr (void)
{
  fflush (stdout);

  if (write (STDOUT_FILENO, "\033[H\033[J", 6) == -1)
    {
      return -1;
    }

  return 0;
}

int
mt_getscreensize (int *rows, int *cols)
{
  struct winsize ws;

  if (ioctl (STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
    {
      return -1;
    }

  *rows = ws.ws_row;
  *cols = ws.ws_col;

  return 0;
}

int
mt_delline (void)
{
  fflush (stdout);

  if (write (STDOUT_FILENO, "\033[M", 3) == -1)
    {
      return -1;
    }

  return 0;
}
