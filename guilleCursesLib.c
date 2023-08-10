#include "guilleCursesLib.h"

void initCurses(){
	initscr(); //initialices ncurses terminal mode
	cbreak(); //handles terminal drive buffers (no enter needed to process chars)
	noecho(); //does not show the characters typed
	keypad(stdscr,TRUE); //enables rare keys
}

void ncursesTest(){
	int ch;
	printw("Type any character to see it in bold\n");
	ch = getch();

	printw("The pressed key is: ");
	attron(A_BOLD);
	printw("%c",ch);
	attroff(A_BOLD);
	refresh();
	getch();
}

WINDOW * createRWin(){
	WINDOW * win;
	int startx, starty, width, height;

	height = LINES;
	width = COLS;

	startx = (COLS - width)/2;
	starty = (LINES - height)/2;

	win = newwin(height, width, starty, startx);
	box(win,0,0);
	wrefresh(win);
	refresh();

	return win;
}

void endCurses(){
	endwin();
}