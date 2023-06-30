#include <catch2/catch.hpp>
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

#define MAX_BOARD_SIZE 9

// Function prototypes
void test_initializeBoard();
void test_isValidMove();
void test_makeMove();
void test_saveBoard();
void test_loadBoard();
void test_boardExists();

// Unit test for initializeBoard
void test_initializeBoard() {
    // Create a sample board
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

    // Call the function
    initializeBoard(board, 3);

    // Assertion: All cells should be initialized with '-'
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assert(board[i][j] == '-');
        }
    }
}

// Unit test for isValidMove
void test_isValidMove() {
    // Create a sample board
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = {
        { '-', '-', '-' },
        { '-', '-', '-' },
        { '-', '-', '-' }
    };

    // Assertion: All cells should be valid moves
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assert(isValidMove(board, i, j));
        }
    }

    // Make a move in the board
    makeMove(board, 1, 1, 'O');

    // Assertion: The cell (1, 1) should no longer be a valid move
    assert(!isValidMove(board, 1, 1));
}

// Unit test for makeMove
void test_makeMove() {
    // Create a sample board
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = {
        { '-', '-', '-' },
        { '-', '-', '-' },
        { '-', '-', '-' }
    };

    // Make a move in the board
    makeMove(board, 1, 1, 'O');

    // Assertion: The cell (1, 1) should be marked with 'O'
    assert(board[1][1] == 'O');
}

// Unit test for saveBoard
void test_saveBoard() {
    // Create a sample board
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = {
        { '-', '-', '-' },
        { '-', '-', '-' },
        { '-', '-', '-' }
    };

    // Call the function
    saveBoard(board, 3);

    // Load the board from the file
    int size;
    char loadedBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    loadBoard(loadedBoard, &size);

    // Assertion: The loaded board should be equal to the original board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assert(board[i][j] == loadedBoard[i][j]);
        }
    }
}

// Unit test for loadBoard
void test_loadBoard() {
    // Create a sample board
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = {
        { '-', '-', '-' },
        { '-', '-', '-' },
        { '-', '-', '-' }
    };

    // Save the board to a file
    saveBoard(board, 3);

    // Create a new board and load the saved board
    int size;
    char loadedBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    loadBoard(loadedBoard, &size);

    // Assertion: The loaded board should be equal to the original board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assert(board[i][j] == loadedBoard[i][j]);
        }
    }
}

// Unit test for boardExists
void test_boardExists() {
    // Assertion: The board file should not exist initially
    assert(!boardExists());

    // Create a sample board
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = {
        { '-', '-', '-' },
        { '-', '-', '-' },
        { '-', '-', '-' }
    };

    // Save the board to a file
    saveBoard(board, 3);

    // Assertion: The board file should exist after saving the board
    assert(boardExists());
}

int main() {
    // Run unit tests
    test_initializeBoard();
    test_isValidMove();
    test_makeMove();
    test_saveBoard();
    test_loadBoard();
    test_boardExists();

    printf("All tests passed!\n");

    return 0;
}
