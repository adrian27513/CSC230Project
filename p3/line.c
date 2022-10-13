/**
  @file line.c
  @author Adrian Chan (amchan)
  This program measures the next line length of a given file and reads in the next line from a file to a string.
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
