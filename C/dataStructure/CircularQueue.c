//
// Created by Anvei on 2022/10/9.
//

#include "CircularQueue.h"
#include <stdlib.h>

/**
 * 循环队列的初始化
 * @param pqueue
 * @param size
 * @return
 */
bool cirqueue_init(CircularQueue *pqueue, int size)
{
    cirqueue_ele *temp = malloc(sizeof(cirqueue_ele) * (size + 1));     // 多分配一个位置，用来标记队列已满
    if (!temp) return false;                                                  // 当rear指向front前一位即表示已满
    pqueue->base = temp;
    pqueue->size = size;
    pqueue->front =  0;
    pqueue->rear = 0;
    return true;
}

/**
 * 循环队列的释放内存
 * @param queue
 */
void cirqueue_destory(CircularQueue queue)
{
    free(queue.base);
}

/**
 * 获取队列的长度
 * @param queue
 * @return
 */
int cirqueue_length(CircularQueue queue)
{
    return (queue.rear - queue.front + queue.size + 1) % (queue.size + 1);
}

/**
 * 获取
 * @param queue
 * @return
 */
bool cirqueue_full(CircularQueue queue)
{
    return cirqueue_length(queue) == queue.size;
}

/**
 * 出队
 * @param pqueue
 * @return
 */
cirqueue_ele cirqueue_dequeue(CircularQueue *pqueue)
{
    if (pqueue->rear == pqueue->front)
        exit(-110829);
    cirqueue_ele res = *(pqueue->base + pqueue->front);
    pqueue->front = (pqueue->front + 1 + pqueue->size + 1) % (pqueue->size + 1);
    return res;
}

/**
 * 入队
 * @param pqueue
 * @param ele
 * @return
 */
bool cirqueue_enqueue(CircularQueue *pqueue, cirqueue_ele ele)
{
    if (cirqueue_full(*pqueue)) return false;
    *(pqueue->base + pqueue->rear) = ele;
    pqueue->rear = (pqueue->rear + 1 + pqueue->size + 1) % (pqueue->size + 1);
    return true;
}
