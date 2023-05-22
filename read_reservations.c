#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "guest.h"
#include "read_reservations.h"

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

        if (fields_read != 11) {
            continue; // Skip this line if it doesn't have the correct number of fields
        }

        i++;
    }

    // Close the file
    fclose(fp);
}