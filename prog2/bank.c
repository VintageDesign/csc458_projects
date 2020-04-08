#include "bank.h"

int safe_check(int customer_number, int request[])
{
    int retval = -1;

    int finished[NUMBER_OF_CUSTOMERS];
    int work[NUMBER_OF_RESOURCES];
    int alloc_copy[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    int need_copy[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];


    for(int customer_idx = 0
        ; customer_idx < NUMBER_OF_CUSTOMERS
        ; customer_idx++)
    {
        for(int resource_idx = 0
            ; resource_idx < NUMBER_OF_RESOURCES
            ; resource_idx++)
        {
            alloc_copy[customer_idx][resource_idx]
                = allocation[customer_idx][resource_idx];
            need_copy[customer_idx][resource_idx]
                = need[customer_idx][resource_idx];
            work[resource_idx] = available[resource_idx];
        }
        finished[customer_idx] = 0;
    }

    if(check_work(work, request) == 0)
    {
        if(check_max(maximum[customer_number], request, alloc_copy[customer_number]) == 0)
        {
            for(int index = 0; index < NUMBER_OF_RESOURCES; index++)
            {
                work[index]                        -= request[index];
                need_copy[customer_number][index]  -= request[index];
                alloc_copy[customer_number][index] += request[index];
            }

            // Run through the algorithm to see if the request is safe.
            retval = run_algorithm(work, need_copy, alloc_copy, finished);

        }
    }
    return retval;
}

int run_algorithm(int work[], int need_copy[][NUMBER_OF_RESOURCES], int alloc[][NUMBER_OF_RESOURCES], int finished[])
{
    int retval = -1;
    int changed = 0;
    int num_finished = 0;

    while(changed == 0)
    {
        changed = 1;
        num_finished = 0;
        for(int index = 0; index < NUMBER_OF_CUSTOMERS; index++)
        {
            if(finished[index] == 0 && check_work(work, need_copy[index]) == 0)
            {
                changed = 0;
                finished[index] = 1;
                for(int resource = 0; resource < NUMBER_OF_RESOURCES; resource++)
                {
                    work[resource] += alloc[index][resource];
                }
            }

        }
        for(int index = 0; index < NUMBER_OF_CUSTOMERS; index++)
        {
            num_finished += finished[index];
        }

        if(num_finished == NUMBER_OF_CUSTOMERS)
        {
            retval = 1;
            break;
        }
    }
    return retval;
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
