#include <stdio.h>
#include "main.h"
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ROWS 10
#define MAX_COLS 10
#define SHIPS_NUMBER 3

// Глобальная матрица для хранения маркеров
char grid_destryed_ships[2][MAX_COLS][MAX_ROWS];
char grid_visible[2][MAX_COLS][MAX_ROWS];
char grid_chosen_cells[2][MAX_COLS][MAX_ROWS];

// Инициализация глобальной матрицы
void initialize_grid()
{
    memset(grid_destryed_ships, ' ', sizeof(grid_destryed_ships));
    memset(grid_visible, ' ', sizeof(grid_visible));
    memset(grid_chosen_cells, ' ', sizeof(grid_chosen_cells));
}

int main()
{
    initialize_grid(); // Инициализация матрицы

    // add_ship(0, 0, 2, 2);
    const int cells = 10;
    char s;

    int rows = cells;
    int cols = cells + 1;
    const int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // int current_player = ask_player_number();
    // printf("Выбран игрок %d\n", current_player);
    // place_all_ships(current_player);
    printf("Игрок 1, расставьте свои корабли:\n");
    place_all_ships(1);

    printf("Игрок 2, расставьте свои корабли:\n");
    place_all_ships(2);

    // draw square

    // process_input(&ship, current_player);

    game_loop(cols, rows, numbers);

    printf("Все корабли потоплены!\n");
    scanf("%s", &s);
    return 0;
}

char *bprintf(char *fmt, ...)
{
    static char buffer[10];
    va_list ap = NULL;

    va_start(ap, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, ap);
    return buffer;
}

void line(int cols, const char *start, const char *middle, void(chars(int i)), const char *end, int offset)
{
    printf("%*s%s", offset, "", start);
    for (int j = 0; j < cols - 1; j++)
    {
        if (NULL != middle)
            printf("%s", middle);
        if (NULL != chars)
            chars(j);
    }

    printf("%s%s", end, offset != 0 ? "\n" : "");
}

void row_header(int j)
{
    const char *letters[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
    printf(" %s │", letters[j]);
}

void get_coordinates(const char *input, int *row, int *col)
{
    if (input == NULL || input[0] == '\0' || input[1] == '\0')
    {
        printf("Некорректный ввод!\n");
        *row = -1;
        *col = -1;
        return;
    }

    char letter = tolower(input[0]);
    if (letter >= 'a' && letter <= 'j')
    {
        *col = letter - 'a' + 1;
    }
    else
    {
        printf("Некорректный столбец!\n");
        *row = -1;
        *col = -1;
        return;
    }

    int number;
    if (sscanf(&input[1], "%d", &number) >= 1 && number <= 10)
    {
        *row = number;
    }
    else
    {
        printf("Некорректная строка!\n");
        *row = -1;
        *col = -1;
    }
}

void process_input(int *ship_count, int main_player)
{
    char input[10];
    int row, col;

    int enemy = main_player == 1 ? 2 : 1;

    // int current_player = ask_player_number();
    // printf("Выбран игрок %d\n", current_player);
    // place_all_ships(current_player);

    printf("Введите координаты для атаки (например, A2 или J10): ");
    scanf("%s", input);
    get_coordinates(input, &row, &col);

    if (is_cell_chosen(row - 1, col - 1, enemy))
    {
        printf("Клетка %d,%d уже была выбрана, выберите другую\n", row, col);
        printf("Введите координаты для атаки (например, A2 или J10): ");
        scanf("%s", input);
        get_coordinates(input, &row, &col);
    };

    if (row != -1 && col != -1)
    {
        if (is_cell_occupied(row - 1, col - 1, enemy)) 
        {
            add_marker(row - 1, col - 1, enemy);
            printf("ПОПАЛ\n");
            (*ship_count)--;
            printf("Осталось кораблей: %d\n", *ship_count);
        }
        else
        {
            add_miss(row - 1, col - 1, enemy);
            printf("МИМО\n");
        }
    }
    else
    {
        printf("Ошибка в вводе координат!\n");
    }
}

// Функция для добавления маркера

bool add_ship(int j, int i, int player)
{
    int offset = player == 1 ? 0 : 3;

    // Проверка допустимости индексов и игрока
    if (j < 0 || j >= MAX_COLS || i < 0 || i >= MAX_ROWS || (player != 1 && player != 2))
    {
        printf("Некорректные параметры для добавления маркера!\n");
        return false;
    }

    // В зависимости от игрока, добавляем в нужную сетку
    grid_visible[offset / 3][i][j] = 'K';

    return true;
}

bool add_marker(int j, int i, int player)
{
    int offset = player == 1 ? 0 : 3;

    // Проверка допустимости индексов и игрока
    if (j < 0 || j >= MAX_COLS || i < 0 || i >= MAX_ROWS || (player != 1 && player != 2))
    {
        printf("Некорректные параметры для добавления маркера!\n");
        return false;
    }
    grid_destryed_ships[offset / 3][i][j] = 'D';

    return true;
}

bool add_miss(int j, int i, int player)
{
    int offset = player == 1 ? 0 : 3;

    // Проверка допустимости индексов и игрока
    if (j < 0 || j >= MAX_COLS || i < 0 || i >= MAX_ROWS || (player != 1 && player != 2))
    {
        printf("Некорректные параметры для добавления маркера!\n");
        return false;
    }
    grid_chosen_cells[offset / 3][i][j] = '+';

    return true;
}

// Функция для проверки наличия маркера в клетке
bool is_cell_occupied(int j, int i, int player)
{
    int offset = player == 1 ? 0 : 3;

    // Проверка допустимости индексов
    if (j < 0 || j >= MAX_COLS || i < 0 || i >= MAX_ROWS || (player != 1 && player != 2))
    {
        printf("Некорректные параметры для проверки клетки!\n");
        return false;
    }

    // Проверка, занята ли клетка
    return grid_visible[offset / 3][i][j] == 'K';
}

// checking has cell been already chosen once
bool is_cell_chosen(int j, int i, int player)
{
    int offset = player == 1 ? 0 : 3;

    // Проверка допустимости индексов
    if (j < 0 || j >= MAX_COLS || i < 0 || i >= MAX_ROWS || (player != 1 && player != 2))
    {
        printf("Некорректные параметры для проверки клетки!\n");
        return false;
    }

    // check was chosen or not
    return grid_chosen_cells[offset / 3][i][j] == '+';
}

// Обновленная функция line с учетом маркеров
void line_with_markers(int cols, const char *start, const char *middle, void(chars(int i)), const char *end, int offset, int row, int player_index)
{
    printf("%*s%s", offset, "", start);
    for (int j = 0; j < cols - 1; j++)
    {
        if (player_index == 1 && offset == 0)
        {
            if (grid_visible[offset / 3][j][row] == 'K' && grid_destryed_ships[offset / 3][j][row] == 'D')
            {
                printf(" D │");
            }
            else if (grid_visible[offset / 3][j][row] == 'K' && grid_destryed_ships[offset / 3][j][row] != 'D')
            {
                printf(" K │");
            }
            else if (grid_chosen_cells[offset / 3][j][row] == '+')
            {

                printf(" + │");
            }
            else
            {
                printf("   │");
            }
            if (NULL != chars)
                chars(j);
        }
        else if (player_index == 2 && offset == 3)
        {
            if (grid_visible[offset / 3][j][row] == 'K' && grid_destryed_ships[offset / 3][j][row] == 'D')
            {
                printf(" D │");
            }
            else if (grid_visible[offset / 3][j][row] == 'K' && grid_destryed_ships[offset / 3][j][row] != 'D')
            {
                printf(" K │");
            }
            else if (grid_chosen_cells[offset / 3][j][row] == '+')
            {

                printf(" + │");
            }
            else
            {
                printf("   │");
            }
            if (NULL != chars)
                chars(j);
        }
        else
        {
            if (grid_visible[offset / 3][j][row] == 'K' && grid_destryed_ships[offset / 3][j][row] == 'D')
            {
                printf(" D │");
            }
            else if (grid_chosen_cells[offset / 3][j][row] == '+')
            {

                printf(" + │");
            }
            else
            {
                printf("   │");
            }
            if (NULL != chars)
                chars(j);
        }
    }
    printf("%s%s", end, offset != 0 ? "\n" : "");
}

void place_all_ships(int player)
{
    int ships_to_place = SHIPS_NUMBER;
    char input[10];
    int row, col;
    // int board_owner = player;

    printf("=== Расстановка кораблей для игрока %d ===\n", player);

    for (int i = 0; i < ships_to_place;)
    {
        printf("Добавьте корабль #%d (например, A2 или J10): ", i + 1);
        scanf("%s", input);
        get_coordinates(input, &row, &col);

        if (row != -1 && col != -1)
        {
            if (add_ship(row - 1, col - 1, player)) // unified function
            {
                printf("Корабль #%d установлен в %s\n", i + 1, input);
                i++; // only increment if successful
            }
            else
            {
                printf("Ошибка при установке корабля! Повторите ввод.\n");
            }
        }
        else
        {
            printf("Ошибка в координатах! Повторите ввод.\n");
        }
    }

    printf("Все %d кораблей установлены для игрока %d.\n", ships_to_place, player);
}

int ask_player_number()
{
    int player;

    do
    {
        printf("Вы игрок 1 или 2? Введите 1 или 2: ");
        scanf("%d", &player);

        if (player != 1 && player != 2)
        {
            printf("Некорректный номер игрока! Попробуйте снова.\n");
        }
    } while (player != 1 && player != 2);

    return player;
}

void game_loop(int cols, int rows, const int *numbers)
{
    int ships_player1 = SHIPS_NUMBER;
    int ships_player2 = SHIPS_NUMBER;

    while (ships_player1 > 0 && ships_player2 > 0)
    {
        printf("\n===== ХОД ИГРОКА 1 =====\n");
        draw_boards(cols, rows, numbers, 1);
        process_input(&ships_player2, 1); // Игрок 1 атакует игрока 2

        if (ships_player2 == 0)
        {
            printf("Игрок 1 победил!\n");
            break;
        }

        printf("\n===== ХОД ИГРОКА 2 =====\n");
        draw_boards(cols, rows, numbers, 2);
        process_input(&ships_player1, 2); // Игрок 2 атакует игрока 1

        if (ships_player1 == 0)
        {
            printf("Игрок 2 победил!\n");
            break;
        }
    }
}

void draw_boards(int cols, int rows, const int *numbers, int player_index)
{
    line(cols, "┌", "───┬", NULL, "───┐", 0);
    line(cols, "┌", "───┬", NULL, "───┐", 3);

    line(cols, "│   │", NULL, row_header, "", 0);
    line(cols, "│   │", NULL, row_header, "", 3);

    for (int i = 0; i < rows; i++)
    {

        line(cols, "├", "───┼", NULL, "───┤", 0);
        line(cols, "├", "───┼", NULL, "───┤", 3);

        line_with_markers(cols, bprintf("│%2d │", numbers[i]), "   │", NULL, "", 0, i, player_index);
        line_with_markers(cols, bprintf("│%2d │", numbers[i]), "   │", NULL, "", 3, i, player_index);
    }

    line(cols, "└", "───┴", NULL, "───┘", 0);
    line(cols, "└", "───┴", NULL, "───┘", 3);
}