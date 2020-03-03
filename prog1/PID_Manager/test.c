/**
 * test.c
 *
 * Test the implementation of the PID manager.
 *
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pid.h"

#define NUM_THREADS 100
#define ITERATIONS   10
#define SLEEP         5

int in_use[PID_MAX + 1];

/**
 * mutex lock used when accessing data structure
 * to ensure there are no duplicate pid's in use.
 */
pthread_mutex_t test_mutex;



// Thread code
void *allocator(void *param)
{
    int i, pid;

    for (i = 0; i < ITERATIONS; i++) {
        /* sleep for a random period of time */
        sleep((int)(random() % SLEEP));

        /* allocate a pid */
        pid = allocate_pid();

        if (pid == 1)
            printf("No pid available\n");
        else {
            /* indicate in the in_use map the pid is in use */
            pthread_mutex_lock(&test_mutex);

            in_use[pid] = 1;

            pthread_mutex_unlock(&test_mutex);

            /* sleep for a random period of time */
            sleep((int)(random() % SLEEP));

            /* unlock the pid */
            pthread_mutex_lock(&test_mutex);

            in_use[pid] = 0;

            pthread_mutex_unlock(&test_mutex);

            release_pid(pid);

        }
    }
}

int main(void)
{
    int i;
    pthread_t tids[NUM_THREADS];
    pthread_mutex_init(&test_mutex, NULL);

    for (i = 0; i <= PID_MAX; i++) {
        in_use[i] = 0;
    }


    /* allocate the pid map */
    if (allocate_map() == -1)
        return -1;

    srandom((unsigned)time(NULL));

    /* create the threads */
    for(int index = 0; index < NUM_THREADS; index++)
    {
        // Pointer math sucks and should never be used *uses pointer math*
        pthread_create(tids + index, NULL, allocator, NULL);
    }

    /* join the threads */
    pthread_exit(NULL);

    /* test is finished */

    return 0;
}
