#include "myTerm.h"

#include <string.h>

int
mt_setfgcolor (enum Colors color)
{
  char buf[32];

  snprintf (buf, sizeof (buf), "\033[38;5;%dm", color);
  fflush (stdout);

  if (write (STDOUT_FILENO, buf, strlen (buf)) == -1)
    {
      return -1;
    }

  return 0;
}

int
mt_setbgcolor (enum Colors color)
{
  char buf[32];

  snprintf (buf, sizeof (buf), "\033[48;5;%dm", color);
  fflush (stdout);

  if (write (STDOUT_FILENO, buf, strlen (buf)) == -1)
    {
      return -1;
    }

  return 0;
}

int
mt_setdefaultcolor (void)
{
  fflush (stdout);

  if (write (STDOUT_FILENO, "\033[0m", 4) == -1)
    {
      return -1;
    }

  return 0;
}
