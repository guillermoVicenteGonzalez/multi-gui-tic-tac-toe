#include <stdio.h>
#include <stdlib.h>
#define PCHAR 'X'
#define ECHAR 'O'

typedef struct gameState{
	char ** board;
	int boardTam;
	int turn;
	int winCond;
}gameState;

char ** createBoard(int tam);
void recorrerBoard(char **board, int boardTam);
gameState createGame(int tam, int winCond);
void setCell(char ** board, int x, int y, char c);
int fillableRows(char **board, int tam);
int fillableCols(char **board, int tam);
int fillableDiags(char **board, int tam);
int fillableAntiDiags(char **board, int tam);