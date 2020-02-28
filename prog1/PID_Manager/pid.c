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
    for(int index = 0; index <= PID_MAX - PID_MIN; index++)
    {
        pid_map = 0;
    }

    return 0;
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
