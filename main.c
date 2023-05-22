#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "guest.h"
#include "write_user_data_to_csv.h"
#include "print_current_reservations.h"
#include "read_reservations.h"

int main(void) {
    int num_guests = 100;

    // Allocate memory for the guest_list array
    guest* guest_list = calloc(num_guests, sizeof(guest));

    char user_input;
    printf("user menu: n = new reservation, c = check current reservations, a = guests have arrived, l = guests have left\nYour input: ");
    scanf("%c", &user_input);

    // Initialize a new guest variable
    guest new_guest;

    switch (user_input) {
        case 'n':
            // Code for getting new reservation details and writing to the CSV file
            break;

        case 'c':
            // Read the guest reservations from the file
            read_reservations(guest_list, num_guests);

            // Print the current reservations
            print_current_reservations(guest_list, num_guests);

            // Free the memory allocated for the guest_list array
            free(guest_list);
            break;

        case 'a':
            // Code for handling guests arrival
            break;

        case 'l':
            // Code for handling guests departure
            break;

        default:
            printf("No such input allowed\n");
            break;
    }

    return 0;
}
