#include <stdio.h>
#include <string.h>
#include "guest.h"
#include "csv_operations.h"

void test_write_user_data_to_csv() {
    // Create a new guest
    guest new_guest;
    strcpy(new_guest.name, "John");
    strcpy(new_guest.surname, "Doe");
    strcpy(new_guest.birthday, "1990-01-01");
    strcpy(new_guest.phone, "123456789");
    strcpy(new_guest.address, "123 Main St");
    strcpy(new_guest.email, "john.doe@example.com");
    strcpy(new_guest.reservation_date, "2023-06-22");
    strcpy(new_guest.reservation_time, "18:00");
    new_guest.num_guests = 4;
    strcpy(new_guest.table_number, "A1");
    strcpy(new_guest.arrival, "2023-06-22");
    strcpy(new_guest.departure, "2023-06-23");

    // Call the function
    test_write_user_data_to_csv(new_guest);
}

void test_read_reservations() {
    // Create an array of guests
    guest guest_list[10];
    int num_guests = 10;

    // Call the function
    test_read_reservations(guest_list, num_guests);

    // Print the guest information
    for (int i = 0; i < num_guests; i++) {
        printf("Guest %d:\n", i + 1);
        printf("Name: %s\n", guest_list[i].name);
        printf("Surname: %s\n", guest_list[i].surname);
        printf("Birthday: %s\n", guest_list[i].birthday);
        printf("Phone: %s\n", guest_list[i].phone);
        printf("Address: %s\n", guest_list[i].address);
        printf("Email: %s\n", guest_list[i].email);
        printf("Reservation Date: %s\n", guest_list[i].reservation_date);
        printf("Reservation Time: %s\n", guest_list[i].reservation_time);
        printf("Num Guests: %d\n", guest_list[i].num_guests);
        printf("Table Number: %s\n", guest_list[i].table_number);
        printf("Arrival: %s\n", guest_list[i].arrival);
        printf("Departure: %s\n", guest_list[i].departure);
        printf("\n");
    }
}

void test_write_reservations() {
    // Create an array of guests
    guest guest_list[10];
    int num_guests = 10;

    // Call the function
    test_write_reservations(guest_list, num_guests);
}

int main() {
    // Run unit tests
    test_write_user_data_to_csv();
    test_read_reservations();
    test_write_reservations();

    return 0;
}
