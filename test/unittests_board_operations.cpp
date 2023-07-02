#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <cstdio>
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

TEST_CASE("Initialize board") {
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

    SECTION("Initialize board with size 3") {
        initializeBoard(board, 3);

        // Check if all cells are set to '-'
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                REQUIRE(board[i][j] == '-');
            }
        }
    }

    SECTION("Initialize board with size 5") {
        initializeBoard(board, 5);

        // Check if all cells are set to '-'
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                REQUIRE(board[i][j] == '-');
            }
        }
    }
}

TEST_CASE("Display board") {
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    initializeBoard(board, 3);

    SECTION("Display empty board") {
        // Redirect stdout to a stringstream to capture the output
        std::stringstream output;
        std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());

        displayBoard(board, 3);

        // Restore stdout
        std::cout.rdbuf(oldCoutBuf);

        // Check the captured output
        std::string expectedOutput =
            "\nBoard:\n- - - \n- - - \n- - - \n";
        REQUIRE(output.str() == expectedOutput);
    }

    SECTION("Display non-empty board") {
        board[0][1] = 'X';
        board[1][0] = 'O';
        board[2][2] = 'X';

        // Redirect stdout to a stringstream to capture the output
        std::stringstream output;
        std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());

        displayBoard(board, 3);

        // Restore stdout
        std::cout.rdbuf(oldCoutBuf);

        // Check the captured output
        std::string expectedOutput =
            "\nBoard:\n- X - \nO - - \n- - X \n";
        REQUIRE(output.str() == expectedOutput);
    }
}

TEST_CASE("Valid move") {
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    initializeBoard(board, 3);

    SECTION("Valid move on an empty cell") {
        bool valid = isValidMove(board, 1, 1);
        REQUIRE(valid == true);
    }

    SECTION("Invalid move on an occupied cell") {
        board[0][0] = 'X';
        bool valid = isValidMove(board, 0, 0);
        REQUIRE(valid == false);
    }
}

TEST_CASE("Make move") {
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    initializeBoard(board, 3);

    SECTION("Make move on an empty cell") {
        makeMove(board, 1, 2, 'X');
        REQUIRE(board[1][2] == 'X');
    }

    SECTION("Make move on an occupied cell") {
        board[0][1] = 'O';
        makeMove(board, 0, 1, 'X');
        REQUIRE(board[0][1] == 'O');
    }
}

TEST_CASE("Save and load board") {
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    initializeBoard(board, 3);
    board[1][1] = 'X';

    SECTION("Save and load board with size 3") {
        saveBoard(board, 3);

        char loadedBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
        int size;
        bool loaded = loadBoard(loadedBoard, &size);

        REQUIRE(loaded == true);
        REQUIRE(size == 3);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                REQUIRE(loadedBoard[i][j] == board[i][j]);
            }
        }
    }

    SECTION("Save and load board with size 5") {
        saveBoard(board, 5);

        char loadedBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
        int size;
        bool loaded = loadBoard(loadedBoard, &size);

        REQUIRE(loaded == true);
        REQUIRE(size == 5);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                REQUIRE(loadedBoard[i][j] == board[i][j]);
            }
        }
    }
}

TEST_CASE("Board exists") {
    SECTION("Existing board file") {
        // Create an empty board file
        std::FILE* file = std::fopen("board.txt", "w");
        std::fclose(file);

        bool exists = boardExists();
        REQUIRE(exists == true);

        // Delete the board file
        std::remove("board.txt");
    }

    SECTION("Non-existing board file") {
        bool exists = boardExists();
        REQUIRE(exists == false);
    }
}

TEST_CASE("Delete board") {
    // Create an empty board file
    std::FILE* file = std::fopen("board.txt", "w");
    std::fclose(file);

    deleteBoard();

    // Check if the board file is deleted
    bool exists = boardExists();
    REQUIRE(exists == false);
}

TEST_CASE("Get integer input") {
    SECTION("Valid input") {
        // Redirect stdin to a stringstream to provide input
        std::stringstream input("42\n");
        std::streambuf* oldCinBuf = std::cin.rdbuf(input.rdbuf());

        int value = getIntegerInput();

        // Restore stdin
        std::cin.rdbuf(oldCinBuf);

        REQUIRE(value == 42);
    }

    SECTION("Invalid input followed by valid input") {
        // Redirect stdin to a stringstream to provide input
        std::stringstream input("not_a_number\n42\n");
        std::streambuf* oldCinBuf = std::cin.rdbuf(input.rdbuf());

        int value = getIntegerInput();

        // Restore stdin
        std::cin.rdbuf(oldCinBuf);

        REQUIRE(value == 42);
    }
}
