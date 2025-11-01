#include "myTerm.h"

#include <string.h>

int
mt_gotoXY (int x, int y)
{
  char buf[32];

  snprintf (buf, sizeof (buf), "\033[%d;%dH", y, x);
  fflush (stdout);
  if (write (STDOUT_FILENO, buf, strlen (buf)) == -1)
    {
      return -1;
    }

  return 0;
}

int
mt_setcursorvisible (int value)
{
  char buf[32];

  snprintf (buf, sizeof (buf), "\033[?25%c", value ? 'h' : 'l');
  fflush (stdout);

  if (write (STDOUT_FILENO, buf, strlen (buf)) == -1)
    {
      return -1;
    }

  return 0;
}
