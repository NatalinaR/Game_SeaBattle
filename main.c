#include <stdio.h>
#include "main.h"
#include <stdarg.h>

int main()
{
    const int cells = 10;

    int row_count = cells;
    int col_count = cells + 1;

    const char *letters[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Горизонтальные линии
    line(col_count, "┌", "───┬", "───┐\n");

    //вертикальные линии
    printf("│   │");
    line2(col_count, letters);
    printf("\n");

    for (int i = 0; i < row_count; i++)
    {
        // Горизонтальные линии
        line(col_count, "├", "───┼", "───┤\n");

        // Вертикальные разделители
        printf("│%2d │", numbers[i]);

        line(col_count, "", "   │", "\n");
    }
                     
    // Горизонтальные линии
    line(col_count, "└", "───┴", "───┴\n");

    return 0;
}

char *bprintf(char *fmt, ...)
{
    static char buffer[10];
	va_list ap = NULL;

	va_start( ap, fmt );

    vsnprintf( buffer, sizeof(buffer), fmt, ap );
    
    return buffer;
}

void line2(int cols, const char *letters[10])
{
    for (int j = 0; j < cols - 1; j++)
    {
        printf(" %s │", letters[j]);
    }
}

void line(int cols, const char *start, const char *chars, const char *end)
{
    printf(start);
    for (int j = 0; j < cols - 1; j++)
    {
        printf(chars);
    }
    printf(end);
}
