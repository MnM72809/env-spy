#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

int main() {
	// Initialize ncurses
	initscr();
	// Don't echo any keypresses
	noecho();
	// React to keys instantly, without waiting for the Enter key
	cbreak();

	// Print a msg
	printw("Press any key to exit...");

	refresh();

	getch();

	endwin();

	return 0;
}
