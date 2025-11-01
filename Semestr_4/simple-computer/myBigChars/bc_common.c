#include "../include/myBigChars.h"
#include "../include/myTerm.h"

int
bc_strlen (char *str)
{
  if (!str)
    return 0;
  size_t len = 0;
  while (*str)
    {
      if ((*str & 0xC0) != 0x80)
        len++; // тест на то, что символ utf-8
      str++;
    }
  return len;
}

int
bc_printA (char *str)
{
  if (!str)
    return -1;
  printf ("\033(0%s\033(B", str);
  return 0;
}

int
bc_box (int x1, int y1, int x2, int y2, enum Colors box_fg, enum Colors box_bg,
        char *header, enum Colors header_fg, enum Colors header_bg)
{
  // устанавливаем цвет рамки
  mt_setfgcolor (box_fg);
  mt_setbgcolor (box_bg);

  // первая строчка
  mt_gotoXY (x1, y1);

  bc_printA ("┌");
  for (int cx = x1 + 1; cx < x2; ++cx)
    {
      bc_printA ("─");
    }
  bc_printA ("┐");

  // отрисовка заголовка
  if (header != NULL)
    {
      int header_len = bc_strlen (header);
      int header_begin = x1 + (x2 - x1) / 2.0 - header_len / 2.0;
      mt_setfgcolor (header_fg);
      mt_setbgcolor (header_bg);
      mt_gotoXY (header_begin, y1);
      printf (" %s ", header);
    }
  mt_setfgcolor (box_fg);
  mt_setbgcolor (box_bg);

  // середина
  for (int cy = y1 + 1; cy < y2; ++cy)
    {
      mt_gotoXY (x1, cy);
      bc_printA ("│");
      mt_gotoXY (x2, cy);
      bc_printA ("│");
    }

  // последняя строка
  mt_gotoXY (x1, y2);
  bc_printA ("└");
  for (int cx = x1 + 1; cx < x2; ++cx)
    {
      bc_printA ("─");
    }
  bc_printA ("┘");

  // возвращаемся к изначальным цветам терминала
  mt_setdefaultcolor ();
  mt_gotoXY (x1, y2 + 1);

  return 0;
}

int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  int pos;

  if ((x < 0) || (y < 0) || (x > 7) || (y > 7) || (value < 0) || (value > 1))
    return -1;

  if (y <= 3)
    pos = 0;
  else
    pos = 1;

  y = y % 4;

  if (value == 0)
    big[pos] &= ~(1 << (y * 8 + x));
  else
    big[pos] |= 1 << (y * 8 + x);

  return 0;
}

int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  int pos;

  if ((x < 0) || (y < 0) || (x > 7) || (y > 7))
    return -1;

  if (y <= 3)
    pos = 0;
  else
    pos = 1;

  y = y % 4;
  *value = (big[pos] >> (y * 8 + x)) & 1;

  return 0;
}

int
bc_printbigchar (int *big, int x, int y, enum Colors fg, enum Colors bg)
{
  int maxx, maxy;
  int bit;
  int i, j;
  char row[9];

  mt_getscreensize (&maxy, &maxx);
  if ((x < 0) || (y < 0) || (x + 8 > maxx) || (y + 8 > maxy))
    return -1;
  row[8] = '\0';
  if (fg != BLACK)
    mt_setfgcolor (fg);
  if (bg != BLACK)
    mt_setbgcolor (bg);
  for (i = 0; i < 8; i++)
    {
      for (j = 0; j < 8; j++)
        {
          bc_getbigcharpos (big, j, i, &bit);
          if (!bit)
            row[j] = ' ';
          else
            row[j] = 'a';
        }
      mt_gotoXY (x, y + i);
      bc_printA (row);
    }

  mt_setdefaultcolor ();

  return 0;
}

int
bc_bigcharwrite (int fd, int *big, int count)
{
  if (fd < 0 || big == NULL || count <= 0)
    return -1;

  ssize_t bytes_to_write = count * 2 * sizeof (int); // 2 int на символ
  ssize_t written = write (fd, big, bytes_to_write);

  if (written != bytes_to_write)
    return -1;

  return 0;
}

int
bc_bigcharread (int fd, int *big, int need_count, int *count)
{
  if (fd < 0 || big == NULL || need_count <= 0 || count == NULL)
    return -1;

  ssize_t bytes_to_read = need_count * 2 * sizeof (int); // 2 int на символ
  ssize_t read_bytes = read (fd, big, bytes_to_read);

  if (read_bytes < 0 || read_bytes % (2 * sizeof (int)) != 0)
    {
      *count = 0;
      return -1;
    }

  *count = read_bytes / (2 * sizeof (int));
  return 0;
}
