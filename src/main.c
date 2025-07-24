#include <ncurses.h>
#include <unistd.h>

#include "filter.h"
#include "windows.h"

int main() {
	initialize_ncurses();
    AppWindows windows = create_windows();

	// Print a msg in the title bar
	mvwprintw(windows.title_win, 1, 2, "Title");
	wnoutrefresh(windows.title_win);

	// Print a msg in the status bar
	mvwprintw(windows.status_bar_win, 0, 1, "Press Ctrl + C to quit");
	wnoutrefresh(windows.status_bar_win);

	// Filter init function
	filter_setup(windows.filter_bar_win);
	
    // Update the screen with all the changes
	doupdate();

	getch();

    sleep(10);

	endwin();

	return 0;
}
