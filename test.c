//#include "TTTapi.h"
#include "guilleCursesLib.h"

int main(int argc, char const *argv[])
{
	coords c;
	coords d;
	char **board;
	WINDOW * mainWin;
	WINDOW * TTTWin;
	WINDOW * shadow;
	int selection;


	//board = createBoard(3);

	initCurses();
	refresh();
	init_pair(1, COLOR_GREEN, COLOR_WHITE);
	attron(COLOR_PAIR(1));


	refresh();
	mainWin = createRWin();
	wbkgd(mainWin,COLOR_PAIR(1));
	wrefresh(mainWin);


	selection = menu();


	destroy_win(mainWin);
	mainWin = createRWin();
	wbkgd(mainWin,COLOR_PAIR(1));
	wrefresh(mainWin);

	if(0 == selection){
		playAgainstIA();
	}else if(1 == selection){

	}
	

	//getch();
	endCurses();
	return 0;




/*
	board = createBoard(3);
	setCell(board,0,0,ECHAR);
	setCell(board,1,1,PCHAR);
	setCell(board,0,2,PCHAR);



	recorrerBoard(board,3);




	c = alfabetaVB(board,3);
	printf("[x]:%d    [y]:%d",c.x,c.y);
*/


	return 0;
	
	
}