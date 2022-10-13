/**
  @file replace.c
  @author Adrian Chan (amchan)
  This program replaces words from a given file according to user input.
*/

#include "line.h"
#include "expand.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** Number of required arguments at the end of the command line. */
#define REQUIRED_ARGS 2
/** Input Element Offset in argv array */
#define INPUT_ELEMENT argc - 2
/** Output Element Offset in argv array */
#define OUTPUT_ELEMENT argc - 1
/** Number of target/replacement words */
#define PAIRS_COUNT (argc - 3) / 2
/**
  This is the program starting point. It reads from a file and replaces user given target-replacement pairs and outputs the result to another file.
  @param argc number of command line arguments
  @param argv list of command line arguments
  @return program exit status
*/
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
  
  char *target[PAIRS_COUNT];
  char **targetPointer = target;
  char *replacement[PAIRS_COUNT];
  char **replacementPointer = replacement;
  
  int maxLength = 0;
  int pairs = 0;
  int targetCount = 0;
  int replaceCount = 0;
  
  for (int i = 1; i < INPUT_ELEMENT; i++) {
    if (i % 2 == 1) {
      for (int j = 0; j < targetCount; j++) {
        if (strcmp(target[j], argv[i]) == 0) {
          fprintf(stderr, "Duplicate target: %s\n", argv[i]);
          exit(1);
        }
      }
      
      for (int j = 0; j < targetCount; j++) {
        if (strcmp(target[j], argv[i + 1]) == 0) {
          target[j] = argv[i];
        }
      }
      *targetPointer++ = argv[i];
      targetCount++;
    } else {
      *replacementPointer = argv[i];
      
      for (int j = 0; j < replaceCount; j++) {
        if (strcmp(replacement[j], argv[i - 1]) == 0) {
          replacement[j] = argv[i];
        }
      }
      replacementPointer++;
      replaceCount++;
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
