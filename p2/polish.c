#include "base.h"
#include "bounds.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static long parseExpression()
{ 
  int ch = getchar();
  signed long a = 0;
  signed long b = 0;
  
  while (ch != EOF) {
    switch (ch) {
      case '+':
        a = parseExpression();
        b = parseExpression();
        checkAdd(a, b);
        return a + b;
      case '~':
        a = parseExpression();
        b = parseExpression();
        checkSub(a, b);
        return a - b;
      case '*':
        a = parseExpression();
        b = parseExpression();
        checkMul(a, b);
        return a * b;
      case '/':
        a = parseExpression();
        b = parseExpression();
        checkDiv(a, b);
        return a / b;
      case ' ':
        break;
      case '\n':
        break;
      default:
        ungetc(ch, stdin);
        return readNumber();
    }
    ch = getchar();
  }
  exit(FAIL_INPUT);
}

int main()
{
  
  int ch = getchar();
  signed long out = 0;
  while (ch != EOF) {
    if (ch != ' ' && ch != '\n') {
      ungetc(ch, stdin);
      out = parseExpression();
      printNumber(out);
    }
    ch = getchar();
  }
  
  return EXIT_SUCCESS;
}