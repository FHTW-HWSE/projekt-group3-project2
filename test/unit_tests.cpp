#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <cstring>
#include <cstdio>
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

TEST_CASE("Write user data to CSV1")
{
    SECTION("Write new guest reservation")
    {
        // Create a new guest with reservation data
        guest new_guest;
        strcpy(new_guest.name, "John");
        strcpy(new_guest.surname, "Doe");
        strcpy(new_guest.birthday, "12.12.2000");
        strcpy(new_guest.phone, "123456789");
        strcpy(new_guest.address, "123 Main St");
        strcpy(new_guest.email, "john.doe@example.com");
        strcpy(new_guest.reservation_date, "03.07.2023");
        strcpy(new_guest.reservation_time, "18:00");
        new_guest.num_guests = 4;
        strcpy(new_guest.table_number, "11");
        strcpy(new_guest.arrival, "18:00");
        strcpy(new_guest.departure, "20:00");

        // Redirect stdout to a stringstream to capture the output
        std::stringstream output;
        std::streambuf *oldCoutBuf = std::cout.rdbuf(output.rdbuf());

        write_user_data_to_csv(new_guest);

        // Restore stdout
        std::cout.rdbuf(oldCoutBuf);

        // Check the captured output
        std::string expectedOutput = "Your data has been saved\n";
        REQUIRE(output.str() == expectedOutput);

        // Read the saved reservation from the file
        guest guest_list[1];
        read_reservations(guest_list, 1);

        // Check if the saved reservation matches the original reservation
        REQUIRE(strcmp(guest_list[0].name, "John") == 0);
        REQUIRE(strcmp(guest_list[0].surname, "Doe") == 0);
        REQUIRE(strcmp(guest_list[0].birthday, "12.12.2000") == 0);
        REQUIRE(strcmp(guest_list[0].phone, "123456789") == 0);
        REQUIRE(strcmp(guest_list[0].address, "123 Main St") == 0);
        REQUIRE(strcmp(guest_list[0].email, "john.doe@example.com") == 0);
        REQUIRE(strcmp(guest_list[0].reservation_date, "03.07.2023") == 0);
        REQUIRE(strcmp(guest_list[0].reservation_time, "18:00") == 0);
        REQUIRE(guest_list[0].num_guests == 4);
        REQUIRE(strcmp(guest_list[0].table_number, "11") == 0);
        REQUIRE(strcmp(guest_list[0].arrival, "18:00") == 0);
        REQUIRE(strcmp(guest_list[0].departure, "20:00") == 0);
    }
}

TEST_CASE("Read and write reservations1")
{
    SECTION("Write and read guest reservations")
    {
        // Create an array of guest reservations
        guest guest_list[2];
        strcpy(guest_list[0].name, "John");
        strcpy(guest_list[0].surname, "Doe");
        strcpy(guest_list[0].birthday, "12.12.2000");
        strcpy(guest_list[0].phone, "123456789");
        strcpy(guest_list[0].address, "123 Main St");
        strcpy(guest_list[0].email, "john.doe@example.com");
        strcpy(guest_list[0].reservation_date, "03.07.2023");
        strcpy(guest_list[0].reservation_time, "18:00");
        guest_list[0].num_guests = 4;
        strcpy(guest_list[0].table_number, "11");
        strcpy(guest_list[0].arrival, "18:00");
        strcpy(guest_list[0].departure, "20:00");

        strcpy(guest_list[1].name, "Jane");
        strcpy(guest_list[1].surname, "Smith");
        strcpy(guest_list[1].birthday, "11.11.1999");
        strcpy(guest_list[1].phone, "987654321");
        strcpy(guest_list[1].address, "456 Oak St");
        strcpy(guest_list[1].email, "jane.smith@example.com");
        strcpy(guest_list[1].reservation_date, "03.07.2023");
        strcpy(guest_list[1].reservation_time, "19:00");
        guest_list[1].num_guests = 2;
        strcpy(guest_list[1].table_number, "12");
        strcpy(guest_list[1].arrival, "19:00");
        strcpy(guest_list[1].departure, "20:00");

        // Write the guest reservations to the file
        write_reservations(guest_list, 2);

        // Read the guest reservations from the file
        guest read_guest_list[2];
        read_reservations(read_guest_list, 2);

        // Check if the read guest reservations match the original guest reservations
        REQUIRE(strcmp(read_guest_list[0].name, "John") == 0);
        REQUIRE(strcmp(read_guest_list[0].surname, "Doe") == 0);
        REQUIRE(strcmp(read_guest_list[0].birthday, "12.12.2000") == 0);
        REQUIRE(strcmp(read_guest_list[0].phone, "123456789") == 0);
        REQUIRE(strcmp(read_guest_list[0].address, "123 Main St") == 0);
        REQUIRE(strcmp(read_guest_list[0].email, "john.doe@example.com") == 0);
        REQUIRE(strcmp(read_guest_list[0].reservation_date, "03.07.2023") == 0);
        REQUIRE(strcmp(read_guest_list[0].reservation_time, "18:00") == 0);
        REQUIRE(read_guest_list[0].num_guests == 4);
        REQUIRE(strcmp(read_guest_list[0].table_number, "11") == 0);
        REQUIRE(strcmp(read_guest_list[0].arrival, "18:00") == 0);
        REQUIRE(strcmp(read_guest_list[0].departure, "20:00") == 0);

        REQUIRE(strcmp(read_guest_list[1].name, "Jane") == 0);
        REQUIRE(strcmp(read_guest_list[1].surname, "Smith") == 0);
        REQUIRE(strcmp(read_guest_list[1].birthday, "11.11.1999") == 0);
        REQUIRE(strcmp(read_guest_list[1].phone, "987654321") == 0);
        REQUIRE(strcmp(read_guest_list[1].address, "456 Oak St") == 0);
        REQUIRE(strcmp(read_guest_list[1].email, "jane.smith@example.com") == 0);
        REQUIRE(strcmp(read_guest_list[1].reservation_date, "03.07.2023") == 0);
        REQUIRE(strcmp(read_guest_list[1].reservation_time, "19:00") == 0);
        REQUIRE(read_guest_list[1].num_guests == 2);
        REQUIRE(strcmp(read_guest_list[1].table_number, "12") == 0);
        REQUIRE(strcmp(read_guest_list[1].arrival, "19:00") == 0);
        REQUIRE(strcmp(read_guest_list[1].departure, "20:00") == 0);
    }
}

TEST_CASE("Print current reservations1")
{
    // Create a sample guest list
    guest guest_list[3];
    guest_list[0] = guest{"John", "Doe", "12.12.2000", "123456789", "123 Main St", "john.doe@example.com", "03.07.2023", "18:00", 4, "11", "18:00", "20:00"};
    guest_list[1] = guest{"Jane", "Smith", "11.11.1999", "987654321", "456 Oak St", "jane.smith@example.com", "03.07.2023", "19:00", 2, "12", "19:00", "20:00"};
    guest_list[2] = guest{"John", "Doe", "12.12.2000", "123456789", "123 Main St", "john.doe@example.com", "03.07.2023", "18:00", 4, "11", "18:00", "20:00"};

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
            "John                          Doe                            18:00        11          4\n"
            "Jane                          Smith                          19:00        12          2\n";
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

TEST_CASE("Delete reservation1")
{
    // Create a sample guest list
    guest guest_list[3];
    guest_list[0] = guest{"John", "Doe", "12.12.2000", "123456789", "123 Main St", "john.doe@example.com", "03.07.2023", "18:00", 4, "11", "18:00", "20:00"};
    guest_list[1] = guest{"Jane", "Smith", "11.11.1999", "987654321", "456 Oak St", "jane.smith@example.com", "03.07.2023", "19:00", 2, "12", "19:00", "20:00"};
    guest_list[2] = guest{"John", "Doe", "12.12.2000", "123456789", "123 Main St", "john.doe@example.com", "03.07.2023", "18:00", 4, "11", "18:00", "20:00"};

    SECTION("Delete an existing reservation")
    {
        delete_reservation(guest_list, 3, "12");

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
        delete_reservation(guest_list, 3, "22");

        // Check if the guest list remains unchanged
        REQUIRE(std::strcmp(guest_list[0].name, "John") == 0);
        REQUIRE(std::strcmp(guest_list[1].name, "Jane") == 0);
        REQUIRE(std::strcmp(guest_list[2].name, "Bob") == 0);
    }
}

TEST_CASE("Guest arrival1")
{
    // Create a sample guest list
    guest guest_list[3];
    guest_list[0] = guest{"John", "Doe", "12.12.2000", "123456789", "123 Main St", "john.doe@example.com", "03.07.2023", "18:00", 4, "11", "18:00", "20:00"};
    guest_list[1] = guest{"Jane", "Smith", "11.11.1999", "987654321", "456 Oak St", "jane.smith@example.com", "03.07.2023", "19:00", 2, "12", "19:00", "20:00"};
    guest_list[2] = guest{"John", "Doe", "12.12.2000", "123456789", "123 Main St", "john.doe@example.com", "03.07.2023", "18:00", 4, "11", "18:00", "20:00"};

    SECTION("Guest arrives at an existing reservation")
    {
        guest_arrival(guest_list, 3, "12", "12:30");

        // Check if the arrival time is updated
        REQUIRE(std::strcmp(guest_list[1].arrival, "12:30") == 0);
    }

    SECTION("Guest arrives at a non-existing reservation")
    {
        guest_arrival(guest_list, 3, "22", "12:30");

        // Check if the guest list remains unchanged
        REQUIRE(std::strcmp(guest_list[0].arrival, "") == 0);
        REQUIRE(std::strcmp(guest_list[1].arrival, "") == 0);
        REQUIRE(std::strcmp(guest_list[2].arrival, "") == 0);
    }
}

TEST_CASE("Guest departure1")
{
    // Create a sample guest list
    guest guest_list[3];
    guest_list[0] = guest{"John", "Doe", "12.12.2000", "123456789", "123 Main St", "john.doe@example.com", "03.07.2023", "18:00", 4, "11", "18:00", "20:00"};
    guest_list[1] = guest{"Jane", "Smith", "11.11.1999", "987654321", "456 Oak St", "jane.smith@example.com", "03.07.2023", "19:00", 2, "12", "19:00", "20:00"};
    guest_list[2] = guest{"John", "Doe", "12.12.2000", "123456789", "123 Main St", "john.doe@example.com", "03.07.2023", "18:00", 4, "11", "18:00", "20:00"};

    SECTION("Guest departs from an existing reservation")
    {
        guest_departure(guest_list, 3, "12", "14:30");

        // Check if the departure time is updated
        REQUIRE(std::strcmp(guest_list[1].departure, "14:30") == 0);
    }

    SECTION("Guest departs from a non-existing reservation")
    {
        guest_departure(guest_list, 3, "22", "14:30");

        // Check if the guest list remains unchanged
        REQUIRE(std::strcmp(guest_list[0].departure, "") == 0);
        REQUIRE(std::strcmp(guest_list[1].departure, "") == 0);
        REQUIRE(std::strcmp(guest_list[2].departure, "") == 0);
    }
}
