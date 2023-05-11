lib := libuthread.a

all: $(lib)

CC := gcc
CFLAGS := -Wall -Wextra -Werror

libuthread.a: preempt.o sem.o uthread.o queue.o context.o
    ar rcs $@ $^

preempt.o: preempt.c uthread.h
    $(CC) $(CFLAGS) -c -o $@ $<

sem.o: sem.c sem.h uthread.h queue.h context.h
    $(CC) $(CFLAGS) -c -o $@ $<

uthread.o: uthread.c uthread.h queue.h context.h
    $(CC) $(CFLAGS) -c -o $@ $<

queue.o: queue.c queue.h node.h
    $(CC) $(CFLAGS) -c -o $@ $<

context.o: context.c context.h private.h
    $(CC) $(CFLAGS) -c -o $@ $<

clean:
    rm -f *.o $(lib)
