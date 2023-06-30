#ifndef CHANGES_H
#define CHANGES_H

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

void print_current_reservations(guest* guest_list, int num_guests);

void delete_reservation(guest* guest_list, int num_guests, char* table_number);

void guest_arrival(guest* guest_list, int num_guests, char* table_number, char* time);

void guest_departure(guest* guest_list, int num_guests, char* table_number, char* time);

#endif