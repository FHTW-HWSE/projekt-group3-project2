#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 15
#define OPTION_ADMIN 1
#define OPTION_WAITER 2
#define OPTION_EXIT 3

void initializeBoard(char board[MAX_SIZE][MAX_SIZE], int size) {
    // Initialisiere das Spielfeld mit '-' Markierungen
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            board[i][j] = '-';
        }
    }
}

void displayBoard(char board[MAX_SIZE][MAX_SIZE], int size) {
    // Zeige den aktuellen Zustand des Spielfelds an
    int i, j;
    printf("\nBoard:\n");
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

bool isValidMove(char board[MAX_SIZE][MAX_SIZE], int row, int col) {
    // Überprüfe, ob ein Zug gültig ist
    return (board[row][col] == '-');
}

void makeMove(char board[MAX_SIZE][MAX_SIZE], int row, int col, char marker) {
    // Mache einen Zug auf dem Spielfeld
    board[row][col] = marker;
}

void saveBoard(char board[MAX_SIZE][MAX_SIZE], int size) {
    // Speichere das Spielfeld in eine Datei
    FILE* file = fopen("board.txt", "w");
    if (file == NULL) {
        printf("Error opening file for saving the board.\n");
    }

    fprintf(file, "%d\n", size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(file, "%c ", board[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

bool loadBoard(char board[MAX_SIZE][MAX_SIZE], int* size) {
    // Lade das Spielfeld aus einer Datei
    FILE* file = fopen("board.txt", "r");
    if (file == NULL) {
        printf("Error opening file for loading the board.\n");
        return false;
    }

    fscanf(file, "%d", size);

    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            fscanf(file, " %c", &board[i][j]);
        }
    }

    fclose(file);
    return true;
}

bool boardExists() {
    // Überprüfe, ob die Spielfelddatei existiert
    FILE* file = fopen("board.txt", "r");
    if (file == NULL) {
        fclose(file);
        return false;
    }
    fclose(file);
    return true;
}

void deleteBoard() {
    // Lösche die Spielfelddatei
    remove("board.txt");
}

int getIntegerInput() {
    // Lese eine Ganzzahleneingabe vom Benutzer ein
    int input;
    char c;
    while (scanf("%d", &input) != 1) {
        while ((c = getchar()) != '\n' && c != EOF);

        printf("Invalid input.\nPlease enter a number: ");
    }
    return input;
}

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
