#include "base.h"
#include <stdio.h>
#include <stdlib.h>

long readNumber()
{
  signed long out = 0;
  if (scanf("%ld", &out) != 1) {
    exit(102);
  }
  return out;
}

void printNumber(long val)
{
  printf("%ld",val);
  putchar('\n');
}