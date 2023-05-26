#include "TTTapi.h"

int main(int argc, char const *argv[])
{
	int **board;

	board = createBoard(3);
	recorrerBoard(board,3);
	return 0;
}