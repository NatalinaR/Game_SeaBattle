#include <stdio.h>
#include "main.h"
#include <stdarg.h>
#include <ctype.h>

int main()
{

    int ship = 10;


    const int cells = 10;
    char s;

    int rows = cells;
    int cols = cells + 1;

    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

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
            line(cols, bprintf("│%2d │", numbers[i]), "   │", NULL, "", 0);
            line(cols, bprintf("│%2d │", numbers[i]), "   │", NULL, "", 3);
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
        *col = letter - 'a';
    }
    else
    {
        printf("Некорректный столбец!\n");
        *row = -1;
        *col = -1;
        return;
    }

    int number;
    if (sscanf(&input[1], "%d", &number) == 1 && number >= 0 && number <= 10)
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
        printf("Вы выбрали строку %d и столбец %d\n", row, col);
        (*ship_count)--;
        printf("Осталось кораблей: %d\n", *ship_count);
    }
    else
    {
        printf("Ошибка в вводе координат!\n");
    }
}