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
sem_t sem_create(size_t count)
{
	/* TODO Phase 3 */
    struct semaphore* semap = malloc(sizeof(struct semaphore));
    if (semap == NULL) {
        return NULL;
    }

    semap -> waiting_list = queue_create();
    semap->count = count;

    return semap;
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
	/* TODO Phase 3 */
	    /* Try to take a resource */
    if(sem == NULL)
	return -1;
    if (sem->count == 0) {
        /* If no resources available, wait until one becomes available */
        queue_enqueue(sem->waiting_list, uthread_current());
        uthread_black();
    }
    else{
    	sem->count--;
    }
    return 0;
	
}

int sem_up(sem_t sem)
{
	/* TODO Phase 3 */
    if(sem == NULL)
	return -1;
    

    /* If threads are waiting, wake up the oldest one */
    if (!queue_length(sem->waiting_list)) {
	    sem->count++;
    }
    else{
	    
	struct uthread_tcb* new ;
       queue_dequeue(sem->waiting_list, ((void**) &new));
        uthread_unblock(new);
    }

    return 0;
}

