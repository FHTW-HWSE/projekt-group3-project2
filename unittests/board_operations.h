#ifndef BOARD_OPERATIONS_H
#define BOARD_OPERATIONS_H

#define MAX_BOARD_SIZE 9
#define OPTION_ADMIN 1
#define OPTION_WAITER 2
#define OPTION_EXIT 3

void initializeBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size);
void displayBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size);
bool isValidMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int row, int col);
void makeMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int row, int col, char marker);
void saveBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size);
bool loadBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int* size);
bool boardExists();
void deleteBoard();
int getIntegerInput();

#endif  // BOARD_OPERATIONS_H
