#include <ncurses.h>
#include <stdbool.h>

#include "windows.h"

void initialize_ncurses()
{
	// Initialize ncurses
	initscr();
	refresh(); // Refresh stdscr
	// Don't echo any keypresses
	noecho();
	// React to keys instantly, without waiting for the Enter key
	cbreak();
	// Enable function keys, arrow keys, etc.
	keypad(stdscr, TRUE);
}

AppWindows create_windows()
{
	int term_x, term_y;
	getmaxyx(stdscr, term_y, term_x); // Get terminal size
	
	// Determine window sizes
	
	float pane_width_ratio = 0.35; // Left pane takes 35% of the width
	
	bool use_borders = true;

	int title_height = 5;
	int status_bar_height = 1;
	int filter_bar_height = 1;
	int left_pane_height = term_y - status_bar_height - 6; // Leave space for status bar
	int right_pane_height = left_pane_height; 

	int title_width = term_x;
	int filter_bar_width = term_x;
	int left_pane_width = (int)(term_x * pane_width_ratio);
	int right_pane_width = term_x - left_pane_width;
	int status_bar_width = term_x;

	int left_pane_top = title_height + filter_bar_height;
	int right_pane_top = left_pane_top;

	// Create windows
	WINDOW *title_win = newwin(title_height, title_width, 0, 0);
	WINDOW *filter_bar_win = newwin(filter_bar_height, filter_bar_width, title_height, 0);
	WINDOW *left_pane_win = newwin(left_pane_height, left_pane_width, left_pane_top, 0);
	WINDOW *right_pane_win = newwin(right_pane_height, right_pane_width, right_pane_top, left_pane_width);
	WINDOW *status_bar_win = newwin(status_bar_height, status_bar_width, term_y - status_bar_height, 0);

	// Set window borders
	if (use_borders)
	{
        box(title_win, 0, 0);
		box(left_pane_win, 0, 0);
		box(right_pane_win, 0, 0);
		wnoutrefresh(title_win);
		wnoutrefresh(left_pane_win);
		wnoutrefresh(right_pane_win);
	}

	AppWindows app_windows = {
        .title_win = title_win,
		.filter_bar_win = filter_bar_win,
		.left_pane_win = left_pane_win,
		.right_pane_win = right_pane_win,
		.status_bar_win = status_bar_win
	};

	return app_windows;
}
