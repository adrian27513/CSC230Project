/**
  @file byteBuffer.c
  @author Adrian Chan
  Creates and processes ByteBuffers to the requirements of ripeMD
*/

#include "byteBuffer.h"

ByteBuffer *createBuffer()
{
  ByteBuffer *buffer = malloc(sizeof(ByteBuffer));
  buffer->data = malloc(INITIAL_CAP * sizeof(byte));
  buffer->len = 0;
  buffer->cap = INITIAL_CAP;
  
  return buffer;
}

void addByte(ByteBuffer *buffer, byte b)
{
  if (buffer->len == buffer->cap) {
    buffer->cap *= CAP_INCREASE;
    buffer->data = realloc(buffer->data, buffer->cap * sizeof(byte));
  }
  
  buffer->data[buffer->len++] = b;
}

void freeBuffer(ByteBuffer *buffer)
{
  free(buffer->data);
  free(buffer);
}

ByteBuffer *readFile(const char *filename)
{
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL) {
    return NULL;
  }
  
  ByteBuffer *buffer = createBuffer();
  int bytesRead = 1;
  
  while (bytesRead != 0) {
    bytesRead = fread(buffer->data + buffer->len, sizeof(byte), buffer->cap - buffer->len, fp);
    buffer->len += bytesRead;
    if (buffer->len == buffer->cap) {
      buffer->cap *= CAP_INCREASE;
      buffer->data = realloc(buffer->data, buffer->cap * sizeof(byte));
    }
  }
  fclose(fp);
  
  return buffer;
  
}
