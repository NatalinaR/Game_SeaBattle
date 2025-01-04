#include <stdio.h>
#include "main.h"
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_ROWS 10
#define MAX_COLS 10

// ������쭠� ����� ��� �࠭���� ��થ஢
char grid_hidden[2][MAX_COLS][MAX_ROWS];
char grid_visible[2][MAX_COLS][MAX_ROWS];

// ���樠������ ������쭮� ������
void initialize_grid()
{
    memset(grid_hidden, ' ', sizeof(grid_hidden));
    memset(grid_visible, ' ', sizeof(grid_visible));
}

int main()
{
    initialize_grid(); // ���樠������ ������

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
        line(cols, "�", "����", NULL, "��Ŀ", 0);
        line(cols, "�", "����", NULL, "��Ŀ", 3);

        line(cols, "�   �", NULL, row_header, "", 0);
        line(cols, "�   �", NULL, row_header, "", 3);

        for (int i = 0; i < rows; i++)
        {

            line(cols, "�", "����", NULL, "��Ĵ", 0);
            line(cols, "�", "����", NULL, "��Ĵ", 3);

            line_with_markers(cols, bprintf("�%2d �", numbers[i]), "   �", NULL, "", 0, i);
            line_with_markers(cols, bprintf("�%2d �", numbers[i]), "   �", NULL, "", 3, i);
        }

        line(cols, "�", "����", NULL, "����", 0);
        line(cols, "�", "����", NULL, "����", 3);

        process_input(&ship);
    }

    printf("�� ��ࠡ�� ��⮯����!\n");
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
    printf(" %s �", letters[j]);
}

void get_coordinates(const char *input, int *row, int *col)
{
    if (input == NULL || input[0] == '\0' || input[1] == '\0')
    {
        printf("�����४�� ����!\n");
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
        printf("�����४�� �⮫���!\n");
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
        printf("�����४⭠� ��ப�!\n");
        *row = -1;
        *col = -1;
    }
}

void process_input(int *ship_count)
{
    char input[10];
    int row, col;

    printf("������ ���न���� (���ਬ��, A2 ��� J10): ");
    scanf("%s", input);

    get_coordinates(input, &row, &col);

    if (row != -1 && col != -1)
    {
        printf("�� ��ࠫ� �⮫��� %d � ��ப� %d\n", col, row);
        add_marker(row - 1, col - 1, 1); // ��� ��ப� 1

    }
    else
    {
        printf("�訡�� � ����� ���न���!\n");
    }

    printf("������ ���न���� ��� �⠪� (���ਬ��, A2 ��� J10): ");
    scanf("%s", input);
    get_coordinates(input, &row, &col);

    if (row != -1 && col != -1)
    {
        if (is_cell_occupied(row - 1, col - 1, 2)) // ��� ��ப� 2
        {
            add_marker(row - 1, col - 1, 2);
            printf("���⪠ %d,%d ����� ��� ��ப� 2\n", row, col);
            (*ship_count)--;
            printf("��⠫��� ��ࠡ���: %d\n", *ship_count);
        }
        else
        {
            printf("���⪠ %d,%d ᢮����� ��� ��ப� 2\n", row, col);
        }
    }
    else
    {
        printf("�訡�� � ����� ���न���!\n");
    }
}

// �㭪�� ��� ���������� ��થ�
bool add_marker(int j, int i, int player)
{
    int offset = player == 1 ? 0 : 3;

    // �஢�ઠ �����⨬��� �����ᮢ
    if (j < 0 || j >= MAX_COLS || i < 0 || i >= MAX_ROWS || (player != 1 && player != 2))
    {
        printf("�����४�� ��ࠬ���� ��� ���������� ��થ�!\n");
        return false;
    }

    // ���������� ��થ� 'K'
    grid_visible[offset / 3][i][j] = 'K';
    return true;
}

bool add_ship(int j, int i, int player)
{
    int offset = player == 1 ? 0 : 3;

    // �஢�ઠ �����⨬��� �����ᮢ
    if (j < 0 || j >= MAX_COLS || i < 0 || i >= MAX_ROWS || (player != 1 && player != 2))
    {
        printf("�����४�� ��ࠬ���� ��� ���������� ��થ�!\n");
        return false;
    }

    // ���������� ��થ� 'K'
    grid_hidden[offset / 3][i][j] = 'K';
    return true;
}
// ᥩ�� �஢������ ⮫쪮 ��ன ��ப

// �㭪�� ��� �஢�ન ������ ��થ� � ���⪥ 
bool is_cell_occupied(int j, int i, int player)
{
    int offset = player == 1 ? 0 : 3;

    // �஢�ઠ �����⨬��� �����ᮢ
    if (j < 0 || j >= MAX_COLS || i < 0 || i >= MAX_ROWS || (player != 1 && player != 2))
    {
        printf("�����४�� ��ࠬ���� ��� �஢�ન ���⪨!\n");
        return false;
    }

    // �஢�ઠ, ����� �� ���⪠
    return grid_hidden[offset / 3][i][j] == 'K';
}

// ����������� �㭪�� line � ��⮬ ��થ஢
void line_with_markers(int cols, const char *start, const char *middle, void(chars(int i)), const char *end, int offset, int row)
{
    printf("%*s%s", offset, "", start);
    for (int j = 0; j < cols - 1; j++)
    {
        if (grid_visible[offset / 3][j][row] == 'K')
        {
            printf(" K �");
        }
        else
        {
            printf("   �");
        }
        if (NULL != chars)
            chars(j);
    }
    printf("%s%s", end, offset != 0 ? "\n" : "");
}