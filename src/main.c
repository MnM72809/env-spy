#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>

/*#include "filter.h"*/
#include "windows.h"

bool main_loop()
{
    bool running = true;
	int ch;
	
	// Set a shorter timeout for getch to make exiting more responsive
	timeout(50);
	set_escdelay(20);

    while (running)
	{
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
	initialize_windows(&windows);

    bool success = main_loop();
	if (!success)
	{
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

	// Restore terminal
	nocbreak();
	echo();
	endwin();

	return 0;
}


