#define MAX_LEN 100

typedef struct {
    char name[MAX_LEN];
    char surname[MAX_LEN];
    char birthday[10];
    char phone[15];
    char address[MAX_LEN];
    char email[MAX_LEN];
    char reservation_date[10];
    char reservation_time[5];
    int num_guests;
    int table_number;
    char arrival[5];
    char departure[5];
} guest;