// #define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include <catch.hpp>
#include <cstring>
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
#include "board_operations.h"

TEST_CASE("Print current reservations2", "[current_reservations]")
{
    // Create a sample guest list
    guest *guest_list = static_cast<guest *>(calloc(3, sizeof(guest)));
    guest_list[0] = guest{"Lazar", "Clark", "12.02.1985", "15551234567", "123 Main Street", "lazar.clark@example.com", "24.06.2023", "14:45", 3, "11", "14:45", "15:45"};
    guest_list[1] = guest{"Boris", "Smith", "21.07.1976", "15551234568", "456 Elm Street", "boris.smith@example.com", "28.06.2023", "08:45", 4, "12", "08:45", "9:30"};
    guest_list[2] = guest{"Christian", "Muster", "12.10.1996", "6754938246", "Wexstrasse 45", "christimuster@gmail.com", "03.07.2023", "18:45", 4, "23", "18:45", "19:30"};

    SECTION("Reservations on the current date")
    {
        // Redirect stdout to a stringstream to capture the output
        std::stringstream output;
        std::streambuf *oldCoutBuf = std::cout.rdbuf(output.rdbuf());

        print_current_reservations(guest_list, 3);

        // Restore stdout
        std::cout.rdbuf(oldCoutBuf);

        // Check the captured output
        std::string expectedOutput =
            "Name:                          Surname:                       Time:        Table:       Guests:\n"
            "John                          Doe                            12:00        11          4\n"
            "Jane                          Smith                          13:00        23          2\n";
        REQUIRE(output.str() == expectedOutput);
    }

    SECTION("No reservations on the current date")
    {
        // Redirect stdout to a stringstream to capture the output
        std::stringstream output;
        std::streambuf *oldCoutBuf = std::cout.rdbuf(output.rdbuf());

        print_current_reservations(guest_list, 3);

        // Restore stdout
        std::cout.rdbuf(oldCoutBuf);

        // Check the captured output
        std::string expectedOutput =
            "Name:                          Surname:                       Time:        Table:       Guests:\n";
        REQUIRE(output.str() == expectedOutput);
    }
}

TEST_CASE("Delete reservation2")
{
    // Create a sample guest list
    guest *guest_list = static_cast<guest *>(calloc(3, sizeof(guest)));
    guest_list[0] = guest{"Lazar", "Clark", "12.02.1985", "15551234567", "123 Main Street", "lazar.clark@example.com", "24.06.2023", "14:45", 3, "11", "14:45", "15:45"};
    guest_list[1] = guest{"Boris", "Smith", "21.07.76", "15551234568", "456 Elm Street", "boris.smith@example.com", "28.06.2023", "08:45", 4, "12", "08:45", "9:30"};
    guest_list[2] = guest{"Mihajlo", "Erickson", "09.11.88", "15551234570", "321 Maple Drive", "mihajlo.erickson@example.com", "03.07.2023", "18:45", 2, "13", "18:30", "20:00"};
    guest_list[2] = guest{"Christian", "Muster", "12.10.96", "6754938246", "Wexstrasse 45", "christimuster@gmail.com", "03.07.2023", "18:45", 4, "23", "18:45", "19:30"};

    char table_number[] = "23";
    char temp_time[] = "18:45";
    SECTION("Delete an existing reservation")
    {
        delete_reservation(guest_list, 3, table_number);

        // Check if the reservation is deleted
        REQUIRE(guest_list[1].name[0] == '\0');
        REQUIRE(guest_list[1].surname[0] == '\0');
        REQUIRE(guest_list[1].reservation_date[0] == '\0');
        REQUIRE(guest_list[1].reservation_time[0] == '\0');
        REQUIRE(guest_list[1].table_number[0] == '\0');
        REQUIRE(guest_list[1].num_guests == '\0');
    }

    SECTION("Delete a non-existing reservation")
    {
        delete_reservation(guest_list, 3, table_number);

        // Check if the guest list remains unchanged
        REQUIRE(std::strcmp(guest_list[0].name, "John") == 0);
        REQUIRE(std::strcmp(guest_list[1].name, "Jane") == 0);
        REQUIRE(std::strcmp(guest_list[2].name, "Bob") == 0);
    }
}

TEST_CASE("Guest arrival2")
{
    // Create a sample guest list
    guest *guest_list = static_cast<guest *>(calloc(3, sizeof(guest)));
    guest_list[0] = guest{"Lazar", "Clark", "12.02.1985", "15551234567", "123 Main Street", "lazar.clark@example.com", "24.06.2023", "14:45", 3, "11", "14:45", "15:45"};
    guest_list[1] = guest{"Boris", "Smith", "21.07.76", "15551234568", "456 Elm Street", "boris.smith@example.com", "28.06.2023", "08:45", 4, "12", "08:45", "9:30"};
    guest_list[2] = guest{"Mihajlo", "Erickson", "09.11.88", "15551234570", "321 Maple Drive", "mihajlo.erickson@example.com", "03.07.2023", "18:45", 2, "13", "18:30", "20:00"};
    guest_list[2] = guest{"Christian", "Muster", "12.10.96", "6754938246", "Wexstrasse 45", "christimuster@gmail.com", "03.07.2023", "18:45", 4, "23", "18:45", "19:30"};

    char table_number[] = "23";
    char temp_time[] = "18:45";

    SECTION("Guest arrives at an existing reservation")
    {
        guest_arrival(guest_list, 3, table_number, temp_time);

        // Check if the arrival time is updated
        REQUIRE(std::strcmp(guest_list[1].arrival, temp_time) == 0);
    }

    SECTION("Guest arrives at a non-existing reservation")
    {
        guest_arrival(guest_list, 3, table_number, temp_time);

        // Check if the guest list remains unchanged
        REQUIRE(std::strcmp(guest_list[0].arrival, "") == 0);
        REQUIRE(std::strcmp(guest_list[1].arrival, "") == 0);
        REQUIRE(std::strcmp(guest_list[2].arrival, "") == 0);
    }
}

TEST_CASE("Guest departure2")
{
    // Create a sample guest list
    guest *guest_list = static_cast<guest *>(calloc(3, sizeof(guest)));
    guest_list[0] = guest{"Lazar", "Clark", "12.02.1985", "15551234567", "123 Main Street", "lazar.clark@example.com", "24.06.2023", "14:45", 3, "11", "14:45", "15:45"};
    guest_list[1] = guest{"Boris", "Smith", "21.07.76", "15551234568", "456 Elm Street", "boris.smith@example.com", "28.06.2023", "08:45", 4, "12", "08:45", "9:30"};
    guest_list[2] = guest{"Mihajlo", "Erickson", "09.11.88", "15551234570", "321 Maple Drive", "mihajlo.erickson@example.com", "03.07.2023", "18:45", 2, "13", "18:30", "20:00"};
    guest_list[2] = guest{"Christian", "Muster", "12.10.96", "6754938246", "Wexstrasse 45", "christimuster@gmail.com", "03.07.2023", "18:45", 4, "23", "18:45", "19:30"};

    char table_number[] = "23";
    char temp_time[] = "18:45";

    SECTION("Guest departs from an existing reservation")
    {
        guest_departure(guest_list, 3, table_number, temp_time);

        // Check if the departure time is updated
        REQUIRE(std::strcmp(guest_list[1].departure, temp_time) == 0);
    }

    SECTION("Guest departs from a non-existing reservation")
    {
        guest_departure(guest_list, 3, table_number, temp_time);

        // Check if the guest list remains unchanged
        REQUIRE(std::strcmp(guest_list[0].departure, "") == 0);
        REQUIRE(std::strcmp(guest_list[1].departure, "") == 0);
        REQUIRE(std::strcmp(guest_list[2].departure, "") == 0);
    }
}
