game: main.c TTTapi.o
	gcc main.c TTTapi.o -o game 

test: test.c TTTapi.o
	gcc test.c TTTapi.o -o test

TTTapi.o: TTTapi.c TTTapi.h
	gcc -c TTTapi.c TTTapi.h