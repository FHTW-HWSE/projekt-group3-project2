#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cstring>
#include "guest.h"

TEST_CASE("Print current reservations") {
    // Create a sample guest list
    guest guest_list[3];
    guest_list[0] = { "John", "Doe", "01.07.2023", "12:00", "A01", 4 };
    guest_list[1] = { "Jane", "Smith", "01.07.2023", "13:00", "B02", 2 };
    guest_list[2] = { "Bob", "Johnson", "02.07.2023", "14:00", "C03", 3 };

    SECTION("Reservations on the current date") {
        // Redirect stdout to a stringstream to capture the output
        std::stringstream output;
        std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());

        print_current_reservations(guest_list, 3);

        // Restore stdout
        std::cout.rdbuf(oldCoutBuf);

        // Check the captured output
        std::string expectedOutput =
            "Name:                          Surname:                       Time:        Table:       Guests:\n"
            "John                          Doe                            12:00        A01          4\n"
            "Jane                          Smith                          13:00        B02          2\n";
        REQUIRE(output.str() == expectedOutput);
    }

    SECTION("No reservations on the current date") {
        // Redirect stdout to a stringstream to capture the output
        std::stringstream output;
        std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());

        print_current_reservations(guest_list, 3);

        // Restore stdout
        std::cout.rdbuf(oldCoutBuf);

        // Check the captured output
        std::string expectedOutput =
            "Name:                          Surname:                       Time:        Table:       Guests:\n";
        REQUIRE(output.str() == expectedOutput);
    }
}

TEST_CASE("Delete reservation") {
    // Create a sample guest list
    guest guest_list[3];
    guest_list[0] = { "John", "Doe", "01.07.2023", "12:00", "A01", 4 };
    guest_list[1] = { "Jane", "Smith", "01.07.2023", "13:00", "B02", 2 };
    guest_list[2] = { "Bob", "Johnson", "02.07.2023", "14:00", "C03", 3 };

    SECTION("Delete an existing reservation") {
        delete_reservation(guest_list, 3, "B02");

        // Check if the reservation is deleted
        REQUIRE(guest_list[1].name[0] == '\0');
        REQUIRE(guest_list[1].surname[0] == '\0');
        REQUIRE(guest_list[1].reservation_date[0] == '\0');
        REQUIRE(guest_list[1].reservation_time[0] == '\0');
        REQUIRE(guest_list[1].table_number[0] == '\0');
        REQUIRE(guest_list[1].num_guests == '\0');
    }

    SECTION("Delete a non-existing reservation") {
        delete_reservation(guest_list, 3, "D04");

        // Check if the guest list remains unchanged
        REQUIRE(std::strcmp(guest_list[0].name, "John") == 0);
        REQUIRE(std::strcmp(guest_list[1].name, "Jane") == 0);
        REQUIRE(std::strcmp(guest_list[2].name, "Bob") == 0);
    }
}

TEST_CASE("Guest arrival") {
    // Create a sample guest list
    guest guest_list[3];
    guest_list[0] = { "John", "Doe", "01.07.2023", "12:00", "A01", 4 };
    guest_list[1] = { "Jane", "Smith", "01.07.2023", "13:00", "B02", 2 };
    guest_list[2] = { "Bob", "Johnson", "02.07.2023", "14:00", "C03", 3 };

    SECTION("Guest arrives at an existing reservation") {
        guest_arrival(guest_list, 3, "B02", "12:30");

        // Check if the arrival time is updated
        REQUIRE(std::strcmp(guest_list[1].arrival, "12:30") == 0);
    }

    SECTION("Guest arrives at a non-existing reservation") {
        guest_arrival(guest_list, 3, "D04", "12:30");

        // Check if the guest list remains unchanged
        REQUIRE(std::strcmp(guest_list[0].arrival, "") == 0);
        REQUIRE(std::strcmp(guest_list[1].arrival, "") == 0);
        REQUIRE(std::strcmp(guest_list[2].arrival, "") == 0);
    }
}

TEST_CASE("Guest departure") {
    // Create a sample guest list
    guest guest_list[3];
    guest_list[0] = { "John", "Doe", "01.07.2023", "12:00", "A01", 4 };
    guest_list[1] = { "Jane", "Smith", "01.07.2023", "13:00", "B02", 2 };
    guest_list[2] = { "Bob", "Johnson", "02.07.2023", "14:00", "C03", 3 };

    SECTION("Guest departs from an existing reservation") {
        guest_departure(guest_list, 3, "B02", "14:30");

        // Check if the departure time is updated
        REQUIRE(std::strcmp(guest_list[1].departure, "14:30") == 0);
    }

    SECTION("Guest departs from a non-existing reservation") {
        guest_departure(guest_list, 3, "D04", "14:30");

        // Check if the guest list remains unchanged
        REQUIRE(std::strcmp(guest_list[0].departure, "") == 0);
        REQUIRE(std::strcmp(guest_list[1].departure, "") == 0);
        REQUIRE(std::strcmp(guest_list[2].departure, "") == 0);
    }
}
