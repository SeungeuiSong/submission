# Phase 1
## Queue
To implement our queue, we decided a doubly-linked list would suffice simplest
for an O(1) enqueue and dequeue structure. With a doubly-linked list, we are
able to use the tail to see what is at the end of the queue instantlaneously,
instead of having to traverse the list every single time we want to enqueue
something. Additionally, it's easier to backtrack this way.
## Makefile
In order to learn more about Makefiles, we referenced the slides on canvas as
well as the linked page on static libraries in the project document 
(http://tldp.org/HOWTO/Program-Library-HOWTO/static-libraries.html).
## Queue Testing
For Phase 1, we only had to test the Queue, but this still consumed a lot of
time due to the difficulties of getting the Makefile to work as intended. Our
queue tester added onto the queue tester example that was provided in order to
fully test the rest of the functions necessary to make sure our queue had no
issues. We tested for destroy, delete, and iterate in addition to the tests on
create and enqueue/dequeue. For destroy, we first created a queue, then tested
the queue_destroy on it to see if it was destroyed or not, based on the return
value implemented in queue.c. Similarly for delete, we created a queue, but we
then enqueued values into the queue and deleted one of the values. We tested to
make sure that the value was deleted. For iterate, we implemented a function
that sets all values to three and tests if the length of the given queue is
accurate with what it should be. In the iterate function itself, we called this
function after creating a queue with values enqueued, and asserted afterwards
checking that all of the values were equal to three.
# Phase 2
## UThread
To implement the UThread library, we implemented our queue data structure into
two lists: a ready list and a waiting list. These two queues helped to change
the state that the given thread was in, as threads could be easily blocked and
unblocked this way. To create a thread, we initialized a uthread_tcb with a
pointer to the stack, pointer to the context (referenced in context API), the 
current state and the thread ID to identify the thread. After initializing all
of the necessary components of the thread, we queued the created threat into
both queues. To run the threads, we allocated threads to signify the original
(main) thread, the first thread, and the previous and next threads. The first
thread is placed into both queues, and if the waiting queue is not empty, the
thread will switch context (another context API function) to the next thread,
and dequeue that thread from the waiting queue. When the current thread yields, 
it is enqueued into the waiting list and switches context again. On exit call,
the thread's state is set to 0 and the stack's memory is freed. Additionally,
the thread is deleted from the ready list queue and the process is dequeued.
Finally, the context is once again switched.
## Makefile
Updating the Makefile in this stage had us making big changes, as we realized
we were going to need to incorporate many files, so we included variables to
make our lives easier for the future steps.
# Phase 3
## Semaphores
To implement semaphores, we created a semaphore struct with a count, signifying
whether the resource is available or not, and a waiting list queue that stores
all of the threads that are waiting for a given resource. If count is 0, the
thread will be blocked as the resource is not available. Whenever a thread
releases a resource, it checks to see if there are any threads in the waiting
list queue to schedule them to that resource. The destroy function frees the 
memory of the semaphore and returns 0 if completed. The sem_down function checks
to see if the resource is available or not, and it is, decrements the count of
the semaphore representing the resource. If the resource is not available when
sem_down is called, the thread is queued into the waitlist of the semaphore and
blocked. The sem_up function does the opposite. It checks to see if there are
any waiting threads for the given resource in the queue, and if there is, the
thread at the front of the queue is dequeued and unblocked. If there are not any
threads in the waiting list queue, the count is simply incremented, signifying
that there is now availability with the given resource.
# Phase 4
## Preemption
For preemption, we referenced the GNU C Library provided on the Project 2 page 
(https://www.gnu.org/software/libc/manual/) for many of the tasks. To enable 
alarms, a signal was set with SIGVTALRM, where it was unblocked, or allowed to 
go through. For disabling, it was the opposite. Disabling an alarm blocked the 
signal instead of unblocking it. When start is called, we initialized the signal 
handler and a timer is set to tick a specific number of times per second 
according to the specified constant HZ. The handler forces the current thread to
yield in order to allow scheduling of another thread. The stop function simply 
reverts the signal and timer to their previous values.
## Preemption Testing
In order to test our design, we created two threads in test_preempt.c, and used
a function to yield for the other thread. In doing so, we test that the threads
aren't just hogging the processor to themself for the entire duration. This
ensures that each thread will yield for another thread. If one of these threads
fails to yield or be created, an error message will be printed out signifying
which thread caused the issue.