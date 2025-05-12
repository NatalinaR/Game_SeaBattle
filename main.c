#include <stdio.h>
#include "main.h"
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ROWS 10
#define MAX_COLS 10
#define SHIPS_NUMBER 3

// ������쭠� ����� ��� �࠭���� ��થ஢
char grid_destryed_ships[2][MAX_COLS][MAX_ROWS];
char grid_visible[2][MAX_COLS][MAX_ROWS];
char grid_chosen_cells[2][MAX_COLS][MAX_ROWS];

// ���樠������ ������쭮� ������
void initialize_grid()
{
    memset(grid_destryed_ships, ' ', sizeof(grid_destryed_ships));
    memset(grid_visible, ' ', sizeof(grid_visible));
    memset(grid_chosen_cells, ' ', sizeof(grid_chosen_cells));
}

int main()
{
    initialize_grid(); // ���樠������ ������

    // add_ship(0, 0, 2, 2);
    const int cells = 10;
    char s;

    int rows = cells;
    int cols = cells + 1;
    const int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // int current_player = ask_player_number();
    // printf("��࠭ ��ப %d\n", current_player);
    // place_all_ships(current_player);
    printf("��ப 1, ���⠢�� ᢮� ��ࠡ��:\n");
    place_all_ships(1);

    printf("��ப 2, ���⠢�� ᢮� ��ࠡ��:\n");
    place_all_ships(2);

    // draw square

    // process_input(&ship, current_player);

    game_loop(cols, rows, numbers);

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

void process_input(int *ship_count, int main_player)
{
    char input[10];
    int row, col;

    int enemy = main_player == 1 ? 2 : 1;

    // int current_player = ask_player_number();
    // printf("��࠭ ��ப %d\n", current_player);
    // place_all_ships(current_player);

    printf("������ ���न���� ��� �⠪� (���ਬ��, A2 ��� J10): ");
    scanf("%s", input);
    get_coordinates(input, &row, &col);

    if (is_cell_chosen(row - 1, col - 1, enemy))
    {
        printf("���⪠ %d,%d 㦥 �뫠 ��࠭�, �롥�� �����\n", row, col);
        printf("������ ���न���� ��� �⠪� (���ਬ��, A2 ��� J10): ");
        scanf("%s", input);
        get_coordinates(input, &row, &col);
    };

    if (row != -1 && col != -1)
    {
        if (is_cell_occupied(row - 1, col - 1, enemy)) 
        {
            add_marker(row - 1, col - 1, enemy);
            printf("�����\n");
            (*ship_count)--;
            printf("��⠫��� ��ࠡ���: %d\n", *ship_count);
        }
        else
        {
            add_miss(row - 1, col - 1, enemy);
            printf("����\n");
        }
    }
    else
    {
        printf("�訡�� � ����� ���न���!\n");
    }
}

// �㭪�� ��� ���������� ��થ�

bool add_ship(int j, int i, int player)
{
    int offset = player == 1 ? 0 : 3;

    // �஢�ઠ �����⨬��� �����ᮢ � ��ப�
    if (j < 0 || j >= MAX_COLS || i < 0 || i >= MAX_ROWS || (player != 1 && player != 2))
    {
        printf("�����४�� ��ࠬ���� ��� ���������� ��થ�!\n");
        return false;
    }

    // � ����ᨬ��� �� ��ப�, ������塞 � �㦭�� ���
    grid_visible[offset / 3][i][j] = 'K';

    return true;
}

bool add_marker(int j, int i, int player)
{
    int offset = player == 1 ? 0 : 3;

    // �஢�ઠ �����⨬��� �����ᮢ � ��ப�
    if (j < 0 || j >= MAX_COLS || i < 0 || i >= MAX_ROWS || (player != 1 && player != 2))
    {
        printf("�����४�� ��ࠬ���� ��� ���������� ��થ�!\n");
        return false;
    }
    grid_destryed_ships[offset / 3][i][j] = 'D';

    return true;
}

bool add_miss(int j, int i, int player)
{
    int offset = player == 1 ? 0 : 3;

    // �஢�ઠ �����⨬��� �����ᮢ � ��ப�
    if (j < 0 || j >= MAX_COLS || i < 0 || i >= MAX_ROWS || (player != 1 && player != 2))
    {
        printf("�����४�� ��ࠬ���� ��� ���������� ��થ�!\n");
        return false;
    }
    grid_chosen_cells[offset / 3][i][j] = '+';

    return true;
}

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
    return grid_visible[offset / 3][i][j] == 'K';
}

// checking has cell been already chosen once
bool is_cell_chosen(int j, int i, int player)
{
    int offset = player == 1 ? 0 : 3;

    // �஢�ઠ �����⨬��� �����ᮢ
    if (j < 0 || j >= MAX_COLS || i < 0 || i >= MAX_ROWS || (player != 1 && player != 2))
    {
        printf("�����४�� ��ࠬ���� ��� �஢�ન ���⪨!\n");
        return false;
    }

    // check was chosen or not
    return grid_chosen_cells[offset / 3][i][j] == '+';
}

// ����������� �㭪�� line � ��⮬ ��થ஢
void line_with_markers(int cols, const char *start, const char *middle, void(chars(int i)), const char *end, int offset, int row, int player_index)
{
    printf("%*s%s", offset, "", start);
    for (int j = 0; j < cols - 1; j++)
    {
        if (player_index == 1 && offset == 0)
        {
            if (grid_visible[offset / 3][j][row] == 'K' && grid_destryed_ships[offset / 3][j][row] == 'D')
            {
                printf(" D �");
            }
            else if (grid_visible[offset / 3][j][row] == 'K' && grid_destryed_ships[offset / 3][j][row] != 'D')
            {
                printf(" K �");
            }
            else if (grid_chosen_cells[offset / 3][j][row] == '+')
            {

                printf(" + �");
            }
            else
            {
                printf("   �");
            }
            if (NULL != chars)
                chars(j);
        }
        else if (player_index == 2 && offset == 3)
        {
            if (grid_visible[offset / 3][j][row] == 'K' && grid_destryed_ships[offset / 3][j][row] == 'D')
            {
                printf(" D �");
            }
            else if (grid_visible[offset / 3][j][row] == 'K' && grid_destryed_ships[offset / 3][j][row] != 'D')
            {
                printf(" K �");
            }
            else if (grid_chosen_cells[offset / 3][j][row] == '+')
            {

                printf(" + �");
            }
            else
            {
                printf("   �");
            }
            if (NULL != chars)
                chars(j);
        }
        else
        {
            if (grid_visible[offset / 3][j][row] == 'K' && grid_destryed_ships[offset / 3][j][row] == 'D')
            {
                printf(" D �");
            }
            else if (grid_chosen_cells[offset / 3][j][row] == '+')
            {

                printf(" + �");
            }
            else
            {
                printf("   �");
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

    printf("=== ����⠭���� ��ࠡ��� ��� ��ப� %d ===\n", player);

    for (int i = 0; i < ships_to_place;)
    {
        printf("������� ��ࠡ�� #%d (���ਬ��, A2 ��� J10): ", i + 1);
        scanf("%s", input);
        get_coordinates(input, &row, &col);

        if (row != -1 && col != -1)
        {
            if (add_ship(row - 1, col - 1, player)) // unified function
            {
                printf("��ࠡ�� #%d ��⠭����� � %s\n", i + 1, input);
                i++; // only increment if successful
            }
            else
            {
                printf("�訡�� �� ��⠭���� ��ࠡ��! ������ ����.\n");
            }
        }
        else
        {
            printf("�訡�� � ���न����! ������ ����.\n");
        }
    }

    printf("�� %d ��ࠡ��� ��⠭������ ��� ��ப� %d.\n", ships_to_place, player);
}

int ask_player_number()
{
    int player;

    do
    {
        printf("�� ��ப 1 ��� 2? ������ 1 ��� 2: ");
        scanf("%d", &player);

        if (player != 1 && player != 2)
        {
            printf("�����४�� ����� ��ப�! ���஡�� ᭮��.\n");
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
        printf("\n===== ��� ������ 1 =====\n");
        draw_boards(cols, rows, numbers, 1);
        process_input(&ships_player2, 1); // ��ப 1 �⠪�� ��ப� 2

        if (ships_player2 == 0)
        {
            printf("��ப 1 �������!\n");
            break;
        }

        printf("\n===== ��� ������ 2 =====\n");
        draw_boards(cols, rows, numbers, 2);
        process_input(&ships_player1, 2); // ��ப 2 �⠪�� ��ப� 1

        if (ships_player1 == 0)
        {
            printf("��ப 2 �������!\n");
            break;
        }
    }
}

void draw_boards(int cols, int rows, const int *numbers, int player_index)
{
    line(cols, "�", "����", NULL, "��Ŀ", 0);
    line(cols, "�", "����", NULL, "��Ŀ", 3);

    line(cols, "�   �", NULL, row_header, "", 0);
    line(cols, "�   �", NULL, row_header, "", 3);

    for (int i = 0; i < rows; i++)
    {

        line(cols, "�", "����", NULL, "��Ĵ", 0);
        line(cols, "�", "����", NULL, "��Ĵ", 3);

        line_with_markers(cols, bprintf("�%2d �", numbers[i]), "   �", NULL, "", 0, i, player_index);
        line_with_markers(cols, bprintf("�%2d �", numbers[i]), "   �", NULL, "", 3, i, player_index);
    }

    line(cols, "�", "����", NULL, "����", 0);
    line(cols, "�", "����", NULL, "����", 3);
}