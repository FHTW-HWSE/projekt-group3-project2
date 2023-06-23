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
#include "reservation.h"

void reservation(){
    int num_guests = 7;

    const char case_arrival = 'a';
    const char case_departure = 'l';
    const char case_todays_reservations = 'c';
    const char case_new_guest = 'n';
    const char case_delete_reservation = 'd';
    const char case_go_back = 'b';


    // Allocate memory for the guest_list array
    guest* guest_list = calloc(num_guests, sizeof(guest));

    char user_input;
    printf("user menu:\na = guests have arrived\nl = guests have left\nc = todays reservations\nn = new reservation\nd = delete reservation\nb = back\nYour input: ");
    
    scanf("%c", &user_input);

    // Initialize a new guest variable
    switch (user_input) {
        guest new_guest;
        guest cancled_reservation;
        char temp_table[5];
        char temp_time[6];

        case case_new_guest:
            printf("Please enter name: ");
            scanf("%s", new_guest.name);

            printf("Please enter surname: ");
            scanf("%s", new_guest.surname);

            printf("Please enter birthday (format dd.mm.yyyy): ");
            scanf("%10s", new_guest.birthday);

            while (!validateDate(new_guest.birthday)) {
                printf("Invalid birthday format. Please enter again (format dd.mm.yyyy): ");
                scanf("%10s", new_guest.birthday);
            }

            printf("Please enter phone number (max 11 digits, only numbers): ");
            scanf("%11s", new_guest.phone);

            while (!validatePhoneNumber(new_guest.phone)) {
                printf("Invalid phone number format. Please enter again (max 11 digits, only numbers): ");
                scanf("%11s", new_guest.phone);
            }

            printf("Please enter address: ");
            scanf(" %[^\n]%*c", new_guest.address);

            printf("Please enter email: ");
            scanf("%s", new_guest.email);

            printf("Please enter reservation date (format dd.mm.yyyy): ");
            scanf("%10s", new_guest.reservation_date);

            while (!validateDate(new_guest.reservation_date)) {
                printf("Invalid reservation date format. Please enter again (format dd.mm.yyyy): ");
                scanf("%10s", new_guest.reservation_date);
            }

            printf("Please enter reservation time: ");
            scanf("%5s", new_guest.reservation_time);

            while (!validateTime(new_guest.reservation_time)) {
                printf("Invalid reservation time format. Please enter again (format hh:mm): ");
                scanf("%5s", new_guest.reservation_time);
            }

            printf("Please enter the number of guests (max 4): ");

            scanf("%d", &new_guest.num_guests);

            while (new_guest.num_guests > 4)
            {
                printf("Invalid number of guests. Please enter again (max.4): ");
                scanf("%d", &new_guest.num_guests);
            }

            printf("Please enter table number: ");
            scanf("%5s", new_guest.table_number);

            // Code for getting new reservation details and writing to the CSV file
            write_user_data_to_csv(new_guest);
            break;

        case case_todays_reservations:
            // Read the guest reservations from the file
            read_reservations(guest_list, num_guests);

            // Print the current reservations
            print_current_reservations(guest_list, num_guests);

            // Free the memory allocated for the guest_list array
            free(guest_list);
            break;

        case case_delete_reservation:
            printf("Please enter table number: ");
            scanf("%s", cancled_reservation.table_number);

            read_reservations(guest_list, num_guests);
            delete_reservation(guest_list, num_guests, cancled_reservation.table_number);
            write_reservations(guest_list, num_guests);
            break;

        case case_arrival:
            printf("Please enter table number: ");
            scanf("%s", temp_table);

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

        case case_departure:
            printf("Please enter table number: ");
            scanf("%s", temp_table);

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

        case case_go_back:
            break;

        default:
            printf("No such input allowed\n");
            break;
    }
}