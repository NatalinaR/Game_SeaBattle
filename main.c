#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define SHIP_CHARACTER '€'
#define MISS_CHARACTER '+'
#define DESTROYED_SHIP_CHARACTER '∞'

// matrix to save markers
char grid_visible[2][10][10];

int max_rows = 5;
int max_cols = 5;
int ships_number = 5;

#pragma region Main
void initialize_grid()
{
    memset(grid_visible, ' ', sizeof(grid_visible));
}

int main()
{
    char choice;
    char s;

    do
    {
        initialize_grid();
        setup_game_settings(&max_rows, &max_cols, &ships_number);

        const int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        printf("Player 1, place your ship:\n");
        place_all_ships(1);

        printf("Player 2, place your ship:\n");
        place_all_ships(2);

        game_loop(max_cols + 1, max_rows, numbers);

        printf("Good GAME!\n");

        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &choice);

        system("cls");
    } while (choice == 'y' || choice == 'Y');

    printf("Thank you for playing!\n");
    scanf("%s", &s);
    return 0;
}
#pragma endregion

#pragma region Board

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

void line_with_markers(int cols, const char *start, const char *middle, void(chars(int i)), const char *end, int offset, int row, int player_index)
{
    printf("%*s%s", offset, "", start);

    for (int j = 0; j < cols - 1; j++)
    {
        char cell = grid_visible[offset / 3][j][row];
        bool show_S = (player_index == 1 && offset == 0) || (player_index == 2 && offset == 3);

        switch (cell)
        {
        case DESTROYED_SHIP_CHARACTER:
            printf(" %c ≥", DESTROYED_SHIP_CHARACTER);
            break;
        case MISS_CHARACTER:
            printf(" %c ≥", MISS_CHARACTER);
            break;
        case SHIP_CHARACTER:
            if (show_S)
                printf(" %c ≥", SHIP_CHARACTER);
            else
                printf("   ≥");
            break;
        default:
            printf("   ≥");
            break;
        }

        if (chars != NULL)
            chars(j);
    }

    printf("%s%s", end, offset != 0 ? "\n" : "");
}

void row_header(int j)
{
    const char *letters[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
    printf(" %s ≥", letters[j]);
}

void draw_boards(int cols, int rows, const int *numbers, int player_index)
{
    line(cols, "⁄", "ƒƒƒ¬", NULL, "ƒƒƒø", 0);
    line(cols, "⁄", "ƒƒƒ¬", NULL, "ƒƒƒø", 3);

    line(cols, "≥   ≥", NULL, row_header, "", 0);
    line(cols, "≥   ≥", NULL, row_header, "", 3);

    for (int i = 0; i < rows; i++)
    {

        line(cols, "√", "ƒƒƒ≈", NULL, "ƒƒƒ¥", 0);
        line(cols, "√", "ƒƒƒ≈", NULL, "ƒƒƒ¥", 3);

        line_with_markers(cols, bprintf("≥%2d ≥", numbers[i]), "   ≥", NULL, "", 0, i, player_index);
        line_with_markers(cols, bprintf("≥%2d ≥", numbers[i]), "   ≥", NULL, "", 3, i, player_index);
    }

    line(cols, "¿", "ƒƒƒ¡", NULL, "ƒƒƒŸ", 0);
    line(cols, "¿", "ƒƒƒ¡", NULL, "ƒƒƒŸ", 3);
}

#pragma endregion

#pragma region Input
void get_coordinates(const char *input, int *row, int *col)
{
    if (input == NULL || input[0] == '\0' || input[1] == '\0')
    {
        printf("Wrong!\n");
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
        printf("WrongCol!\n");
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
        printf("WrongRow!\n");
        *row = -1;
        *col = -1;
    }
}

void process_input(int *ship_count, int main_player, const int *numbers)
{
    char input[10];
    int row, col;

    int enemy = main_player == 1 ? 2 : 1;

    while (1)
    {

        printf("Attack (e.g., A2): ");
        scanf("%s", input);
        get_coordinates(input, &row, &col);

        // Check for valid coordinates
        if (row == -1 || col == -1)
        {
            printf("Error in coordinates input!\n");
            continue;
        }

        // Bounds check
        if (row < 1 || row > max_rows || col < 1 || col > max_cols)
        {
            printf("Coordinates are out of bounds! Grid is %dx%d.\n", max_rows, max_cols);
            continue;
        }

        // Check if already chosen
        if (check_cell(row - 1, col - 1, enemy, 'C'))
        {
            printf("Cell %d,%d already has been chosen, pick another one\n", row, col);
            continue;
        }

        // If occupied (hit)
        if (check_cell(row - 1, col - 1, enemy, SHIP_CHARACTER))
        {
            system("cls");
            add_marker(row - 1, col - 1, enemy, DESTROYED_SHIP_CHARACTER);
            draw_boards(max_cols + 1, max_rows, numbers, main_player);

            printf("HIT!\n");
            (*ship_count)--;
            // printf("Ships left: %d\n", *ship_count);

            // Allow another shot if it was a hit
            if (*ship_count == 0)
                break;
        }
        else
        {
            system("cls");
            add_marker(row - 1, col - 1, enemy, MISS_CHARACTER);
            draw_boards(max_cols + 1, max_rows, numbers, main_player);
            printf("MISS.\n");
            break;
        }
    }
}
#pragma endregion

#pragma region GameLogic
void place_all_ships(int player)
{
    int ships_to_place = ships_number;
    char input[10];
    int row, col;

    printf("=== Placing ships for player %d ===\n", player);

    for (int i = 0; i < ships_to_place;)
    {
        printf("Place a ship #%d (e.g, A2): ", i + 1);
        scanf("%s", input);
        get_coordinates(input, &row, &col);

        if (row != -1 && col != -1)
        {
            if (add_marker(row - 1, col - 1, player, SHIP_CHARACTER))
            {
                // printf("Ship #%d placed to %s\n", i + 1, input);
                i++;
            }
            else
            {
                printf("Wrong data. Repeat again!\n");
            }
        }
        else
        {
            printf("Wrong coordinates. Repeat again!\n");
        }
    }

    printf("All %d ships have been placed for player %d.\n", ships_to_place, player);

    printf("\n===== Game LOADING =====\n");

    Sleep(1000);
    system("cls");
}

void game_loop(int cols, int rows, const int *numbers)
{
    int ships_player1 = ships_number;
    int ships_player2 = ships_number;

    while (ships_player1 > 0 && ships_player2 > 0)
    {
        printf("\n===== TURN PLAYER 1 =====\n");

        draw_boards(cols, rows, numbers, 1);

        process_input(&ships_player2, 1, numbers); // player 1 attack player 2

        if (ships_player2 == 0)
        {
            printf("Player 1 won!\n");
            break;
        }

        printf("\n===== Next player loading =====\n");
        Sleep(2000);

        system("cls");
        printf("\n===== TURN PLAYER 2 =====\n");

        draw_boards(cols, rows, numbers, 2);

        process_input(&ships_player1, 2, numbers); // player 2 attack player 1

        if (ships_player1 == 0)
        {
            printf("Player 2 won!\n");
            break;
        }

        printf("\n===== Next player loading =====\n");
        Sleep(2000);
        system("cls");
    }
}
#pragma endregion

#pragma region GridHelpers
bool add_marker(int j, int i, int player, char purpose)
{
    int offset = player == 1 ? 0 : 3;

    // è‡Æ¢•‡™† §ÆØ„·‚®¨Æ·‚® ®≠§•™·Æ¢ ® ®£‡Æ™†
    if (j < 0 || j >= max_cols || i < 0 || i >= max_rows || (player != 1 && player != 2))
    {
        printf("Wrong marker parameters!\n");
        return false;
    }

    switch (purpose)
    {
    case SHIP_CHARACTER:
        grid_visible[offset / 3][i][j] = SHIP_CHARACTER;
        break;

    case DESTROYED_SHIP_CHARACTER:
        grid_visible[offset / 3][i][j] = DESTROYED_SHIP_CHARACTER;
        break;

    case MISS_CHARACTER:
        grid_visible[offset / 3][i][j] = MISS_CHARACTER;
        break;

    default:
        printf("Unknown purpose type: %c\n", purpose);
        return false;
    }

    return true;
}

bool check_cell(int j, int i, int player, char type)
{
    int offset = player == 1 ? 0 : 3;

    if (j < 0 || j >= max_cols || i < 0 || i >= max_rows || (player != 1 && player != 2))
    {
        printf("Wrong marker parameters!\n");
        return false;
    }

    char cell = grid_visible[offset / 3][i][j];

    switch (type)
    {
    case SHIP_CHARACTER: // check if a ship is present
        return cell == SHIP_CHARACTER;
    case 'C': // check if cell is chosen (hit or miss)
        return cell == MISS_CHARACTER || cell == DESTROYED_SHIP_CHARACTER;
    default:
        printf("Unknown check type: %c\n", type);
        return false;
    }
}

#pragma endregion

void setup_game_settings(int *rows, int *cols, int *ship_count)
{
    char choice;
    char buffer[100];

    printf("Do you want to use default game settings? (y/n): ");
    scanf(" %c", &choice);
    choice = tolower(choice);
    while (getchar() != '\n');

    if (choice == 'y')
    {
        *rows = max_rows;
        *cols = max_cols;

        printf("Using default settings: %dx%d board, %d ships per player.\n", *rows, *cols, *ship_count);
    }
    else
    {
        int valid_input = 0;
        while (!valid_input)
        {
            printf("Enter number of cells (1 to 10): ");
            fgets(buffer, sizeof(buffer), stdin);

            // Try to extract one integer from the input
            if (sscanf(buffer, "%d", rows) == 1)
            {
                if (*rows >= 1 && *rows <= 10)
                {
                    valid_input = 1;
                }
                else
                {
                    printf("Invalid input! Please enter a number between 1 and 10.\n");
                }
            }
            else
            {
                printf("Invalid input! Please enter a valid number.\n");
            }
        }

        *cols = *rows;

        // Optional: validation
        if (*rows <= 0 || *cols <= 0 || *rows > 10 || *cols > 10)
        {
            printf("Invalid size. Setting default values.\n");
            *rows = max_rows;
            *cols = max_cols;
        }

        *ship_count = (*rows * *cols) / 5;
        if (*ship_count == 0)
            *ship_count = 1; // Minimum one ship
        // printf("Board size set to %dx%d. Ships per player: %d.\n", *rows, *cols, *ship_count);

        max_rows = *rows;
        max_cols = *cols;
        ships_number = *ship_count;
    }
}