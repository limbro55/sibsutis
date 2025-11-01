#ifndef MY_READKEY_H
#define MY_READKEY_H

#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <unistd.h>

enum Keys
{
  KEY_L,
  KEY_S,
  KEY_I,
  KEY_F5,
  KEY_F6,
  KEY_UP,
  KEY_DOWN,
  KEY_RIGHT,
  KEY_LEFT,
  KEY_ESC,
  KEY_ENTER,
  KEY_OTHER,
  KEY_R,
  KEY_T,
};

int rk_readkey (enum Keys *);
int rk_mytermsave (void);
int rk_mytermrestore (void);
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
int rk_readvalue (int *value);
void handleKeyPress (enum Keys *key);
void printKeys ();

#endif
