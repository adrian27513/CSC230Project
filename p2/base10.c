/**
  @file base10.c
  @author Adrian Chan (amchan)
  This program reads in base10 signed long values from standard input and prints out base10 signed long values.
*/
#include "base.h"
#include <stdio.h>
#include <stdlib.h>

long readNumber()
{
  signed long out = 0;
  if (scanf("%ld", &out) != 1) {
    exit(FAIL_INPUT);
  }
  return out;
}

void printNumber(long val)
{
  printf("%ld",val);
  putchar('\n');
}
