#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "guest.h"
#include "print_current_reservations.h"

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
