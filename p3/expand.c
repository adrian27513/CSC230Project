/**
  @file expand.c
  @author Adrian Chan (amchan)
  This program checks the validatiy of a given character, calculates the amount the original string will need to be expanded by, and expands the string
  using given target-replacement pairs.
*/

#include "expand.h"

bool wordChar(int ch)
{
  if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || (ch == '_')) {
    return true;
  }
  
  return false;
}
int expansionBound(char *src, int maxRep)
{
  int length = 0;
  int increase = 0;
  char *start = src;
  char ch = *start;
  while (ch != '\0') {
    if (!wordChar(ch)) {
      if (maxRep - length > 0) {
        increase += maxRep - length;
      }
      length = 0;
    }
    
    length++;
    ch = *(start++);
  }
  
  return increase;
}
void expand(char *src, char *dest, char *tlist[], char *rlist[], int pairs)
{
  char ch = *src;
  char *start = src;
  char *ptr = src;
  bool end = false;
  
  while (!wordChar(ch) && ch != '\n') {
      ptr++;
      *dest++ = ch;
      ch = *ptr;
  }
  if (ch == '\n') {
    end = true;
  }
  start = ptr;
  while (ch != '\n') {
    
    while (wordChar(ch)) {
      ptr++;
      ch = *ptr;
    }
    
    if (ch == '\n') {
      end = true;
    }
    int length = ptr - start;
    
    int stringLength = length + 2;
    
    char str[stringLength];
    char *temp = start;
    for (int i = 0; i < length; i++) {
      str[i] = *temp++;
    }
    
    str[length] = '\0';
    
    bool found = false;
    for (int i = 0; i < pairs; i++) {
      if (strcmp(str, tlist[i]) == 0) {
        strcpy(dest, rlist[i]);
        dest += strlen(rlist[i]);
        found = true;
        break;
      }
    }
    
    if (!found) {
      strcpy(dest, str);
      dest += strlen(str);
    }
    
    while (!wordChar(ch) && ch != '\n') {
      ptr++;
      *dest++ = ch;
      ch = *ptr;
    }
    
    if (ch == '\n') {
      end = true;
    }
    start = ptr;
  }
  
  if (end) {
    *dest++ = '\n';
  }
  *dest = '\0';
}
