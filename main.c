#include <stdio.h>

int main() {
    int row_count = 7;
    int col_count = 7;

    int rows = row_count; 
    int cols = col_count + 1; 

    const char *letters[] = {"a","b","c","d","e","f","g","h","i","j"};
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 1; i++) {
        // Горизонтальные линии
        printf("┌");
        for (int j = 0; j < cols - 1; j++) {
            printf("───┬");
        }
        printf("───┐"); 
        printf("\n");

        //вертикальные линии
        printf("│");
        for (int j = 0; j < cols; j++) {
            if (j > 0) {
                printf(" %s │", letters[j-1]);
            }
            else {printf("   │");}

        }
        printf("\n");


    }

    for (int i = 0; i < rows; i++) {
        // Горизонтальные линии
        printf("├");
        for (int j = 0; j < cols; j++) {
            if (j == cols - 1) {printf("───┤");}
            else {printf("───┼");}
        }
        printf("\n");

        // Вертикальные разделители
        printf("│");
        for (int j = 0; j < cols; j++) {

            if (j < 1)
            {
            	if (numbers[i] == 10 ){printf(" %d│", numbers[i]);}
            	else {printf(" %d │", numbers[i]);}

            }

            else {printf("   │");}

        }

        printf("\n");
    }

    for (int i = 0; i < 1; i++) {
        // Горизонтальные линии
        printf("└");
        for (int j = 0; j < cols - 1; j++) {
            printf("───┴");
        }
        printf("───┘");
        printf("\n");
    }

    return 0;
}
