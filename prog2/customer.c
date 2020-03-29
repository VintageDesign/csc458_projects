#include "customer.h"
#include "bank.h"

int request_resource(int customer_number, int request[])
{
    int retval = -1;

    if (safe_check(customer_number, request))
    {
        for (int index = 0; index < NUMBER_OF_RESOURCES; index++)
        {
            available[index]  -= request[index];
            allocation[index] += request[index];
            need[index]       -= request[index];
        }
        retval = 0;
    }

    return retval;
}

int release_request(int customer_number, int release[])
{
    int retval = 0;

    for (int index = 0; index < NUMBER_OF_RESOURCES; index++)
    {
        available[index]  -= request[index];
        allocation[index] += request[index];
        need[index]       -= request[index];
    }

    return retval;
}
