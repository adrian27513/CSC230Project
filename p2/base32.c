#include "base.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define OUTSIDE_LONG_RANGE 100
#define BASE_32_OFFSET 10

static long charToDigit(int ch)
{
  if (ch >= '0' && '9' >= ch) {
    return ch - '0';
  } else if (ch >= 'A' && 'V' >= ch) {
    return ch - 'A' + BASE_32_OFFSET;
  }
  exit(FAIL_INPUT);
}

static int digitToChar(long d) {
  if (d <= 9) {
    return d + '0';
  }
  return d - BASE_32_OFFSET + 'A';
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
    exit(FAIL_INPUT);
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
        exit(OUTSIDE_LONG_RANGE);
      }
    } else {
      if (LONG_MAX - value < sum) {
        exit(OUTSIDE_LONG_RANGE);
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
