#!/bin/bash

ENTER_ACS=$(tput smacs) #переходим в режим псевдографики
EXIT_ACS=$(tput rmacs) #выходим из режима псевдографики

# Очистка экрана
echo -e "\033[2J"

YGOL1="${ENTER_ACS}l${EXIT_ACS}" # ┌
YGOL2="${ENTER_ACS}k${EXIT_ACS}" # ┐
YGOL3="${ENTER_ACS}m${EXIT_ACS}" # └
YGOL4="${ENTER_ACS}j${EXIT_ACS}" # ┘
GORIZONT="${ENTER_ACS}q${EXIT_ACS}" # ─
VERT="${ENTER_ACS}x${EXIT_ACS}" # │
BLOCK="${ENTER_ACS}a${EXIT_ACS}"


# Выводим цифру 0 в рамке
echo " $YGOL1$GORIZONT$GORIZONT$GORIZONT$GORIZONT$YGOL2 "
echo " $VERT$BLOCK$BLOCK$BLOCK$BLOCK$VERT "
echo " $VERT$BLOCK  $BLOCK$VERT "
echo " $VERT$BLOCK  $BLOCK$VERT "
echo " $VERT$BLOCK$BLOCK$BLOCK$BLOCK$VERT "
echo " $YGOL3$GORIZONT$GORIZONT$GORIZONT$GORIZONT$YGOL4 "