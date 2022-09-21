/**
  @file base32.c
  @author Adrian Chan (amchan)
  This program reads in values from standard input in base32 and converts them to base10 to be processed by the program. It also converts base10 values to base32
  once the calculations are completed to be printed out.
*/
#include "base.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/** Exit code if a value is out of range of a signed long */
#define OUTSIDE_LONG_RANGE 100
/** Letter offset for conversion from base32 to base10 and vice versa */
#define BASE_32_OFFSET 10

/**
  Converts a base32 char input into a base10 long. Exits if char is not a valid base32 value.
  @param ch a base32 char
  @return the equivalent base10 long
*/
static long charToDigit(int ch)
{
  if (ch >= '0' && '9' >= ch) {
    return ch - '0';
  } else if (ch >= 'A' && 'V' >= ch) {
    return ch - 'A' + BASE_32_OFFSET;
  }
  exit(FAIL_INPUT);
}

/**
  Converts a base10 long input into a base32 char.
  @param d a base10 long
  @return the equivlent base32 char
*/
static int digitToChar(long d) {
  if (d <= 9) {
    return d + '0';
  }
  return d - BASE_32_OFFSET + 'A';
}

/**
  Validates if the char is either a base32 value or other valid char value. Exits the program if not a valid char value.
  @param ch char to be checked
  @return true if a base32 value or false if the char is a valid char value but not a base32 value.
*/
static bool validateChar(int ch)
{
  if ((ch >= '0' && '9' >= ch) || (ch >= 'A' && 'V' >= ch)) {
    return true;
  } else if (ch == '\n' || ch == ' ' || ch == '~' || ch == '/' || ch == '*' || ch == '+') {
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

/**
  Prints a base32 value from a given base10 long value.
  @param val base10 long value to be converted
  @return if value is equal to 0
*/
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
