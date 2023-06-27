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
#include "board_operations.h"

#define MAX_BOARD_SIZE 15
#define OPTION_ADMIN 1
#define OPTION_WAITER 2
#define OPTION_EXIT 3

void initializeBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size) {
    // Initialisiere das Spielfeld mit '-' Markierungen
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            board[i][j] = '-';
        }
    }
}

void displayBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size) {
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

bool isValidMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int row, int col) {
    // Überprüfe, ob ein Zug gültig ist
    return (board[row][col] == '-');
}

void makeMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int row, int col, char marker) {
    // Mache einen Zug auf dem Spielfeld
    board[row][col] = marker;
}

void saveBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size) {
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

bool loadBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int* size) {
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