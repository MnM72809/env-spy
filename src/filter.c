#include "filter.h"
#include "windows.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *filter_value;
int filter_cursor_pos = 0;

extern AppWindows *windowsPtr;

void filter_setup(WINDOW *win)
{
	// Initialize filter_value
	filter_value = calloc(256, sizeof(char));

	// Print "Filter: " inside the filter window
	/*mvwprintw(win, 0, 2, "Filter: ");*/
	filter_draw();
	wnoutrefresh(win);
}

bool filter_handle_key(int ch)
{
	/*return false; // tmp*/

	switch (ch)
	{
	case KEY_BACKSPACE: {
		// Handle backspace key
		size_t len = strlen(filter_value);
		if (len > 0)
		{
			// Check if cursor is at the end
			if (filter_cursor_pos >= len)
			{
				memmove(filter_value + filter_cursor_pos - 1,
				        filter_value + filter_cursor_pos,
				        len - filter_cursor_pos + 1);
			}
			else
			{
				filter_value[len - 1] = '\0';
			}
			filter_draw();
			filter_cursor_pos--;
		}
		return true;
	}
	case KEY_DC:
		// Handle delete key
		return true;
	case KEY_LEFT:
		filter_cursor_pos--;
		if (filter_cursor_pos < 0)
			filter_cursor_pos = 0;
		return true;
	case KEY_RIGHT:
		filter_cursor_pos++;
		if (filter_cursor_pos > strlen(filter_value))
			filter_cursor_pos = strlen(filter_value);
		return true;
	// Characters
	default:
		if (ch >= 32 && ch <= 126)
		{
			// ASCII chars
			size_t len = strlen(filter_value);
			if (len < 255)
			{
				if (filter_cursor_pos <= len)
				{
					memmove(filter_value + filter_cursor_pos + 1,
					        filter_value + filter_cursor_pos,
					        len - filter_cursor_pos + 1);
					// + 1 to also move '\0'
					filter_value[filter_cursor_pos] = (char)ch;
				}
				else
				{
					filter_value[len] = (char)ch;
					filter_value[len + 1] = '\0';
				}
				filter_cursor_pos++;
				filter_draw();
			}
			return true;
		}
		return false;
	}
}

void filter_draw()
{
	/*log_msg("Drawing filter win");*/
	WINDOW *win = windowsPtr->filter_bar_win;
	// Draw the filter window
	werase(win);
	wmove(win, 0, 2);
	wprintw(win, "Filter: %s", filter_value);
	/*mv_cursor(windowsPtr->filter_bar_win, filter_cursor_pos, 0);*/
	/*log_msg("Drew filter win: '%s'", filter_value);*/
	wnoutrefresh(win);
}

void filter_cleanup()
{
	if (filter_value)
	{
		free(filter_value);
		filter_value = NULL;
	}
}
