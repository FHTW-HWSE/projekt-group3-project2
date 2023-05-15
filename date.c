#include <stdio.h>
#include <time.h>

int main() {
    time_t currentTime;
    struct tm *localTime;
    char current_date[100];

    // Get the current time
    currentTime = time(NULL);

    // Convert the current time to the local time
    localTime = localtime(&currentTime);

    // Format the current time as a string
    strftime(current_date, sizeof(current_date), "%d.%m.%Y", localTime);

    // Print the current date
    printf("Current date: %s\n", current_date);

    return 0;
}
