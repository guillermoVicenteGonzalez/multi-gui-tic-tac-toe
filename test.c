#include "TTTapi.h"

int main(int argc, char const *argv[])
{
	int **board;
	gameState state;

	state = createGame(3,3);
	recorrerBoard(state.board, state.boardTam);

/*
	board = createBoard(3);
	recorrerBoard(board,3);
	return 0;
	*/
}