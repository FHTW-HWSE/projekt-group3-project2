#ifndef CHANGES_H
#define CHANGES_H

void initializeBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size);
void displayBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size);
bool isValidMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int row, int col);
void makeMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int row, int col, char marker);
void saveBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size);
bool loadBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int* size);
bool boardExists();
void deleteBoard();
int getIntegerInput();

#endif  // CHANGES_H
 