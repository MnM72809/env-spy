#include <ncurses.h>
#include "filter.h"

void filter_setup(WINDOW *win)
{
    // Print "Filter: " inside the filter window
	// Commented out because it doesn't work yet
	// TODO: implement filter
    /*mvwprintw(win, 0, 2, "Filter: ");*/
	wnoutrefresh(win);
}
