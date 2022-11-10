CC = gcc
CFLAGS = -Wall -std=c99 -g -DTESTABLE
hash:hash.o ripeMD.o byteBuffer.o
			gcc hash.o ripeMD.o byteBuffer.o -o hash
testdriver:testdriver.c ripeMD.c byteBuffer.c
			gcc -Wall -std=c99 -g -DTESTABLE testdriver.c ripeMD.c byteBuffer.c -o testdriver
hash.o:hash.c byteBuffer.h ripeMD.h
testdriver.o:testdriver.c ripeMD.h byteBuffer.h
ripeMD.o:ripeMD.c ripeMD.h byteBuffer.h
byteBuffer.o:byteBuffer.c byteBuffer.h
clean:
			rm *.o
			rm hash
			rm testdriver
			rm output.txt
			rm stderr.txt