#include "customer.h"
#include "bank.h"

int request_resource(int customer_number, int request[])
{
    int retval = -1;

    if (safe_check(customer_number, request) == 1)
    {
            printf("Safe, Request Granted\n");
        for (int index = 0; index < NUMBER_OF_RESOURCES; index++)
        {
            available[index]  -= request[index];
            allocation[customer_number][index] += request[index];
            need[customer_number][index]       -= request[index];
        }
        retval = 0;
    }
    else
        printf("Request Denied\n");

    return retval;
}

int release_resource(int customer_number, int release[])
{
    int retval = 0;

    for (int index = 0; index < NUMBER_OF_RESOURCES; index++)
    {
        available[index]  += release[index];
        allocation[customer_number][index] -= release[index];
        need[customer_number][index]       += release[index];
    }

    return retval;
}
