#include <stdio.h>
#include "main.h"
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_ROWS 10
#define MAX_COLS 10

// Глобальная матрица для хранения маркеров
char grid_hidden[2][MAX_COLS][MAX_ROWS];
char grid_visible[2][MAX_COLS][MAX_ROWS];

// Инициализация глобальной матрицы
void initialize_grid()
{
    memset(grid_hidden, ' ', sizeof(grid_hidden));
    memset(grid_visible, ' ', sizeof(grid_visible));
}

int main()
{
    initialize_grid(); // Инициализация матрицы

    add_ship(0, 0, 2);

    int ship = 10;

    const int cells = 10;
    char s;

    int rows = cells;
    int cols = cells + 1;
    const int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    while (ship > 0)
    {
        // draw square
        line(cols, "┌", "───┬", NULL, "───┐", 0);
        line(cols, "┌", "───┬", NULL, "───┐", 3);

        line(cols, "│   │", NULL, row_header, "", 0);
        line(cols, "│   │", NULL, row_header, "", 3);

        for (int i = 0; i < rows; i++)
        {

            line(cols, "├", "───┼", NULL, "───┤", 0);
            line(cols, "├", "───┼", NULL, "───┤", 3);

            line_with_markers(cols, bprintf("│%2d │", numbers[i]), "   │", NULL, "", 0, i);
            line_with_markers(cols, bprintf("│%2d │", numbers[i]), "   │", NULL, "", 3, i);
        }

        line(cols, "└", "───┴", NULL, "───┘", 0);
        line(cols, "└", "───┴", NULL, "───┘", 3);

        process_input(&ship);
    }

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

void process_input(int *ship_count)
{
    char input[10];
    int row, col;

    printf("Введите координаты (например, A2 или J10): ");
    scanf("%s", input);

    get_coordinates(input, &row, &col);

    if (row != -1 && col != -1)
    {
        printf("Вы выбрали столбец %d и строку %d\n", col, row);
        add_marker(row - 1, col - 1, 1); // Для игрока 1

    }
    else
    {
        printf("Ошибка в вводе координат!\n");
    }

    printf("Введите координаты для атаки (например, A2 или J10): ");
    scanf("%s", input);
    get_coordinates(input, &row, &col);

    if (row != -1 && col != -1)
    {
        if (is_cell_occupied(row - 1, col - 1, 2)) // Для игрока 2
        {
            add_marker(row - 1, col - 1, 2);
            printf("Клетка %d,%d занята для игрока 2\n", row, col);
            (*ship_count)--;
            printf("Осталось кораблей: %d\n", *ship_count);
        }
        else
        {
            printf("Клетка %d,%d свободна для игрока 2\n", row, col);
        }
    }
    else
    {
        printf("Ошибка в вводе координат!\n");
    }
}

// Функция для добавления маркера
bool add_marker(int j, int i, int player)
{
    int offset = player == 1 ? 0 : 3;

    // Проверка допустимости индексов
    if (j < 0 || j >= MAX_COLS || i < 0 || i >= MAX_ROWS || (player != 1 && player != 2))
    {
        printf("Некорректные параметры для добавления маркера!\n");
        return false;
    }

    // Добавление маркера 'K'
    grid_visible[offset / 3][i][j] = 'K';
    return true;
}

bool add_ship(int j, int i, int player)
{
    int offset = player == 1 ? 0 : 3;

    // Проверка допустимости индексов
    if (j < 0 || j >= MAX_COLS || i < 0 || i >= MAX_ROWS || (player != 1 && player != 2))
    {
        printf("Некорректные параметры для добавления маркера!\n");
        return false;
    }

    // Добавление маркера 'K'
    grid_hidden[offset / 3][i][j] = 'K';
    return true;
}
// сейчас проверяется только второй игрок

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
    return grid_hidden[offset / 3][i][j] == 'K';
}

// Обновленная функция line с учетом маркеров
void line_with_markers(int cols, const char *start, const char *middle, void(chars(int i)), const char *end, int offset, int row)
{
    printf("%*s%s", offset, "", start);
    for (int j = 0; j < cols - 1; j++)
    {
        if (grid_visible[offset / 3][j][row] == 'K')
        {
            printf(" K │");
        }
        else
        {
            printf("   │");
        }
        if (NULL != chars)
            chars(j);
    }
    printf("%s%s", end, offset != 0 ? "\n" : "");
}