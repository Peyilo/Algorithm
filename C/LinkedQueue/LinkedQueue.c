//
// Created by 35433 on 2022/7/22.
//

#include "LinkedQueue.h"
#include <stdlib.h>
#include <stdio.h>
// 初始化一个空链队列
bool initQueue(LinkedQueue *pQueue)
{
    pQueue->front = pQueue->rear = (QueuePtr)malloc(sizeof(QNode));
    if(!pQueue->front) return false;
    pQueue->front->next = NULL;
    return true;
}

// 释放一个链队列的内存
void destroyQueue(LinkedQueue *pQueue)
{
    int count = 0;
    while(pQueue->front)
    {
        QueuePtr pointer = (QueuePtr) pQueue->front->next;
        free(pQueue->front);
        pQueue->front = pointer;
        count++;
    }
    printf("count = %d\n", count);
}

// 清空一个链队列
bool clearQueue(LinkedQueue *pQueue)
{
    destroyQueue(pQueue);
    bool res= initQueue(pQueue);
    return res;
}

// 判断一个链队列是否为空
bool queueIsEmpty(LinkedQueue queue)
{
    return queue.front == queue.rear;
}

// 获取链队列的长度
int queueOfLength(LinkedQueue queue)
{
    int count = 0;
    QueuePtr pointer = queue.front;
    while(pointer)
    {
        count++;
        pointer = (QueuePtr) pointer->next;
    }
    return count - 1;
}

// 获取链队列的队首元素
ElemType getHead(LinkedQueue queue)
{
    return queue.front->data;
}

// 在链队列队尾插入一个元素
bool enQueue(LinkedQueue *pQueue, ElemType elem)
{
    QueuePtr temp = (QueuePtr) malloc(sizeof(QNode));
    if(!temp) return false;
    temp->next = NULL;
    pQueue->rear->data = elem;
    pQueue->rear->next = (struct QNode *) temp;
    pQueue->rear = temp;
    return true;
}

// 出队
ElemType deQueue(LinkedQueue *pQueue)
{
    if(pQueue->front == pQueue->rear) exit(-1);
    ElemType temp = pQueue->front->data;
    QueuePtr tempPtr = (QueuePtr) pQueue->front->next;
    free(pQueue->front);
    pQueue->front = tempPtr;
    return temp;
}

void queueTraverse(LinkedQueue *pQueue, void (*visit)(ElemType))
{
    QueuePtr pointer = pQueue->front;
    while(pointer != pQueue->rear)
    {
        visit(pointer->data);
        pointer = (QueuePtr) pointer->next;
    }
}