#include <ncurses.h>
#include "filter.h"

void filter_setup(WINDOW *win)
{
    // Print "Filter: " inside the filter window
    mvwprintw(win, 0, 0, "Filter: ");

	wnoutrefresh(win);
}
