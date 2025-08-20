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

/**
 * @brief Insert a character at the specified position in the filter value
 * @param ch The character to insert
 * @param pos The position at which to insert the character
 */
static void filter_insert_char(char ch, int pos)
{
    size_t len = strlen(filter_value);
    if (len < 255)
    {
        memmove(filter_value + pos + 1,
                filter_value + pos,
                len - pos + 1); // +1 to move the null terminator
        filter_value[pos] = ch;
    }
}

/**
 * @brief Delete a character at the specified position in the filter value
 * @param pos The position at which to delete the character
 */
static void filter_delete_char(int pos)
{
    if (pos > 0)
    {
        size_t len = strlen(filter_value);
        memmove(filter_value + pos - 1,
                filter_value + pos,
                len - pos + 1); // +1 to move the null terminator
    }
}


/**
 * @brief Handle a key press event in the filter
 * @param ch The key code of the pressed key
 * @return true if the key press was handled, false otherwise
 */
bool filter_handle_key(int ch)
{
    switch (ch)
    {
    case KEY_BACKSPACE:
		if (filter_cursor_pos <= 0) return true; // No-op because we can't delete before the start
        filter_delete_char(filter_cursor_pos);
		filter_cursor_pos--;
        filter_draw();
        return true;
    case KEY_DC:
		if (filter_cursor_pos < 0 || filter_cursor_pos >= strlen(filter_value)) return true;
        filter_delete_char(filter_cursor_pos + 1);
        filter_draw();
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
			filter_insert_char((char)ch, filter_cursor_pos);
			filter_cursor_pos++;
			filter_draw();
			return true;
		}
		return false;
	}
	return false;
}


/**
 * @brief Draw the filter window
 */
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
