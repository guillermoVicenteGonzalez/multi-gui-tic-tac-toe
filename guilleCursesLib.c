#include "guilleCursesLib.h"
#include <string.h>

void initCurses(){
	initscr(); //initialices ncurses terminal mode
	cbreak(); //handles terminal drive buffers (no enter needed to process chars)
	noecho(); //does not show the characters typed
	keypad(stdscr,TRUE); //enables rare keys

	if(has_colors() == FALSE){
		printw("Your terminal has no color support");
		getch();
	}else{
		start_color();
		init_pair(1, COLOR_GREEN, COLOR_WHITE); //fondo
		init_pair(2,COLOR_RED,COLOR_BLUE); //menues
		init_pair(3,COLOR_BLACK,COLOR_BLACK); //negro para sombras
	}
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
	//box(win,0,0);
	wrefresh(win);
	refresh();

	return win;
}


void endCurses(){
	endwin();
}


WINDOW * createTTTWin(int tam){
	WINDOW *TTTWin;
	WINDOW *shadow;

	int width = tam +2;
	int height = tam+2;
	int screenWM, screenHM; //middle of the screen

	screenHM = (LINES - height)/2;
	screenWM = (COLS-width)/2;

	init_pair(2,COLOR_WHITE,COLOR_BLUE);
	attron(COLOR_PAIR(2));
	TTTWin = newwin(height,width,screenHM,screenWM);
	box(TTTWin,0,0);
	wbkgd(TTTWin,COLOR_PAIR(2));


	shadow = newwin(height,width,screenHM+1,screenWM+1);
	wbkgd(shadow,COLOR_PAIR(3));

	wrefresh(shadow);
	wrefresh(TTTWin);

	return TTTWin;
}

void printBoardCurses(WINDOW * win, char ** board, int tam){
	for(int i=0;i<tam;i++){
		for(int j=0; j<tam; j++){
			//mvwaddch(win,i,j,board[i][j]);
			if(board[i][j] == ' '){
				mvwaddch(win,i+1,j+1,'_');
			}else{
				mvwaddch(win,i+1,j+1,board[i][j]);
			}
		}
	}

	refresh();
	wrefresh(win);
}

WINDOW * createShadow(int h, int w, int starty, int startx, int offset){
	WINDOW * shadow;

	attron(COLOR_PAIR(3));

	shadow = newwin(h,w,starty+(2*offset),startx);
	wbkgd(shadow,COLOR_PAIR(2));
	wrefresh(shadow);
	refresh();

	return shadow;
}

void selectCell(int tam, WINDOW * win){
	int ch;
	position cursPos;

	cursPos.x =1;
	cursPos.y=1;

	keypad(win, TRUE);
	init_pair(4,COLOR_GREEN,COLOR_BLACK);
	attron(COLOR_PAIR(4));
	refresh();

	do{
		ch =getch();
		switch(ch){
			case KEY_UP:
				cursPos.y--;
				break;

			case KEY_DOWN:
				cursPos.y++;
				break;

			case KEY_LEFT:
				cursPos.x--;
				break;

			case KEY_RIGHT:
				cursPos.x++;
				break;
		}

		if(cursPos.x > tam){
			cursPos.x=1;
		}else if(cursPos.y > tam){
			cursPos.y=1;
		}else if(cursPos.x<1){
			cursPos.x = tam;
		}else if(cursPos.y<1){
			cursPos.y=tam;
		}

		wmove(win,cursPos.y, cursPos.x);
		wrefresh(win);


	}while(ch != 10);
}


int menu(){
	WINDOW * menuWin;
	WINDOW * shadow;
	int width, height, startx, starty, auxX, auxY;
	char message[30];
	int selection = 0;
	int ch;

	width = COLS/2;
	height = LINES/2;
	startx = (COLS -width)/2;
	starty = (LINES-height)/2;

	menuWin = newwin(height, width,starty,startx);
	shadow = newwin(height, width,starty+1,startx+2);

	wbkgd(shadow,COLOR_PAIR(3));
	wbkgd(menuWin,COLOR_PAIR(2));
	box(menuWin,0,0);

	wrefresh(shadow);
	wrefresh(menuWin);

    wattron(menuWin,A_STANDOUT);
    wattron(menuWin,A_BLINK);
	strcpy(message,"Player against IA");
	auxX = ((width-2) - strlen(message))/2;
	auxY = 3;
	mvwprintw(menuWin, auxY, auxX,message);
	wattroff(menuWin,A_STANDOUT);
	wattroff(menuWin,A_BLINK);


	strcpy(message,"Player against Player");
	auxX = ((width-2) - strlen(message))/2;
	auxY = 5;
	
	mvwprintw(menuWin, auxY, auxX,message);
	wmove(menuWin,auxY,auxX);
	wrefresh(menuWin);

	curs_set(0); //oculta el cursor
	do{
		ch=getch();
		switch(ch){
			case KEY_UP:
				selection = 0;
			    wattron(menuWin,A_STANDOUT);
			    wattron(menuWin,A_BLINK);
				strcpy(message,"Player against IA");
				auxX = ((width-2) - strlen(message))/2;
				auxY = 3;
				mvwprintw(menuWin, auxY, auxX,message);
				wattroff(menuWin,A_STANDOUT);
				wattroff(menuWin,A_BLINK);
				wmove(menuWin,auxY,auxX-1);


				strcpy(message,"Player against Player");
				auxX = ((width-2) - strlen(message))/2;
				auxY = 5;
				
				mvwprintw(menuWin, auxY, auxX,message);
				wrefresh(menuWin);


				break;

			case KEY_DOWN:
				selection = 1;
				strcpy(message,"Player against IA");
				auxX = ((width-2) - strlen(message))/2;
				auxY = 3;
				mvwprintw(menuWin, auxY, auxX,message);


				strcpy(message,"Player against Player");
				auxX = ((width-2) - strlen(message))/2;
				auxY = 5;
				wattron(menuWin,A_STANDOUT);
			    wattron(menuWin,A_BLINK);
				mvwprintw(menuWin, auxY, auxX,message);
				wattroff(menuWin,A_STANDOUT);
				wattroff(menuWin,A_BLINK);

				wmove(menuWin,auxY,auxX-1);
				wrefresh(menuWin);
				break;
		}

		//attroff(A_STANDOUT);
		wrefresh(menuWin);

	}while(ch != 10);
	curs_set(1); //vuelve a mostrar el cursor

	//borrar ventanas

	return selection;
}


/*
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
}*/