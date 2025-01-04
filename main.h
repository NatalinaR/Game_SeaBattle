#pragma once
#include <stdbool.h>
void line(int cols, const char *start, const char *middle, void (chars(int i)), const char *end, int offset);



// void first_line(int cols);

// void first_vertical_line(int cols, const char *letters[10]);

// void horizontal_line_field(int cols);

// void vertical_line_field(int cols, int numbers[10], int i);

// void last_line(int cols);

char *bprintf(char *fmt, ...);
void row_header(int j); 
void get_coordinates(const char *input, int *row, int *col);
void process_input(int *ship_count);

void line_with_markers(int cols, const char *start, const char *middle, void(chars(int i)), const char *end, int offset, int row);

bool add_marker(int j, int i, int player);
bool is_cell_occupied(int j, int i, int player);
bool add_ship(int j, int i, int player);

