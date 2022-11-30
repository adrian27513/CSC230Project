CC = gcc
CFLAGS = -Wall -std=c99 -g
interpret:interpret.o parse.o syntax.o value.o
											gcc -Wall -std=c99 -g interpret.o parse.o syntax.o value.o -o interpret
interpret.o:interpret.c parse.h syntax.h value.h
parse.o:parse.c parse.h syntax.h value.h
syntax.o:syntax.c syntax.h value.h
value.o:value.c value.h
clean:
			rm *.o
			rm interpret
			rm output.txt
			rm stderr.txt