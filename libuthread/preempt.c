#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"

/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100
static void NonPreemptive()
{
    uthread_yield();
}


void preempt_disable(void)
{
    sigset_t setofsignal;
    sigemptyset(&setofsignal);
    sigaddset(&setofsignal, SIGVTALRM);
    sigprocmask(SIG_BLOCK, &setofsignal, NULL);
}

void preempt_enable(void)
{
    sigset_t setofsignal;
    sigemptyset(&setofsignal);
    sigaddset(&setofsignal, SIGVTALRM);
    sigprocmask(SIG_UNBLOCK, &setofsignal, NULL);
}

void preempt_start(bool preempt)
{
    if (preempt) {
        struct sigaction sa;
        sa.sa_handler = timer_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGALRM, &sa, NULL);

        timer.it_value.tv_sec = 0;
        timer.it_value.tv_usec = 1000000 / HZ;
        timer.it_interval.tv_sec = 0;
        timer.it_interval.tv_usec = 1000000 / HZ;
        setitimer(ITIMER_REAL, &timer, NULL);
    }
}

void preempt_stop(void)
{
	/* TODO Phase 4 */
	preempt_start(preempt_enabled);
}

