//
// Created by 35433 on 2022/7/19.
//

#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef double ElemType;
typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node, *LinkedList; // 可以定义多个别名

bool initList(LinkedList *pList);

int getLength(LinkedList list);

ElemType getElem(LinkedList list, int index);

bool listInsert(LinkedList list, int index, ElemType elem);

ElemType listDelete(LinkedList list, int index);

void mergeList(LinkedList list1, LinkedList list2);

void destroyList(LinkedList list);

#endif //LINKEDLIST_LINKEDLIST_H
