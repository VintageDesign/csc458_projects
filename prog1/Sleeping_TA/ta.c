/**
 * General structure of the teaching assistant.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

void *ta_loop(void *param)
{

    /* seed random generator */
    srandom((unsigned)time(NULL));

    while (1) {

        /* wait for a student to show up */
        //Sleep
        if (sem_wait(&seats) != 0 )
            printf("%s\n",strerror(errno));

        /* acquire the mutex lock */
        if (pthread_mutex_lock(&seat_count) !=0)
            printf("%s\n",strerror(errno));

        waiting_students -= 1;

        /* indicate the TA is ready to help a student */
        if (sem_post(&ta_semaphore) != 0 )
            printf("%s\n",strerror(errno));

        /* release mutex lock */
        if (pthread_mutex_unlock(&seat_count) != 0 )
            printf("%s\n",strerror(errno));

        /* helping students random time */
        help_student( (int) (random() % MAX_SLEEP_TIME));

    }
}

