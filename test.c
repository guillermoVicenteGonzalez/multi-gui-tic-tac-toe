#include "TTTapi.h"

int main(int argc, char const *argv[])
{
	coords c;
	coords d;
	char **board;

/*
	list lst = createList(c);
	
	c.x = 1;
	c.y = 2;

	pushToList(c,lst);


	c.x=3;
	c.y=4;
	pushToList(c,lst);
	//pushToList(7,lst);
	printList(lst);
	printContent(getFromList(lst));
	printf("\n");
	//printf("\n");
	//printf("\n%d\n",printCont));
	printList(lst);
	freeList(lst);
	printf("\n");*/


	board = createBoard(3);
	recorrerBoard(board,3);
	c = alfabeta(board,3);
	printf("[x]:%d    [y]:%d",c.x,c.y);
	return 0;
	
}