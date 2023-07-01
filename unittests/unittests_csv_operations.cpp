#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cstdio>
#include <cstring>
#include "guest.h"
#include "csv_operations.h"

TEST_CASE("Write user data to CSV") {
    SECTION("Write new guest reservation") {
        // Create a new guest with reservation data
        guest new_guest;
        strcpy(new_guest.name, "John");
        strcpy(new_guest.surname, "Doe");
        strcpy(new_guest.birthday, "1990-01-01");
        strcpy(new_guest.phone, "123456789");
        strcpy(new_guest.address, "123 Main St");
        strcpy(new_guest.email, "john.doe@example.com");
        strcpy(new_guest.reservation_date, "2023-07-01");
        strcpy(new_guest.reservation_time, "18:00");
        new_guest.num_guests = 4;
        strcpy(new_guest.table_number, "A1");
        strcpy(new_guest.arrival, "2023-07-01");
        strcpy(new_guest.departure, "2023-07-02");

        // Redirect stdout to a stringstream to capture the output
        std::stringstream output;
        std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());

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
        REQUIRE(strcmp(guest_list[0].birthday, "1990-01-01") == 0);
        REQUIRE(strcmp(guest_list[0].phone, "123456789") == 0);
        REQUIRE(strcmp(guest_list[0].address, "123 Main St") == 0);
        REQUIRE(strcmp(guest_list[0].email, "john.doe@example.com") == 0);
        REQUIRE(strcmp(guest_list[0].reservation_date, "2023-07-01") == 0);
        REQUIRE(strcmp(guest_list[0].reservation_time, "18:00") == 0);
        REQUIRE(guest_list[0].num_guests == 4);
        REQUIRE(strcmp(guest_list[0].table_number, "A1") == 0);
        REQUIRE(strcmp(guest_list[0].arrival, "2023-07-01") == 0);
        REQUIRE(strcmp(guest_list[0].departure, "2023-07-02") == 0);
    }
}

TEST_CASE("Read and write reservations") {
    SECTION("Write and read guest reservations") {
        // Create an array of guest reservations
        guest guest_list[2];
        strcpy(guest_list[0].name, "John");
        strcpy(guest_list[0].surname, "Doe");
        strcpy(guest_list[0].birthday, "1990-01-01");
        strcpy(guest_list[0].phone, "123456789");
        strcpy(guest_list[0].address, "123 Main St");
        strcpy(guest_list[0].email, "john.doe@example.com");
        strcpy(guest_list[0].reservation_date, "2023-07-01");
        strcpy(guest_list[0].reservation_time, "18:00");
        guest_list[0].num_guests = 4;
        strcpy(guest_list[0].table_number, "A1");
        strcpy(guest_list[0].arrival, "2023-07-01");
        strcpy(guest_list[0].departure, "2023-07-02");

        strcpy(guest_list[1].name, "Jane");
        strcpy(guest_list[1].surname, "Smith");
        strcpy(guest_list[1].birthday, "1992-05-15");
        strcpy(guest_list[1].phone, "987654321");
        strcpy(guest_list[1].address, "456 Oak St");
        strcpy(guest_list[1].email, "jane.smith@example.com");
        strcpy(guest_list[1].reservation_date, "2023-07-02");
        strcpy(guest_list[1].reservation_time, "19:00");
        guest_list[1].num_guests = 2;
        strcpy(guest_list[1].table_number, "B2");
        strcpy(guest_list[1].arrival, "2023-07-02");
        strcpy(guest_list[1].departure, "2023-07-03");

        // Write the guest reservations to the file
        write_reservations(guest_list, 2);

        // Read the guest reservations from the file
        guest read_guest_list[2];
        read_reservations(read_guest_list, 2);

        // Check if the read guest reservations match the original guest reservations
        REQUIRE(strcmp(read_guest_list[0].name, "John") == 0);
        REQUIRE(strcmp(read_guest_list[0].surname, "Doe") == 0);
        REQUIRE(strcmp(read_guest_list[0].birthday, "1990-01-01") == 0);
        REQUIRE(strcmp(read_guest_list[0].phone, "123456789") == 0);
        REQUIRE(strcmp(read_guest_list[0].address, "123 Main St") == 0);
        REQUIRE(strcmp(read_guest_list[0].email, "john.doe@example.com") == 0);
        REQUIRE(strcmp(read_guest_list[0].reservation_date, "2023-07-01") == 0);
        REQUIRE(strcmp(read_guest_list[0].reservation_time, "18:00") == 0);
        REQUIRE(read_guest_list[0].num_guests == 4);
        REQUIRE(strcmp(read_guest_list[0].table_number, "A1") == 0);
        REQUIRE(strcmp(read_guest_list[0].arrival, "2023-07-01") == 0);
        REQUIRE(strcmp(read_guest_list[0].departure, "2023-07-02") == 0);

        REQUIRE(strcmp(read_guest_list[1].name, "Jane") == 0);
        REQUIRE(strcmp(read_guest_list[1].surname, "Smith") == 0);
        REQUIRE(strcmp(read_guest_list[1].birthday, "1992-05-15") == 0);
        REQUIRE(strcmp(read_guest_list[1].phone, "987654321") == 0);
        REQUIRE(strcmp(read_guest_list[1].address, "456 Oak St") == 0);
        REQUIRE(strcmp(read_guest_list[1].email, "jane.smith@example.com") == 0);
        REQUIRE(strcmp(read_guest_list[1].reservation_date, "2023-07-02") == 0);
        REQUIRE(strcmp(read_guest_list[1].reservation_time, "19:00") == 0);
        REQUIRE(read_guest_list[1].num_guests == 2);
        REQUIRE(strcmp(read_guest_list[1].table_number, "B2") == 0);
        REQUIRE(strcmp(read_guest_list[1].arrival, "2023-07-02") == 0);
        REQUIRE(strcmp(read_guest_list[1].departure, "2023-07-03") == 0);
    }
}
