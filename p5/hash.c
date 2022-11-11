/**
  */
  
#include "byteBuffer.h"
#include "ripeMD.h"

#define ONE_USER_INPUT 2
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
  free(buffer);
  printHash(state);
}
