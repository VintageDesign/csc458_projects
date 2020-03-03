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
        pthread_mutex_lock(&mutex);

        for(int index = 0; index <= PID_MAX - PID_MIN; index++)
        {
            pid_map[index] = 0;
        }

        pthread_mutex_unlock(&mutex);

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
    //TODO warn if not unlockd
    pthread_mutex_lock(&mutex);

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
    //TODO warn if not unlockd
    pthread_mutex_unlock(&mutex);

    printf("Allocated PID: %d\n", retval);

    return retval;
}

// Releases a pid
void release_pid(int pid)
{
    /* acquire the mutex lock and warn if unable */
    //TODO warn if not unlockd
    pthread_mutex_lock(&mutex);

    pid_map[pid - PID_MIN] = 0;

    /* unlock and warn if the mutex was not unlockd  */
    //TODO warn if not unlockd
    pthread_mutex_unlock(&mutex);
    printf("Released PID: %d\n", pid);

    return;

}
