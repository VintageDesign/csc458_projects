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
    if(pthread_mutex_init(&mutex) == 0)
    {
        pthread_mutex_lock(&mutex);

        for(int index = 0; index <= PID_MAX - PID_MIN; index++)
        {
            pid_map[index] = 0;
        }

        pthread_mutex_release(&mutex);

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
    //TODO warn if not released
    pthread_mutex_lock(&mutex);

    /* find the next available pid */
    for( int index = 1; index <= PID_MAX - PID_MIN && retval != -1; index++)
    {
        temp = pid_map[index];

        if(temp == 1){
            retval = temp;
        }
    }

    /* release and warn if the mutex was not released */
    //TODO warn if not released
    pthread_mutex_release(&mutex);

    return retval;
}

// Releases a pid
void release_pid(int pid)
{
    /* acquire the mutex lock and warn if unable */
    //TODO warn if not released
    pthread_mutex_lock(&mutex);

    pid_map[pid] = 0;

    /* release and warn if the mutex was not released  */
    //TODO warn if not released
    pthread_mutex_release(&mutex);

    return;

}
