#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 100

struct guest {
    char name[MAX_LEN];
    char surname[MAX_LEN];
    char birthday[MAX_LEN];
    char phone[MAX_LEN];
    char address[MAX_LEN];
    char email[MAX_LEN];
    char reservation_date[MAX_LEN];
    char reservation_time[MAX_LEN];
    int num_guests;
    int table_number;
    char arrival[MAX_LEN];
    char departure[MAX_LEN];
};

void read_reservations(struct guest* guest_list, int num_guests) {
    // Open the CSV file for reading
    FILE* fp = fopen("test.csv", "r");

    time_t currentTime;
    struct tm *localTime;
    char current_date[100];

    // Get the current time
    currentTime = time(NULL);

    // Convert the current time to the local time
    localTime = localtime(&currentTime);

    // Format the current time as a string
    strftime(current_date, sizeof(current_date), "%d.%m.%Y", localTime);

    // Check if the file exists
    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    // Read the header row
    char header[MAX_LEN];
    fgets(header, MAX_LEN, fp);

    // Read each guest reservation and store it in the guest_list array
    int i = 0;
    char line[MAX_LEN];
    while (i < num_guests && fgets(line, MAX_LEN, fp) != NULL) {
        // Remove newline characters
        strtok(line, "\n");
        strtok(line, "\r");

        int fields_read = sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%s", 
        guest_list[i].name, guest_list[i].surname, guest_list[i].birthday, guest_list[i].phone, 
        guest_list[i].address, guest_list[i].email, guest_list[i].reservation_date, 
        guest_list[i].reservation_time, &guest_list[i].num_guests, guest_list[i].arrival, guest_list[i].departure);

        if (fields_read != 11) {
            continue; // Skip this line if it doesn't have the correct number of fields
        }
        
        if(strcmp(guest_list[i].reservation_date, current_date) == 0){
            printf("%-30s %-30s Date: %-12s Time: %-8s Guests: %d\n", guest_list[i].name, guest_list[i].surname, guest_list[i].reservation_date, guest_list[i].reservation_time, guest_list[i].num_guests);
        }
        i++;
    }

    // Close the file
    fclose(fp);
}

void write_user_data_to_csv(struct guest new_guest) {
    // Open the CSV file for writing
    FILE *fp = fopen("test.csv", "a");

    // Write the header row if the file is empty
    if (ftell(fp) == 0) {
        fprintf(fp, "Name,Surname,Birthday,Phone,Address,Email,Reservation_Date,Reservation_Time,Num_Guests,Arrival,Departure\n");
    }

    // Write the new guest reservation to the file
    fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s,%d,%s,%s\n", new_guest.name, 
    new_guest.surname, new_guest.birthday, new_guest.phone, new_guest.address, new_guest.email, 
    new_guest.reservation_date, new_guest.reservation_time, new_guest.num_guests, new_guest.arrival, new_guest.departure);

    // Close the file
    fclose(fp);

    printf("Your data has been saved to data.csv\n");
}

int main(void){

    int num_guests = 100;

    // Allocate memory for the guest_list array
    struct guest* guest_list = calloc(num_guests, sizeof(struct guest));

    char user_input;
    printf("user menu: n = new reservation, c = check current reservations, a = guests have arrived, l = guests have left\nYour input: ");
    scanf("%c", &user_input);

    // Initialize a new guest variable
    
    struct guest new_guest;

    switch (user_input) {
        case 'n':
            printf("Please enter your name: ");
            scanf("%s", new_guest.name);

            printf("Please enter your surname: ");
            scanf(" %[^\n]", new_guest.surname);

            printf("Please enter your birthday (format dd.mm.yyyy): ");
            scanf("%s", new_guest.birthday);

            printf("Please enter your phone number (max 11 digits, only numbers): ");
            scanf("%s", new_guest.phone);

            printf("Please enter your address: ");
            scanf(" %[^\n]", new_guest.address);

            printf("Please enter your email: ");
            scanf("%s", new_guest.email);

            printf("Please enter your reservation date: ");
            scanf("%s", new_guest.reservation_date);

            printf("Please enter your reservation time: ");
            scanf("%s", new_guest.reservation_time);

            printf("Please enter the number of guests (max 4): ");
            scanf("%d", &new_guest.num_guests);

            write_user_data_to_csv(new_guest);
            break;

        case 'c':

            // Read the guest reservations and store them in the guest_list array
            read_reservations(guest_list, 100);

            // Free the memory allocated for the guest_list array
            free(guest_list);
            break;

        case 'a':
            break;
        
        case 'l':
            break;

        default:
            printf("No such input allowed\n");
            break;
    }
    return 0;
}