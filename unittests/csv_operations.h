#ifndef CSV_OPERATIONS_H
#define CSV_OPERATIONS_H

#include "guest.h"

void write_user_data_to_csv(guest new_guest);
void read_reservations(guest* guest_list, int num_guests);
void write_reservations(guest* guest_list, int num_guests);

#endif  // CSV_OPERATIONS_H
