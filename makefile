game: main.c TTTapi.o list.o guilleCursesLib.o
	gcc main.c TTTapi.o list.o guilleCursesLib.o -lncurses -o game

test: test.c TTTapi.o list.o guilleCursesLib.o
	gcc test.c TTTapi.o list.o guilleCursesLib.o -lncurses -o test

TTTapi.o: TTTapi.c TTTapi.h
	gcc -c TTTapi.c TTTapi.h

guilleCursesLib.o: guilleCursesLib.c guilleCursesLib.h
	gcc -c guilleCursesLib.c guilleCursesLib.h -lncurses

list.o: list.c list.h
	gcc -c list.c list.h 