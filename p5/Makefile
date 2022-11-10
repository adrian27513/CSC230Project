CC = gcc
CFLAGS = -Wall -std=c99 -g
hash:hash.o ripeMD.o byteBuffer.o
			gcc hash.o ripeMD.o byteBuffer.o -o hash
test:testdriver.o ripeMD.o byteBuffer.o
			gcc -DTESTABLE testdriver.o ripeMD.o byteBuffer.o -o testdriver
hash.o:hash.c byteBuffer.h ripeMD.h
testdriver.o:testdriver.c ripeMD.h byteBuffer.h
ripeMD.o:ripeMD.c ripeMD.h byteBuffer.h
byteBuffer.o:byteBuffer.c byteBuffer.h
clean:
			rm *.o
			rm output.txt
			rm hash
			rm testdriver