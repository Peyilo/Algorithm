//
// Created by 35433 on 2022/7/22.
// 循环队列的实现
//

#include "CircularQueue.h"
#include <stdio.h>

// 循环队列的初始化
bool initCircularQueue(CircularQueue *pQueue)
{
    pQueue->base = (ElemType*)malloc(MAXLENGTH * sizeof(ElemType));
    if(!pQueue->base) return false;
    pQueue->front = pQueue->rear = 0;
    return true;
}

// 判断循环队列是否为空
bool circularQueueIsEmpty(CircularQueue queue)
{
    return queue.rear == queue.front;
}

// 获取循环队列的长度
int queueOfLength(CircularQueue queue)
{
    return (queue.rear - queue.front + MAXLENGTH) % MAXLENGTH;
}

// 入队
bool enQueue(CircularQueue *pQueue, ElemType elem)
{
    /* 当rear指针在front的后一位时代表队列已满，即有一个位置是空的，不放元素，用来标记队列已满 */
    if((pQueue->rear + 1) % MAXLENGTH == pQueue->front) return false;
    pQueue->base[pQueue->rear] = elem;
    pQueue->rear = (pQueue->rear + 1) % MAXLENGTH;
    return true;
}

// 出队
ElemType deQueue(CircularQueue *pQueue)
{
    if(circularQueueIsEmpty(*pQueue))
    {
        printf("The circular queue is full!\n");
        exit(-1);
    }
    ElemType temp = pQueue->base[pQueue->front];
    pQueue->front = (pQueue->front + 1) % MAXLENGTH;
    return temp;
}

// 释放内存
void destroyCircularQueue(CircularQueue *pQueue)
{
    free(pQueue->base);
}

// 清空队列
void clearCircularQueue(CircularQueue *pQueue)
{
    pQueue->front = pQueue->rear = 0;
}