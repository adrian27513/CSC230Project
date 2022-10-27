/**
  @file input.h
  @author Adrian Chan (amchan)
  Header file and declares the public imlementation of input.c
*/
#include <stdio.h>
#include <stdlib.h>

/**
  Reads one line from a given file and returns a string
  @param fp file to read from
  @return string of the line read
*/
char *readLine(FILE *fp);
