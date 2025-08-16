#pragma once
#include <ncurses.h>
#include <stdbool.h>

extern char *filter_value;

void filter_setup(WINDOW *win);
bool filter_handle_key(int ch);
void filter_draw();
void filter_cleanup();
