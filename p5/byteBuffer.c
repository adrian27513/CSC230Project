/** 
*/

#include "byteBuffer.h"


ByteBuffer *createBuffer()
{
  ByteBuffer *buffer = malloc(sizeof(ByteBuffer));
  buffer->data = malloc(5 * sizeof(byte));
  buffer->len = 0;
  buffer->cap = 5;
}

void addByte(ByteBuffer *buffer, byte b)
{
  if (buffer->len == buffer->cap) {
    buffer->cap *= 2;
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
  int bytesRead = fread(buffer->data, sizeof(byte), buffer->cap, fp);
  
  while (bytesRead == buffer->cap) {
    buffer->cap *= 2;
    buffer->data = realloc(buffer->data, buffer->cap * sizeof(byte));
    bytesRead = fread(buffer->data, sizeof(byte), buffer->cap, fp);
  }
  buffer->len = bytesRead;
  fclose(fp);
  
}