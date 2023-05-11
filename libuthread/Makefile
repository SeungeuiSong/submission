# Target library
lib := libuthread.a

all: $(lib)

CC := gcc
CFLAGS :=   -Wall-Wextra -Werror

## Phase 1: Build library
libuthread.a:   preempt.o   sem.o   queue.o uthread.o   context.o
ar rcs $@ $^

preempt.o:  preempt.c   uthread.o
$(CC)$(CFLAGS)  -c  -o  $@  $<

sem.o:  sem.c   sem.h   uthread.o   queue.o context.o
$(CC)$(CFLAGS)  -c  -o  $@  $<  -l  uthread -l  queue   -l  context

uthread.o:  uthread.c   uthread.h   queue.o context.o
$(CC)$(CFLAGS)  -c  -o  $@  $<  -l  context -l  queue

queue.o:    queue.c queue.h
$(CC)$(CFLAGS)  -c  -o  $@  $<

context.o:  private.h   context.c
$(CC)$(CFLAGS)  -c  -o  $@  $<     

clean:
rm  -rf sem.o   queue.o preempt.o   uthread.o   context.o   libuthread.a
