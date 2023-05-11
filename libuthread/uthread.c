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
    struct uthread_tcb *prev_thread = process;
    queue_enqueue(ready_list, prev_thread);
    queue_dequeue(ready_list, ((void**) &process));
    uthread_ctx_switch(prev_thread->context, process->context);
    preempt_enable();

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
    uthread_ctx_switch(prev_thread->context, next_thread->context);
    preempt_enable();
}
/*
int uthread_create(uthread_func_t func, void *arg)
{
    preempt_disable();
    struct uthread_tcb *new_thread = (struct uthread_tcb *)malloc(sizeof(struct uthread_tcb));
    if (new_thread == NULL) {
        preempt_enable();
        return -1;
    }

    new_thread->stack = uthread_ctx_alloc_stack();
    if (new_thread->stack == NULL) {
        free(new_thread);
        preempt_enable();
        return -1;
    }

    new_thread->tid = queue_length(ready_list) + 1;
    new_thread->state = 1;

    if (uthread_ctx_init(new_thread->context, new_thread->stack, func, arg) == -1) {
        free(new_thread->stack);
        free(new_thread);
        preempt_enable();
        return -1;
    }

    int rv = uthread_ctx_init(new_thread->context, new_thread->stack, func, arg);
    queue_enqueue(ready_list, new_thread);
    queue_enqueue(waiting_list, new_thread);
    preempt_enable();
    return rv;
}*/

int uthread_create(uthread_func_t func, void arg)
{
    preempt_disable();
    struct uthread_tcbnew_thread = (struct uthread_tcb *)malloc(sizeof(struct uthread_tcb));
    if (new_thread == NULL) {
        preempt_enable();
        return -1;
    }

    new_thread->stack = uthread_ctx_alloc_stack();
    if (new_thread->stack == NULL) {
        free(new_thread);
        preempt_enable();
        return -1;
    }

    new_thread->tid = queue_length(&ready_list) + 1;
    new_thread->state = 1;

    if (uthread_ctx_init(&(new_thread->context), new_thread->stack, func, arg) == -1) {
        free(new_thread->stack);
        free(new_thread);
        preempt_enable();
        return -1;
    }

    queue_enqueue(&ready_list, new_thread);
    preempt_enable();
    return new_thread->tid;
}


int uthread_run(bool preempt, uthread_func_t func, void *arg)
{
    if (preempt) {
	preempt_start(preempt);
    }
    int tid = uthread_create(func, arg);
    if (tid == -1) {
        return -1;
    }
    uthread_yield();
    return tid;
}
void uthread_block(void)
{
    preempt_disable();
    struct uthread_tcb *prev_thread = process;
    prev_thread->state = 0;
    queue_enqueue(waiting_list, prev_thread);
    queue_dequeue(ready_list, ((void**) &process));
    uthread_ctx_switch(prev_thread->context, next_thread->context);
    preempt_enable();
}

void uthread_unblock(struct uthread_tcb *uthread)
{
    preempt_disable();
    uthread->state = 1;
    queue_delete(waiting_list, uthread);
    queue_enqueue(ready_list, uthread);
    preempt_enable();
}
