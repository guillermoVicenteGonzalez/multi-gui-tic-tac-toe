#include <stdio.h>
#include "TTTapi.h"


/*
gameState createGame(int tam, int winCond){
	char **board;
	gameState state;

	state.board = createBoard(tam);
	state.boardTam = tam;
	state.winCond = winCond;
	state.turn = 0;

	return state;


	//crea estructura de datos
}*/

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

void freeBoard(char ** board, int tam){
	for(int i=0;i<tam;i++){
		free(board[i]);
	}

	free(board);
}

void setCell(char ** board, int x, int y, char c){
	board[x][y] = c;
}

int fillableRows(char **board, int tam, char c){
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
int fillableCols(char **board, int tam, char c){
	int count = 0;
	int flag = 1;

	//para cada columna
	for(int j=0; j<tam; j++){
		flag = 1;

		//si encontramos una fila que tenga 1 char de player => no completable
		for(int i=0;i<tam;i++){
			if(board[i][j] == c){
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

int fillableDiags(char **board, int tam, char c){
	int count;
	int flag = 1;

	//las casillas diagonales siempre son (1,1), (2,2)...
	for(int i=0; i<tam; i++){
		if(board[i][i] == c){
			flag = 0;
		}
	}

	if(flag ==0){
		return 0;
	}else{
		return 1;
	}
}

int fillableAntiDiags(char **board, int tam, char c){
	int count;
	int flag = 1;

	//la antiadiag es (3,0) (2,1)(1,2)...
	//filas = tam -i
	//columnas = i
	for(int i=0; i<tam; i++){
		if(board[(tam-1)-i][i] == c){
			flag = 0;
		}
	}

	if(flag ==0){
		return 0;
	}else{
		return 1;
	}
}

/*

state enemyAi(){
	//recorro la matriz. Meto los huecos en una lista
	//creo una copia del tablero

	/* Para cada elemento de la lista
	 - marco con ECHAR esa casilla. Saco de la lista
	 - meto en otra lista las casillas vacias
	 - pruebo en cada una a poner PCHAR
	 - invoco a  exploreState.
	 - guardo los heuristicState en una lista
	 - al explorar todas las casillas guardo el mejor resultado.
	 - en la siguiente exploracion, comparo heurisiticas.
	 Solo sigo si obtengo una mejor, si no, dejo de explorar.

	


}*/

//te da un tablero y devuelve la metrica del enemigo
int exploreState(char ** board, int tam, int x, int y){
	//resultado es fillables del enemigo - fillables tuyas
	int result;
	int enemyRes;
	int playerRes;

	enemyRes = fillableRows(board, tam, PCHAR);
	enemyRes += fillableCols(board,tam, PCHAR);
	enemyRes += fillableDiags(board,tam, PCHAR);
	enemyRes += fillableAntiDiags(board,tam, PCHAR);

	playerRes = fillableRows(board, tam, ECHAR);
	playerRes += fillableCols(board, tam, ECHAR);
	playerRes += fillableDiags(board, tam, ECHAR);
	playerRes += fillableAntiDiags(board, tam, ECHAR);

	result = playerRes - enemyRes;

	printf("\nplayerRes: %d - enemyRes: %d = %d\n",playerRes, enemyRes, result);
	return result;
}


void recorrerBoard(char **board, int tam){
	for(int i=0;i<tam;i++){
		for(int j=0;j<tam;j++){
			fprintf(stdout, "[%d][%d]:%c\t", i,j,board[i][j]);
		}
		fprintf(stdout,"\n");
	}
}