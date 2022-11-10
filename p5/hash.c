/**
  */
  
#include "byteBuffer.h"
#include "ripeMD.h"

int main(int argc, char *argv[])
{
  ByteBuffer *buffer = readFile(argv[1]);
  HashState *state = malloc(sizeof(HashState));
  initState(state);
  hashBlock(state, buffer->data);
  free(buffer);
  printHash(state);
}
