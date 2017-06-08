#include <stdio.h>
#include <ncurses.h>
#define N 50

int main() {
	char c;
	char pass[N] = {0};
	int i = 0;

	initscr();
	erase();

	move(1, 0);
	printw("password> ");
	refresh();

	while(1) {
		noecho();
		c = getch();
		if (c != '\n') {
			printw("*");
			pass[i++] = c;
		} else {
			break;
		}
	}

	//move(4, 1);
	printw("\nyour input: %s", pass);

	move(4, 0);
	printw("any key to finish> ");
	getch();

	endwin();

	return 0;
}
