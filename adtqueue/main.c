/**
 * @file main.c
 * 
 * @brief Provides an example program that uses the
 * ADT Queue. Please note that the QueueElem type
 * must be defined as 'char'.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include <time.h>

#define STRESS_TEST_SIZE 1000

void testFIFO(PtQueue queue);
void testStress(PtQueue queue);

int main() {
    PtQueue queue = queueCreate();
    if(queue == NULL) {
        printf("Could not create the queue. \n");
        return EXIT_FAILURE;
    }

    //test FIFO twice - make sure implementation works
    //after being emptied.
    testFIFO(queue);
    testFIFO(queue);

    //stress test - useful for comparing different implementations
    testStress(queue);

    queueDestroy(&queue);

    return EXIT_SUCCESS;
}

void testFIFO(PtQueue queue) {
    queuePrint(queue);

    //Test FIFO behavior (visually from output)
    char examples[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    for(int i=0; i<sizeof(examples)/sizeof(char); i++) {
        char ex = examples[i];
        printf("Pushing %c ...", ex);
        queueEnqueue(queue, ex);

        char front;
        queueFront(queue, &front);
        int size;
        queueSize(queue, &size);
        printf("-> %c at front of queue (size = %d).\n", front, size);
    }

    queuePrint(queue);

    while(!queueIsEmpty(queue)) {
        char front;
        queueDequeue(queue, &front);
        int size;
        queueSize(queue, &size);
        printf("Dequeued %c from queue -> (resulting size = %d).\n", front, size);
    }

    queuePrint(queue);
}

void testStress(PtQueue queue) {
    printf("\nStress testing with %d elements... \n", STRESS_TEST_SIZE);

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    /* Do the work. */
    for(int i=0; i<STRESS_TEST_SIZE; i++) {
        int error_code = queueEnqueue(queue, 'a');
        if(error_code != QUEUE_OK) {
            printf("Stopping because an error ocurred... Code: %d \n", error_code);
            break;
        }
    }

    while(!queueIsEmpty(queue)) {
        char front;
        queueDequeue(queue, &front);       
    }

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("-- Time taken: %lf seconds \n", cpu_time_used);
}