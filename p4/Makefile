CC = gcc
CFLAGS = -Wall -std=c99 -g
kiosk:kiosk.o input.o menu.o
									gcc kiosk.o input.o menu.o -o kiosk
kiosk.o:kiosk.c input.h menu.h
input.o: input.c input.h
menu.o: menu.c menu.h
clean:
			rm *.o
			rm output.txt
			rm kiosk