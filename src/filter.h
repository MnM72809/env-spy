#pragma once
#include <ncurses.h>
#include <stdbool.h>

extern char *filter_value;

/* extern int *filtered_indices;
extern int filtered_count;
extern int filtered_cap; */

void filter_setup(WINDOW *win);
bool filter_handle_key(int ch);
void filter_draw();
void filter_cleanup();

/* Actual filter functionality */

void filter_compute();
int filter_count();
int filter_index_at(int i);