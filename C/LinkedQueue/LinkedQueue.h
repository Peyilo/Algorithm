//
// Created by 35433 on 2022/7/22.
//

#ifndef QUEUE_LINKEDQUEUE_H
#define QUEUE_LINKEDQUEUE_H

#include <stdbool.h>

typedef char *ElemType;

typedef struct {
    ElemType data;
    struct QNode *next;
}QNode, *QueuePtr; // 定义多个别名

typedef struct {
    QueuePtr front; // 队头指针
    QueuePtr rear; // 队尾指针
}LinkedQueue;

bool initQueue(LinkedQueue *pQueue);

void destroyQueue(LinkedQueue *pQueue);

bool clearQueue(LinkedQueue *pQueue);

bool queueIsEmpty(LinkedQueue queue);

int queueOfLength(LinkedQueue queue);

ElemType getHead(LinkedQueue queue);

bool enQueue(LinkedQueue *pQueue, ElemType elem);

ElemType deQueue(LinkedQueue *pQueue);

void queueTraverse(LinkedQueue *pQueue, void (*visit)(ElemType));

#endif //QUEUE_LINKEDQUEUE_H
