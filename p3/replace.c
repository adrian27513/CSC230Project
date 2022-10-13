/**
  */

#include "line.h"
#include "expand.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** Number of required arguments at the end of the command line. */
#define REQUIRED_ARGS 2
#define INPUT_ELEMENT argc - 2
#define OUTPUT_ELEMENT argc - 1
int main (int argc, char *argv[])
{
  //if (argc < REQUIRED_ARGS) {
  //  exit(1);
  //}
  
  FILE *outFile = fopen(argv[OUTPUT_ELEMENT], "w");
  FILE *input = fopen(argv[INPUT_ELEMENT], "r");
  
  if (!outFile || !input) {
    fprintf(stderr, "usage: replace (<target> <replacement>)* <input-file> <output-file>");
  }
  char *target[(argc - 3) / 2];
  char **targetPointer = target;
  char *replacement[(argc - 3) / 2];
  char **replacementPointer = replacement;
  
  int maxLength = 0;
  int pairs = 0;
  
  for (int i = 1; i < argc - 2; i++) {
    if (i % 2 == 1) {
      *targetPointer++ = argv[i];
    } else {
      *replacementPointer++ = argv[i];
    }
    
    if (maxLength < strlen(argv[i])) {
        maxLength = strlen(argv[i]);
    }
    pairs++;
  }
  int lineLength = measureLine(input);
  while (lineLength != 0) {
    char str[lineLength];
    readLine(input, str);
    
    int expansion = expansionBound(str, maxLength);
    
    char expandedStr[lineLength + expansion + 1];
    
    expand(str, expandedStr, target, replacement, (pairs/2));
    fprintf(outFile, "%s\n", expandedStr);
    lineLength = measureLine(input);
  }
  fclose(outFile);
  fclose(input);
  return EXIT_SUCCESS;
}