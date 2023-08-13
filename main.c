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
	int boardSize=3;


	//board = createBoard(3);

	initCurses();
	refresh();
	//attron(COLOR_PAIR(1));


	refresh();
	mainWin = createRWin();
	wbkgd(mainWin,COLOR_PAIR(1));
	wrefresh(mainWin);

	do{
		destroy_win(mainWin);
		mainWin = createRWin();
		wbkgd(mainWin,COLOR_PAIR(1));
		selection = menu();
		destroy_win(mainWin);
		mainWin = createRWin();
		wbkgd(mainWin,COLOR_PAIR(1));
		wrefresh(mainWin);

		if(0 == selection){
			winner= playAgainstIA(boardSize);
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
				//wattron(mainWin,COLOR_PAIR(4));
				refresh();
				strcpy(message,"Enemy wins");
				mvwprintw(mainWin,3,((COLS - strlen(message))/2),message);
				//wattroff(mainWin,COLOR_PAIR(4));
			}

			wrefresh(mainWin);
			getch();
		}else if(1 == selection){
			winner= playAgainstPlayer(boardSize);
			if(winner == 0){
				//draw
				strcpy(message,"Draw");
				mvwprintw(mainWin,3,((COLS - strlen(message))/2),message);
			}else if(winner ==1){
				//player
				strcpy(message,"Player 1 wins");
				mvwprintw(mainWin,3,((COLS - strlen(message))/2),message);
			}else if(winner == 2){
				//enemy
				//wattron(mainWin,COLOR_PAIR(4));
				refresh();
				strcpy(message,"Player 2 wins");
				mvwprintw(mainWin,3,((COLS - strlen(message))/2),message);
				//wattroff(mainWin,COLOR_PAIR(4));
			}

			wrefresh(mainWin);
			getch();	
		}else if(2==selection){
			boardSize = sizeMenu(boardSize);
		}
	}while(selection != 3);
	

	endCurses(); //se que esto es estupido, pero quizas en un futuro añada algo.
	return 0;
}