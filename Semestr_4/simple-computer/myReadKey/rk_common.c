#include "../include/myReadKey.h"
#include "myCuAlu.h"
#include "mySimpleComputer.h"

#include <ctype.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>

struct termios SETTINGS;

int
rk_readkey (enum Keys *key)
{
  fflush (stdout);
  char buffer[5] = "\0";
  read (STDIN_FILENO, buffer, 5);
  if (key == NULL)
    return 0;
  if (buffer[0] == '\033')
    if (buffer[1] == '\0')
      *key = KEY_ESC;
    else if (buffer[1] == '[')
      if (buffer[2] == 'A' && buffer[3] == '\0')
        *key = KEY_UP;
      else if (buffer[2] == 'B' && buffer[3] == '\0')
        *key = KEY_DOWN;
      else if (buffer[2] == 'C' && buffer[3] == '\0')
        *key = KEY_RIGHT;
      else if (buffer[2] == 'D' && buffer[3] == '\0')
        *key = KEY_LEFT;
      else if (buffer[2] == '1' && buffer[3] == '5')
        *key = KEY_F5;
      else if (buffer[2] == '1' && buffer[3] == '7')
        *key = KEY_F6;
      else
        *key = KEY_OTHER;
    else
      *key = KEY_OTHER;
  else if (buffer[0] == '\n' && buffer[1] == '\0')
    *key = KEY_ENTER;
  else if ((buffer[0] == 'l' || buffer[0] == 'L') && buffer[1] == '\0')
    *key = KEY_L;
  else if ((buffer[0] == 's' || buffer[0] == 'S') && buffer[1] == '\0')
    *key = KEY_S;
  else if ((buffer[0] == 'i' || buffer[0] == 'I') && buffer[1] == '\0')
    *key = KEY_I;
  else if ((buffer[0] == 'r' || buffer[0] == 'R') && buffer[1] == '\0')
    *key = KEY_R;
  else if ((buffer[0] == 't' || buffer[0] == 'T') && buffer[1] == '\0')
    *key = KEY_T;

  else
    *key = KEY_OTHER;
  return 0;
}

int
rk_mytermsave ()
{
  if (tcgetattr (STDIN_FILENO, &SETTINGS))
    return -1;
  return 0;
}

int
rk_mytermrestore ()
{
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &SETTINGS);
  return 0;
}

int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
  struct termios curr;
  tcgetattr (STDIN_FILENO, &curr);

  if (regime)
    curr.c_lflag |= ICANON;
  else
    {
      curr.c_lflag &= ~ICANON;
      sigint ? (curr.c_lflag |= ISIG) : (curr.c_lflag &= ~ISIG);
      echo ? (curr.c_lflag |= ECHO) : (curr.c_lflag &= ~ECHO);
      curr.c_cc[VMIN] = vmin;
      curr.c_cc[VTIME] = vtime;
    }

  tcsetattr (0, TCSAFLUSH, &curr);

  return 0;
}

static int
converter (int *num)
{
  if (*num > 16383)
    {
      *num -= 16384;
      *num = (16383 - *num + 1) * -1;
    }
  return 0;
}

// -1 возвращаем, когда значение не должно меняться
int
rk_readvalue (int *value)
{
  isig_generator_stop ();
  rk_mytermregime (0, 0, 1, 1, 0);

  int err_code = 0;
  const int buf_size = 6;
  char buffer[buf_size];
  buffer[buf_size - 1] = '\0';

  char ch;
  fflush (stdin);
  for (int i = 0; buffer[i] != '\0'; ++i)
    {
      ch = getchar ();
      if (i == 0)
        {
          if (ch == '0')
            printf ("\b+");
          else if (ch == '1')
            printf ("\b-");
          else if (ch == '+')
            ch = '0';
          else if (ch == '-')
            ch = '1';
        }

      if (ch == '\e' || ch == '\n')
        {
          err_code = -1;
          break;
        }
      else
        buffer[i] = ch;
    }

  // проверка на корректность ввода
  if (!(buffer[0] == '0' || buffer[0] == '1') && err_code != -1)
    err_code = -1;
  for (int i = 1; buffer[i] != 0 && err_code != -1; ++i)
    {
      if (i % 2 == 1)
        {
          if (buffer[i] > '7' || buffer[i] < '0')
            {
              err_code = -1;
            }
        }
      else
        {
          if (!(('0' <= buffer[i] && buffer[i] <= '9')
                || ('A' <= buffer[i] && buffer[i] <= 'F')
                || ('a' <= buffer[i] && buffer[i] <= 'f')))
            {
              err_code = -1;
            }
        }
    }

  if (err_code != -1)
    {
      int number;
      char *tmp;
      int sign, cmd, op;

      number = strtol (buffer, &tmp, 16);
      sign = (number >> 16) & 0x1;
      cmd = (number >> 8) & 0x7F;
      op = number & 0x7F;
      number = (sign << 14) | (cmd << 7) | op;
      converter (&number);
      *value = number;
    }

  rk_mytermregime (0, 30, 0, 0, 0);
  isig_generator_start ();

  return err_code;
}
