 # ----------------------------------------------------------------
 # Purpose : A makefile to compile lasertank program
 # ----------------------------------------------------------------


# Makefile Variables:
CC = gcc
EXEC = laserTank
CFLAGS = -g -Wall -ansi -pedantic -Werror
OBJ = main.o newSleep.o map.o playerMove.o laser.o fileIO.o linkedlist.o log.o


$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c main.h structs.h macros.h newSleep.h map.h playerMove.h laser.h fileIO.h linkedlist.h log.h
	$(CC) -c main.c $(CFLAGS)

newSleep.o :newSleep.c newSleep.h
	$(CC) -c newSleep.c $(CFLAGS)

map.o :map.c map.h
	$(CC) -c map.c $(CFLAGS)

playerMove.o :playerMove.c playerMove.h
	$(CC) -c playerMove.c $(CFLAGS)

laser.o :laser.c laser.h
	$(CC) -c laser.c $(CFLAGS)

fileIO.o :fileIO.c fileIO.h
	$(CC) -c fileIO.c $(CFLAGS)

linkedlist.o :linkedlist.c linkedlist.h
	$(CC) -c linkedlist.c $(CFLAGS)

log.o :log.c log.h
	$(CC) -c log.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)
