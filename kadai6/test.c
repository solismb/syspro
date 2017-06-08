#include <stdio.h>
#include <ncurses.h>

int main() {
	char c;
	initscr();
	erase();
	move(1, 0);
	printw("input> ");
	refresh();
	c = getch();
	printw("\nyou entered: %c", c);
	move(4, 2);
	printw("any key> ");
	getch();
	endwin();
	return 0;
}
