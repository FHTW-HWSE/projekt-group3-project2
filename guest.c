#define MAX_LEN 100

typedef struct {
    char name[MAX_LEN];
    char surname[MAX_LEN];
    char birthday[11];
    char phone[16];
    char address[MAX_LEN];
    char email[MAX_LEN];
    char reservation_date[11];
    char reservation_time[6];
    int num_guests;
    int table_number;
    char arrival[6];
    char departure[6];
} guest;