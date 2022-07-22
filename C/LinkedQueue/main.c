#include <stdio.h>
#include "LinkedQueue.h"

int main() {
    LinkedQueue queue, *pQueue = &queue;
    initQueue(pQueue);
    for(int i = 0; i < 100; i++)
    {
        enQueue(pQueue, "Anvei");
    }
    printf("The length of queue: %d\n", queueOfLength(queue));
    int count = 0;
    while(!queueIsEmpty(queue))
    {
        printf("No.%d: %s\n", ++count, getHead(queue));
        deQueue(pQueue);
    }
    clearQueue(pQueue);
    destroyQueue(pQueue);
    return 0;
}
