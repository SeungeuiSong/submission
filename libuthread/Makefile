# Target library
lib := libuthread.a

all: $(lib) queueTest

queueTest: queue.o queue_tester_example.o
    gcc -Wall -Wextra -Werror -o queueTest queue.o queue_tester_example.o

queue.o: queue.c queue.h
    gcc -Wall -Wextra -Werror -c -o queue.o queue.c

queue_tester_example.o: queue_tester_example.c
    gcc -Wall -Wextra -Werror -c -o queue_tester_example.o queue_tester_example.c

## TODO: Phase 1
$(lib): queue.o
    ar rcs $(lib) queue.o
clean:
    rm -rf queue.o libuthread.a
