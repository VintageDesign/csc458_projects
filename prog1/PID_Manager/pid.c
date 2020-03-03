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
            pid_map = 0;
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

    /* acquire the mutex lock and warn if unable */

    /* find the next available pid */

    /* release and warn if the mutex was not released */

    return last;
}

// Releases a pid
void release_pid(int pid)
{
    /* acquire the mutex lock and warn if unable */

    /* release and warn if the mutex was not released  */

}
