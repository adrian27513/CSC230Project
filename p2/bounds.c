#include "bounds.h"
#include <limits.h>
#include <stdlib.h>
void checkAdd(long a, long b)
{
  long sum = a + b;
  if (a > 0 && b > 0 && sum < 0) {
    exit(100);
  } else if (a < 0 && b < 0 && sum > 0) {
    exit(100);
  }
}

void checkSub(long a, long b)
{
  long difference = a - b;
  if (a > 0 && b < 0 && difference < 0) {
    exit(100);
  } else if (a < 0 && b > 0 && difference > 0) {
    exit(100);
  }
}
void checkMul(long a, long b)
{
  if (a != 0 || b != 0) {
    if (a > 0 && b > 0) {
      long max = LONG_MAX / b;
      if (a > max) {
        exit(100);
      }
    } else if (a < 0 && b < 0) {
      long max = LONG_MAX / b;
      if (a < max) {
        exit(100);
      }
    } else if (a > 0 && b < 0) {
      long max = LONG_MIN / b;
      if (a > max) {
        exit(100);
      }
    } else if (a < 0 && b > 0) {
      long max = LONG_MIN / a;
      if (b > max) {
        exit(100);
      }
    }
  }
}
void checkDiv(long a, long b)
{
  if (b == 0) {
    exit(101);
  }
  
  if (a == LONG_MIN && b == -1) {
    exit(100);
  }
}