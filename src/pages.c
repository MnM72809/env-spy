#include "pages.h"
#include "env_logic.h"
#include "filter.h"
#include "log.h"
#include "windows.h"
#include <ncurses.h>
#include <stdio.h>

extern EnvVarList *evlist;
extern AppWindows *windowsPtr;
extern int current_var_index;

/* void print_keys() {
    // Iterate through the env vars to print them
    if (evlist == NULL || evlist->count <= 0) {
        wprintw(windowsPtr->left_inner_win, "No environment variables
found.\n"); wnoutrefresh(windowsPtr->left_inner_win); return;
    }

    for (int i = 0; i < evlist->count; i++) {
        char *key_to_print = evlist->vars[i].key;
        wmove(windowsPtr->left_inner_win, i + 0, 0);
        // Highlight the key if it's currently selected
        if (i == current_var_index) {
            wattron(windowsPtr->left_inner_win, A_REVERSE);
        }
        // Print the key
        wprintw(windowsPtr->left_inner_win, "%s", key_to_print);
        // Turn off the highlight
        if (i == current_var_index) {
            wattroff(windowsPtr->left_inner_win, A_REVERSE);
        }
        wnoutrefresh(windowsPtr->left_inner_win);
    }

    box(windowsPtr->left_pane_win, 0, 0);
} */

void print_keys()
{
	/*log_msg("function print_keys");*/
	werase(windowsPtr->left_inner_win);
	// Iterate through the env vars to print them
	if ((evlist == NULL || evlist->count <= 0) ||
	    (filter_value[0] != '\0' && filter_count() == 0))
	{
		wprintw(windowsPtr->left_inner_win,
		        "No environment variables found.\n");
		wnoutrefresh(windowsPtr->left_inner_win);
		return;
	}

	int count = (filter_count() > 0) ? filter_count() : evlist->count;

	for (int i = 0; i < count; i++)
	{
		log_msg("filter_index_at: %d", filter_index_at(i));
		char *key_to_print = evlist->vars[filter_index_at(i)].key;
		wmove(windowsPtr->left_inner_win, i + 0, 0);
		// Highlight the key if it's currently selected
		if (i == current_var_index)
		{
			wattron(windowsPtr->left_inner_win, A_REVERSE);
		}
		// Print the key
		wprintw(windowsPtr->left_inner_win, "%s", key_to_print);
		// Turn off the highlight
		if (i == current_var_index)
		{
			wattroff(windowsPtr->left_inner_win, A_REVERSE);
		}
	}
	wnoutrefresh(windowsPtr->left_inner_win);

	box(windowsPtr->left_pane_win, 0, 0);
}

void print_key_data()
{
	werase(windowsPtr->right_inner_win);
	// Print the data of the currently selected key
	if ((evlist == NULL || evlist->count <= 0) ||
	    (filter_value[0] != '\0' && filter_count() == 0))
	{
		/*wprintw(windowsPtr->right_inner_win,
		        "No environment variables found.\n");*/
		wnoutrefresh(windowsPtr->right_inner_win);
		return;
	}

	// Check if current_var_index is valid
	if ((current_var_index > filter_count() - 1 && filter_count() > 0) ||
	    current_var_index < 0 || current_var_index > evlist->count - 1)
	{
		wprintw(windowsPtr->right_inner_win,
		        "Error: Invalid current key index.\n");
		wnoutrefresh(windowsPtr->right_inner_win);
		return;
	}

	/*char dataToPrint[256];*/
	/*snprintf(dataToPrint, sizeof(dataToPrint), "Value: %s",*/
	/*evlist->vars[current_var_index].value);*/

	char *val = evlist->vars[filter_index_at(current_var_index)].value;

	wmove(windowsPtr->right_inner_win, 0, 0);
	if (val[0] == '\0')
	{
		wprintw(windowsPtr->right_inner_win, "Empty value");
	}
	else
	{
		wprintw(windowsPtr->right_inner_win, "Value: %s", val);
	}
	wnoutrefresh(windowsPtr->right_inner_win);
}

int ensureCurrentVarIndexBounds(int index)
{
	if (index >= evlist->count)
		index = evlist->count - 1;
	if (filter_count() > 0 && index >= filter_count())
		index = filter_count() - 1;
	if (index < 0)
		index = 0;
	return index;
}
