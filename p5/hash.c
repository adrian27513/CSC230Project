/**
  @file hash.c
  @author Adrian Chan (amchan)
  Hashes a given file using the ripeMD algorithm
*/
  
#include "byteBuffer.h"
#include "ripeMD.h"

/** argc value when given one user input */
#define ONE_USER_INPUT 2

/**
  Program starting point. Hashes a given file using ripeMD.
  @param argc number of command line arguements
  @param argv list of command line arguements
  @return exit status of program
*/
int main(int argc, char *argv[])
{
  if (argc != ONE_USER_INPUT) {
    fprintf(stderr, "usage: hash <input-file>\n");
    exit(1);
  }
  ByteBuffer *buffer = readFile(argv[1]);
  
  if (buffer == NULL) {
    perror(argv[1]);
    exit(1);
  }
  HashState *state = malloc(sizeof(HashState));
  initState(state);
  padBuffer(buffer);
  
  for (int i = 0; i < buffer->len / BLOCK_BYTES; i++) {
    hashBlock(state, buffer->data + (BLOCK_BYTES * i));
  }
  
  freeBuffer(buffer);
  printHash(state);
  free(state);
}
