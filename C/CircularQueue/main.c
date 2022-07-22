#include <stdio.h>
#include "CircularQueue.h"

void test1();

int main() {
    //test1();
    return 0;
}

void test1()
{
    CircularQueue queue, *pQueue = &queue;
    initCircularQueue(pQueue);
    for(int i = 0; i < 80; i++)
    {
        enQueue(pQueue, "Anvei");
    }
    printf("The length of queue: %d\n", queueOfLength(queue));
    int count = 0;
    for(int i = 0; i < 50; i++)
    {
        printf("No.%d: %s\n", ++count, deQueue(pQueue));
    }
    clearCircularQueue(pQueue);
    destroyCircularQueue(pQueue);
}