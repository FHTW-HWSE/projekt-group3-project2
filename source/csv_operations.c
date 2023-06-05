#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "guest.h"
#include "csv_operations.h"

void read_reservations(guest* guest_list, int num_guests) {
    // Open the CSV file for reading
    FILE* fp = fopen("test.csv", "r");

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
        // Remove newline characters
        strtok(line, "\n");
        strtok(line, "\r");

        int fields_read = sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%s",
            guest_list[i].name, guest_list[i].surname, guest_list[i].birthday, guest_list[i].phone,
            guest_list[i].address, guest_list[i].email, guest_list[i].reservation_date,
            guest_list[i].reservation_time, &guest_list[i].num_guests, guest_list[i].arrival, guest_list[i].departure);

            printf("%s,%s,%s,%s,%s,%s,%s,%s,%d,%s,%s\n",
            guest_list[i].name, guest_list[i].surname, guest_list[i].birthday, guest_list[i].phone,
            guest_list[i].address, guest_list[i].email, guest_list[i].reservation_date,
            guest_list[i].reservation_time, guest_list[i].num_guests, guest_list[i].arrival, guest_list[i].departure);

        if (fields_read != 11) {
            continue; // Skip this line if it doesn't have the correct number of fields
        }

        i++;
    }

    // Close the file
    fclose(fp);
}

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

    // Print reservations for the current date
    for (int i = 0; i < num_guests; i++) {
        if (strcmp(guest_list[i].reservation_date, current_date) == 0) {
            printf("%-30s %-30s Date: %-12s Time: %-8s Guests: %d\n", guest_list[i].name, guest_list[i].surname, guest_list[i].reservation_date, guest_list[i].reservation_time, guest_list[i].num_guests);
        }
    }
}

void write_user_data_to_csv(guest new_guest) { //new reservation
    // Open the CSV file for writing
    FILE *fp = fopen("test.csv", "a");

    // Write the header row if the file is empty
    if (ftell(fp) == 0) {
        fprintf(fp, "Name,Surname,Birthday,Phone,Address,Email,Reservation_Date,Reservation_Time,Num_Guests,Arrival,Departure\n");
    }

    // Write the new guest reservation to the file
    fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s,%d,%s,%s\n", new_guest.name, 
    new_guest.surname, new_guest.birthday, new_guest.phone, new_guest.address, new_guest.email, 
    new_guest.reservation_date, new_guest.reservation_time, new_guest.num_guests, new_guest.arrival, new_guest.departure);

    // Close the file
    fclose(fp);

    printf("Your data has been saved to data.csv\n");
}

void delete_reservation();

void guest_arrival();

void guest_departure();