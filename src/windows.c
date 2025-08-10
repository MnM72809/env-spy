#include <ncurses.h>
#include <stdbool.h>

#include "windows.h"
#include "filter.h"

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

	// TEMPORARY
	// Disable cursor
	curs_set(0);
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

	// Create inner windows for text printing
	WINDOW *left_inner_win = derwin(left_pane_win, left_pane_height - 2, left_pane_width - 2, 1, 1);
	WINDOW *right_inner_win = derwin(right_pane_win, right_pane_height - 2, right_pane_width - 2, 1, 1);

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
		.status_bar_win = status_bar_win,
		.left_inner_win = left_inner_win,
		.right_inner_win = right_inner_win
	};

	return app_windows;
}

void initialize_windows(AppWindows *windows)
{
    // Print a msg in the title bar
	mvwprintw(windows->title_win, 1, 2, "ENV-SPY");

	// Print a msg in the status bar
	mvwprintw(windows->status_bar_win, 0, 1, "Press [Esc] to quit");

	// Filter init function
	// TODO: Implement filter
	filter_setup(windows->filter_bar_win);


	wnoutrefresh(windows->status_bar_win);
	wnoutrefresh(windows->title_win);
	
    // Update the screen with all the changes
	doupdate();

	mv_cursor(windows->filter_bar_win, 0, 10);
}

void mv_cursor(WINDOW *win, int x, int y)
{
    wmove(win, x, y);
	wrefresh(win);
}
