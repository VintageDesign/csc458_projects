#include "bank.h"

int safe_check(int customer_number, int request[])
{
    int retval = -1;

    int work[NUMBER_OF_RESOURCES];
    int alloc_copy[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    int need_copy[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];


    for(int resource_idx = 0; resource_idx < NUMBER_OF_RESOURCES; resource_idx++)
    {
        for(int customer_idx = 0
                ; customer_idx < NUMBER_OF_CUSTOMERS
                ; customer_idx++)
        {
            alloc_copy[customer_idx][resource_idx]
                = allocation[customer_idx][resource_idx];
            need_copy[customer_idx][resource_idx]
                = need[customer_idx][resource_idx];
        }
        work[resource_idx] = available[resource_idx];
    }

    if(check_work(work, request))
    {
        if(check_max(maximum, request, alloc_copy[customer_number]))
        {
            for(int index = 0; index < NUMBER_OF_RESOURCES; index++)
            {
                work[index]                        -= request[index];
                need_copy[customer_number][index]  -= request[index];
                alloc_copy[customer_number][index] += request[index];
            }
        }
    }



}

int check_work(int work[], int req[])
{
    int retval = 0;

    for(int index = 0; index < NUMBER_OF_RESOURCES; index++)
    {
        if(work[index] < req[index])
        {
            retval = -1;
        }
    }

    return retval;
}


int check_max(int max[], int req[], int alloc[])
{
    int retval = 0;

    for(int index = 0; index < NUMBER_OF_RESOURCES; index++)
    {
        if(max[index] < (req[index] + alloc[index]))
        {
            retval = -1;
        }
    }

    return retval;
}
