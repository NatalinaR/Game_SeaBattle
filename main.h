#pragma once
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