#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "private.h"

struct semaphore {
	/* TODO Phase 3 */
	int count;
	queue_t waiting_list;
};

sem_t sem_create(size_t count)
{
	/* TODO Phase 3 */
    struct semaphore* semap = malloc(sizeof(struct semaphore));
    if (semap == NULL) {
        return NULL;
    }

    semap -> waiting_list = queue_creat();
    semap->count = count;

    return semap;
}

int sem_destroy(sem_t sem)
{
	/* TODO Phase 3 */
	
}

int sem_down(sem_t sem)
{
	/* TODO Phase 3 */
}

int sem_up(sem_t sem)
{
	/* TODO Phase 3 */
}

