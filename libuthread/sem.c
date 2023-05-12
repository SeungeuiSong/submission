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

int sem_down(sem_t sem)
{
    preempt_disable();
    sem->count--;
    if (sem->count < 0) {
        struct uthread_tcb *prev_thread = uthread_current();
        queue_enqueue(sem->waiting_list, prev_thread);
        uthread_block();
    }
    preempt_enable();
    return 0;
}

int sem_up(sem_t sem)
{
    if(sem == NULL){
	return -1;}
    preempt_disable();
    sem->count++;
    if (sem->count <= 0) {
        struct uthread_tcb *thread;
        queue_dequeue(sem->waiting_list, ((void**) &thread));
        uthread_unblock(thread);
    }
    preempt_enable();
    return 0;
}
