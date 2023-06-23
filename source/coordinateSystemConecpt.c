#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include "guest.h"
#include "csv_operations.h"
#include "changes.h"
#include "user_validation.h"
#include "reservation.h"
#include "board_operations.h"

int main() {
    int size, row, col, choice;
    char board[MAX_SIZE][MAX_SIZE];

    printf("The admin sets up the room and can mark unusable seats with an O, the waiter can reserve tables using X.\n");

    while (1) {
        printf("-------------------------------------------\n");
        printf("Type %d for Admin, %d for Waiter, %d to Exit: ", OPTION_ADMIN, OPTION_WAITER, OPTION_EXIT);
        choice = getIntegerInput();

        switch (choice) {
            case OPTION_ADMIN: {
                if (boardExists()) {
                    deleteBoard();
                }

                while (1) {
                    printf("Enter the size of the board (up to 15): ");
                    size = getIntegerInput();

                    if (size > MAX_SIZE) {
                        printf("Maximum board size exceeded. Please try again.\n");
                        continue;
                    }
                    break;
                }

                initializeBoard(board, size);
                displayBoard(board, size);

                while (1) {
                    printf("Enter row and column (0 0 to exit): ");
                    row = getIntegerInput();
                    col = getIntegerInput();

                    if (row == 0 && col == 0) {
                        printf("Admin logged out. Saving the board...\n");
                        saveBoard(board, size);
                        break;
                    }

                    if (row < 1 || row > size || col < 1 || col > size) {
                        printf("Invalid move. Try again.\n");
                        continue;
                    }

                    if (!isValidMove(board, row - 1, col - 1)) {
                        printf("Spot already marked. Try again.\n");
                        continue;
                    }

                    makeMove(board, row - 1, col - 1, 'O');
                    displayBoard(board, size);
                }
                break;
            }
            case OPTION_WAITER: {
                
                if (!boardExists()) {
                    printf("There is no board. Log in as admin first to generate one.\n");
                    continue;
                }

                printf("Waiter logged in. Loading the board...\n");
                if (!loadBoard(board, &size)) {
                    printf("Error loading the board. Exiting...\n");
                    return 0;
                }

                displayBoard(board, size);

                while (1) {
                    printf("Enter row and column (0 0 to exit): ");
                    row = getIntegerInput();
                    col = getIntegerInput();

                    if (row == 0 && col == 0) {
                        printf("Waiter logged out. Saving the board...\n");
                        saveBoard(board, size);
                        break;
                    }

                    if (row < 1 || row > size || col < 1 || col > size) {
                        printf("Invalid move. Try again.\n");
                        continue;
                    }

                    if (!isValidMove(board, row - 1, col - 1)) {
                        printf("Spot already marked. Try again.\n");
                        continue;
                    }

                    makeMove(board, row - 1, col - 1, 'X');
                    displayBoard(board, size);
                }
                break;
            }
            case OPTION_EXIT: {
                printf("Exiting the program...\n");
                return 0;
            }
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    return 0;
}
