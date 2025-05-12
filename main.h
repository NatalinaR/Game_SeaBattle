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
void process_input(int *ship_count, int board_owner);

void line_with_markers(int cols, const char *start, const char *middle, void(chars(int i)), const char *end, int offset, int row, int player_index);

bool is_cell_occupied(int j, int i, int player);
bool is_cell_chosen(int j, int i, int player);
// bool add_ship(int j, int i, int player, int board_owner);
bool add_ship(int j, int i, int player);
bool add_marker(int j, int i, int player);
bool add_miss(int j, int i, int player);
int ask_player_number();
void place_all_ships(int player);
void draw_boards(int cols, int rows, const int *numbers, int player_index);
void game_loop(int cols, int rows, const int *numbers);

