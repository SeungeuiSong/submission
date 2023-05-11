#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct node {
		void* val;
		struct node* next;
		struct node* prev;
};

struct queue {
	/* TODO Phase 1 */
	int length;

	struct node* head;
	struct node* tail;
};

queue_t queue_create(void)
{
	/* TODO Phase 1 */

	// create queue, initialize head and tail of queue
	struct queue* queue = malloc(sizeof(struct queue));
	struct node* head = malloc(sizeof(struct node));
	struct node* tail = malloc(sizeof(struct node));

	queue->head = head;
	queue->tail = tail;
	queue->length = 0;
	
	return queue;
}

int queue_destroy(queue_t queue)
{
	/* TODO Phase 1 */

	// return -1 if queue is NULL or if queue is not empty
	if (queue->length != 0 || queue == NULL) {
		return -1;
	}

	// deallocate memory
	free(queue->head);
	free(queue->tail);
	free(queue);

	return 0;
}

int queue_enqueue(queue_t queue, void *data)
{
	/* TODO Phase 1 */

	// return -1 if queue or data is NULL
	if (queue == NULL || data == NULL) {
		return -1;
	}

	// create new node to enqueue into queue and set data value
	struct node* newNode = malloc(sizeof(struct node));
	newNode->val = data;

	// if queue is empty, add a node between head and tail
	if (queue->length == 0) {
		queue->head->next = newNode;
		queue->tail->prev = newNode;
		newNode->prev = queue->head;
		newNode->next = queue->tail;
	}
	// otherwise, add a node right before the tail
	else {
		newNode->prev = queue->tail->prev;
		newNode->next = queue->tail;
		queue->tail->prev->next = newNode;
		queue->tail->prev = newNode;
	}

	// increment length
	queue->length++;

	return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
	/* TODO Phase 1 */

	// return -1 if queue or data is NULL
	if (queue->length == 0 || queue == NULL || data == NULL) {
		return -1;
	}
	
	// get second node in queue in order to make it first node after dequeueing
	struct node* secondNode = queue->head->next->next;

	*data = queue->head->next->val;
	free(queue->head->next);

	// make the old secondNode the new firstNode
	queue->head->next = secondNode;

	// decrement length
	queue->length--;

	return 0;
}

int queue_delete(queue_t queue, void *data)
{
	/* TODO Phase 1 */

	// return -1 if queue or data is NULL
	if (queue == NULL || data == NULL){
		return -1;
	}

	// start at head, traverse until end or until data is found
	struct node* node = queue->head;
	while (node->next != NULL)
	{
		if (node->next->val == data)
		{
			struct node* nextNode = node->next->next;

			if (nextNode == NULL) {
				queue->tail->prev = node;
			}

			free(node->next);
			node->next = nextNode;
			queue->length--;

			return 0;
		}
		node = node->next;
	}

	// if data wasn't found return -1
	return -1;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	/* TODO Phase 1 */

	// return -1 if queue or func is NULL
	if (queue == NULL || func == NULL) {
		return -1;
	}

	// make an array of nodes to represent the queue, set current node to the first element in the queue
	struct node* nodes[queue->length]; 
	struct node* currNode = queue->head->next;

	// put all nodes into array in order of queue
    for (int i = 0; i < queue->length; i++) {
		nodes[i] = currNode;
		currNode = currNode->next;
    }

	// execute the parametized function on all nodes
	for (int i = 0; i < queue->length; i++) {
		if(nodes[i] != NULL)
			func(queue, nodes[i]->val);
	}
	
    return 0;
}

int queue_length(queue_t queue)
{
	/* TODO Phase 1 */

	// return -1 if queue is NULL
	if (queue == NULL) {
		return -1;
	}

	// return the length of the queue
	return queue->length;
}
