#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "private.h"

struct semaphore {
	/* TODO Phase 3 */
	int count;
	queue_t waiting_list;
};
struct uthread_tcb* uthread;
sem_t sem_create(size_t count)
{
	/* TODO Phase 3 */
    struct semaphore* sem = malloc(sizeof(struct semaphore));
    if (sem == NULL) {
        return NULL;
    }

    sem -> waiting_list = queue_create();
    sem->count = count;
    return sem;
}

int sem_destroy(sem_t sem)
{
	/* TODO Phase 3 */
	if(sem == NULL || queue_length(sem->waiting_list) != 0)
		return -1;
	free(sem);
	return 0;
}

int sem_down(sem_t sem)
{
        /* Try to take a resource */
    if (sem == NULL) {
        return -1;
    }

    if (sem->count == 0) {
        /* If no resources available, wait until one becomes available */
        uthread_block();
    }
    else {
        sem->count--;
    }
    return 0;
    
}

int sem_up(sem_t sem)
{
    if (sem == NULL) {
        return -1;
    }
    

    /* If threads are waiting, wake up the oldest one */
    struct uthread_tcb* uthread;
    
    if (!queue_length(sem->waiting_list)) {
        sem->count++;
    }
    else {
        queue_dequeue(sem->waiting_list, ((void**) &uthread));
        uthread_unblock(uthread);
    }

    return 0;
}
