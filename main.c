#include "guilleCursesLib.h"

int main(int argc, char const *argv[])
{
	coords c;
	coords d;
	char **board;
	WINDOW * mainWin; //background
	WINDOW * TTTWin;
	WINDOW * shadow;
	int selection;
	char message[30];
	int winner;


	//board = createBoard(3);

	initCurses();
	refresh();
	//attron(COLOR_PAIR(1));


	refresh();
	mainWin = createRWin();
	wbkgd(mainWin,COLOR_PAIR(3));
	wrefresh(mainWin);

	do{
		destroy_win(mainWin);
		mainWin = createRWin();
		wbkgd(mainWin,COLOR_PAIR(3));
		selection = menu();
		destroy_win(mainWin);
		mainWin = createRWin();
		wbkgd(mainWin,COLOR_PAIR(3));
		wrefresh(mainWin);

		if(0 == selection){
			winner= playAgainstIA(3);
			if(winner == 0){
				//draw
				strcpy(message,"Draw");
				mvwprintw(mainWin,3,((COLS - strlen(message))/2),message);
			}else if(winner ==1){
				//player
				strcpy(message,"Player wins");
				mvwprintw(mainWin,3,((COLS - strlen(message))/2),message);
			}else if(winner == 2){
				//enemy
				attron(COLOR_PAIR(4));
				refresh();
				strcpy(message,"Enemy wins");
				mvwprintw(mainWin,3,((COLS - strlen(message))/2),message);
				attroff(COLOR_PAIR(4));
			}

			wrefresh(mainWin);
			getch();
		}else if(1 == selection){

		}
	}while(selection != 2);
	

	endCurses();
	return 0;
}