#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "TTTapi.h"
#include <string.h>


void initCurses();
void ncursesTest();
void endCurses();
WINDOW * createRWin();
WINDOW * createTTTWin(int tam);
void printBoardCurses(WINDOW * win, char ** board, int tam);
WINDOW * createShadow(int h, int w, int starty, int startx, int offset);
position selectCell(int tam, WINDOW * win);
int menu();
void destroy_win(WINDOW *local_win);
int playAgainstIA(int tam);
int sizeMenu();
int playAgainstPlayer(int tam);