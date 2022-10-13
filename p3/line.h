/**
  @file line.h
  @author Adrian Chan (amchan)
  Header file and declares public implementation of line.c
*/

#include <stdio.h>

/**
  Measures the length of next line from a given file input.
  @param fp file the next line is being measure from
  @return length of the line
*/
int measureLine(FILE *fp);

/**
  Reads in a line from a file input into a string.
  @param fp file being read
  @param str string to read next line into
*/
void readLine(FILE *fp, char str[]);
