/**
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
  
  while (!wordChar(ch) && ch != '\n') {
      ptr++;
      *dest++ = ch;
      ch = *ptr;
    }
  start = ptr;
  
  while (ch != '\n') {
    while (wordChar(ch)) {
      ptr++;
      ch = *ptr;
    }
    int length = ptr - start;
    char str[length + 1];
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
    start = ptr;
  }
  *dest = '\0';
}
