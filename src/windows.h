#pragma once
#include <ncurses.h>

typedef struct {
	WINDOW *title_win;
	WINDOW *filter_bar_win;
	WINDOW *left_pane_win;
	WINDOW *right_pane_win;
	WINDOW *status_bar_win;
	WINDOW *left_inner_win;
	WINDOW *right_inner_win;
} AppWindows;

void initialize_ncurses();
AppWindows create_windows();
void initialize_windows(AppWindows *windows);
void mv_cursor(WINDOW *win, int x, int y);
