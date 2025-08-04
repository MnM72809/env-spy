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
int current_var_index = 0;

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
		} else if (ch == KEY_UP) // Up arrow key
		{
			current_var_index--;
			if (current_var_index < 0) current_var_index = 0;

			wclear(windowsPtr->right_pane_win);
			box(windowsPtr->right_pane_win, 0, 0);
			print_key_data();
			wrefresh(windowsPtr->right_pane_win);
			print_keys(); // For highlight
			wrefresh(windowsPtr->left_pane_win);
			continue; // TODO
		} else if (ch == KEY_DOWN) {
			current_var_index++;
			if (current_var_index >= evlist->count) current_var_index = evlist->count - 1;
			wclear(windowsPtr->right_pane_win);
			box(windowsPtr->right_pane_win, 0, 0);
			print_key_data();
			wrefresh(windowsPtr->right_pane_win);
			print_keys(); // For highlight
			wrefresh(windowsPtr->left_pane_win);
			continue; // TODO
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

	evlist = &list;

	/*wmove(windows.left_pane_win, 1, 1);*/
	/*wprintw(windows.left_pane_win, "%s: %s\n", list.vars->key,*/
	/*list.vars->value);*/
	/*wrefresh(windows.left_pane_win);*/

	print_keys();
	wmove(windows.left_pane_win, 1, 1);
	wnoutrefresh(windows.left_pane_win);
	doupdate();

	// Display data
	print_key_data();
	doupdate();

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
