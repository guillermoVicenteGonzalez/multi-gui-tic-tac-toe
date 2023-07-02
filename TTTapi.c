#include <stdio.h>
#include "TTTapi.h"



gameState createGame(int tam, int winCond){
	char **board;
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
char ** createBoard(int tam){
	char **board;

	if(NULL == (board = (char **) malloc(sizeof(char *) * tam))){
		perror("error allocating board memory");
		return NULL;
	}

	for(int i=0;i<tam;i++){
		board[i] = (char *)malloc(tam * sizeof(char));
		if(board[i] == NULL){
			perror("error allocating board memory");
			return NULL;
		}
	}

	for(int i=0;i<tam;i++){
		for(int j=0;j<tam;j++){
			board[i][j] = ' ';
		}
	}

	return board;
}

void setCell(char ** board, int x, int y, char c){
	board[x][y] = c;
}

int fillableRows(char **board, int tam){
	int count = 0;
	int flag = 1;

	//para cada fila
	for(int i=0; i<tam; i++){
		flag = 1;
		//si encuentro una columna que tenga 1 char de player => no completable
		for(int j=0; j<tam; j++){
			if(board[i][j] == PCHAR){
				flag = 0;
			}
		}

		//si flag = 1 => no he encontrado obstaculos => contamos la fila
		if(flag == 1){
			count ++;
		}
	}

	return count;
}


//realmente es lo mismo que fillRows
int fillableCols(char **board, int tam){
	int count = 0;
	int flag = 1;

	//para cada columna
	for(int j=0; j<tam; j++){
		flag = 1;

		//si encontramos una fila que tenga 1 char de player => no completable
		for(int i=0;i<tam;i++){
			if(board[i][j] == PCHAR){
				flag = 0;
			}
		}

		//si flag = 1 => no he encontrado obstaculos => contamos la columna
		if(flag == 1){
			count ++;
		}
	}

	return count;
}

int fillableDiags(char **board, int tam){
	int count;
	int flag = 1;

	//las casillas diagonales siempre son (1,1), (2,2)...
	for(int i=0; i<tam; i++){
		if(board[i][i] == PCHAR){
			flag = 0;
		}
	}

	if(flag ==0){
		return 0;
	}else{
		return 1;
	}
}

int fillableAntiDiags(char **board, int tam){
	int count;
	int flag = 1;

	//la antiadiag es (3,0) (2,1)(1,2)...
	//filas = tam -i
	//columnas = i
	for(int i=0; i<tam; i++){
		if(board[(tam-1)-i][i] == PCHAR){
			flag = 0;
		}
	}

	if(flag ==0){
		return 0;
	}else{
		return 1;
	}
}


void recorrerBoard(char **board, int tam){
	for(int i=0;i<tam;i++){
		for(int j=0;j<tam;j++){
			fprintf(stdout, "[%d][%d]:%c\t", i,j,board[i][j]);
		}
		fprintf(stdout,"\n");
	}
}