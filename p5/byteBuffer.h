/**
  @file byteBuffer.h
  @author Adrian Chan
  Header file and declares the public implementation of byteBuffer.c
*/

#ifndef _BYTE_BUFFER_H_
#define _BYTE_BUFFER_H_

#include <stdlib.h>
#include <stdio.h>

/** Number of bits in a byte */
#define BBITS 8

/** Initial capacity of ByteBuffer data array */
#define INITIAL_CAP 5

/** Amount to increase capacity by */
#define CAP_INCREASE 2

/** Type used as a byte. */
typedef unsigned char byte;

/** Representation for a file copied to memory, with some padding
    at the end. */
typedef struct {
  /** Array of bytes from the file (no null termination, so it's not a
      string). */
  byte *data;

  /** Number of currently used bytes in the data array. */
  unsigned int len;

  /** Capacity of the data array (it's typically over-allocated. */
  unsigned int cap;
} ByteBuffer;

/**
  Creates and initializes a ByteBuffer
  @return pointer to initialized ByteBuffer
*/
ByteBuffer *createBuffer();

/**
  Adds a given byte to the ByteBUffer data array
  @param buffer ByteBuffer added to
  @param b byte added
*/
void addByte(ByteBuffer *buffer, byte b);

/**
  Frees buffer and all associated memory
*/
void freeBuffer(ByteBuffer *buffer);

/**
  Reads a file into a ByteBuffer
  @param filename
  @return pointer to a filled ByteBuffer
*/
ByteBuffer *readFile(const char *filename);
#endif
