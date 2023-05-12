#include <stdio.h>
#include <unistd.h>
#include "uthread.h"
#include "private.h"

void threadFunc(void *thread) {
    int id = *(int*)thread;
    printf("Thread %d\n", id);
    uthread_yield();
    printf("Thread %d yield\n", id);
    uthread_exit();
}

void testThreads() {
    int thread1_id = 1;
    int thread2_id = 2;

    if (uthread_create(threadFunc, &thread1_id) != 0) {
        fprintf(stderr, "*** FAILED creation of thread 1 ***\n");
        return;
    }

    if (uthread_create(threadFunc, &thread2_id) != 0) {
        fprintf(stderr, "*** FAILED creation of thread 2 ***\n");
        return;
    }

}

int main() {
    uthread_run(true, testThreads, NULL);
    return 0;
}
