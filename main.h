#pragma once
void line(int cols, const char *start, const char *middle, const char *end);

void first_line(int cols);

void first_vertical_line(int cols, const char *letters[10]);

void horizontal_line_field(int cols);

void vertical_line_field(int cols, int numbers[10], int i);

void last_line(int cols);
