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

void print_current_reservations(guest* guest_list, int num_guests) {
    time_t currentTime;
    struct tm* localTime;
    char current_date[100];

    // Get the current time
    currentTime = time(NULL);

    // Convert the current time to the local time
    localTime = localtime(&currentTime);

    // Format the current time as a string
    strftime(current_date, sizeof(current_date), "%d.%m.%Y", localTime);

    printf("Name:                          Surname:                       Time:        Table:       Guests:\n");

    // Print reservations for the current date
    for (int i = 0; i < num_guests; i++) {
        if (strcmp(guest_list[i].reservation_date, current_date) == 0) {
            printf("%-30s %-30s %-12s %-12s %d\n", guest_list[i].name, guest_list[i].surname, 
            guest_list[i].reservation_time,guest_list[i].table_number, guest_list[i].num_guests);
        }
    }
}

void delete_reservation(guest* guest_list, int num_guests, char* table_number){
    int i = 0;
    while (i < num_guests) {
        if(strcmp(table_number, guest_list[i].table_number) == 0){
            for(int y = 0; y < MAX_LEN; y++){
                guest_list[i].name[y] = '\0';
            }
            for(int y = 0; y < MAX_LEN; y++){
                guest_list[i].surname[y] = '\0';
            }
            for(int y = 0; y < 10; y++){
                guest_list[i].birthday[y] = '\0';
            }
            for(int y = 0; y < 15; y++){
                guest_list[i].phone[y] = '\0';
            }
            for(int y = 0; y < MAX_LEN; y++){
                guest_list[i].address[y] = '\0';
            }
            for(int y = 0; y < MAX_LEN; y++){
                guest_list[i].email[y] = '\0';
            }              
            for(int y = 0; y < 10; y++){
                guest_list[i].reservation_date[y] = '\0';
            }
            for(int y = 0; y < 5; y++){
                guest_list[i].reservation_time[y] = '\0';
            }

            guest_list[i].num_guests = '\0';

            for(int y = 0; y < 5; y++){
                guest_list[i].table_number[y] = '\0';
            }
            for(int y = 0; y < 5; y++){
                guest_list[i].arrival[y] = '\0';
            }
            for(int y = 0; y < 5; y++){
                guest_list[i].departure[y] = '\0';
            }
            break;
        }
        i++;
    }
}

void guest_arrival(guest* guest_list, int num_guests, char* table_number, char* time){
    for(int i = 0; i < num_guests; i++) {
        if(strcmp(table_number, guest_list[i].table_number) == 0){
            for(int y = 0; y < 6; y++){
                guest_list[i].arrival[y] = time[y];
            }
        }
    }
}

void guest_departure(guest* guest_list, int num_guests, char* table_number, char* time){
    for(int i = 0; i < num_guests; i++) {
        if(strcmp(table_number, guest_list[i].table_number) == 0){
            for(int y = 0; y < 6; y++){
                guest_list[i].departure[y] = time[y];
            }
        }
    }
}
