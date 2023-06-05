#ifndef READ_RESERVATIONS_H
#define READ_RESERVATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "guest.h"

void read_reservations(guest* guest_list, int num_guests);
void print_current_reservations(guest* guest_list, int num_guests);
void write_user_data_to_csv(guest new_guest);


#endif
