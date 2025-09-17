#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//Check if a specified column is valid
int validCol(int board[9][9], int column) {
    int seen[10] = {0};
    int isCorrect = 1;
    for (int row = 0; row < 9; row++) {
        int value = board[row][column];
        if (!value) continue;
        if (!seen[value]) {
            seen[value] = 1;
        } else {
            isCorrect = 0;
            // printf("Mistake on Column %d duplicate: %d\n", column, value);
        }
    }
    return isCorrect;
}
//Check if a specified row is valid
int validRow(int board[9][9], int row) {
    int seen[10] = {0};
    int isCorrect = 1;
    for (int column = 0; column < 9; column++) {
        int value = board[row][column];
        if (!value) continue;
        if (!seen[value]) {
            seen[value] = 1;
        } else {
            isCorrect = 0;
            // printf("Mistake on Row %d duplicate: %d\n", row, value);
        }
    }
    return isCorrect;
}
//Check if a specified subgrid is valid
int validSub(int board[9][9], int startRow, int startCol) {
    int seen[10] = {0};
    int isCorrect = 1;
    for (int row = startRow; row < startRow + 3; row++) {
        for (int column = startCol; column < startCol + 3; column++) {
            int value = board[row][column];
            if (value == 0) continue;
            if (!seen[value]) {
                seen[value] = 1;
            } else {
                isCorrect = 0;
                // printf("Mistake on Block %d duplicate: %d\n", (row / 3) * 3 + (column / 3), value);
            }
        }
    }

    return isCorrect;
}

//Draw board on terminal
void drawBoard(int highlightRow, int highlightCol, int board[9][9]) {
    printf("Move:\nw = up\ns = down\na = left\nd = right\n");
    printf("\n+---------+----------+----------+\n");
    for (int row = 0; row < 9; row++) {
        for (int column = 0; column < 9; column++) {
            if (column == 0 && row == highlightRow && column == highlightCol) {
                printf("|I%d ", board[row][column]);
            } else if ((column + 1) % 3 == 0 && row == highlightRow && column == highlightCol) {
                printf("I%d | ", board[row][column]);
            } else if (row == highlightRow && column == highlightCol) {
                printf("I%d ", board[row][column]);
            } else if ((column + 1) % 3 == 0) {
                printf(" %d | ", board[row][column]);
            } else if (column == 0) {
                printf("| %d ", board[row][column]);
            } else {
                printf(" %d ", board[row][column]);
            }
        }
        if ((row + 1) % 3 == 0) printf("\n+---------+----------+----------+\n");
        else printf("\n");
    }
}

//Suduko solver, remove this in main to start the board as empty.
int auto_ans(int board[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int column = 0; column < 9; column++) {
            if (board[row][column] == 0) {
                for (int candidate = 1; candidate <= 9; candidate++) {
                    board[row][column] = candidate;
                    if (validRow(board, row) && validCol(board, column) &&
                            validSub(board, (row / 3) * 3, (column / 3) * 3)) {
                        if (auto_ans(board)) return 1;  // recurse
                    }
                    board[row][column] = 0;  // reset
                }
                return 0;  // no valid number fits here
            }
        }
    }
    return 1; // solved!
}

int main() {
    int currentRow = 0, currentCol = 0;
    int board[9][9] = {0};
    auto_ans(board); //remove this line to empty the suduko
    int filledCells = 80; // reset this to 0
    board[0][0] = 0; // remove this line if you remove the auto-ans function

    printf("Progress: %.02f%%\nNo. of cell filled: %.0f\n",
           (filledCells / 81.0) * 100, (float)filledCells);
    drawBoard(0, 0, board);

    while (filledCells != 81) {
        char inputChar = getch();
        int value = inputChar - '0';

        switch (inputChar) {
        case 'w': // move the cursor up
            if (currentRow > 0) currentRow--;
            break;
        case 's': // move cursor down
            if (currentRow < 8) currentRow++;
            break;
        case 'a': // move cursor left 
            if (currentCol > 0) currentCol--;
            break;
        case 'd': // move cursor right
            if (currentCol < 8) currentCol++;
            break;
        }
        
        //draw board per change
        if (value >= 0 && value <= 9 && board[currentRow][currentCol] != value) {
            if (board[currentRow][currentCol] == 0) filledCells++;
            else if (value == 0) filledCells--;
            board[currentRow][currentCol] = value;
        }
        system("clear");
        printf("Progress: %.02f%%\nNo. of cell filled: %.0f\n",
               (filledCells / 81.0) * 100, (float)filledCells);
        drawBoard(currentRow, currentCol, board);
        
    }

    system("clear");
    printf("Progress: %.02f%%\nNo. of cell filled: %.0f\n",
           (filledCells / 81.0) * 100, (float)filledCells);
    drawBoard(currentRow, currentCol, board);
    //check the board answer
    int isCorrect = 1;
    for (int index = 0; index < 9; index++) {
        if (validCol(board, index) == 0 || validRow(board, index) == 0) {
            isCorrect = 0;
            break;
        }
    }
    if (isCorrect == 1) {
        for (int row = 0; row < 9; row += 3) {
            for (int column = 0; column < 9; column += 3) {
                if (validSub(board, row, column) == 0) {
                    isCorrect = 0;
                    break;
                }
            }
            if (!isCorrect) break;
        }
    }

    if (isCorrect) {
        printf("Sudoku is valid!\n");
    } else {
        printf("Sudoku is invalid!\n");
    }

    return 0;
}