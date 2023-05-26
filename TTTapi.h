#include <stdio.h>
#include <stdlib.h>

typedef struct gameState{
	int ** board;
	int boardTam;
	int turn;
	int winCond;
}gameState;

int ** createBoard(int tam);
void recorrerBoard(int **board, int boardTam);
gameState createGame(int tam, int winCond);