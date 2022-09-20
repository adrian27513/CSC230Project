CC = gcc
CFLAGS = -Wall -std=c99 -g
all:polish10 polish32
polish10:polish.o base10.o bounds.o
				 gcc polish.o base10.o bounds.o -o polish10
polish32:polish.o base32.o bounds.o
				 gcc polish.o base32.o bounds.o -o polish32
polish.o:polish.c base.h bounds.h
base10.o:base10.c base.h
base32.o:base32.c base.h
bounds.o:bounds.c bounds.h