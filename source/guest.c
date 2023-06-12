#define MAX_LEN 300

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
    char table_number[5];
    char arrival[6];
    char departure[6];
} guest;