/**
  @file input.c
  @author Adrian Chan (amchan)
  Reads a line from a file and returns the line read as a string
*/
#include "input.h"

char *readLine(FILE *fp)
{
  int capacity = 50;
  int len = 0;
  
  char *str = malloc(capacity * sizeof(char));
  
  char ch;
  
  while (fscanf(fp, "%c", &ch) == 1) {
    if (ch == EOF || ch == '\0') {
      return '\0';
    }
    if (ch == '\n') {
      str[len] = '\0';
      return str;
    }
    
    if (len == capacity - 2) {
      capacity = 2 * capacity;
      str = realloc(str, capacity * sizeof(char));
    }
    str[len++] = ch;
  }
  
  str[len] = '\0';
  
  return str;
}
