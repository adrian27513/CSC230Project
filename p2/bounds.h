/**
  @file bounds.h
  @author Adrian Chan (amchan)
  Header file and declares the public implementation of bounds.c.
*/

/** Exit code if a value is out of range of a signed long */
#define OUTSIDE_LONG_RANGE 100
/** Exit code if there is an attempt to divide by 0 */
#define DIV_BY_ZERO 101

/**
  Checks if addtion between two values does not overflow. Exits the program if addition overflows.
  @param a first value to be checked
  @param b second value to be checked
*/
void checkAdd(long a, long b);

/**
  Checks if subtraction between two values does not overflow. Exits the program if subtraction overflows.
  @param a first value to be checked
  @param b second value to be checked
*/
void checkSub(long a, long b);

/**
  Checks if multiplication between two values does not overflow. Exits the program if multiplication overflows.
  @param a first value to be checked
  @param b second value to be checked
*/
void checkMul(long a, long b);

/**
  Checks if division between two values does not overflow. Exits the program if division overflows or if there is an attempt to divide by 0.
  @param a first value to be checked
  @param b second value to be checked
*/
void checkDiv(long a, long b);
