#ifndef USER_VALIDATION_H
#define USER_VALIDATION_H

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

bool validatePhoneNumber(const char* phone);

bool validateDate(const char* date);

bool validateTime(const char* time);

#endif