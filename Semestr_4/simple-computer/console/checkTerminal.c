#include "myTerm.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

void
checkTerminal ()
{
  if (!isatty (STDOUT_FILENO))
    {
      fprintf (stderr, "Ошибка: выходной поток не является терминалом\n");
      exit (EXIT_FAILURE);
    }
  else
    {
      printf ("Поток вывода соответсвует терминалу\n");
    }
}

void
checkScreenSize ()
{
  struct winsize w;

  ioctl (STDOUT_FILENO, TIOCGWINSZ, &w);
  if (w.ws_col < INTERFACE_WIDTH || w.ws_row < INTERFACE_HEIGHT)
    {
      fprintf (stderr,
               "Ошибка: недостаточный размер экрана (требуется %dx%d)\n",
               INTERFACE_WIDTH, INTERFACE_HEIGHT);
      exit (EXIT_FAILURE);
    }
  else
    {
      printf ("Проверка размера экрана пройдена\n");
    }
}

void
clearScreen ()
{
  printf ("\033[2J\033[H");
  printf ("Экран очищен");
}