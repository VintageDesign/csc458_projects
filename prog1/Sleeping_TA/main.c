#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>
#include "ta.h"

pthread_t ta;
pthread_t students[NUM_OF_STUDENTS];

/**
 * Initialize all relevant data structures and
 * synchronization objects.
 */
void init()
{
    // Init the seats semaphore
    if (sem_init(&seats, 0, 0))
        printf("error init students_sem\n");
    if (sem_init(&ta_semaphore, 0, 0))
        printf("%s\n",strerror(errno));



    // Init the office mutex
    if (pthread_mutex_init(&seat_count, NULL))
        printf("error init ta\n");

    // Assign student IDs
    for (int i = 0; i < NUM_OF_STUDENTS; i++)
        student_id[i] = i;
}

void create_students()
{

    for (int i = 0; i < NUM_OF_STUDENTS; i++) {
        pthread_create(&students[i], 0, student_loop, (void *) &student_id[i]);
    }
}

void create_ta()
{

    pthread_create(&ta, 0, ta_loop, NULL);

}

int main(void)
{
    int i;

    init();
    create_ta();
    create_students();

    for (i = 0; i < NUM_OF_STUDENTS; i++)
        pthread_join(students[i], NULL);

    /* when all students have finished, we will cancel the TA thread */
    if (pthread_cancel(ta) != 0)
        printf("%s\n",strerror(errno));

    return 0;
}

