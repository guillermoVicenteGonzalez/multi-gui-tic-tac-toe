#include <stdio.h>
#include "TTTapi.h"

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

void clearCell(char **board, int x, int y){
	board[x][y] = ' ';
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


//te da un tablero y devuelve la metrica del enemigo
int exploreState(char ** board, int tam, int x, int y){
	//resultado es fillables del enemigo - fillables tuyas
	int result;
	int IARes;
	int playerRes;

	IARes = fillableRows(board, tam, PCHAR);
	IARes += fillableCols(board,tam, PCHAR);
	IARes += fillableDiags(board,tam, PCHAR);
	IARes += fillableAntiDiags(board,tam, PCHAR);

	playerRes = fillableRows(board, tam, ECHAR);
	playerRes += fillableCols(board, tam, ECHAR);
	playerRes += fillableDiags(board, tam, ECHAR);
	playerRes += fillableAntiDiags(board, tam, ECHAR);

	result = IARes - playerRes;

	//printf("\nIARes: %d - playerRes: %d = %d\n",IARes, playerRes, result);
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


char ** createBoardCopy(char ** board, int tam){
	char ** tempBoard;
	tempBoard = createBoard(tam);

	for(int i=0;i<tam; i++){
		for(int j=0;j<tam; j++){
			tempBoard[i][j] = board[i][j];
		}
	}

	return tempBoard;
}



//la x y la y estan cambiadas respecto a lo que serian en un eje de coords cartesianas
//esta version solo funciona cuando empieza la IA
//Cuando empieza el jugador, no detecta cuando esta a punto de ganar,
coords alfabeta(char ** board, int tam){
	//
	coords finalCoord; //resultado de la funcion
	coords currentCoord; //coordenada de la jugada que la maquina esta evaluando hacer
	coords tempCoord; //coordenada temporal (son jugadas del jugador)
	coords auxCoord; //variable usada para rellenar la lista.
	char ** tempBoard;
	int alfa = -7;
	int beta = 7;
	list lst;
	list auxLst;
	int h;

	//creamos el tablero auxiliar
	//y metemos en una lista las casillas vacias
	lst = createList();

	tempBoard = createBoardCopy(board, tam);
	for(int i=0; i<tam; i++){
		for(int j=0;j<tam; j++){
			if(board[i][j] == ' '){
				auxCoord.x = i;
				auxCoord.y = j;
				pushToList(auxCoord, lst);
			}
		}
	}


	//ahora por cada celda
	//colocamos una X
	//rellenamos otra lista con las casillas vacias
	//para cada casilla ponemos una O
	//calculamos la heuristica
	//en la primera iteracion la vamos metiendo en beta
	while(lst->length > 1){
		//tomamos el primer elemento de la lista y ponemos una X en esa coordenada
		currentCoord = getFromList(lst);
		setCell(tempBoard, currentCoord.x,currentCoord.y,ECHAR);

		//ahora rellenamos una segunda lista con las casillas que quedan vacias (posibles movimientos del rival)
		auxLst = createList();
		for(int i=0;i<BOARDTAM;i++){
			for(int j=0;j<BOARDTAM;j++){
				if(tempBoard[i][j] == ' '){
					auxCoord.x = i;
					auxCoord.y = j;
					pushToList(auxCoord, auxLst);
				}
			}
		}

		beta = 7;
		//con la lista llena evaluamos cada uno
		while(auxLst->length > 1){
			tempCoord = getFromList(auxLst);
			setCell(tempBoard,tempCoord.x, tempCoord.y, PCHAR);
			//printf("se esta evaluando:\nX -> x:%d y:%d\nO -> x:%d y:%d\n",currentCoord.x, currentCoord.y, tempCoord.x, tempCoord.y);
			//recorrerBoard(tempBoard,3);
			h = exploreState(tempBoard,3,3,3);

			//si alfa es mejor que un estado de la exploracion, dejo de explorar
			if(alfa != -7 && h<alfa){
				//printf("\ndejo de explorar\n");
				//printf("h=%d; alfa=%d\n",h,alfa);
				break;
			}

			//si no, comparo y al final de la iteracion me tengo que quedar con el mejor beta.
			if(h<beta){
				//printf("h=%d; beta=%d => beta=%d\n",h,beta,h);
				beta = h;
			}else if(beta == -7){//si es la primera exploracion
				beta =h;
			}

			clearCell(tempBoard, tempCoord.x, tempCoord.y);
			//printf("\n");
		}

		/*
		al terminar de explorar todos los estados
		o salir prematuramente
		Se compara la beta (mejor jugada del oponente) con alfa (la jugada que mas nos beneficiaba hasta ahora)
		*/
		//printf("\n--------------------------------------\ntras esta exploracion, beta = %d\n--------------------------------------\n",beta);
		if(alfa == -7 || (beta != 7 && beta > alfa)){
			//printf("alfa previo= %d ",alfa);
			alfa = beta;
			finalCoord =currentCoord;
			//printf("alfa nuevo= %d\n",alfa);
		}

		/*
		Ahora: 
		- liberamos el tablero temporal
		- Creamos otra copia
		- Metemos en una lista las casillas vacias de nuevo
		*/

		freeBoard(tempBoard,BOARDTAM);
		tempBoard = createBoardCopy(board, tam);
		freeList(auxLst);


	}

	//aqui devolvemos la final coord, que deberia de ser la mejor de las jugadas.

	//printList(lst);
	//printf("\nla mejor heuristica es: %d\n",alfa);
	return finalCoord;

}

coords alfabeta2(char **board, int tam){
		//
	coords finalCoord; //resultado de la funcion
	coords currentCoord; //coordenada de la jugada que la maquina esta evaluando hacer
	coords tempCoord; //coordenada temporal (son jugadas del jugador)
	coords auxCoord; //variable usada para rellenar la lista.
	char ** tempBoard;
	int alfa = -7;
	int beta = 7;
	list lst;
	list auxLst;
	int h;

	//creamos el tablero auxiliar
	//y metemos en una lista las casillas vacias
	lst = createList();

	tempBoard = createBoardCopy(board, tam);
	for(int i=0; i<tam; i++){
		for(int j=0;j<tam; j++){
			if(board[i][j] == ' '){
				auxCoord.x = i;
				auxCoord.y = j;
				pushToList(auxCoord, lst);
			}
		}
	}

	//ahora por cada celda
	//colocamos una X
	//rellenamos otra lista con las casillas vacias
	//para cada casilla ponemos una O
	//calculamos la heuristica
	//en la primera iteracion la vamos metiendo en beta
	while(lst->length > 1){
		//tomamos el primer elemento de la lista y ponemos una X en esa coordenada
		currentCoord = getFromList(lst);
		setCell(tempBoard, currentCoord.x,currentCoord.y,ECHAR);

		//antes de seguir comprobamos si esa casilla nos da la victoria
		if(checkWinCond(tempBoard,tam,ECHAR)){
			return currentCoord;
		}

		//ahora rellenamos una segunda lista con las casillas que quedan vacias (posibles movimientos del rival)
		auxLst = createList();
		for(int i=0;i<tam;i++){
			for(int j=0;j<tam;j++){
				if(tempBoard[i][j] == ' '){
					auxCoord.x = i;
					auxCoord.y = j;
					pushToList(auxCoord, auxLst);
				}
			}
		}

		beta = 7;
		//con la lista llena evaluamos cada uno
		while(auxLst->length > 1){
			tempCoord = getFromList(auxLst);
			setCell(tempBoard,tempCoord.x, tempCoord.y, PCHAR);
			//printf("se esta evaluando:\nX -> x:%d y:%d\nO -> x:%d y:%d\n",currentCoord.x, currentCoord.y, tempCoord.x, tempCoord.y);
			//recorrerBoard(tempBoard,3);
			h = exploreState(tempBoard,3,3,3);

			//si alfa es mejor que un estado de la exploracion, dejo de explorar
			if(alfa != -7 && h<alfa){
				//printf("\ndejo de explorar\n");
				//printf("h=%d; alfa=%d\n",h,alfa);
				break;
			}


			//si no, comparo y al final de la iteracion me tengo que quedar con el mejor beta.
			if(h<beta){
				//printf("h=%d; beta=%d => beta=%d\n",h,beta,h);
				beta = h;
			}else if(beta == -7){//si es la primera exploracion
				beta =h;
			}

			//!NUEVO. Verifico si gana el jugador
			//en ese caso le asigno artificialmente una beta muy grande
			//o: devuelvo
			if(checkWinCond(tempBoard,tam,PCHAR)){
				beta = -6;
				//printf("aqui el jugador gana: beta es %d\n",beta);
			}

			clearCell(tempBoard, tempCoord.x, tempCoord.y);
			//printf("\n");
		}

		/*
		al terminar de explorar todos los estados
		o salir prematuramente
		Se compara la beta (mejor jugada del oponente) con alfa (la jugada que mas nos beneficiaba hasta ahora)
		*/
		//printf("\n--------------------------------------\ntras esta exploracion, beta = %d\n--------------------------------------\n",beta);
		if(alfa == -7 || (beta != 7 && beta > alfa)){
			//printf("alfa previo= %d ",alfa);
			alfa = beta;
			finalCoord =currentCoord;
			//printf("alfa nuevo= %d\n",alfa);
		}

		/*
		Ahora: 
		- liberamos el tablero temporal
		- Creamos otra copia
		- Metemos en una lista las casillas vacias de nuevo
		*/

		freeBoard(tempBoard,tam);
		tempBoard = createBoardCopy(board, tam);
		freeList(auxLst);


	}

	//aqui devolvemos la final coord, que deberia de ser la mejor de las jugadas.

	//printList(lst);
	//printf("\nla mejor heuristica es: %d\n",alfa);
	return finalCoord;
}

coords alfabetaVB(char ** board, int tam){
	//
	coords finalCoord; //resultado de la funcion
	coords currentCoord; //coordenada de la jugada que la maquina esta evaluando hacer
	coords tempCoord; //coordenada temporal (son jugadas del jugador)
	coords auxCoord; //variable usada para rellenar la lista.
	char ** tempBoard;
	int alfa = -7;
	int beta = 7;
	list lst;
	list auxLst;
	int h;

	//creamos el tablero auxiliar
	//y metemos en una lista las casillas vacias
	lst = createList();

	tempBoard = createBoardCopy(board, tam);
	for(int i=0; i<tam; i++){
		for(int j=0;j<tam; j++){
			if(board[i][j] == ' '){
				auxCoord.x = i;
				auxCoord.y = j;
				pushToList(auxCoord, lst);
			}
		}
	}


	//ahora por cada celda
	//colocamos una X
	//rellenamos otra lista con las casillas vacias
	//para cada casilla ponemos una O
	//calculamos la heuristica
	//en la primera iteracion la vamos metiendo en beta
	while(lst->length > 1){
		//tomamos el primer elemento de la lista y ponemos una X en esa coordenada
		currentCoord = getFromList(lst);
		setCell(tempBoard, currentCoord.x,currentCoord.y,ECHAR);

		//ahora rellenamos una segunda lista con las casillas que quedan vacias (posibles movimientos del rival)
		auxLst = createList();
		for(int i=0;i<BOARDTAM;i++){
			for(int j=0;j<BOARDTAM;j++){
				if(tempBoard[i][j] == ' '){
					auxCoord.x = i;
					auxCoord.y = j;
					pushToList(auxCoord, auxLst);
				}
			}
		}

		beta = 7;
		//con la lista llena evaluamos cada uno
		while(auxLst->length > 1){
			tempCoord = getFromList(auxLst);
			setCell(tempBoard,tempCoord.x, tempCoord.y, PCHAR);
			printf("se esta evaluando:\nX -> x:%d y:%d\nO -> x:%d y:%d\n",currentCoord.x, currentCoord.y, tempCoord.x, tempCoord.y);
			recorrerBoard(tempBoard,3);
			h = exploreState(tempBoard,3,3,3);

			//si alfa es mejor que un estado de la exploracion, dejo de explorar
			if(alfa != -7 && h<alfa){
				//printf("\ndejo de explorar\n");
				//printf("h=%d; alfa=%d\n",h,alfa);
				break;
			}

			//si no, comparo y al final de la iteracion me tengo que quedar con el mejor beta. (el que sea menor)
			if(h<beta){
				printf("h=%d; beta=%d => beta=%d\n",h,beta,h);
				beta = h;
			}else if(beta == -7){//si es la primera exploracion
				beta =h;
			}

			//!NUEVO. Verifico si gana el jugador
			//en ese caso le asigno artificialmente una beta muy grande
			//o: devuelvo
			if(checkWinCond(tempBoard,BOARDTAM,PCHAR)){
				beta = -6;
				printf("aqui el jugador gana: beta es %d\n",beta);
			}

			clearCell(tempBoard, tempCoord.x, tempCoord.y);
			printf("\n");
		}

		/*
		al terminar de explorar todos los estados
		o salir prematuramente
		Se compara la beta (mejor jugada del oponente) con alfa (la jugada que mas nos beneficiaba hasta ahora)
		*/
		printf("\n--------------------------------------\ntras esta exploracion, beta = %d\n--------------------------------------\n",beta);
		if(alfa == -7 || (beta != 7 && beta > alfa)){
			printf("alfa previo= %d ",alfa);
			alfa = beta;
			finalCoord =currentCoord;
			printf("alfa nuevo= %d\n",alfa);
		}

		/*
		Ahora: 
		- liberamos el tablero temporal
		- Creamos otra copia
		- Metemos en una lista las casillas vacias de nuevo
		*/

		freeBoard(tempBoard,BOARDTAM);
		tempBoard = createBoardCopy(board, tam);
		freeList(auxLst);


	}

	//aqui devolvemos la final coord, que deberia de ser la mejor de las jugadas.

	//printList(lst);
	//printf("\nla mejor heuristica es: %d\n",alfa);
	return finalCoord;

}


int checkFullRow(char **board, int tam, char c){
	int flag = 1;

	for(int i=0;i<tam;i++){
		for(int j=0;j<tam;j++){
			if(board[i][j]!= c)
				flag =0;
				//printf("x:%d y:%d == %c\n",i,j,board[i][j]);
		}

		if(flag == 1){
			return flag;
		}else{
			flag = 1;
		}
	}

	return 0;
}

int checkFullCol(char ** board, int tam, char c){
	int flag = 1;

	for(int j=0;j<tam;j++){
		for(int i=0;i<tam;i++){
			if(board[i][j]!= c)
				flag =0;
			//printf("x:%d y:%d != %c\n",i,j,c);
		}

		if(flag == 1){
			return flag;
		}else{
			flag = 1;
		}
	}

	return 0;
}


int checkFullDiag(char **board, int tam, char c){
	int flag = 1;

	for(int i=0;i<tam;i++){
		if(board[i][i] != c)
			flag = 0;
	}

	return flag;
}

int checkFullAntiDiag(char **board, int tam, char c){
	int flag = 1;

	for(int i=0; i<tam; i++){
		if(board[(tam-1)-i][i] != c){
			flag = 0;
		}
	}

	return flag;
}

int checkWinCond(char **board, int tam, char c){
	int res = 0;
	if(checkFullRow(board,tam,c)) return 1;
	if(checkFullCol(board,tam,c)) return 1;
	if(checkFullDiag(board, tam,c)) return 1;
	if(checkFullAntiDiag(board,tam,c)) return 1;

	return 0;
}

int checkDraw(char ** board, int tam){
	for(int i=0;i<tam;i++){
		for(int j=0;j<tam;j++){
			if(board[i][j] == ' ') return 0;
		}
	}

	return 1; //si todas las casillas estan ocupadas => empate.
}

/***************************************************************************
 * FRONT STUFF
 * *************************************************************************/
