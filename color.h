#ifndef COLORS
  #define COLORS
  #include <stdio.h>
  #define clrscr() printf("\033[H\033[2J")
  #define couleur(param) printf("\033[%sm",param)
#endif
