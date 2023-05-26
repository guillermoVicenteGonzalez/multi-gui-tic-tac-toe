#include <stdio.h>
#include "TTTapi.h"


gameState createGame(int tam, int winCond){
	int **board;
	gameState state;

	state.board = createBoard(tam);
	state.boardTam = tam;
	state.winCond = winCond;
	state.turn = 0;

	return state;


	//crea estructura de datos
}

/**
 * First allocates memory for board which will have tam rows of pointers
 * Then allocates memory for each row, which will have tam cells of integers.
 * Then assigns value 0 == empty for each cell
 * Lastly?? returns the board 
 **/
int ** createBoard(int tam){
	int **board;

	if(NULL == (board = (int **) malloc(sizeof(int *) * tam))){
		perror("error allocating board memory");
		return NULL;
	}

	for(int i=0;i<tam;i++){
		board[i] = (int *)malloc(tam * sizeof(int));
		if(board[i] == NULL){
			perror("error allocating board memory");
			return NULL;
		}
	}

	for(int i=0;i<tam;i++){
		for(int j=0;j<tam;j++){
			board[i][j] = 0;
		}
	}

	return board;
}

void recorrerBoard(int **board, int tam){
	for(int i=0;i<tam;i++){
		for(int j=0;j<tam;j++){
			fprintf(stdout, "[%d][%d]:%d\t", i,j,board[i][j]);
		}
		fprintf(stdout,"\n");
	}
}