#include <pthread.h>

#define PID_MIN  	300
#define PID_MAX 	500

/* mutex lock for accessing pid_map */
pthread_mutex_t mutex;

int pid_map[PID_MAX+1];

int last;	// last pid in use


/******************************************************************************
 * @brief Allocates the array of available PID's EX: pid_map[300] is set as 1
 *        if pid 300 is in use.
 *
 * @returns retval  1 if failed, 0 if sucsessful
 *****************************************************************************/
int allocate_map(void);

/******************************************************************************
 * @brief Finds the next available PID, marks it as 'in use' and returns the value
 * EX: pid_map[300] is set as 1 if pid 300 is in use.
 *
 * @returns retval  -1 if failed, PID_val if sucsessful
 *****************************************************************************/
int allocate_pid(void);

/******************************************************************************
 * @brief  marks the specified PID as free
 *****************************************************************************/
void release_pid(int pid);
