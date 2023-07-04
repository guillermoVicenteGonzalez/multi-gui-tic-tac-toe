#include "TTTapi.h"
#include "list.h"

int main(int argc, char const *argv[])
{
	list lst = createList(3);
	//pushToList(5,lst);
	//pushToList(7,lst);
	printList(lst);
	//printf("\n%d\n",getFromList(lst));
	//printList(lst);
	freeList(lst);

/*
	board = createBoard(3);
	recorrerBoard(board,3);
	return 0;
	*/
}