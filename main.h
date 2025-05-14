#pragma once
#include <stdbool.h>

void initialize_grid();
char *bprintf(char *fmt, ...);
void row_header(int j); 
void draw_boards(int cols, int rows, const int *numbers, int player_index);
void line(int cols, const char *start, const char *middle, void (chars(int i)), const char *end, int offset);
void line_with_markers(int cols, const char *start, const char *middle, void(chars(int i)), const char *end, int offset, int row, int player_index);

void place_all_ships(int player);
void get_coordinates(const char *input, int *row, int *col);

void process_input(int *ship_count, int board_owner, const int *numbers);
void game_loop(int cols, int rows, const int *numbers);

bool check_cell(int j, int i, int player, char type);
bool add_marker(int j, int i, int player, char purpose);

void setup_game_settings(int *rows, int *cols, int *ship_count);




