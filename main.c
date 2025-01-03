#include <stdio.h>
#include <locale.h>
#include "main.h"

int main()
{

    int row_count = 10;
    int col_count = 10;
    char s;

    int rows = row_count;
    int cols = col_count + 1;

    const char *letters[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // draw square
    line(cols, "�", "����", "��Ŀ\n");

    first_vertical_line(cols, letters);

    for (int i = 0; i < rows; i++)
    {

        line(cols, "�", "����", "��Ĵ\n");
        vertical_line_field(cols, numbers, i);
    }

    last_line(cols);
    printf("487");
    scanf("%c", &s);
    return 0;
}

void last_line(int cols)
{
    printf("�");
    for (int j = 0; j < cols - 1; j++)
    {
        printf("����");
    }
    printf("����\n");
}

void vertical_line_field(int cols, int numbers[10], int i)
{

    printf("�%2d �", numbers[i]);

    line(cols, "", "   �", "\n");
}

void first_vertical_line(int cols, const char *letters[10])
{
    printf("�   �");
    for (int j = 0; j < cols - 1; j++)
    {
        printf(" %s �", letters[j]);
    }
    printf("\n");
}

char *bprintf(char *fmt, ...)
{
    static char buffer[10];
        va_list ap=NULL;

        va_start(ap, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, ap);

    return buffer;

}

void line(int cols, const char *start, const char *middle, const char *end)
{
    printf("%s", start);
    for (int j = 0; j < cols - 1; j++)
    {
        printf("%s", middle);
    }
    printf("%s", end);
}