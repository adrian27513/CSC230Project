/**
  */
  
#include "byteBuffer.h"
#include "ripeMD.h"

int main(int argc, char *argv[])
{
  if (argc != 2) {
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
  
  for (int i = 0; i < buffer->len / 64; i++) {
    hashBlock(state, buffer->data + (64 * i));
  }
  free(buffer);
  printHash(state);
}
