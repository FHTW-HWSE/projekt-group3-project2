#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "guest.h"
#include "csv_operations.h"
#include "changes.h"

int main(void) {
    int num_guests = 6;

    // Allocate memory for the guest_list array
    guest* guest_list = calloc(num_guests, sizeof(guest));

    char user_input;
    printf("user menu:\na = guests have arrived\nl = guests have left\nc = todays reservations\nn = new reservation\nd = delete reservation\nb = back\nYour input: ");
    scanf("%c", &user_input);

    // Initialize a new guest variable
    switch (user_input) {
        guest new_guest;
        guest cancled_reservation;
        char arrival_table[5];
        char arrival_time[5];

        case 'n':
            printf("Please enter name: ");
            scanf("%s", new_guest.name);

            printf("Please enter surname: ");
            scanf("%s", new_guest.surname);

            printf("Please enter birthday (format dd.mm.yyyy): ");
            scanf("%s", new_guest.birthday);

            printf("Please enter phone number (max 11 digits, only numbers): ");
            scanf("%s", new_guest.phone);

            printf("Please enter address: ");
            scanf("%s", new_guest.address);

            printf("Please enter email: ");
            scanf("%s", new_guest.email);

            printf("Please enter reservation date: ");
            scanf("%s", new_guest.reservation_date);

            printf("Please enter reservation time: ");
            scanf("%s", new_guest.reservation_time);

            printf("Please enter the number of guests (max 4): ");
            scanf("%d", &new_guest.num_guests);

            printf("Please enter table number: ");
            scanf("%s", new_guest.table_number);

            printf("Arrival: ");
            scanf("%s", new_guest.arrival);

            printf("Departure: ");
            scanf("%s", new_guest.departure);

            // Code for getting new reservation details and writing to the CSV file
            write_user_data_to_csv(new_guest);
            break;

        case 'c':
            // Read the guest reservations from the file
            read_reservations(guest_list, num_guests);

            // Print the current reservations
            print_current_reservations(guest_list, num_guests);

            // Free the memory allocated for the guest_list array
            free(guest_list);
            break;

        case 'd':
            printf("Please enter table number: ");
            scanf("%s", cancled_reservation.table_number);

            read_reservations(guest_list, num_guests);
            delete_reservation(guest_list, num_guests, cancled_reservation.table_number);
            write_reservations(guest_list, num_guests);
            break;

        case 'a':
            printf("Please enter table number: ");
            scanf("%s", arrival_table);

            printf("Please enter arrival time: ");
            scanf("%s", arrival_time);

            // Code for handling guests arrival
            read_reservations(guest_list, num_guests);
            guest_departure(guest_list, num_guests, arrival_table, arrival_time);
            write_reservations(guest_list, num_guests);
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
