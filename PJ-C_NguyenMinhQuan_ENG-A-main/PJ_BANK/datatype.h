#include <stdbool.h>
struct Date{
	int day, month, year;
};

struct Admin{
	char email[50];
	char password[50];
};

struct User{
    char id[10];
    char name[50];
    struct Date dateOfBirth;
    bool gender; // 0: Nu, 1: Nam
    char phone[15];
    char email[50];
    bool status; // 0: mo khoa, 1: khoa
    char password [15];
};