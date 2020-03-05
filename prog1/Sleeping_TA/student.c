/**
 * General structure of a student.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

void *student_loop(void *param)
{
    /* varaibles */
    int *lnumber            = (int *) param;
    int studentid           = *lnumber;
    int times_through_loop  = 0;
    int sleep_time          = 0;


    srandom((unsigned)time(NULL));

    while (times_through_loop < 5) {
        sleep_time = (int) (random() % MAX_SLEEP_TIME);
        times_through_loop++;

        hang_out(studentid, sleep_time);

        /* acquire the mutex lock */
        if (pthread_mutex_lock(&seat_count) != 0)
            printf("StudentA %s\n",strerror(errno));

        /* is there a seat available */
        if (waiting_students < NUM_OF_SEATS) {
            waiting_students++;

            printf("\t\tStudent %d takes a seat waiting = %d\n",studentid, waiting_students);

            // try to wake up the ta
            if ( sem_post(&seats) != 0)
                printf("StudentB %s\n",strerror(errno));

            if (pthread_mutex_unlock(&seat_count) != 0)
                printf("StudentC %s\n",strerror(errno));

            // Mark busy
            if (sem_wait(&ta_semaphore) != 0)
                printf("StudentD %s\n",strerror(errno));

            printf("Student %d receiving help\n", studentid);

        }
        else {
            printf("\t\t\tStudent %d will try later\n", studentid);
            pthread_mutex_unlock(&seat_count);
        }
    }
}

