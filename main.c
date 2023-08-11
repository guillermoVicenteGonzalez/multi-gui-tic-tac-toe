#include "TTTapi.h"

int main(int argc, char const *argv[])
{
	char **board;
	list  lst;

	board = createBoard(3);

	setCell(board,0 ,0,PCHAR);
	setCell(board,1,0,ECHAR);
	recorrerBoard(board,3);
	

	exploreState(board,3,3,3);
	freeBoard(board,3);

	lst = createList(3);
	return 0;


	/*
	1.Menu para escoger
	 - IA
	 - 2P

	2 Juego como tal
	 - construir tablero
	 - pintar tablero
	 - turno 1 
}