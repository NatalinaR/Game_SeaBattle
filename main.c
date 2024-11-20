#include <stdio.h>
#include <locale.h>
#include "main.h"

int main()
{

    int row_count = 10;
    int col_count = 10;

    int rows = row_count;
    int cols = col_count + 1;

    const char *letters[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    //draw square
    first_line(cols);

    first_vertical_line(cols, letters);

    for (int i = 0; i < rows; i++)
    {
        
        horizontal_line_field(cols);
        vertical_line_field(cols, numbers, i);
    }

    last_line(cols);

    return 0;
}

void last_line(int cols)
{
    printf("└");
    for (int j = 0; j < cols - 1; j++)
    {
        printf("───┴");
    }
    printf("───┘");
    printf("\n");
}

void vertical_line_field(int cols, int numbers[10], int i)
{
    printf("│");
    for (int j = 0; j < cols; j++)
    {

        if (j < 1)
        {
            if (numbers[i] == 10)
            {
                printf(" %d│", numbers[i]);
            }
            else
            {
                printf(" %d │", numbers[i]);
            }
        }

        else
        {
            printf("   │");
        }
    }

    printf("\n");
}

void horizontal_line_field(int cols)
{
    printf("├");
    for (int j = 0; j < cols; j++)
    {
        if (j == cols - 1)
        {
            printf("───┤");
        }
        else
        {
            printf("───┼");
        }
    }
    printf("\n");
}

void first_vertical_line(int cols, const char *letters[10])
{
    printf("│");
    for (int j = 0; j < cols; j++)
    {
        if (j > 0)
        {
            printf(" %s │", letters[j - 1]);
        }
        else
        {
            printf("   │");
        }
    }
    printf("\n");
}

void first_line(int cols)
{
    printf("┌");
    line(cols);
    printf("───┐");
    printf("\n");
}

void line(int cols)
{
    for (int j = 0; j < cols - 1; j++)
    {
        printf("───┬");
    }
}