#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"
#include "queue.h"


struct uthread_tcb* process;
queue_t ready_list;
queue_t waiting_list;
struct uthread_tcb* prev_thread;
struct uthread_tcb* next_thread;
struct uthread_tcb* main_thread;

struct uthread_tcb {
	/* TODO Phase 2 */
    ucontext_t* context;
    void *stack; 
    int state; 
    int tid;
};

struct uthread_tcb *uthread_current(void)
{
	/* TODO Phase 2/3 */
	getcontext(process->context);
	return process;
}

void uthread_yield(void)
{
    preempt_disable();
    queue_enqueue(waiting_list, uthread_current());
    uthread_ctx_switch(prev_thread->context,main_thread->context);
	/* TODO Phase 2 */
}

void uthread_exit(void)
{
    preempt_disable();
    struct uthread_tcb *prev_thread = process;
    prev_thread->state = 0;
    free(prev_thread->stack);
    queue_delete(ready_list, prev_thread);
    queue_dequeue(ready_list, ((void**) &process));
    uthread_ctx_switch(prev_thread->context, main_thread->context);
}

int uthread_create(uthread_func_t func, void *arg)
{
    preempt_disable();
    struct uthread_tcb *new_thread = (struct uthread_tcb *)malloc(sizeof(struct uthread_tcb));
    if (new_thread == NULL) {
        preempt_enable();
        return -1;
    }

    new_thread->context = malloc(sizeof(ucontext_t));
    new_thread->stack = uthread_ctx_alloc_stack();
    new_thread->state = 1;
    new_thread->tid = uthread_ctx_init(new_thread->context, new_thread->stack, func, arg);

    if (uthread_ctx_init(new_thread->context, new_thread->stack, func, arg) == -1) {
        free(new_thread->stack);
        free(new_thread->context);
        free(new_thread);
        preempt_enable();
        return -1;
    }

    queue_enqueue(ready_list, new_thread);
    queue_enqueue(waiting_list, new_thread);
    preempt_enable();
    return new_thread->tid;
}

int uthread_run(bool preempt, uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
	preempt_start(preempt);


	struct uthread_tcb* first = malloc(sizeof(struct uthread_tcb));
	if(first == NULL)
		return -1;
	first->context = malloc(sizeof(ucontext_t));
    	first->stack = uthread_ctx_alloc_stack();
	int output = uthread_ctx_init(first->context, first->stack, func, arg);
	waiting_list = queue_create();
	ready_list = queue_create();
	queue_enqueue(waiting_list, first);
    	queue_enqueue(ready_list, first);
	
	next_thread = malloc(sizeof(struct uthread_tcb));
	prev_thread = malloc(sizeof(struct uthread_tcb));
	prev_thread->context = malloc(sizeof(ucontext_t));
	getcontext(prev_thread->context);
	main_thread = malloc(sizeof(struct uthread_tcb));
	main_thread->context = malloc(sizeof(ucontext_t));
	getcontext(main_thread->context);
	if(queue_length(waiting_list)){
		queue_dequeue(waiting_list, ((void**) &next_thread));
		process = next_thread;
		uthread_ctx_switch(prev_thread->context, next_thread->context);
	}
	preempt_stop();
	
	struct uthread_tcb* b[queue_length(ready_list)];
	for(int i = 0; i < queue_length(ready_list); i++)
	{
	queue_dequeue(ready_list, (void**)&b[i]);
	free((b[i])->stack);
        free(b[i]->context);
        free(b[i]);
	}
	free(main_thread->context);
	free(prev_thread->context);
	free(main_thread);
	free(prev_thread);
	queue_destroy(waiting_list);
	queue_destroy(ready_list);
	preempt_stop();
	return output;
}

void uthread_block(void)
{  
  queue_enqueue(waiting_list, uthread_current());    
  uthread_ctx_switch(prev_thread->context,main_thread->context);
}

void uthread_unblock(struct uthread_tcb *uthread)
{
    queue_enqueue(waiting_list, uthread);
}
