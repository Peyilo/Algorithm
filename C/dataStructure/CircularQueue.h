//
// Created by Anvei on 2022/10/9.
//
// 循环队列的实现：选进先出，只能从对头移除元素、从队尾加入元素
// 为了避免内存浪费，采用循环结构

#ifndef ALGORITHM_CIRCULARQUEUE_H
#define ALGORITHM_CIRCULARQUEUE_H
#ifdef __cplusplus
extern "C" {
#endif
#include "stdbool.h"

typedef char *cirqueue_ele;
typedef struct {
    cirqueue_ele *base;
    int front;          // 指向首元素
    int rear;           // 指向下一次入队插入的位置
    int size;
} CircularQueue;

bool cirqueue_init(CircularQueue *pqueue, int size);
void cirqueue_destory(CircularQueue queue);
int cirqueue_length(CircularQueue queue);
cirqueue_ele cirqueue_dequeue(CircularQueue *pqueue);
bool cirqueue_enqueue(CircularQueue *pqueue, cirqueue_ele ele);

#ifdef __cplusplus
}
#endif
#endif //ALGORITHM_CIRCULARQUEUE_H
