/** 
*/

#include "ripeMD.h"
#include "byteBuffer.h"

void initState(HashState *state)
{
  state->A = 0x67452301;
  state->B = 0xEFCDAB89;
  state->C = 0x98BADCFE;
  state->D = 0x10325476;
  state->E = 0xC3D2E1F0;
}

void padBuffer(ByteBuffer *buffer)
{
  unsigned long original = buffer->len * BBITS;
  
  addByte(buffer, 0x80);
  int zeroAdd = (BLOCK_BYTES - (buffer->len % BLOCK_BYTES)) - LEN_BLEN;
  
  for (int i = 0; i < zeroAdd; i++) {
    addByte(buffer, 0x00);
  }
  
  //unsigned long mask = BYTE_MASK;
  for (int i = 0; i < LEN_BLEN; i++) {
    addByte(buffer, (original & (BYTE_MASK << (i * BBITS))) >> (i * BBITS));
  }
}

static void printHelper(longword field)
{ 
  for (int i = 0; i < sizeof(longword); i++) {
    printf("%02x", (field & (BYTE_MASK << (i * BBITS))) >> (i * BBITS));
  }
}
void printHash(HashState *state)
{
  printHelper(state->A);
  printHelper(state->B);
  printHelper(state->C);
  printHelper(state->D);
  printHelper(state->E);
  printf("\n");
}

static longword bitwiseF0(longword a, longword b, longword c)
{
  return a ^ b ^ c;
}

static longword bitwiseF1(longword a, longword b, longword c)
{
  return (a & b) | (~a & c);
}

static longword bitwiseF2(longword a, longword b, longword c)
{
  return (a | ~b) ^ c;
}
static longword bitwiseF3(longword a, longword b, longword c)
{
  return (a & c) | (b & ~c);
}

static longword bitwiseF4(longword a, longword b, longword c)
{
  return a ^ (b | ~c);
}

static longword rotateLeft(longword value, int s)
{
  longword mask = UINT_MAX << (LONGWORD_BLEN - s);
  return (value << s) | ((value & mask) >> (LONGWORD_BLEN - s)); 
}

static void hashIteration(HashState *state, longword datum, int shift, longword noise, BitwiseFunction f)
{
  longword A = state->A;
  longword B = state->B;
  longword C = state->C;
  longword D = state->D;
  longword E = state->E;
  
  state->A = E;
  state->B = rotateLeft((A + f(B, C, D) + datum + noise), shift) + E;
  state->C = B;
  state->D = rotateLeft(C, C_ROTATE);
  state->E = D;
}

static void hashRound(HashState *state, longword data[BLOCK_LONGWORDS], int perm[RIPE_ITERATIONS], int shift[RIPE_ITERATIONS], longword noise, BitwiseFunction f)
{
  for (int i = 0; i < BLOCK_LONGWORDS; i++) {
    hashIteration(state, data[perm[i]], shift[i], noise, f);
  }
}

void hashBlock(HashState *state, byte block[BLOCK_BYTES])
{
  static int leftPerm[RIPE_ROUNDS][RIPE_ITERATIONS] = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
    {7, 4, 13, 1, 10, 6, 15, 3, 12, 0, 9, 5, 2, 14, 11, 8},
    {3, 10, 14, 4, 9, 15, 8, 1, 2, 7, 0, 6, 13, 11, 5, 12},
    {1, 9, 11, 10, 0, 8, 12, 4, 13, 3, 7, 15, 14, 5, 6, 2},
    {4, 0, 5, 9, 7, 12, 2, 10, 14, 1, 3, 8, 11, 6, 15, 13}
  };
  
  static int rightPerm[RIPE_ROUNDS][RIPE_ITERATIONS] = {
    {5, 14, 7, 0, 9, 2, 11, 4, 13, 6, 15, 8, 1, 10, 3, 12},
    {6, 11, 3, 7, 0, 13, 5, 10, 14, 15, 8, 12, 4, 9, 1, 2},
    {15, 5, 1, 3, 7, 14, 6, 9, 11, 8, 12, 2, 10, 0, 4, 13},
    {8, 6, 4, 1, 3, 11, 15, 0, 5, 12, 2, 13, 9, 7, 10, 14},
    {12, 15, 10, 4, 1, 5, 8, 7, 6, 2, 13, 14, 0, 3, 9, 11}
  };
  
  static int leftShift[RIPE_ROUNDS][RIPE_ITERATIONS] = {
    {11, 14, 15, 12, 5, 8, 7, 9, 11, 13, 14, 15, 6, 7, 9, 8},
    {7, 6, 8, 13, 11, 9, 7, 15, 7, 12, 15, 9, 11, 7, 13, 12},
    {11, 13, 6, 7, 14, 9, 13, 15, 14, 8, 13, 6, 5, 12, 7, 5},
    {11, 12, 14, 15, 14, 15, 9, 8, 9, 14, 5, 6, 8, 6, 5, 12},
    {9, 15, 5, 11, 6, 8, 13, 12, 5, 12, 13, 14, 11, 8, 5, 6}
  };
  
  static int rightShift[RIPE_ROUNDS][RIPE_ITERATIONS] = {
    {8, 9, 9, 11, 13, 15, 15, 5, 7, 7, 8, 11, 14, 14, 12, 6},
    {9, 13, 15, 7, 12, 8, 9, 11, 7, 7, 12, 7, 6, 15, 13, 11},
    {9, 7, 15, 11, 8, 6, 6, 14, 12, 13, 5, 14, 13, 13, 7, 5},
    {15, 5, 8, 11, 14, 14, 6, 14, 6, 9, 12, 9, 12, 5, 15, 8},
    {8, 5, 12, 9, 12, 5, 14, 6, 8, 13, 6, 5, 15, 13, 11, 11}
  };
  
  static longword leftNoise[RIPE_ROUNDS] = {
    0x00000000,
    0x5A827999,
    0x6ED9EBA1,
    0x8F1BBCDC,
    0xA953FD4E
  };
  
  static longword rightNoise[RIPE_ROUNDS] = {
    0x50A28BE6,
    0x5C4DD124,
    0x6D703EF3,
    0x7A6D76E9,
    0x00000000
  };
  
  static BitwiseFunction leftFunction[RIPE_ROUNDS] = {
    bitwiseF0,
    bitwiseF1,
    bitwiseF2,
    bitwiseF3,
    bitwiseF4
  };
  
  static BitwiseFunction rightFunction[RIPE_ROUNDS] = {
    bitwiseF4,
    bitwiseF3,
    bitwiseF2,
    bitwiseF1,
    bitwiseF0
  };
  
  longword data[BLOCK_LONGWORDS];
  for (int i = 0; i < BLOCK_LONGWORDS; i++) {
    longword temp = 0;
    for (int j = 0; j < sizeof(longword); j++) {
      longword b = (longword) block[(i*sizeof(longword)) + j];
      temp |= (b << (j * BBITS));
    }
    data[i] = temp;
  }
  
  HashState leftState = *state;
  HashState rightState = *state;
  HashState *left = &leftState;
  HashState *right = &rightState;
  
  for (int i = 0; i < RIPE_ROUNDS; i++) {
    hashRound(left, data, leftPerm[i], leftShift[i], leftNoise[i], leftFunction[i]);
    hashRound(right, data, rightPerm[i], rightShift[i], rightNoise[i], rightFunction[i]);
  }
  
  longword A = state->A;
  longword B = state->B;
  longword C = state->C;
  longword D = state->D;
  longword E = state->E;
  
  state->A = left->C + B + right->D;
  state->B = left->D + C + right->E;
  state->C = left->E + D + right->A;
  state->D = left->A + E + right->B;
  state->E = left->B + A + right->C;
}

// Put the following at the end of your implementation file.
// If we're compiling for unit tests, create wrappers for the otherwise
// private functions we'd like to be able to test.

#ifdef TESTABLE

longword bitwiseF0Wrapper( longword b, longword c, longword d )
{
  return bitwiseF0( b, c, d );
}

longword bitwiseF1Wrapper( longword b, longword c, longword d )
{
  return bitwiseF1( b, c, d );
}

longword bitwiseF2Wrapper( longword b, longword c, longword d )
{
  return bitwiseF2( b, c, d );
}

longword bitwiseF3Wrapper( longword b, longword c, longword d )
{
  return bitwiseF3( b, c, d );
}

longword bitwiseF4Wrapper( longword b, longword c, longword d )
{
  return bitwiseF4( b, c, d );
}

longword rotateLeftWrapper( longword value, int s )
{
  return rotateLeft( value, s );
}

void hashIterationWrapper( HashState *state,
                           longword datum,
                           int shift,
                           longword noise,
                           BitwiseFunction f )
{
  hashIteration( state, datum, shift, noise, f );
}

void hashRoundWrapper( HashState *state,
                       longword *block,
                       int perm[ RIPE_ITERATIONS ],
                       int shift[ RIPE_ITERATIONS ],
                       longword noise,
                       BitwiseFunction f )
{
  hashRound( state, block, perm, shift, noise, f );
}

#endif
