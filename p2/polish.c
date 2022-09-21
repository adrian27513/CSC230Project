/**
  @file polish.c
  @author Adrian Chan (amchan)
  This program reads in an expression in polish notation and prints out the value of the expression in either base32 or base10.
*/
#include "base.h"
#include "bounds.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
  Parses the polish notation expression from standard input until EOF in either base10 or base32. Exits the program if there is no input.
  @return value of the polish expression read from standard input.
*/
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

/**
  This is the program starting point. Reads in whitespace from standard input until reaching the first non-white space character. It prints out the value of the
  polish notation expression(s) that was given in standard input.
  @return program exit status
*/
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
