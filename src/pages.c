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
		wprintw(windowsPtr->left_pane_win, "No environment variables found.\n");
		wnoutrefresh(windowsPtr->left_pane_win);
		return;
	}

	for (int i = 0; i < evlist->count; i++) {
		char *key_to_print = evlist->vars[i].key;
		wmove(windowsPtr->left_pane_win, i + 1, 1);
		wprintw(windowsPtr->left_pane_win, "%s", key_to_print);
		wnoutrefresh(windowsPtr->left_pane_win);
	}
}

void print_key_data() {
	// Print the data of the currently selected key
	if (evlist == NULL || evlist->count <= 0) {
		wprintw(windowsPtr->right_pane_win,
		        "No environment variables found.\n");
		wnoutrefresh(windowsPtr->right_pane_win);
		return;
	}

	// Check if current_var_index is valid
	if (current_var_index > evlist->count - 1 || current_var_index < 0) {
		wprintw(windowsPtr->right_pane_win,
		        "Error: Invalid current key index.\n");
		wnoutrefresh(windowsPtr->right_pane_win);
		return;
	}

	/*char dataToPrint[256];*/
	/*snprintf(dataToPrint, sizeof(dataToPrint), "Value: %s",*/
	/*evlist->vars[current_var_index].value);*/

	wmove(windowsPtr->right_pane_win, 1, 1);
	wprintw(windowsPtr->right_pane_win, "Value: %s",
	        evlist->vars[current_var_index].value);
	wnoutrefresh(windowsPtr->right_pane_win);
}
