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

int main() {
    int size, row, col, choice;
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    system("clear");
    printf("The admin sets up the room and can mark unusable seats with an O, the waiter can reserve tables using X.\n");

    while (1) {
        printf("-------------------------------------------\n");
        printf("Type %d for Admin, %d for Waiter, %d to Exit: ", OPTION_ADMIN, OPTION_WAITER, OPTION_EXIT);
        choice = getIntegerInput();
        system("clear");

        switch (choice) {
            case OPTION_ADMIN: {
                if (boardExists()) {
                    deleteBoard();
                }

                while (1) {
                    printf("Enter the size of the board (up to 15): ");
                    size = getIntegerInput();

                    if (size > MAX_BOARD_SIZE) {
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

                int num_guests = size * size;

                time_t currentTime;
                struct tm* localTime;
                char current_date[100];
                // Get the current time
                currentTime = time(NULL);
                // Convert the current time to the local time
                localTime = localtime(&currentTime);
                // Format the current time as a string
                strftime(current_date, sizeof(current_date), "%d.%m.%Y", localTime);

                // Allocate memory for the guest_list array
                guest* guest_list = calloc(num_guests, sizeof(guest));

                char user_input;

                while (1) {
                    printf("user menu:\na = guests have arrived\nl = guests have left\nc = todays reservations\nn = new reservation\nd = delete reservation\nm = view restaurant\nf = find neighbors\nb = back\nYour input: ");
                    scanf(" %c", &user_input);

                    switch (user_input) {
                        int row, col, choice;

                        case 'n': {
                            read_reservations(guest_list, num_guests);
                            guest new_guest;
                            system("clear");

                            printf("Please enter name: ");
                            scanf("%s", new_guest.name);
                            //tolower(new_guest.name);
                            system("clear");

                            printf("Please enter surname: ");
                            scanf("%s", new_guest.surname);
                            //tolower(new_guest.surname);
                            system("clear");

                            printf("Please enter birthday (format dd.mm.yyyy): ");
                            scanf("%10s", new_guest.birthday);

                            while (!validateDate(new_guest.birthday)) {
                                printf("Invalid birthday format. Please enter again (format dd.mm.yyyy): ");
                                scanf("%10s", new_guest.birthday);
                            }
                            system("clear");

                            printf("Please enter phone number (max 11 digits, only numbers): ");
                            scanf("%11s", new_guest.phone);

                            while (!validatePhoneNumber(new_guest.phone)) {
                                printf("Invalid phone number format. Please enter again (max 11 digits, only numbers): ");
                                scanf("%11s", new_guest.phone);
                            }
                            system("clear");

                            printf("Please enter address: ");
                            scanf(" %[^\n]%*c", new_guest.address);
                            //tolower(new_guest.address);
                            system("clear");

                            printf("Please enter email: ");
                            scanf("%s", new_guest.email);
                            //tolower(new_guest.email);
                            system("clear");

                            printf("Please enter reservation date (format dd.mm.yyyy): ");
                            scanf("%10s", new_guest.reservation_date);

                            while (!validateDate(new_guest.reservation_date)) {
                                printf("Invalid reservation date format. Please enter again (format dd.mm.yyyy): ");
                                scanf("%10s", new_guest.reservation_date);
                            }
                            system("clear");

                            printf("Please enter reservation time: ");
                            scanf("%5s", new_guest.reservation_time);

                            while (!validateTime(new_guest.reservation_time)) {
                                printf("Invalid reservation time format. Please enter again (format hh:mm): ");
                                scanf("%5s", new_guest.reservation_time);
                            }
                            system("clear");

                            printf("Please enter the number of guests (max 4): ");
                            scanf("%d", &new_guest.num_guests);

                            while (new_guest.num_guests > 4  || new_guest.num_guests < 1) {
                                printf("Invalid number of guests. Please enter again (1-4 guests): ");
                                scanf("%d", &new_guest.num_guests);
                            }
                            system("clear");

                            printf("Please enter table number: ");
                            scanf("%5s", new_guest.table_number);
                            for(int i = 0; i < num_guests; i++){
                                while (strcmp(guest_list[i].reservation_date, current_date) == 0 && strcmp(guest_list[i].table_number, new_guest.table_number) == 0 && strcmp(guest_list[i].reservation_time, new_guest.reservation_time) == 0) {
                                    printf("Table is already taken. Please choose another table : ");
                                    scanf("%5s", new_guest.table_number);
                                }
                            }

                            system("clear");
                            // Code for getting new reservation details and writing to the CSV file
                            write_user_data_to_csv(new_guest);
                            break;
                        }

                        case 'c': {
                            // Read the guest reservations from the file
                            read_reservations(guest_list, num_guests);
                            system("clear");
                            // Print the current reservations
                            print_current_reservations(guest_list, num_guests);
                            while (1) {
                                printf("Enter 0 0 to exit): ");
                                row = getIntegerInput();
                                col = getIntegerInput();

                                if (row == 0 && col == 0) {
                                    printf("Waiter logged out. Saving the board...\n");
                                    break;
                                }
                            }
                            system("clear");
                            break;

                        }

                        case 'd': {
                            //add Name and Date
                            guest canceled_reservation;
                            system("clear");
                            printf("Please enter table number: ");
                            scanf("%s", canceled_reservation.table_number);

                            read_reservations(guest_list, num_guests);
                            delete_reservation(guest_list, num_guests, canceled_reservation.table_number);
                            write_reservations(guest_list, num_guests);
                            break;
                        }

                        case 'a': {
                            char temp_table[5];
                            char temp_time[6];
                            system("clear");
                            printf("Please enter table number: ");
                            scanf("%s", temp_table);

                            system("clear");
                            printf("Please enter arrival time: ");
                            scanf("%s", temp_time);

                            while (!validateTime(temp_time)) {
                                printf("Invalid reservation time format. Please enter again (format hh:mm): ");
                                scanf("%5s", temp_time);
                            }

                            // Code for handling guests arrival
                            read_reservations(guest_list, num_guests);
                            guest_arrival(guest_list, num_guests, temp_table, temp_time);
                            write_reservations(guest_list, num_guests);
                            break;
                        }

                        case 'l': {
                            char temp_table[5];
                            char temp_time[6];
                            system("clear");
                            printf("Please enter table number: ");
                            scanf("%s", temp_table);

                            system("clear");
                            printf("Please enter departure time: ");
                            scanf("%s", temp_time);

                            while (!validateTime(temp_time)) {
                                printf("Invalid reservation time format. Please enter again (format hh:mm): ");
                                scanf("%5s", temp_time);
                            }

                            // Code for handling guests departure
                            read_reservations(guest_list, num_guests);
                            guest_departure(guest_list, num_guests, temp_table, temp_time);
                            write_reservations(guest_list, num_guests);
                            break;
                        }

                        case 'm': {
                            char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
                            system("clear");
                            initializeBoard(board, size);

                            read_reservations(guest_list, num_guests);

                            for(int i = 0; i < num_guests; i++){
                                if (strcmp(guest_list[i].reservation_date, current_date) == 0) {
                                    int row = guest_list[i].table_number[0] - '0' - 1;
                                    int col = guest_list[i].table_number[1] - '0' - 1;
                                    board[row][col] = 'X';
                                }
                            }

                            displayBoard(board, size);

                            while (1) {
                                printf("Enter row and column (0 0 to exit): ");
                                row = getIntegerInput();
                                col = getIntegerInput();

                                if (row == 0 && col == 0) {
                                    printf("Waiter logged out. Saving the board...\n");
                                    system("clear");
                                    break;
                                }
                            }
                            break;
                        }

                        case 'f': {
                            char temp_table[5];
                            char temp_time[5];
                            char temp_date[10];
                            read_reservations(guest_list, num_guests);
                            system("clear");

                            printf("Please enter date: ");
                            scanf("%s", temp_date);
                            printf("Please enter time: ");
                            scanf("%s", temp_time);
                            printf("Please enter table number: ");
                            scanf("%s", temp_table);

                            int neighborsRow[] = { -1, 0, 1, 0 };
                            int neighborsCol[] = { 0, 1, 0, -1 };
                            int numNeighbors = 4;
                            row = temp_table[0] - '0';
                            col = temp_table[1] - '0';
                            
                            system("clear");
                            printf("Name:                          Surname:                       Tel:        Email:\n");
                            // Check each neighbor
                            for (int i = 0; i < numNeighbors; i++) {
                                int newRow = row + neighborsRow[i];
                                int newCol = col + neighborsCol[i];

                                char comp_table[5];

                                sprintf(comp_table, "%d%d", newRow, newCol);

                                for(int j = 0; j < num_guests; j++){
                                    if (strcmp(guest_list[j].reservation_date, temp_date) == 0 && strncmp(guest_list[j].reservation_time, temp_time, 5) == 0 && strcmp(guest_list[j].table_number, comp_table) == 0) {
                                        printf("%-30s %-30s %-12s %-12s\n", guest_list[j].name, guest_list[j].surname, guest_list[j].phone, guest_list[j].email);
                                    }

                                }
                            }

                            while (1) {

                                printf("Enter 0 0 to exit): ");
                                row = getIntegerInput();
                                col = getIntegerInput();

                                if (row == 0 && col == 0) {
                                    printf("Waiter logged out. Saving the board...\n");
                                    break;
                                }
                            }
                            system("clear");
                            break;
                        }

                        case 'b': {
                            system("clear");
                            break;                  
                        }

                        default: {
                            printf("Invalid input. Please try again.\n");
                            continue;
                        }
                    }
                    break;
                }
                break;
            }
            case OPTION_EXIT: {
                printf("Exiting...\n");
                return 0;
            }
            default: {
                printf("Invalid input. Please try again.\n");
                break;
            }
        }
    }
}

