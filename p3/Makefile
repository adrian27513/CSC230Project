CC = gcc
CFLAGS = -Wall -std=c99 -g
replace:replace.o line.o expand.o
									gcc replace.o line.o expand.o -o replace
replace.o:replace.c line.h expand.h
line.o: line.c line.h
expand.o: expand.c expand.h
clean:
			rm *.o
			rm output.txt
			rm replace
