lib := libuthread.a

all: $(lib)

CC := gcc
CFLAGS := -Wall -Wextra -Werror

## TODO: Phase 1
libuthread.a: uthread.o preempt.o sem.o queue.o context.o
	ar rcs libuthread.a preempt.o sem.o uthread.o queue.o context.o
preempt.o : uthread.o preempt.c 
	$(CC) $(CFLAGS) -c -o $@ preempt.c -l uthread.o
sem.o : uthread.o sem.h queue.o context.o sem.c 
	$(CC) $(CFLAGS) -c -o $@ sem.c -l uthread.o -l queue.o -l context.o
uthread.o : uthread.h queue.o context.o uthread.c 
	$(CC) $(CFLAGS) -c -o $@ uthread.c -l context.o -l queue.o
queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c -o $@ queue.c
context.o : private.h context.c
	$(CC) $(CFLAGS) -c -o $@ context.c
clean:
	rm -rf sem.o queue.o preempt.o uthread.o context.o libuthread.a
