/**
 * A solution to the pid manager problem.
 *
 */

#include "pid.h"
#include <pthread.h>
#include <stdio.h>

// Allocates the pid map.
int allocate_map(void)
{
    int retval = 1;

    // Init mutex lock
    if(pthread_mutex_init(&mutex, NULL) == 0)
    {
        if(pthread_mutex_lock(&mutex) != 0)
            printf("Couldnt get mutex lock");

        for(int index = 0; index <= PID_MAX - PID_MIN; index++)
        {
            pid_map[index] = 0;
        }

        if(pthread_mutex_unlock(&mutex) != 0)
            printf("Couldnt release mutex lock");

        retval = 0;
    }

    return retval;
}

// Allocates a pid
int allocate_pid(void)
{
    /* local variables */
    int retval = 1;
    int temp = -1;

    /* acquire the mutex lock and warn if unable */
    if(pthread_mutex_lock(&mutex) != 0)
        printf("Couldnt get mutex lock");

    /* find the next available pid */
    for( int index = 1; index <= PID_MAX - PID_MIN; index++)
    {
        temp = pid_map[index];

        if(temp == 0){
            retval = index + PID_MIN;
            pid_map[index] = 1;
            break;
        }
    }

    /* unlock and warn if the mutex was not unlockd */
    if(pthread_mutex_unlock(&mutex) != 0)
        printf("Couldnt release mutex lock");

    printf("Allocated PID: %d\n", retval);

    return retval;
}

// Releases a pid
void release_pid(int pid)
{
    /* acquire the mutex lock and warn if unable */
    if(pthread_mutex_lock(&mutex) != 0)
        printf("Couldnt get mutex lock");

    pid_map[pid - PID_MIN] = 0;

    /* unlock and warn if the mutex was not unlockd  */
    if(pthread_mutex_unlock(&mutex) != 0)
        printf("Couldnt release mutex lock");
    printf("Released PID: %d\n", pid);

    return;

}
