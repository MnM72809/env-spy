#include "pages.h"
#include "env_logic.h"
#include "windows.h"
#include <ncurses.h>
#include <stdio.h>

extern EnvVarList *evlist;
extern AppWindows *windowsPtr;
extern int current_var_index;

void print_keys() {
	// Iterate through the env vars to print them
	if (evlist == NULL || evlist->count <= 0) {
		wprintw(windowsPtr->left_inner_win, "No environment variables found.\n");
		wnoutrefresh(windowsPtr->left_inner_win);
		return;
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
}

void print_key_data() {
	// Print the data of the currently selected key
	if (evlist == NULL || evlist->count <= 0) {
		wprintw(windowsPtr->right_inner_win,
		        "No environment variables found.\n");
		wnoutrefresh(windowsPtr->right_inner_win);
		return;
	}

	// Check if current_var_index is valid
	if (current_var_index > evlist->count - 1 || current_var_index < 0) {
		wprintw(windowsPtr->right_inner_win,
		        "Error: Invalid current key index.\n");
		wnoutrefresh(windowsPtr->right_inner_win);
		return;
	}

	/*char dataToPrint[256];*/
	/*snprintf(dataToPrint, sizeof(dataToPrint), "Value: %s",*/
	/*evlist->vars[current_var_index].value);*/

	wmove(windowsPtr->right_inner_win, 0, 0);
	wprintw(windowsPtr->right_inner_win, "Value: %s",
	        evlist->vars[current_var_index].value);
	wnoutrefresh(windowsPtr->right_inner_win);
}
