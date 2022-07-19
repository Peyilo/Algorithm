//
// Created by 35433 on 2022/7/19.
//

#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H

/* 状态代码Status */
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef double ElemType;
typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node, *LinkedList; // 可以定义多个别名

LinkedList initList();
int getLength(LinkedList list);
ElemType getElem(LinkedList list, int index);
Status listInsert(LinkedList list, int index, ElemType elem);
Status listDelete(LinkedList list, int index, ElemType *pElem);
void mergeList(LinkedList list1, LinkedList list2);
void destroyList(LinkedList list);

#endif //LINKEDLIST_LINKEDLIST_H
