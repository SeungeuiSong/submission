# Target library
lib := libuthread.a

all: $(lib)

CC := gcc
CFLAGS := -Wall -Wextra -Werror

## TODO: Phase 1
libuthread.a: preempt.o sem.o queue.o uthread.o context.o
	ar rcs libuthread.a preempt.o sem.o uthread.o queue.o  context.o

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c -o $@ queue.c

uthread.o : uthread.c uthread.h queue.o context.o
	$(CC) $(CFLAGS) -c -o $@ uthread.c -l context.o -l queue.o

sem.o : sem.c sem.h uthread.o queue.o context.o
	$(CC) $(CFLAGS) -c -o $@ sem.c -l uthread.o -l queue.o -l context.o

context.o : private.h context.c
	$(CC) $(CFLAGS) -c -o $@ context.c

preempt.o : preempt.c uthread.o
	$(CC) $(CFLAGS) -c -o $@ preempt.c -l uthread.o
	
clean:
	rm -rf libuthread.a queue.o uthread.o sem.o context.o preempt.o
