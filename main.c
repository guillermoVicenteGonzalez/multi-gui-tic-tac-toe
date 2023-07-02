#include "TTTapi.h"

int main(int argc, char const *argv[])
{
	char **board;

	board = createBoard(3);

	setCell(board,0 ,0,PCHAR);

	printf("%d\n", fillableRows(board,3));
	printf("%d\n", fillableDiags(board,3));
	printf("%d\n", fillableAntiDiags(board,3));
	recorrerBoard(board,3);
	return 0;
}