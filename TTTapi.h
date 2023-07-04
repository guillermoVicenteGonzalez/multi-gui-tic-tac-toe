#include <stdio.h>
#include <stdlib.h>
#define PCHAR 'X'
#define ECHAR 'O'

/*
typedef struct gameState{
	char ** board;
	int boardTam;
	int turn;
	int winCond;
} gameState;

typedef struct position{
	int x;
	int y;
} position;

typedef struct heuristicState{
	position pos;
	int heuristic;
} hState;*/


char ** createBoard(int tam);
void recorrerBoard(char **board, int boardTam);
//gameState createGame(int tam, int winCond);
void setCell(char ** board, int x, int y, char c);
int fillableRows(char **board, int tam, char c);
int fillableCols(char **board, int tam, char c);
int fillableDiags(char **board, int tam, char c);
int fillableAntiDiags(char **board, int tam, char c);
void freeBoard(char ** board, int tam);
int exploreState(char ** board, int tam, int x, int y);