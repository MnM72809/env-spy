#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

/*#include "filter.h"*/
#include "env_logic.h"
#include "pages.h"
#include "windows.h"

AppWindows *windowsPtr = NULL;
EnvVarList *evlist = NULL;

bool main_loop() {
	bool running = true;
	int ch;

	// Set a shorter timeout for getch to make exiting more responsive
	timeout(50);
	set_escdelay(20);

	while (running) {
		ch = getch();
		if (ch == 27 || ch == KEY_EXIT) // Exit key
		{
			break;
		}
	}
	return true;
}

int main() {
	initialize_ncurses();
	AppWindows windows = create_windows();
	windowsPtr = &windows;
	initialize_windows(&windows);

	EnvVarList list = {NULL, 0, 8};
	list.vars = calloc(list.capacity, sizeof(EnvVar));
	if (!list.vars)
		return 1;

	load_envvarlist(&list);

	wmove(windows.left_pane_win, 1, 1);
	wprintw(windows.left_pane_win, "%s: %s\n", list.vars->key,
	        list.vars->value);
	wrefresh(windows.left_pane_win);

	evlist = &list;

	print_home();

	bool success = main_loop();
	if (!success) {
		// TODO: Handle error
	}

	// Clean up

	clear();
	refresh();

	delwin(windows.title_win);
	delwin(windows.filter_bar_win);
	delwin(windows.left_pane_win);
	delwin(windows.right_pane_win);
	delwin(windows.status_bar_win);

	// Free envvarlist
	free_envvarlist(&list);

	// Restore terminal
	nocbreak();
	echo();
	endwin();

	return 0;
}
