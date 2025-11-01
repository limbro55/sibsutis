#ifndef MY_BIGCHARS_H
#define MY_BIGCHARS_H

#include "../include/myTerm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// подсчитывает количество
// символов в UTF-8 строке
int bc_strlen (char *str);

// выводит строку символов с
// использованием дополнительной
// кодировочной таблицы
int bc_printA (char *str);

// выводит на экран псевдографическую рамку
int bc_box (int x1, int y1, int x2, int y2, enum Colors box_fg,
            enum Colors box_bg, char *header, enum Colors header_fg,
            enum Colors header_bg);

int bc_setbigcharpos (int *big, int x, int y, int value);
int bc_getbigcharpos (int *big, int x, int y, int *value);
int bc_printbigchar (int *big, int x, int y, enum Colors fg, enum Colors bg);
int bc_bigcharwrite (int fd, int *big, int count);
int bc_bigcharread (int fd, int *big, int need_count, int *count);

int generateFont ();
void printBigCell (int cell, int x, int y);

#endif
