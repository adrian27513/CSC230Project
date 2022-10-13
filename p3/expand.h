/**
  */

#include <stdbool.h>
#include <string.h>

bool wordChar(int ch);
int expansionBound(char *src, int maxRep);
void expand(char *src, char *dest, char *tlist[], char *rlist[], int pairs);