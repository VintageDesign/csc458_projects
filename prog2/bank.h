#include <stdio.h>
/* these may be any values >= 0 */
#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3
#define MAX_LOOP 5

/* the available amount of each resource */
int available[NUMBER_OF_RESOURCES];

/*the maximum demand of each customer */
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* the amount currently allocated to each customer */
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* the remaining need of each customer */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];


int safe_check(int customer_number, int request[]);
int run_algorithm(int work[], int need_copy[][NUMBER_OF_RESOURCES], int alloc[][NUMBER_OF_RESOURCES], int finished[]);
int check_work(int work[], int req[]);
int check_max(int work[], int req[], int max[]);
