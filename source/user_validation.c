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

bool validatePhoneNumber(const char* phone) {
    // Validate that the phone number consists only of digits and has a maximum length of 11
    for (int i = 0; phone[i] != '\0'; i++) {
        if (!isdigit((unsigned char)phone[i]) || i >= 11) {
            return false;
        }
    }
    return true;
}

bool validateDate(const char* date) {
    // Validate that the date has the format dd.mm.yyyy
    int day, month, year;
    if (sscanf(date, "%2d.%2d.%4d", &day, &month, &year) != 3) {
        return false;
    }
    if (day < 1 || day > 31 || month < 1 || month > 12) {
        return false;
    }
    // Additional validation checks can be added for specific ranges of day, month, year
    return true;
}

bool validateTime(const char* time) {
    // Validate that the time has the format hh:mm
    int hour, minute;
    if (sscanf(time, "%2d:%2d", &hour, &minute) != 2) {
        return false;
    }
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        return false;
    }
    // Additional validation checks can be added for specific ranges of hour, minute
    return true;
}