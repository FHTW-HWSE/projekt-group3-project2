#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "guest.h"
#include "write_user_data_to_csv.h"

void write_user_data_to_csv(guest new_guest) {
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