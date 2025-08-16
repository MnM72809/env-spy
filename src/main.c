#include "env_logic.h"
#include "filter.h"
#include "log.h"
#include "pages.h"
#include "windows.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

AppWindows *windowsPtr = NULL;
EnvVarList *evlist = NULL;
int current_var_index = 0;

extern char *filter_value;
extern int filter_cursor_pos;

#define up_down_process()                                                      \
	do                                                                         \
	{                                                                          \
		/* Clear only inner content window to preserve border */               \
		werase(windowsPtr->right_inner_win);                                   \
		/* Redraw outer border */                                              \
		box(windowsPtr->right_pane_win, 0, 0);                                 \
		/* Refresh border */                                                   \
		wnoutrefresh(windowsPtr->right_pane_win);                              \
		/* Print updated value in inner window */                              \
		print_key_data();                                                      \
		/* Print updated keys with highlight */                                \
		print_keys(); /* For highlight */                                      \
		/* Refresh left border */                                              \
		wnoutrefresh(windowsPtr->left_pane_win);                               \
		/* Move the cursor to the filter window */                             \
		wmove(windowsPtr->filter_bar_win, 0, filter_cursor_pos + 10);          \
		/* Refresh filter window */                                            \
		wnoutrefresh(windowsPtr->filter_bar_win);                              \
		doupdate();                                                            \
	} while (0)

bool main_loop()
{
	bool running = true;
	int ch;

	// Set a shorter timeout for getch to make exiting more responsive
	/*timeout(50);*/
	set_escdelay(20);

	while (running)
	{
		mv_cursor(windowsPtr->filter_bar_win, filter_cursor_pos, 0);
		doupdate();
		ch = getch();
		if (ch == 27 || ch == KEY_EXIT) // Exit key
		{
			break;
		}
		else if (ch == KEY_UP) // Up arrow key
		{
			current_var_index--;
			if (current_var_index < 0)
				current_var_index = 0;

			up_down_process();
			continue;
		}
		else if (ch == KEY_DOWN)
		{
			current_var_index++;
			if (current_var_index >= evlist->count)
				current_var_index = evlist->count - 1;

			up_down_process();
			continue;
		}
		else if (filter_handle_key(ch))
		{
			log_msg("cursor pos: '%d', filter_value: '%s'", filter_cursor_pos,
			        filter_value);
			continue;
		}
	}
	return true;
}

int main()
{
	// Init log
	log_init("envspy.log");

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

	// Initial draw of key list in inner pane
	print_keys();
	// Position cursor at first entry of inner window
	wmove(windows.left_inner_win, 0, 0);
	wnoutrefresh(windows.left_inner_win);
	doupdate();

	// Display data
	print_key_data();
	doupdate();

	bool success = main_loop();
	if (!success)
	{
		// TODO: Handle error
	}

	// Clean up

	clear();
	refresh();

	// Delete child (inner) windows before outer panes
	delwin(windows.title_win);
	delwin(windows.filter_bar_win);
	delwin(windows.left_inner_win);
	delwin(windows.right_inner_win);
	delwin(windows.left_pane_win);
	delwin(windows.right_pane_win);
	delwin(windows.status_bar_win);

	// Free envvarlist
	free_envvarlist(&list);

	// Restore terminal
	nocbreak();
	echo();
	endwin();

	// End log
	log_close();

	return 0;
}
