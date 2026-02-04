//compile with gcc led8x8.c -lcurses
//run with ./a.out
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
int main (void) 
{
   	initscr();
	int col,row;
	getmaxyx(stdscr, row, col);
	//		     w len y  x
	WINDOW *win = newwin(0, 0, 0, 0);
	mvprintw(0,0,"Welcome to led8x8!");
	//draw 8x8:
	//mvprintw(5+x,y*4,"%c",179);
	//mvvline(6,6,ACS_VLINE,6);
	mvvline(4,1,'|',15);
	mvvline(4,1+4,'|',15);
	mvvline(4,1+8,'|',15);
	mvvline(4,1+12,'|',15);
	mvvline(4,1+16,'|',15);
	mvvline(4,1+20,'|',15);
	mvvline(4,1+24,'|',15);
	mvvline(4,1+28,'|',15);
	mvvline(4,1+32,'|',15);
	//mvhline(7,7,ACS_HLINE,7);
	mvhline(3,2,'-',31);
	mvhline(5,2,'-',31);
	mvhline(7,2,'-',31);
	mvhline(9,2,'-',31);
	mvhline(11,2,'-',31);
	mvhline(13,2,'-',31);
	mvhline(15,2,'-',31);
	mvhline(17,2,'-',31);
	mvhline(19,2,'-',31);
	//printf("Please choose a box number: ");
	mvprintw(1,0,"Please choose a box number: ");
	int boxnumber;
	refresh();
	box(win, 1,1);
	refresh();
	//scanf(" %d",&boxnumber);
	scanw(" %d",&boxnumber);
	boxnumber=boxnumber-1;
	//printf("You have selected box number: %d\n",boxnumber+1);
	//mvprintw(2,0,"You have selected box number: %d\n",boxnumber+1);
	refresh();
	int x;
	int y;
	x=boxnumber/8;
	y=boxnumber%8;
	//printf("The coordinates are x: %d, y: %d\n",x,y);
	mvprintw(2,0,"The coordinates are x: %d, y: %d\n",x,y);
	mvprintw(4+x*2,3+y*4,"X");
	getch();
	endwin();
	return EXIT_SUCCESS;
}
