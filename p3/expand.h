/**
  @file expand.h
  @author Adrian Chan (amchan)
  Header file and declares the public implmentation of expand.c
*/

#include <stdbool.h>
#include <string.h>

/**
  Check if a given char is a valid word character: alphanumeric or underscore.
  @param ch character to check
  @return true if valid false if not
*/
bool wordChar(int ch);

/**
  Calculates how big of an array expansion will need to be done.
  @param src start of string
  @param maxRep the max length of any replacement string
  @return length to increase the original char array by
*/
int expansionBound(char *src, int maxRep);
/**
  Expands the original string by replacing words using given target-replacement pairs.
  @param src original string
  @param dest new expanded string
  @param tlist list of target words
  @param list of replacement words
  @param pairs number of target-replacement pairs
*/
void expand(char *src, char *dest, char *tlist[], char *rlist[], int pairs);
