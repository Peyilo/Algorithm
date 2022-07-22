//
// Created by 35433 on 2022/7/22.
//

#ifndef CIRCULARQUEUE_CIRCULARQUEUE_H
#define CIRCULARQUEUE_CIRCULARQUEUE_H
#include <stdbool.h>
#include <stdlib.h>
#define MAXLENGTH 100
typedef char* ElemType;

typedef struct {
    ElemType *base;
    int front;
    int rear;
}CircularQueue;

bool initCircularQueue(CircularQueue *pQueue);

bool circularQueueIsEmpty(CircularQueue queue);

int queueOfLength(CircularQueue queue);

bool enQueue(CircularQueue *pQueue, ElemType elem);

ElemType deQueue(CircularQueue *pQueue);

void destroyCircularQueue(CircularQueue *pQueue);

void clearCircularQueue(CircularQueue *pQueue);

#endif //CIRCULARQUEUE_CIRCULARQUEUE_H
