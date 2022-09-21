#include "base.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

static long charToDigit(int ch)
{
  if (ch >= '0' && '9' >= ch) {
    return ch - '0';
  } else if (ch >= 'A' && 'V' >= ch) {
    return ch - 'A' + 10;
  }
  exit(102);
}

static int digitToChar(long d) {
  if (d <= 9) {
    return d + '0';
  }
  return d - 10 + 'A';
}

static bool acceptedChar(int ch)
{
  return ch == '\n' || ch == ' ' || ch == '~' || ch == '/' || ch == '*' || ch == '+';
}
static bool validateChar(int ch)
{
  if ((ch >= '0' && '9' >= ch) || (ch >= 'A' && 'V' >= ch)) {
    return true;
  } else if (acceptedChar(ch)) {
    return false;
  } else {
    exit(102);
  }
}
long readNumber()
{
  long value = 0;
  int ch = getchar();
  bool negative = false;
  
  if (ch == '-') {
    negative = true;
    ch = getchar();
  }  
  
  while (validateChar(ch)) {
    long d = charToDigit(ch);
    value = value * 32;
    long sum = negative ? -d : d;
    
    if (negative) {
      if (LONG_MIN - value > sum) {
        exit(100);
      }
    } else {
      if (LONG_MAX - value < sum) {
        exit(100);
      }
    }
    value = value + sum;
    ch = getchar();
  }
  
  ungetc(ch, stdin);
  return value;
}

static void printBase32(long val)
{
  if (val == 0) {
    return;
  }
  
  bool negative = val < 0;
  
  long d = val % 32;
  
  long digit = negative ? -d : d;
  
  int ch = digitToChar(digit);
  printBase32(val / 32);
  putchar(ch);
}
void printNumber(long val)
{
  if (val == 0) {
    putchar('0');
  }
  
  if (val < 0) {
    putchar('-');
  }
  printBase32(val);
  putchar('\n');
}
