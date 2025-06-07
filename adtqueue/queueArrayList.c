/**
 * @file queueArrayList.c
 * 
 * @brief Provides an implementation of the ADT Queue with an array list
 * as the underlying data structure.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "queue.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 20

typedef struct queueImpl {
	// TODO
	QueueElem *elements;   // Array of elements
	int capacity;          // Current capacity of the array
	int size;              // Current number of elements in the queue
} QueueImpl;

static bool ensureCapacity(PtQueue queue) {
    if (queue->size == queue->capacity) {
        int newCapacity = queue->capacity * 2;
        QueueElem* newArray = (QueueElem*) realloc( queue->elements, 
                                newCapacity * sizeof(QueueElem) );
        
        if(newArray == NULL) return false; 

        queue->elements = newArray;
        queue->capacity = newCapacity;
    }
    
    return true;
}

PtQueue queueCreate() {
	PtQueue queue = (PtQueue)malloc(sizeof(QueueImpl));
	if (queue == NULL) return NULL;
	queue->elements = (QueueElem*)calloc(INITIAL_CAPACITY, sizeof(QueueElem));
	if (queue->elements == NULL) {
		free(queue);
		return NULL;	
	}
	queue->size = 0;
	queue->capacity = INITIAL_CAPACITY;
	return queue;
}

int queueDestroy(PtQueue *ptQueue) {
	PtQueue queue = (*ptQueue);

	if (queue == NULL) return QUEUE_NULL;

	free(queue->elements);
	free(queue);

	*ptQueue = NULL; // Set the pointer to NULL after freeing
	return QUEUE_OK;
}

int queueEnqueue(PtQueue queue, QueueElem elem) { 
	if (queue == NULL) return QUEUE_NULL;

	if(!ensureCapacity(queue)) return QUEUE_NO_MEMORY;
	// TODO
	queue->elements[queue->size] = elem;
    queue->size++;
	return QUEUE_OK;
}

int queueDequeue(PtQueue queue, QueueElem *ptElem) { 
	if (queue == NULL) return QUEUE_NULL;

	if (queue->size == 0) return QUEUE_EMPTY;

	// TODO
	*ptElem = queue->elements[0]; // Get the front element
	for(int i = 0; i < queue->size - 1; i++) {
		queue->elements[i] = queue->elements[i + 1]; // Shift elements down
	}
	queue->size--; // Decrease the size of the queue
	return QUEUE_OK;
}

int queueFront(PtQueue queue, QueueElem *ptElem) { 
	if (queue == NULL) return QUEUE_NULL;

	if (queue->size == 0) return QUEUE_EMPTY;

	// TODO
	*ptElem = queue->elements[0]; // Get the front element
	return QUEUE_OK;
}

int queueSize(PtQueue queue, int *ptSize) {
	return queue == NULL ? QUEUE_NULL : (*ptSize = queue->size, QUEUE_OK);
}

bool queueIsEmpty(PtQueue queue) {
	return queue == NULL || queue->size == 0;
}

int queueClear(PtQueue queue) {
	if (queue == NULL) return QUEUE_NULL;
	for (int i = 0; i < queue->size; i++) {
		strcpy(&queue->elements[i], ""); // Clear each element
	}
	return QUEUE_OK;
}

void queuePrint(PtQueue queue) { 
	// TODO
	if (queue == NULL) {
		printf("Queue is NULL\n");
		return;
	}
	if (queue->size == 0) {
		printf("Queue is empty\n");
		return;
	}
	printf("Queue contents: ");
	for (int i = 0; i < queue->size; i++) {
		queueElemPrint(queue->elements[i]); // Print each element
		if (i < queue->size - 1) {
			printf(", "); // Print a comma between elements
		}
	}
	printf("\n");
}

