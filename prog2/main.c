#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "bank.h"
#include "customer.h"

pthread_mutex_t bank_mutex;
int customer_ids[NUMBER_OF_CUSTOMERS];
int total_resources[NUMBER_OF_RESOURCES];

void read_args(int argc, char * argv[], int table[]);
void init_customers(pthread_t customers[]);
void init_tables(int table[]);
void print_table(void);

// Thread code
void *customer(void *param)
{
    int * id_p = (int *) param;
    int   id   = *id_p;
    int   request[NUMBER_OF_RESOURCES];

    for(int round = 0; round < MAX_LOOP; round++)
    {
        for(int index = 0; index < NUMBER_OF_RESOURCES; index++)
        {
            if(available[index] > 0)
                request[index] = rand() % available[index] + 1;
            else
                request[index] = 0;
        }



        pthread_mutex_lock(&bank_mutex);
        printf("Request P%d <", id);
        for(int index = 0; index < NUMBER_OF_RESOURCES; index++)
        {
            printf("%d", request[index]);

            if(index < NUMBER_OF_RESOURCES - 1)
            {
                printf(", ");
            }
        }
        printf(">\n");
        request_resource(id, request);
        print_table();
        pthread_mutex_unlock(&bank_mutex);

        // sleep random time
        sleep(rand() % 2);

        // Only release 50% of the time
        if((rand()%10) > 5)
        {
            for(int index = 0; index < NUMBER_OF_RESOURCES; index++)
            {
                if(allocation[id][index] >0)
                    request[index] = rand() % (allocation[id][index] + 1);
                else
                    request[index] = 0;
            }

            pthread_mutex_lock(&bank_mutex);
            printf("Release P%d <", id);
            for(int index = 0; index < NUMBER_OF_RESOURCES; index++)
            {
                printf("%d", request[index]);

                if(index < NUMBER_OF_RESOURCES - 1)
                {
                    printf(", ");
                }
            }
            printf(">\n");
            release_resource(id, request);
            print_table();
            pthread_mutex_unlock(&bank_mutex);
        }
    }
}

int main(int argc, char * argv[])
{
    srand(69420);
    pthread_t customers[NUMBER_OF_CUSTOMERS];
    pthread_mutex_init(&bank_mutex, NULL);

    int unallocated[NUMBER_OF_RESOURCES];


    read_args(argc, argv, unallocated);

    init_tables(unallocated);

    printf("Initial Table:\n");
    print_table();

    init_customers(customers);
    for(int index = 0; index < NUMBER_OF_CUSTOMERS; index++)
    {
        // Pointer math sucks and should never be used *uses pointer math*
        pthread_join(customers[index], NULL);
    }
    pthread_exit(NULL);


}

void read_args(int argc, char * argv[], int table[])
{
    if(argc - 1 != NUMBER_OF_RESOURCES)
    {
        printf("Bankers Algorithm requires %d resources.\nExiting...\n"
                , NUMBER_OF_RESOURCES);
        exit(-1);
    }
    else
    {
        printf("Allocating...\n");
        for(int index = 0; index < NUMBER_OF_RESOURCES; index++)
        {
            table[index] = atoi(argv[index+1]); // Ascii offset to get to numbers
            printf("%c: %d\n", (char) index + 65, table[index]);
        }

    }

    return;

}

void init_tables(int table[])
{
    int rand_val;
    int sum[NUMBER_OF_RESOURCES];
    int remaining[NUMBER_OF_RESOURCES];

    for(int resource = 0; resource < NUMBER_OF_RESOURCES; resource++)
    {
        remaining[resource] = table[resource];
        total_resources[resource] = table[resource];
        sum[resource] = 0;
    }

    for(int customer = 0; customer < NUMBER_OF_CUSTOMERS; customer++)
    {
    //printf("Customer %d:\n", customer);
        for(int resource = 0; resource < NUMBER_OF_RESOURCES; resource++)
        {
            // Generate Max
            rand_val = rand();
           // printf("max_rand: %d\n", rand_val);
            maximum[customer][resource] = rand_val % remaining[resource] + 1 ;
            //printf("maximum: %d\n", maximum[customer][resource]);

            // generate alloc
            rand_val = rand();
            //printf("alloc_rand: %d\n", rand_val);
            allocation[customer][resource] = rand_val % maximum[customer][resource];
            //printf("allocation: %d\n", allocation[customer][resource]);
            remaining[resource] -= allocation[customer][resource];
            sum[resource] += allocation[customer][resource];
            // generate need based off max and alloc
            need[customer][resource] = maximum[customer][resource] - allocation[customer][resource];
     //       printf("sum: %d\n", sum[resource]);
        }
    }
    for(int resource = 0; resource < NUMBER_OF_RESOURCES; resource++)
    {
        available[resource] = table[resource] - sum[resource];
    }
}

void print_table(void)
{
    printf("\tAllocation\tNeed\tAvailable\n\tA B C\t\tA B C\tA B C\n");
    for(int customer = 0; customer < NUMBER_OF_CUSTOMERS; customer++)
    {
        printf("P%d\t", customer);
        for(int resource = 0; resource < NUMBER_OF_RESOURCES; resource++)
        {
            printf("%d ", allocation[customer][resource]);
        }
        printf("\t\t");
        for(int resource = 0; resource < NUMBER_OF_RESOURCES; resource++)
        {
            printf("%d ", need[customer][resource]);
        }
        if(customer == 0)
        {
            printf("\t");
            for(int resource = 0; resource < NUMBER_OF_RESOURCES; resource++)
            {
                printf("%d ", available[resource]);
            }
        }
        printf("\n");
    }
        printf("\n\n\n");
}
void init_customers(pthread_t customers[])
{
    for(int index = 0; index < NUMBER_OF_CUSTOMERS; index++)
    {
        customer_ids[index] = index;
        pthread_create(&customers[index], 0, customer, (void *) &customer_ids[index]);
    }

}

/*
int main(void)
{
    int i;
    pthread_t tids[NUM_THREADS];
    pthread_mutex_init(&test_mutex, NULL);

    for (i = 0; i <= PID_MAX; i++) {
        in_use[i] = 0;
    }


    if (allocate_map() == -1)
        return -1;

    srandom((unsigned)time(NULL));

    for(int index = 0; index < NUM_THREADS; index++)
    {
        // Pointer math sucks and should never be used *uses pointer math*
        pthread_create(tids + index, NULL, allocator, NULL);
    }

    for(int index = 0; index < NUM_THREADS; index++)
    {
        // Pointer math sucks and should never be used *uses pointer math*
        pthread_join(tids[index], NULL);
    }
    pthread_exit(NULL);


    return 0;
}*/
