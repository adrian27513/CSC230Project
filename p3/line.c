/**
  */

#include "line.h"

int measureLine(FILE *fp)
{
  long location = ftell(fp);
  char ch = ' ';
  int count = 0;
  while ( ch != '\n' && ch != '\0' && fscanf(fp, "%c", &ch) != EOF ) {
    count++;
  }
  
  fseek(fp, location, SEEK_SET);
  return count;
}

void readLine(FILE *fp, char str[])
{
  char ch = ' ';
  char *start = str;
  while (ch != '\n' && ch != '\0' && fscanf(fp, "%c", &ch) != EOF) {
    *start++ = ch;
  }
  *start = '\0';
  
}
