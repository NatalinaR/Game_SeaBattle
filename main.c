#include <stdio.h>
#include "main.h"
#include <stdarg.h>

int main()
{
    const int cells = 10;

    int row_count = cells;
    int col_count = cells + 1;

    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const char *letters[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};

    // Горизонтальные линии
    line(col_count, "┌", "───┬", NULL,"───┐\n");

    //вертикальные линии
    line(col_count, "│   │", NULL, row_header, "\n");

    for (int i = 0; i < row_count; i++)
    {
        // Горизонтальные линии
        line(col_count, "├", "───┼", NULL,"───┤\n");

        // Вертикальные разделители
        line(col_count, bprintf("│%2d │", numbers[i]),"   │",  NULL, "\n");
    }
                     
    // Горизонтальные линии
    line(col_count, "└", "───┴", NULL,"───┴\n");

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

void line(int cols, const char *start, const char *s, void (chars(int i)), const char *end)
{
    printf(start);
    for (int j = 0; j < cols - 1; j++)
    {
        if (NULL != s)
            printf(s);
        if (NULL != chars)
            chars(j);
    }
    printf(end);
}


void row_header(int j)
{
    const char *letters[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};

    printf(" %s │", letters[j]);
}