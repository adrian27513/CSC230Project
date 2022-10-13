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
  
  FILE *outFile = fopen(argv[OUTPUT_ELEMENT], "w");
  FILE *input = fopen(argv[INPUT_ELEMENT], "r");
  
  if (!input) {
    fprintf(stderr, "Can't open file: %s\n", argv[INPUT_ELEMENT]);
    exit(1);
  }
  
  if (!outFile) {
    fprintf(stderr, "Can't open file: %s\n", argv[OUTPUT_ELEMENT]);
    exit(1);
  }
  
  char *target[(argc - 3) / 2];
  char **targetPointer = target;
  char *replacement[(argc - 3) / 2];
  char **replacementPointer = replacement;
  
  int maxLength = 0;
  int pairs = 0;
  int targetCount = 0;
  for (int i = 1; i < argc - 2; i++) {
    
    for (int j = 0; j < targetCount; j++) {
      if (strcmp(target[j], argv[i]) == 0) {
        fprintf(stderr, "Duplicate target: %s\n", argv[i]);
        exit(1);
      }
    }
    
    if (i % 2 == 1) {
      *targetPointer++ = argv[i];
      targetCount++;
    } else {
      *replacementPointer++ = argv[i];
    }
    
    if (maxLength < strlen(argv[i])) {
        maxLength = strlen(argv[i]);
    }
    
    char *start = argv[i];
    while (*start != '\0') {
      if (!wordChar(*start++)) {
        fprintf(stderr, "Invalid word: %s\n", argv[i]);
        exit(1);
      }
    }
    
    pairs++;
  }
  int lineLength = measureLine(input);
  while (lineLength != 0) {
    char str[lineLength + 2];
    readLine(input, str);
    
    int expansion = expansionBound(str, maxLength);
    
    char expandedStr[lineLength + expansion + 1];
    
    expand(str, expandedStr, target, replacement, (pairs/2));
    fprintf(outFile, "%s", expandedStr);
    lineLength = measureLine(input);
  }
  fclose(outFile);
  fclose(input);
  return EXIT_SUCCESS;
}
