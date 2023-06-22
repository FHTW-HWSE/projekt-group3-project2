#include <assert.h>
#include <stdbool.h>
#include <ctype.h>

// Function prototypes
void test_print_current_reservations();
void test_delete_reservation();
void test_guest_arrival();
void test_guest_departure();

// Unit test for print_current_reservations
void test_print_current_reservations() {
    // Create sample guest list
    guest guest_list[] = {
        { "John", "Doe", "22.06.2023", "18:30", "001", 4 },
        { "Jane", "Smith", "22.06.2023", "19:00", "002", 2 },
        { "Bob", "Johnson", "23.06.2023", "12:00", "003", 3 },
        { "Alice", "Williams", "22.06.2023", "20:00", "004", 6 }
    };
    int num_guests = 4;

    // Call the function
    print_current_reservations(guest_list, num_guests);

    // No assertion needed as it's a print function
}

// Unit test for delete_reservation
void test_delete_reservation() {
    // Create sample guest list
    guest guest_list[] = {
        { "John", "Doe", "22.06.2023", "18:30", "001", 4 },
        { "Jane", "Smith", "22.06.2023", "19:00", "002", 2 },
        { "Bob", "Johnson", "23.06.2023", "12:00", "003", 3 },
        { "Alice", "Williams", "22.06.2023", "20:00", "004", 6 }
    };
    int num_guests = 4;

    // Delete a reservation
    delete_reservation(guest_list, num_guests, "002");

    // Check if the reservation is deleted
    bool reservation_deleted = true;
    for (int i = 0; i < num_guests; i++) {
        if (strcmp(guest_list[i].table_number, "002") == 0) {
            reservation_deleted = false;
            break;
        }
    }

    // Assertion: The reservation with table number "002" should be deleted
    assert(reservation_deleted);
}

// Unit test for guest_arrival
void test_guest_arrival() {
    // Create sample guest list
    guest guest_list[] = {
        { "John", "Doe", "22.06.2023", "18:30", "001", 4 },
        { "Jane", "Smith", "22.06.2023", "19:00", "002", 2 },
        { "Bob", "Johnson", "23.06.2023", "12:00", "003", 3 },
        { "Alice", "Williams", "22.06.2023", "20:00", "004", 6 }
    };
    int num_guests = 4;

    // Update guest arrival time
    guest_arrival(guest_list, num_guests, "003", "12:15");

    // Find the guest with table number "003"
    bool arrival_updated = false;
    for (int i = 0; i < num_guests; i++) {
        if (strcmp(guest_list[i].table_number, "003") == 0) {
            // Assertion: Arrival time should be updated to "12:15"
            assert(strcmp(guest_list[i].arrival, "12:15") == 0);
            arrival_updated = true;
            break;
        }
    }

    // Assertion: The guest arrival time should be updated
    assert(arrival_updated);
}

// Unit test for guest_departure
void test_guest_departure() {
    // Create sample guest list
    guest guest_list[] = {
        { "John", "Doe", "22.06.2023", "18:30", "001", 4 },
        { "Jane", "Smith", "22.06.2023", "19:00", "002", 2 },
        { "Bob", "Johnson", "23.06.2023", "12:00", "003", 3 },
        { "Alice", "Williams", "22.06.2023", "20:00", "004", 6 }
    };
    int num_guests = 4;

    // Update guest departure time
    guest_departure(guest_list, num_guests, "004", "21:30");

    // Find the guest with table number "004"
    bool departure_updated = false;
    for (int i = 0; i < num_guests; i++) {
        if (strcmp(guest_list[i].table_number, "004") == 0) {
            // Assertion: Departure time should be updated to "21:30"
            assert(strcmp(guest_list[i].departure, "21:30") == 0);
            departure_updated = true;
            break;
        }
    }

    // Assertion: The guest departure time should be updated
    assert(departure_updated);
}

int main() {
    // Run unit tests
    test_print_current_reservations();
    test_delete_reservation();
    test_guest_arrival();
    test_guest_departure();

    printf("All tests passed!\n");

    return 0;
}
