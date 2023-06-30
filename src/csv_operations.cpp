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


void write_user_data_to_csv(guest new_guest) { //new reservation
    // Open the CSV file for reading
    FILE* fp = fopen("reservation.csv", "a");

    // Check if the file exists
    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    // Write the header row if the file is empty
    if (ftell(fp) == 0) {
        fprintf(fp, "Name,Surname,Birthday,Phone,Address,Email,Reservation_Date,Reservation_Time,Num_Guests,Table_Number,Arrival,Departure\n");
    }

    // Write the new guest reservation to the file
    fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s,%d,%s,%s,%s\n", new_guest.name, 
    new_guest.surname, new_guest.birthday, new_guest.phone, new_guest.address, new_guest.email, 
    new_guest.reservation_date, new_guest.reservation_time, new_guest.num_guests,new_guest.table_number, new_guest.arrival, new_guest.departure);

    // Close the file
    fclose(fp);

    printf("Your data has been saved\n");
}

void read_reservations(guest* guest_list, int num_guests) {
    // Open the CSV file for reading
    FILE* fp = fopen("reservation.csv", "r");

    // Check if the file exists
    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    // Read the header row
    char header[MAX_LEN];
    fgets(header, MAX_LEN, fp);

    // Read each guest reservation and store it in the guest_list array
    int i = 0;
    char line[MAX_LEN];
    while (i < num_guests && fgets(line, MAX_LEN, fp) != NULL) {
        strtok(line, "\n");
        strtok(line, "\r");

        int fields_read = sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%s",
            guest_list[i].name, guest_list[i].surname, guest_list[i].birthday, guest_list[i].phone,
            guest_list[i].address, guest_list[i].email, guest_list[i].reservation_date,
            guest_list[i].reservation_time, &guest_list[i].num_guests, guest_list[i].table_number, guest_list[i].arrival, guest_list[i].departure);

        if (fields_read != 12) {
            continue; // Skip this line if it doesn't have the correct number of fields
        }
        i++;
    }

    // Close the file
    fclose(fp);
}

void write_reservations(guest* guest_list, int num_guests) {
    // Open the CSV file for reading
    FILE* fp = fopen("reservation.csv", "w");

    // Check if the file exists
    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    fprintf(fp, "Name,Surname,Birthday,Phone,Address,Email,Reservation_Date,Reservation_Time,Num_Guests,Table_Number,Arrival,Departure\n");
    for(int i = 0; i < num_guests; i++){
        if(strcmp(guest_list[i].name,"") == 0){
            continue;
        } else {
            // Write the new guest reservation to the file
            fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s,%d,%s,%s,%s\n", guest_list[i].name, guest_list[i].surname, 
                guest_list[i].birthday, guest_list[i].phone, guest_list[i].address, guest_list[i].email, guest_list[i].reservation_date, 
                guest_list[i].reservation_time, guest_list[i].num_guests, guest_list[i].table_number, guest_list[i].arrival, guest_list[i].departure);
        }
    }
    fclose(fp);
}
